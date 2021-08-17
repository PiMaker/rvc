#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <assert.h>
#include "types.h"
#include "uart.h"

const int MEM_SIZE = 1024 * 1024 * 64 - 2048 * 128;

// little endian, zero extended
uint do_mem_get_byte(cpu_t *cpu, uint addr) {

    if (cpu->dtb != NULL && addr >= 0x1020 && addr <= 0x1fff) {
        if (VERBOSE >= 2)
            printf("DTB read @%04x/%04x\n", addr, addr - 0x1020);
        return cpu->dtb[addr - 0x1020];
    }

    /* if (cpu->mtd != NULL && addr >= 0x40000000 && addr < (0x40000000 + MEM_SIZE)) { */
    /*     return cpu->mtd[addr - 0x40000000]; */
    /* } */

    switch (addr) {
        // CLINT
        case 0x02000000: return cpu->clint.msip ? 1 : 0;
        case 0x02000001: return 0;
        case 0x02000002: return 0;
        case 0x02000003: return 0;

        case 0x02004000: return (cpu->clint.mtimecmp_lo >> 0) & 0xFF;
        case 0x02004001: return (cpu->clint.mtimecmp_lo >> 8) & 0xFF;
        case 0x02004002: return (cpu->clint.mtimecmp_lo >> 16) & 0xFF;
        case 0x02004003: return (cpu->clint.mtimecmp_lo >> 24) & 0xFF;
        case 0x02004004: return (cpu->clint.mtimecmp_hi >> 0) & 0xFF;
        case 0x02004005: return (cpu->clint.mtimecmp_hi >> 8) & 0xFF;
        case 0x02004006: return (cpu->clint.mtimecmp_hi >> 16) & 0xFF;
        case 0x02004007: return (cpu->clint.mtimecmp_hi >> 24) & 0xFF;

        case 0x0200bff8: return (cpu->clint.mtime_lo >> 0) & 0xFF;
        case 0x0200bff9: return (cpu->clint.mtime_lo >> 8) & 0xFF;
        case 0x0200bffa: return (cpu->clint.mtime_lo >> 16) & 0xFF;
        case 0x0200bffb: return (cpu->clint.mtime_lo >> 24) & 0xFF;
        case 0x0200bffc: return (cpu->clint.mtime_hi >> 0) & 0xFF;
        case 0x0200bffd: return (cpu->clint.mtime_hi >> 8) & 0xFF;
        case 0x0200bffe: return (cpu->clint.mtime_hi >> 16) & 0xFF;
        case 0x0200bfff: return (cpu->clint.mtime_hi >> 24) & 0xFF;

        // UART (first has rbr_thr_ier_iir, second has lcr_mcr_lsr_scr)
        case 0x10000000:
            if ((UART_GET2(LCR) >> 7) == 0) {
                uint rbr = UART_GET1(RBR);
                UART_SET1(RBR, 0);
                UART_SET2(LSR, (UART_GET2(LSR) & ~LSR_DATA_AVAILABLE));
                uart_update_iir(cpu);
                return rbr;
            } else {
                return 0;
            }
        case 0x10000001: return UART_GET2(LCR) >> 7 == 0 ? UART_GET1(IER) : 0;
        case 0x10000002: return UART_GET1(IIR);
        case 0x10000003: return UART_GET2(LCR);
        case 0x10000004: return UART_GET2(MCR);
        case 0x10000005: return UART_GET2(LSR);
        case 0x10000007: return UART_GET2(SCR);

        /* case 0x80001000: return 0; */
        /* case 0x80001001: return 0; */
        /* case 0x80001002: return 0; */
        /* case 0x80001003: return 0; */
        /* case 0x80001004: return 0; */
        /* case 0x80001005: return 0; */
        /* case 0x80001006: return 0; */
        /* case 0x80001007: return 0; */
        /* case 0x80001040: return 0; */
        /* case 0x80001041: return 0; */
        /* case 0x80001042: return 0; */
        /* case 0x80001043: return 0; */
        /* case 0x80001044: return 0; */
        /* case 0x80001045: return 0; */
        /* case 0x80001046: return 0; */
        /* case 0x80001047: return 0; */
    }

    if ((addr & 0x80000000) == 0) {
        return 0;
    }

    addr = addr & 0x7FFFFFFF;
    if (addr >= MEM_SIZE) {
        if (VERBOSE >= 1) {
            printf("WARN: out-of-bounds memory read @0x%08x\n", addr | 0x80000000);
        }
        return 0;
    }

    return cpu->mem[addr];
}

uint mem_get_byte(cpu_t *cpu, uint addr) {
    uint ret = do_mem_get_byte(cpu, addr);
    if (VERBOSE >= 3)
        printf("mem_get_byte(%08x) = 0x%08x\n", addr, ret);
    return ret;
}

uint mem_get_half_word(cpu_t *cpu, uint addr) {
    /* assert((addr & ~(0x1)) == addr); */
    return mem_get_byte(cpu, addr) | ((uint16_t)mem_get_byte(cpu, addr + 1) << 8);
}

uint mem_get_word(cpu_t *cpu, uint addr) {
    /* assert((addr & ~(0x3)) == addr); */
    return mem_get_byte(cpu, addr) |
        ((uint16_t)mem_get_byte(cpu, addr + 1) << 8) |
        ((uint16_t)mem_get_byte(cpu, addr + 2) << 16) |
        ((uint16_t)mem_get_byte(cpu, addr + 3) << 24);
}

void mem_set_byte(cpu_t *cpu, uint addr, uint val) {
    if (VERBOSE >= 3)
        printf("mem_set_byte(%08x, %08x)\n", addr, val);

    switch (addr) {
        // CLINT
        case 0x02000000: cpu->clint.msip = (val & 1) != 0; return;
        case 0x02000001: return;
        case 0x02000002: return;
        case 0x02000003: return;

        case 0x02004000: cpu->clint.mtimecmp_lo = (cpu->clint.mtimecmp_lo & ~(0xff << 0)) | (val << 0); return;
        case 0x02004001: cpu->clint.mtimecmp_lo = (cpu->clint.mtimecmp_lo & ~(0xff << 8)) | (val << 8); return;
        case 0x02004002: cpu->clint.mtimecmp_lo = (cpu->clint.mtimecmp_lo & ~(0xff << 16)) | (val << 16); return;
        case 0x02004003: cpu->clint.mtimecmp_lo = (cpu->clint.mtimecmp_lo & ~(0xff << 24)) | (val << 24); return;
        case 0x02004004: cpu->clint.mtimecmp_hi = (cpu->clint.mtimecmp_hi & ~(0xff << 0)) | (val << 0); return;
        case 0x02004005: cpu->clint.mtimecmp_hi = (cpu->clint.mtimecmp_hi & ~(0xff << 8)) | (val << 8); return;
        case 0x02004006: cpu->clint.mtimecmp_hi = (cpu->clint.mtimecmp_hi & ~(0xff << 16)) | (val << 16); return;
        case 0x02004007: cpu->clint.mtimecmp_hi = (cpu->clint.mtimecmp_hi & ~(0xff << 24)) | (val << 24); return;

        case 0x0200bff8: cpu->clint.mtime_lo = (cpu->clint.mtime_lo & ~(0xff << 0)) | (val << 0); return;
        case 0x0200bff9: cpu->clint.mtime_lo = (cpu->clint.mtime_lo & ~(0xff << 8)) | (val << 8); return;
        case 0x0200bffa: cpu->clint.mtime_lo = (cpu->clint.mtime_lo & ~(0xff << 16)) | (val << 16); return;
        case 0x0200bffb: cpu->clint.mtime_lo = (cpu->clint.mtime_lo & ~(0xff << 24)) | (val << 24); return;
        case 0x0200bffc: cpu->clint.mtime_hi = (cpu->clint.mtime_hi & ~(0xff << 0)) | (val << 0); return;
        case 0x0200bffd: cpu->clint.mtime_hi = (cpu->clint.mtime_hi & ~(0xff << 8)) | (val << 8); return;
        case 0x0200bffe: cpu->clint.mtime_hi = (cpu->clint.mtime_hi & ~(0xff << 16)) | (val << 16); return;
        case 0x0200bfff: cpu->clint.mtime_hi = (cpu->clint.mtime_hi & ~(0xff << 24)) | (val << 24); return;

        // UART (first has rbr_thr_ier_iir, second has lcr_mcr_lsr_scr)
        case 0x10000000:
            if ((UART_GET2(LCR) >> 7) == 0) {
                UART_SET1(THR, val);
                UART_SET2(LSR, (UART_GET2(LSR) & ~LSR_THR_EMPTY));
                uart_update_iir(cpu);
            }
            return;
        case 0x10000001:
            if (UART_GET2(LCR) >> 7 == 0) {
                if ((UART_GET1(IER) & IER_THREINT_BIT) == 0 &&
                    (val & IER_THREINT_BIT) != 0 &&
                    UART_GET1(THR) == 0)
                {
                    cpu->uart.thre_ip = true;
                }
                UART_SET1(IER, val);
                uart_update_iir(cpu);
            }
            return;
        case 0x10000003: UART_SET2(LCR, val); return;
        case 0x10000004: UART_SET2(MCR, val); return;
        case 0x10000007: UART_SET2(SCR, val); return;

        /* case 0x80001000: printf("%c", (unsigned char)val); return; */
        /* case 0x80001001: return; */
        /* case 0x80001002: return; */
        /* case 0x80001003: return; */
        /* case 0x80001004: return; */
        /* case 0x80001005: return; */
        /* case 0x80001006: return; */
        /* case 0x80001007: return; */
        /* case 0x80001040: return; */
        /* case 0x80001041: return; */
        /* case 0x80001042: return; */
        /* case 0x80001043: return; */
        /* case 0x80001044: return; */
        /* case 0x80001045: return; */
        /* case 0x80001046: return; */
        /* case 0x80001047: return; */
    }

    if ((addr & 0x80000000) == 0) {
        return;
    }

    const int MEM_SIZE = 1024 * 1024 * 128;

    addr = addr & 0x7FFFFFFF;
    if (addr >= MEM_SIZE) {
        if (VERBOSE >= 1) {
            printf("WARN: out-of-bounds memory write @0x%08x\n", addr | 0x80000000);
        }
        return;
    }
    cpu->mem[addr] = val;
}

void mem_set_half_word(cpu_t *cpu, uint addr, uint val) {
    /* assert((addr & ~(0x1)) == addr); */
    mem_set_byte(cpu, addr, val & 0xFF);
    mem_set_byte(cpu, addr + 1, (val >> 8) & 0xFF);
}

void mem_set_word(cpu_t *cpu, uint addr, uint val) {
    /* assert((addr & ~(0x3)) == addr); */
    mem_set_byte(cpu, addr, val & 0xFF);
    mem_set_byte(cpu, addr + 1, (val >> 8) & 0xFF);
    mem_set_byte(cpu, addr + 2, (val >> 16) & 0xFF);
    mem_set_byte(cpu, addr + 3, val >> 24);
}

#endif
