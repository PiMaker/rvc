#ifndef MEM_H
#define MEM_H

#include <assert.h>
#include "types.h"

// little endian, zero extended
uint mem_get_byte(cpu_t *cpu, uint addr) {
    /* printf("TRACE: mem_get_byte(%d)\n", addr); */
    assert(addr & 0x80000000);
    return cpu->mem[addr & 0x7FFFFFFF];
}

uint mem_get_half_word(cpu_t *cpu, uint addr) {
    return mem_get_byte(cpu, addr) | ((uint16_t)mem_get_byte(cpu, addr + 1) << 8);
}

uint mem_get_word(cpu_t *cpu, uint addr) {
    return mem_get_byte(cpu, addr) |
        ((uint16_t)mem_get_byte(cpu, addr + 1) << 8) |
        ((uint16_t)mem_get_byte(cpu, addr + 2) << 16) |
        ((uint16_t)mem_get_byte(cpu, addr + 3) << 24);
}

void mem_set_byte(cpu_t *cpu, uint addr, uint val) {
    assert(addr & 0x80000000);
    cpu->mem[addr & 0x7FFFFFFF] = val;
}

void mem_set_half_word(cpu_t *cpu, uint addr, uint val) {
    mem_set_byte(cpu, addr, val & 0xFF);
    mem_set_byte(cpu, addr + 1, (val >> 8) & 0xFF);
}

void mem_set_word(cpu_t *cpu, uint addr, uint val) {
    mem_set_byte(cpu, addr, val & 0xFF);
    mem_set_byte(cpu, addr + 1, (val >> 8) & 0xFF);
    mem_set_byte(cpu, addr + 2, (val >> 16) & 0xFF);
    mem_set_byte(cpu, addr + 3, val >> 24);
}

#endif
