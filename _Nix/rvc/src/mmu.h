#ifndef MMU_H
#define MMU_H

#include "types.h"

void mmu_update(uint satp) {
    cpu.mmu.mode = satp >> 31;
    cpu.mmu.ppn = satp & 0x7fffffff;
}

#include "mem.h"
#include "trap.h"

#define MMU_MODE_OFF 0
#define MMU_MODE_SV32 1

#define MMU_ACCESS_FETCH 0
#define MMU_ACCESS_READ 1
#define MMU_ACCESS_WRITE 2

#define PAGESIZE 4096
#define PTESIZE 4

#define ADDR_PART_OFFSET(x) ((x >> 0) & 0xfff)
#define ADDR_PART_PN0(x) ((x >> 12) & 0x3ff)
#define ADDR_PART_PN1(x) ((x >> 22) & 0xfff)

typedef struct {
    bool v, r, w, x, u, g, a, d;
    uint rsw;
    uint ppn0;
    uint ppn1;
} mmu_page;

uint get_trap_type(uint mode) {
    return mode == MMU_ACCESS_FETCH ? trap_InstructionPageFault :
        (mode == MMU_ACCESS_READ ? trap_LoadPageFault : trap_StorePageFault);
}

uint get_effective_privilege(out uint sum, out uint mxr) {
    uint mstatus = read_csr_raw(CSR_MSTATUS);
    sum = (mstatus >> 18) & 0x1;
    mxr = (mstatus >> 19) & 0x1;
    if ((mstatus >> 17) & 0x1) {
        // TODO: Check if this shouldn't be 9
        return (mstatus >> 11) & 0x3;
    }
    return cpu.csr.privilege;
}

mmu_page load_page(uint addr) {
    uint data = mem_get_cached_or_tex(addr & 0x7ffffffc);
    mmu_page ret;
    #define BOOL(name, bit) ret.name = (data >> bit) & 0x1;
    BOOL(v, 0)
    BOOL(r, 1)
    BOOL(w, 2)
    BOOL(x, 3)
    BOOL(u, 4)
    BOOL(g, 5)
    BOOL(a, 6)
    BOOL(d, 7)
    #undef BOOL
    ret.rsw = (data >> 8) & 0x3;
    ret.ppn0 = (data >> 10) & 0x3ff;
    ret.ppn1 = (data >> 20) & 0xfff;
    return ret;
}

uint mmu_translate(inout ins_ret ins, uint addr, uint mode) {
    if (cpu.mmu.mode == MMU_MODE_OFF) {
        return addr;
    }

    #define FAULT \
        ins.trap.en = true; \
        ins.trap.type = get_trap_type(mode); \
        ins.trap.value = addr; \
        return 0;

    uint sum, mxr;
    uint priv = get_effective_privilege(sum, mxr);

    // machine mode fetch will always use physical addresses, otherwise 'mxr'
    // defines if paging will be used
    if (priv == PRIV_MACHINE || (cpu.csr.privilege == PRIV_MACHINE && mode == MMU_ACCESS_FETCH)) {
        return addr;
    }

    bool super;
    mmu_page page;

    // perform two-layer page walk, exit early in case of super page
    [loop]
    for (uint im = 0; im < 2; im++) {
        uint page_addr = im == 0 ?
            (cpu.mmu.ppn * PAGESIZE + ADDR_PART_PN1(addr) * PTESIZE) :
            ((page.ppn0 | (page.ppn1 << 10)) * PAGESIZE + ADDR_PART_PN0(addr) * PTESIZE);
        page = load_page(page_addr);
        super = im == 0;

        if (!page.v || (!page.r && page.w)) {
            FAULT
        }

        if (page.r || page.x) {
            break;
        } else if (im == 1) {
            // non-leaf page at bottom level
            FAULT
        }
    }

    // PTE has been found, permission check
    bool perm =
        priv == PRIV_MACHINE || // machine can read everything
        (priv == PRIV_USER && page.u) || // this is a user page
        (priv == PRIV_SUPERVISOR && (!page.u || sum)); // supervisor page or SUM
    bool access =
        (mode == MMU_ACCESS_FETCH && page.x) ||
        (mode == MMU_ACCESS_READ && (page.r || (page.x && mxr))) ||
        (mode == MMU_ACCESS_WRITE && page.w);
    bool allowed = perm && access;

    if (!allowed) {
        /* access permission fault */
        FAULT
    }

    if (super && page.ppn0 != 0) {
        /* misaligned super page fault */
        FAULT
    }

    if (!page.a || (mode == MMU_ACCESS_WRITE && !page.d)) {
        /* access/dirty bit fault */
        FAULT
    }

    // translation success
    uint pa = ADDR_PART_OFFSET(addr);
    pa |= super ? ADDR_PART_PN0(addr) << 12 : page.ppn0 << 12;
    pa |= page.ppn1 << 22;

    /* cpu.debug_arb_1 = pa; */

    /* if (!(pa & 0x80000000) || (pa & 0x7fffffff) >= RAM_MAX) { */
    /*     FAULT */
    /* } */

    return pa;
}

#endif
