#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include "types.h"
#include "mem.h"
#include "emu.h"
#include "mmu.h"

cpu_t cpu_init(uint8_t *mem, uint8_t *dtb, uint8_t *mtd, uint mtd_size) {
    cpu_t ret;
    ret.clock = 0;
    for (uint i = 0; i < 32; i++) {
        ret.xreg[i] = 0;
    }
    ret.xreg[0xb] = 0x1020; // linux? device tree?
    ret.pc = 0x80000000;
    ret.mem = mem;
    ret.reservation_en = false;

    init_csrs(&ret);

    ret.dtb = dtb;
    ret.mtd = mtd;
    ret.mtd_size = mtd_size;

    ret.net.netrx = malloc(4096);
    ret.net.nettx = malloc(4096);

    ret.clint.msip = false;
    ret.clint.mtimecmp_lo = 0;
    ret.clint.mtimecmp_hi = 0;
    ret.clint.mtime_lo = 0;
    ret.clint.mtime_hi = 0;

    ret.uart.rbr_thr_ier_iir = 0;
    ret.uart.lcr_mcr_lsr_scr = 0x00200000; // LSR_THR_EMPTY is set
    ret.uart.thre_ip = false;
    ret.uart.interrupting = false;

    ret.mmu.mode = 0;
    ret.mmu.ppn = 0;

    ret.start_time_ref = _Time;

    return ret;
}

static char *cmd_buf = NULL;

void cpu_dump(cpu_t *cpu) {
    printf("CPU state @%d:\n", cpu->clock);
    for (int i = 0; i < 32; i += 4) {
        printf("  .x%02d = %08x  .x%02d = %08x  .%02d = %08x  .%02d = %08x\n",
               i, cpu->xreg[i],
               i+1, cpu->xreg[i+1],
               i+2, cpu->xreg[i+2],
               i+3, cpu->xreg[i+3]);
    }
    printf("  .pc  = %08x\n", cpu->pc);
    /* ins_ret ret; */
    /* printf("  next ins: %08x\n", *(uint*)(cpu->mem + mmu_translate(&ret, cpu->pc & 0x7FFFFFFF, MMU_ACCESS_FETCH))); */

    /* if (cmd_buf == NULL) { */
    /*     cmd_buf = malloc(4096); */
    /* } */
    /* sprintf(cmd_buf, "addr2line -e testinit/init %x", cpu->pc); */
    /* system(cmd_buf); */

    uint arb[8];
    for (int iarb = 0; iarb < 8; iarb++) {
        uint arb_t = cpu->xreg[iarb*4+0] ^
                     cpu->xreg[iarb*4+1] ^
                     cpu->xreg[iarb*4+2] ^
                     cpu->xreg[iarb*4+3];
        printf("arb%d=0x%08x ", iarb, arb_t);
        if (iarb == 3) printf("\n");
        arb[iarb] = arb_t;
    }
    printf("\nARB=0x%08x\n", arb[0] ^ arb[1] ^ arb[2] ^ arb[3] ^ arb[4] ^ arb[5] ^ arb[6] ^ arb[7] ^ cpu->pc);

    printf("\n");
}

void cpu_tick(cpu_t *cpu) {
    cpu->clock++;
    emulate(cpu);
}

#endif
