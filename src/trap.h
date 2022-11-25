#ifndef TRAP_H
#define TRAP_H

#include <stdbool.h>
#include "types.h"

#define PRIV_USER 0
#define PRIV_SUPERVISOR 1
#define PRIV_MACHINE 3

static const uint interrupt_offset = 0x80000000;
const uint trap_InstructionAddressMisaligned = 0;
const uint trap_InstructionAccessFault = 1;
const uint trap_IllegalInstruction = 2;
const uint trap_Breakpoint = 3;
const uint trap_LoadAddressMisaligned = 4;
const uint trap_LoadAccessFault = 5;
const uint trap_StoreAddressMisaligned = 6;
const uint trap_StoreAccessFault = 7;
const uint trap_EnvironmentCallFromUMode = 8;
const uint trap_EnvironmentCallFromSMode = 9;
const uint trap_EnvironmentCallFromMMode = 11;
const uint trap_InstructionPageFault = 12;
const uint trap_LoadPageFault = 13;
const uint trap_StorePageFault = 15;
const uint trap_UserSoftwareInterrupt = interrupt_offset + 0;
const uint trap_SupervisorSoftwareInterrupt = interrupt_offset + 1;
const uint trap_MachineSoftwareInterrupt = interrupt_offset + 3;
const uint trap_UserTimerInterrupt = interrupt_offset + 4;
const uint trap_SupervisorTimerInterrupt = interrupt_offset + 5;
const uint trap_MachineTimerInterrupt = interrupt_offset + 7;
const uint trap_UserExternalInterrupt = interrupt_offset + 8;
const uint trap_SupervisorExternalInterrupt = interrupt_offset + 9;
const uint trap_MachineExternalInterrupt = interrupt_offset + 11;

const uint MIP_MEIP = 0x800;
const uint MIP_MTIP = 0x080;
const uint MIP_MSIP = 0x008;
const uint MIP_SEIP = 0x200;
const uint MIP_STIP = 0x020;
const uint MIP_SSIP = 0x002;
const uint MIP_ALL = MIP_MEIP | MIP_MTIP | MIP_MSIP | MIP_SEIP | MIP_STIP | MIP_SSIP;

// include after trap_ definitions
#include "csr.h"

// returns true if IRQ was handled or !is_interrupt
bool handle_trap(cpu_t *cpu, ins_ret *ret, trap t, bool is_interrupt) {
    uint current_privilege = cpu->csr.privilege;

    uint mdeleg = read_csr_raw(cpu, is_interrupt ? CSR_MIDELEG : CSR_MEDELEG);
    uint sdeleg = read_csr_raw(cpu, is_interrupt ? CSR_SIDELEG : CSR_SEDELEG);
    uint pos = t.type & 0xFFFF;

    uint new_privilege = ((mdeleg >> pos) & 1) == 0 ?
        PRIV_MACHINE : (((sdeleg >> pos) & 1) == 0 ?
            PRIV_SUPERVISOR : PRIV_USER);

    uint mstatus = read_csr_raw(cpu, CSR_MSTATUS);
    uint sstatus = read_csr_raw(cpu, CSR_SSTATUS);
    uint current_status = current_privilege == PRIV_MACHINE ?
         mstatus : (current_privilege == PRIV_SUPERVISOR ?
            sstatus : read_csr_raw(cpu, CSR_USTATUS));

    // check if IRQ should be ignored
    if (is_interrupt) {
        uint ie = new_privilege == PRIV_MACHINE ?
            read_csr_raw(cpu, CSR_MIE) : (new_privilege == PRIV_SUPERVISOR ?
                read_csr_raw(cpu, CSR_SIE) : read_csr_raw(cpu, CSR_UIE));

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
    cpu->csr.privilege = new_privilege;

    uint csr_epc_addr = new_privilege == PRIV_MACHINE ? CSR_MEPC : (new_privilege == PRIV_SUPERVISOR ? CSR_SEPC : CSR_UEPC);
    uint csr_cause_addr = new_privilege == PRIV_MACHINE ? CSR_MCAUSE : (new_privilege == PRIV_SUPERVISOR ? CSR_SCAUSE : CSR_UCAUSE);
    uint csr_tval_addr = new_privilege == PRIV_MACHINE ? CSR_MTVAL : (new_privilege == PRIV_SUPERVISOR ? CSR_STVAL : CSR_UTVAL);
    uint csr_tvec_addr = new_privilege == PRIV_MACHINE ? CSR_MTVEC : (new_privilege == PRIV_SUPERVISOR ? CSR_STVEC : CSR_UTVEC);

    write_csr_raw(cpu, csr_epc_addr, is_interrupt ? ret->pc_val : cpu->pc);
    write_csr_raw(cpu, csr_cause_addr, t.type);
    write_csr_raw(cpu, csr_tval_addr, t.value);
    ret->pc_val = read_csr_raw(cpu, csr_tvec_addr);

    if ((ret->pc_val & 0x3) != 0) {
        // vectored handler
        ret->pc_val = (ret->pc_val & ~0x3) + 4*pos;
    }

    // NOTE: No user mode interrupt/exception handling!
    // Importantly, this clears xIE in mstatus, so even if MIP isn't cleared,
    // the interrupt will not be immediately reentrant.
    if (new_privilege == PRIV_MACHINE) {
        uint mie = (mstatus >> 3) & 1;
        uint new_status = (mstatus & ~0x1888) | (mie << 7) | (current_privilege << 11);
        write_csr_raw(cpu, CSR_MSTATUS, new_status);
    } else { // PRIV_SUPERVISOR
        uint sie = (sstatus >> 1) & 1;
        uint new_status = (sstatus & ~0x122) | (sie << 5) | ((current_privilege & 1) << 8);
        write_csr_raw(cpu, CSR_SSTATUS, new_status);
    }

    if (VERBOSE >= (is_interrupt && t.type != trap_MachineTimerInterrupt && t.type != trap_SupervisorTimerInterrupt ? 1 : 2))
        printf("trap: type=%08x value=%08x (IRQ: %d) moved PC from @%08x (#%d) to @%08x (#%d)\n", t.type, t.value, is_interrupt, cpu->pc, current_privilege, ret->pc_val, new_privilege);

    return true;
}

void handle_irq_and_trap(cpu_t *cpu, ins_ret *ret) {
    trap t = ret->trap;
    uint mip_reset = MIP_ALL;
    uint cur_mip = read_csr_raw(cpu, CSR_MIP);
    bool irq = false;

    if (!t.en) {
        irq = true;
        uint mirq = cur_mip & read_csr_raw(cpu, CSR_MIE);
        if (false) {}
#define HANDLE(mip, ttype) else if (mirq & mip) { mip_reset = mip; t.en = true; t.type = ttype; }
        HANDLE(MIP_MEIP, trap_MachineExternalInterrupt)
        HANDLE(MIP_MSIP, trap_MachineSoftwareInterrupt)
        HANDLE(MIP_MTIP, trap_MachineTimerInterrupt)
        HANDLE(MIP_SEIP, trap_SupervisorExternalInterrupt)
        HANDLE(MIP_SSIP, trap_SupervisorSoftwareInterrupt)
        HANDLE(MIP_STIP, trap_SupervisorTimerInterrupt)
#undef HANDLE
    }

    if (t.en) {
        bool handled = handle_trap(cpu, ret, t, irq);
        if (handled && irq) {
            // reset MIP value if IRQ other than timer was handled
            // (MTIP/STIP will be reset by write to mtimecmp)
            if ((mip_reset & 0x0A0) == 0)
                write_csr_raw(cpu, CSR_MIP, cur_mip & ~mip_reset);
            if (VERBOSE >= 3)
                printf("IRQ handled: old_mip=%03x new_mip=%03x\n", cur_mip, read_csr_raw(cpu, CSR_MIP));
        }
    }
}

#endif
