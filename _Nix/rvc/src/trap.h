#ifndef TRAP_H
#define TRAP_H

#define PRIV_USER 0
#define PRIV_SUPERVISOR 1
#define PRIV_MACHINE 3

#define interrupt_offset 0x80000000
#define trap_InstructionAddressMisaligned 0
#define trap_InstructionAccessFault 1
#define trap_IllegalInstruction 2
#define trap_Breakpoint 3
#define trap_LoadAddressMisaligned 4
#define trap_LoadAccessFault 5
#define trap_StoreAddressMisaligned 6
#define trap_StoreAccessFault 7
#define trap_EnvironmentCallFromUMode 8
#define trap_EnvironmentCallFromSMode 9
#define trap_EnvironmentCallFromMMode 11
#define trap_InstructionPageFault 12
#define trap_LoadPageFault 13
#define trap_StorePageFault 15
#define trap_UserSoftwareInterrupt interrupt_offset + 0
#define trap_SupervisorSoftwareInterrupt interrupt_offset + 1
#define trap_MachineSoftwareInterrupt interrupt_offset + 3
#define trap_UserTimerInterrupt interrupt_offset + 4
#define trap_SupervisorTimerInterrupt interrupt_offset + 5
#define trap_MachineTimerInterrupt interrupt_offset + 7
#define trap_UserExternalInterrupt interrupt_offset + 8
#define trap_SupervisorExternalInterrupt interrupt_offset + 9
#define trap_MachineExternalInterrupt interrupt_offset + 11

#define MIP_MEIP 0x800
#define MIP_MTIP 0x080
#define MIP_MSIP 0x008
#define MIP_SEIP 0x200
#define MIP_STIP 0x020
#define MIP_SSIP 0x002
#define MIP_ALL 0xAAA // MIP_MEIP | MIP_MTIP | MIP_MSIP | MIP_SEIP | MIP_STIP | MIP_SSIP

// include after trap_ definitions
#include "csr.h"

// returns true if IRQ was handled or !is_interrupt
bool handle_trap(inout ins_ret ret, bool is_interrupt, uint c_mie) {
    trap t = ret.trap;
    uint current_privilege = cpu.csr.privilege;

    uint mdeleg = read_csr_raw(is_interrupt ? CSR_MIDELEG : CSR_MEDELEG);
    uint sdeleg = read_csr_raw(is_interrupt ? CSR_SIDELEG : CSR_SEDELEG);
    uint pos = t.type & 0xFFFF;

    uint new_privilege = ((mdeleg >> pos) & 1) == 0 ?
        PRIV_MACHINE : (((sdeleg >> pos) & 1) == 0 ?
            PRIV_SUPERVISOR : PRIV_USER);

    uint mstatus = read_csr_raw(CSR_MSTATUS);
    uint sstatus = read_csr_raw(CSR_SSTATUS);
    uint current_status = current_privilege == PRIV_MACHINE ?
         mstatus : (current_privilege == PRIV_SUPERVISOR ?
            sstatus : read_csr_raw(CSR_USTATUS));

    // check if IRQ should be ignored
    if (is_interrupt) {
        uint ie = new_privilege == PRIV_MACHINE ?
            c_mie : (new_privilege == PRIV_SUPERVISOR ?
                read_csr_raw(CSR_SIE) : read_csr_raw(CSR_UIE));

        uint current_mie = (current_status >> 3) & 1;
        uint current_sie = (current_status >> 1) & 1;
        uint current_uie = current_status & 1;

        uint msie = (ie >> 3) & 1;
        uint ssie = (ie >> 1) & 1;
        uint usie = ie & 1;

        uint mtie = (ie >> 7) & 1;
        uint stie = (ie >> 5) & 1;
        uint utie = (ie >> 4) & 1;

        uint meie = (ie >> 11) & 1;
        uint seie = (ie >> 9) & 1;
        uint ueie = (ie >> 8) & 1;

        if (new_privilege < current_privilege) {
            return false;
        } else if (new_privilege == current_privilege) {
            if (current_privilege == PRIV_MACHINE && current_mie == 0) {
                return false;
            } else if (current_privilege == PRIV_SUPERVISOR && current_sie == 0) {
                return false;
            } else if (current_privilege == PRIV_USER && current_uie == 0) {
                return false;
            }
        }

#define MASK(trap, val) case trap: if (val == 0) { return false; } else { break; }
        switch (t.type) {
            MASK(trap_UserSoftwareInterrupt, usie)
            MASK(trap_SupervisorSoftwareInterrupt, ssie)
            MASK(trap_MachineSoftwareInterrupt, msie)
            MASK(trap_UserTimerInterrupt, utie)
            MASK(trap_SupervisorTimerInterrupt, stie)
            MASK(trap_MachineTimerInterrupt, mtie)
            MASK(trap_UserExternalInterrupt, ueie)
            MASK(trap_SupervisorExternalInterrupt, seie)
            MASK(trap_MachineExternalInterrupt, meie)
        }
#undef MASK
    }

    // should be handled, do that now
    cpu.csr.privilege = new_privilege;

    uint csr_epc_addr = new_privilege == PRIV_MACHINE ? CSR_MEPC : (new_privilege == PRIV_SUPERVISOR ? CSR_SEPC : CSR_UEPC);
    uint csr_cause_addr = new_privilege == PRIV_MACHINE ? CSR_MCAUSE : (new_privilege == PRIV_SUPERVISOR ? CSR_SCAUSE : CSR_UCAUSE);
    uint csr_tval_addr = new_privilege == PRIV_MACHINE ? CSR_MTVAL : (new_privilege == PRIV_SUPERVISOR ? CSR_STVAL : CSR_UTVAL);
    uint csr_tvec_addr = new_privilege == PRIV_MACHINE ? CSR_MTVEC : (new_privilege == PRIV_SUPERVISOR ? CSR_STVEC : CSR_UTVEC);

    write_csr_raw(csr_epc_addr, is_interrupt ? ret.pc_val : cpu.pc);
    write_csr_raw(csr_cause_addr, t.type);
    write_csr_raw(csr_tval_addr, t.value);
    ret.pc_val = read_csr_raw(csr_tvec_addr);

    if ((ret.pc_val & 0x3) != 0) {
        // vectored handler
        ret.pc_val = (ret.pc_val & ~0x3) + 4*pos;
    }

    // NOTE: No user mode interrupt/exception handling!
    if (new_privilege == PRIV_MACHINE) {
        uint mie = (mstatus >> 3) & 1;
        uint new_status = (mstatus & ~0x1888) | (mie << 7) | (current_privilege << 11);
        write_csr_raw(CSR_MSTATUS, new_status);
    } else { // PRIV_SUPERVISOR
        uint sie = (sstatus >> 1) & 1;
        uint new_status = (sstatus & ~0x122) | (sie << 5) | ((current_privilege & 1) << 8);
        write_csr_raw(CSR_SSTATUS, new_status);
    }

    return true;
}

void handle_irq_and_trap(inout ins_ret ret, uint mip_override) {
    bool trap = ret.trap.en;
    uint mip_reset = MIP_ALL;
    uint mie = read_csr_raw(CSR_MIE);

    if (!trap) {
        uint mirq = mip_override & mie;
#define HANDLE(mip, ttype) case mip: mip_reset = mip; ret.trap.en = true; ret.trap.type = ttype; break;
        switch (mirq & MIP_ALL) {
            HANDLE(MIP_MEIP, trap_MachineExternalInterrupt)
            HANDLE(MIP_MSIP, trap_MachineSoftwareInterrupt)
            HANDLE(MIP_MTIP, trap_MachineTimerInterrupt)
            HANDLE(MIP_SEIP, trap_SupervisorExternalInterrupt)
            HANDLE(MIP_SSIP, trap_SupervisorSoftwareInterrupt)
            HANDLE(MIP_STIP, trap_SupervisorTimerInterrupt)
        }
#undef HANDLE
    }

    bool irq = mip_reset != MIP_ALL;
    if (trap || irq) {
        uint new_mip = mip_override;
        bool handled = handle_trap(ret, irq, mie);
        if (handled) {
            cpu.trap_count++;
        }
        if (handled && irq) {
            // reset MIP value since IRQ was handled
            // this implies that mip_reset is not MIP_ALL
            new_mip = mip_override & (~mip_reset);
        }
        write_csr_raw(CSR_MIP, new_mip);
    }
}

#endif
