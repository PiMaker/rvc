#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <string.h>

typedef uint32_t uint;
typedef uint32_t uint;

typedef struct {
    uint32_t clock;
    uint32_t xreg[32];
    uint32_t pc;
    uint8_t *mem;
} cpu_t;

typedef struct {
    uint write_reg;
    uint write_val;
    uint pc_write;
    uint pc_val;
    uint csr_write;
    uint csr_val;
} ins_ret;

ins_ret ins_ret_noop() {
    ins_ret ret;
    memset(&ret, 0, sizeof(ins_ret));
    return ret;
}

uint sign_extend(uint x, uint b) {
    uint m = 1U << (b - 1);
    return (x ^ m) - m;
}

#endif
