#ifndef MEM_H
#define MEM_H

<?:include header.p ?>

#define WORD_SIZE_NONE 0
#define WORD_SIZE_BYTE 1
#define WORD_SIZE_HALF 2
#define WORD_SIZE_FULL 4

uint mem_get_instruction(uint addr) {
    addr = addr & 0x7FFFFFFF;
    uint idx = (addr >> 2) & 0x3;
    addr = addr >> 4;

    uint4 raw = STATE_TEX[RAM_ADDR(addr)];
    return idx_uint4(raw, idx);
}

// little endian, zero extended, addr must be aligned to word boundary
uint mem_get_word(uint addr) {
    addr &= ~(0x3);
    if (addr >= 0x1020 && addr <= 0x1fff) {
        uint dtb_addr = addr - 0x1020;
        uint dtb_idx = (dtb_addr >> 2) & 0x3;
        dtb_addr = dtb_addr >> 4;
        float4 full;
        [branch]
        switch (dtb_idx) {
            case 0:
                full = _Data_DTB_R[uint2(dtb_addr, 0)];
                break;
            case 1:
                full = _Data_DTB_G[uint2(dtb_addr, 0)];
                break;
            case 2:
                full = _Data_DTB_B[uint2(dtb_addr, 0)];
                break;
            case 3:
                full = _Data_DTB_A[uint2(dtb_addr, 0)];
                break;
        }
        return unpack_raw_float4(full);
    }

    [branch]
    switch (addr) {
        // CLINT
        case 0x02000000: return cpu.clint.msip ? 1 : 0;

        case 0x02004000: return cpu.clint.mtimecmp_lo;
        case 0x02004004: return cpu.clint.mtimecmp_hi;
        case 0x0200bff8: return cpu.clint.mtime_lo;
        case 0x0200bffc: return cpu.clint.mtime_hi;

        // UART (first has rbr_thr_ier_iir, second has lcr_mcr_lsr_scr)
        case 0x10000000:
            uint ret = 0;
            if ((UART_GET2(LCR) >> 7) == 0) {
                uint rbr = UART_GET1(RBR);
                UART_SET1(RBR, 0);
                UART_SET2(LSR, (UART_GET2(LSR) & ~LSR_DATA_AVAILABLE));
                uart_update_iir();
                ret = rbr;
            }
            return ret | ((UART_GET2(LCR) >> 7 == 0 ? UART_GET1(IER) : 0) << 8) | (UART_GET1(IIR) << 16) | (UART_GET2(LCR) << 24);
        /* case 0x10000001: return UART_GET2(LCR) >> 7 == 0 ? UART_GET1(IER) : 0; */
        /* case 0x10000002: return UART_GET1(IIR); */
        /* case 0x10000003: return UART_GET2(LCR); */
        case 0x10000004: return UART_GET2(MCR) | (UART_GET2(LSR) << 8) | (UART_GET2(SCR) << 24);
        /* case 0x10000005: return UART_GET2(LSR); */
        /* case 0x10000007: return UART_GET2(SCR); */
    }

    if ((addr & 0x80000000) == 0) {
        return 0;
    }
    addr = addr & 0x7FFFFFFF;

    if (addr >= RAM_MAX) {
        return 0;
    }

    return mem_get_cached_or_tex(addr);
}

void mem_set_byte(uint addr, uint val) {
    [branch]
    switch (addr) {
        // UART (first has rbr_thr_ier_iir, second has lcr_mcr_lsr_scr)
        case 0x10000000:
            if ((UART_GET2(LCR) >> 7) == 0) {
                UART_SET1(THR, val);
                UART_SET2(LSR, (UART_GET2(LSR) & ~LSR_THR_EMPTY));
                uart_update_iir();
            }
            return;
        case 0x10000001:
            if (UART_GET2(LCR) >> 7 == 0) {
                if ((UART_GET1(IER) & IER_THREINT_BIT) == 0 &&
                    (val & IER_THREINT_BIT) != 0 &&
                    UART_GET1(THR) == 0)
                {
                    cpu.uart.thre_ip = true;
                }
                UART_SET1(IER, val);
                uart_update_iir();
            }
            return;
        case 0x10000003: UART_SET2(LCR, val); return;
        case 0x10000004: UART_SET2(MCR, val); return;
        case 0x10000007: UART_SET2(SCR, val); return;
    }

    if ((addr & 0x80000000) == 0) {
        return;
    }
    addr = addr & 0x7FFFFFFF;

    if (addr >= RAM_MAX) {
        return;
    }

    // caching can cause stalls, so check for same value before storing
    uint word_addr = addr & (~0x3);
    uint cur_val = mem_get_cached_or_tex(word_addr);
    val = (cur_val & ~(0xff << ((addr & 0x3)*8))) | (val << ((addr & 0x3)*8));
    if (val != cur_val) {
        // put written value into L1 cache
        mem_cache_bloom |= word_addr;

        [branch]
        switch (RAM_L1_TAG(word_addr)) {
<?
for my $i (0..$ram_l1_set_max) {
    print "case $i:\n";
    for my $j (0..$ram_l1_line_max) {
        my $ci = $i + $j * ($ram_l1_set_max + 1);
        my $e = $j == 0 ? "    " : "else";
        print "$e if (cpu.cache.ram_l1_${ci}_addr == 0xffffffff || cpu.cache.ram_l1_${ci}_addr == word_addr) { cpu.cache.ram_l1_${ci}_addr = word_addr; cpu.cache.ram_l1_${ci}_val = val; return; }\n";
    }
    print "break;\n"
}
?>
        }

        // L1 overflow, stall to avoid fillup until L2 flush (TODO) or next frame
        cpu.cache.ram_l1_last_addr = word_addr;
        cpu.cache.ram_l1_last_val = val;
        cpu.stall = STALL_MEM_CACHE_L1;
    }
}

void mem_set(uint addr, uint val, uint word_size) {

    if (word_size == WORD_SIZE_FULL) {
        [branch]
        switch (addr & (~0x3)) {
            // CLINT/timer - only supports full word write as optimization
            case 0x02000000: cpu.clint.msip = (val & 1) != 0; return;
            case 0x02004000: cpu.clint.mtimecmp_lo = val; return;
            case 0x02004004: cpu.clint.mtimecmp_hi = val; return;
            case 0x0200bff8: cpu.clint.mtime_lo = val; return;
            case 0x0200bffc: cpu.clint.mtime_hi = val; return;
        }
    }

    [loop]
    for (uint i = 0; i < word_size; i++) {
        mem_set_byte(addr + i, (val >> (8 * i)) & 0xff);
    }
}

#endif
