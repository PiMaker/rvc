#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdint.h>
#include "types.h"
#include "mem.h"
#include "emu.h"

cpu_t cpu_init(uint8_t *mem) {
    cpu_t ret;
    ret.clock = 0;
    for (unsigned char i = 0; i < 32; i++) {
        ret.xreg[i] = 0;
    }
    ret.pc = 0x80000000;
    ret.mem = mem;
    return ret;
}

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
    printf("  next ins: %08x\n", *(uint*)(cpu->mem + (cpu->pc & 0x7FFFFFFF)));
}

void cpu_tick(cpu_t *cpu) {
    cpu->clock++;

    uint ins_raw = mem_get_word(cpu, cpu->pc);
    emulate(cpu, ins_raw);
}

#endif
