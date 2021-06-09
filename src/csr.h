#ifndef CSR_H
#define CSR_H

#include <stdbool.h>
#include <stdio.h>
#include "types.h"
#include "trap.h"

const uint CSR_USTATUS = 0x000;
const uint CSR_UIE = 0x004;
const uint CSR_UTVEC = 0x005;
const uint _CSR_USCRATCH = 0x040;
const uint CSR_UEPC = 0x041;
const uint CSR_UCAUSE = 0x042;
const uint CSR_UTVAL = 0x043;
const uint _CSR_UIP = 0x044;
const uint CSR_SSTATUS = 0x100;
const uint CSR_SEDELEG = 0x102;
const uint CSR_SIDELEG = 0x103;
const uint CSR_SIE = 0x104;
const uint CSR_STVEC = 0x105;
const uint _CSR_SSCRATCH = 0x140;
const uint CSR_SEPC = 0x141;
const uint CSR_SCAUSE = 0x142;
const uint CSR_STVAL = 0x143;
const uint CSR_SIP = 0x144;
const uint CSR_SATP = 0x180;
const uint CSR_MSTATUS = 0x300;
const uint CSR_MISA = 0x301;
const uint CSR_MEDELEG = 0x302;
const uint CSR_MIDELEG = 0x303;
const uint CSR_MIE = 0x304;
const uint CSR_MTVEC = 0x305;
const uint _CSR_MSCRATCH = 0x340;
const uint CSR_MEPC = 0x341;
const uint CSR_MCAUSE = 0x342;
const uint CSR_MTVAL = 0x343;
const uint CSR_MIP = 0x344;
const uint _CSR_PMPCFG0 = 0x3a0;
const uint _CSR_PMPADDR0 = 0x3b0;
const uint CSR_MCYCLE = 0xb00;
const uint CSR_CYCLE = 0xc00;
const uint CSR_TIME = 0xc01;
const uint _CSR_INSERT = 0xc02;
const uint CSR_MHARTID = 0xf14;

bool has_csr_access_privilege(cpu_t *cpu, uint addr) {
    uint privilege = (addr >> 8) & 0x3;
    return privilege <= cpu->csr.privilege;
}

// SSTATUS, SIE, and SIP are subsets of MSTATUS, MIE, and MIP
uint read_csr_raw(cpu_t *cpu, uint address) {
    switch (address) {
        case CSR_SSTATUS: return cpu->csr.data[CSR_MSTATUS] & 0x000de162;
        case CSR_SIE: return cpu->csr.data[CSR_MIE] & 0x222;
        case CSR_SIP: return cpu->csr.data[CSR_MIP] & 0x222;
        case CSR_TIME: return cpu->clint.mtime_lo;
        case CSR_MCYCLE: return cpu->clock;
        case CSR_CYCLE: return cpu->clock;
        case CSR_MHARTID: return 0;
        default: return cpu->csr.data[address & 0xffff];
    }
}

void write_csr_raw(cpu_t *cpu, uint address, uint value) {
    switch (address) {
        case CSR_SSTATUS:
            cpu->csr.data[CSR_MSTATUS] &= !0x000de162;
            cpu->csr.data[CSR_MSTATUS] |= value & 0x000de162;
            /* self.mmu.update_mstatus(self.read_csr_raw(CSR_MSTATUS)); */
            break;
        case CSR_SIE:
            cpu->csr.data[CSR_MIE] &= !0x222;
            cpu->csr.data[CSR_MIE] |= value & 0x222;
            break;
        case CSR_SIP:
            cpu->csr.data[CSR_MIP] &= !0x222;
            cpu->csr.data[CSR_MIP] |= value & 0x222;
            break;
        case CSR_MIDELEG:
            cpu->csr.data[address] = value & 0x666; // from qemu
            break;
        /* case CSR_MSTATUS: */
        /*     cpu->csr.data[address] = value; */
        /*     self.mmu.update_mstatus(self.read_csr_raw(CSR_MSTATUS)); */
        /*     break; */
        /* CSR_TIME => { */
        /*     self.mmu.get_mut_clint().write_mtime(value); */
        /* }, */
        case CSR_TIME:
            // ignore writes
            break;
        default: cpu->csr.data[address] = value; break;
    };
}


uint get_csr(cpu_t *cpu, uint address, ins_ret *ret) {
    if (has_csr_access_privilege(cpu, address)) {
        uint r = read_csr_raw(cpu, address);
        if (VERBOSE >= 2)
            printf("CSR read @%03x = %08x\n", address, r);
        return r;
    } else {
        ret->trap.en = true;
        ret->trap.type = trap_IllegalInstruction;
        ret->trap.value = cpu->pc;
        return 0;
    }
}

void set_csr(cpu_t *cpu, uint address, uint value, ins_ret *ret) {
    if (VERBOSE >= 2)
        printf("CSR write @%03x = %08x\n", address, value);
    if (has_csr_access_privilege(cpu, address)) {
        bool read_only = ((address >> 10) & 0x3) == 0x3;
        if (read_only) {
            ret->trap.en = true;
            ret->trap.type = trap_IllegalInstruction;
            ret->trap.value = cpu->pc;
        } else {
            if (address == CSR_SATP) {
                // TODO: update MMU addressing mode
                if (VERBOSE >= 1)
                    printf("WARN: Ignoring write to CSR_SATP (%08x)\n", value);
                return;
            }
            write_csr_raw(cpu, address, value);
        }
    } else {
        ret->trap.en = true;
        ret->trap.type = trap_IllegalInstruction;
        ret->trap.value = cpu->pc;
    }
}

void init_csrs(cpu_t *cpu) {
    cpu->csr.privilege = PRIV_MACHINE;
    for (uint i = 0; i < 4096; i++) {
        cpu->csr.data[i] = 0;
    }
    // RV32AIMSU
    cpu->csr.data[CSR_MISA] = 0b01000000000101000001000100000001;
}

#endif
