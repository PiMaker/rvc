#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

static int VERBOSE = 0;
static bool SINGLE_STEP = false;

typedef uint32_t uint;
typedef uint32_t uint;

typedef struct {
    uint data[4096];
    uint privilege;
} csr_state;

typedef struct {
    uint rbr_thr_ier_iir;
    uint lcr_mcr_lsr_scr;
    bool thre_ip;
    bool interrupting;
} uart_state;

typedef struct {
    bool msip;
    uint mtimecmp_lo;
    uint mtimecmp_hi;
    uint mtime_lo;
    uint mtime_hi;
} clint_state;

typedef struct {
    uint mode;
    uint ppn;
} mmu_state;

typedef struct {
    uint clock;
    uint xreg[32];
    uint pc;
    uint8_t *mem;
    uint8_t *dtb;
    uint8_t *mtd;
    uint mtd_size;
    csr_state csr;
    clint_state clint;
    uart_state uart;
    mmu_state mmu;

    bool reservation_en;
    uint reservation_addr;
} cpu_t;

typedef struct {
    bool en;
    bool irq;
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

static cpu_t cpu;

#endif
