#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint32_t uint;
typedef uint32_t uint;

typedef struct {
    uint data[4096];
    uint privilege;
} csr_state;

typedef struct {
    uint clock;
    uint xreg[32];
    uint pc;
    uint8_t *mem;
    csr_state csr;

    bool reservation_en;
    uint reservation_addr;

    bool debug_single_step;
} cpu_t;

typedef struct {
    bool en;
    uint type;
    uint value;
} trap;

typedef struct {
    uint write_reg;
    uint write_val;
    uint pc_val;
    uint csr_write;
    uint csr_val;
    trap trap;
} ins_ret;

ins_ret ins_ret_noop(cpu_t *cpu) {
    ins_ret ret;
    memset(&ret, 0, sizeof(ins_ret));
    ret.pc_val = cpu->pc + 4;
    return ret;
}

uint sign_extend(uint x, uint b) {
    uint m = ((uint)1) << (b - 1);
    return (x ^ m) - m;
}

#endif
