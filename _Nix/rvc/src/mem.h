#ifndef MEM_H
#define MEM_H



/* must match set/line count above, shift by two to ignore byte offset */
#define RAM_L1_TAG(a) ((a >> 2) & 0xf)


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
case 0:
     if (cpu.cache.ram_l1_0_addr == 0xffffffff || cpu.cache.ram_l1_0_addr == word_addr) { cpu.cache.ram_l1_0_addr = word_addr; cpu.cache.ram_l1_0_val = val; return; }
else if (cpu.cache.ram_l1_16_addr == 0xffffffff || cpu.cache.ram_l1_16_addr == word_addr) { cpu.cache.ram_l1_16_addr = word_addr; cpu.cache.ram_l1_16_val = val; return; }
else if (cpu.cache.ram_l1_32_addr == 0xffffffff || cpu.cache.ram_l1_32_addr == word_addr) { cpu.cache.ram_l1_32_addr = word_addr; cpu.cache.ram_l1_32_val = val; return; }
else if (cpu.cache.ram_l1_48_addr == 0xffffffff || cpu.cache.ram_l1_48_addr == word_addr) { cpu.cache.ram_l1_48_addr = word_addr; cpu.cache.ram_l1_48_val = val; return; }
else if (cpu.cache.ram_l1_64_addr == 0xffffffff || cpu.cache.ram_l1_64_addr == word_addr) { cpu.cache.ram_l1_64_addr = word_addr; cpu.cache.ram_l1_64_val = val; return; }
break;
case 1:
     if (cpu.cache.ram_l1_1_addr == 0xffffffff || cpu.cache.ram_l1_1_addr == word_addr) { cpu.cache.ram_l1_1_addr = word_addr; cpu.cache.ram_l1_1_val = val; return; }
else if (cpu.cache.ram_l1_17_addr == 0xffffffff || cpu.cache.ram_l1_17_addr == word_addr) { cpu.cache.ram_l1_17_addr = word_addr; cpu.cache.ram_l1_17_val = val; return; }
else if (cpu.cache.ram_l1_33_addr == 0xffffffff || cpu.cache.ram_l1_33_addr == word_addr) { cpu.cache.ram_l1_33_addr = word_addr; cpu.cache.ram_l1_33_val = val; return; }
else if (cpu.cache.ram_l1_49_addr == 0xffffffff || cpu.cache.ram_l1_49_addr == word_addr) { cpu.cache.ram_l1_49_addr = word_addr; cpu.cache.ram_l1_49_val = val; return; }
else if (cpu.cache.ram_l1_65_addr == 0xffffffff || cpu.cache.ram_l1_65_addr == word_addr) { cpu.cache.ram_l1_65_addr = word_addr; cpu.cache.ram_l1_65_val = val; return; }
break;
case 2:
     if (cpu.cache.ram_l1_2_addr == 0xffffffff || cpu.cache.ram_l1_2_addr == word_addr) { cpu.cache.ram_l1_2_addr = word_addr; cpu.cache.ram_l1_2_val = val; return; }
else if (cpu.cache.ram_l1_18_addr == 0xffffffff || cpu.cache.ram_l1_18_addr == word_addr) { cpu.cache.ram_l1_18_addr = word_addr; cpu.cache.ram_l1_18_val = val; return; }
else if (cpu.cache.ram_l1_34_addr == 0xffffffff || cpu.cache.ram_l1_34_addr == word_addr) { cpu.cache.ram_l1_34_addr = word_addr; cpu.cache.ram_l1_34_val = val; return; }
else if (cpu.cache.ram_l1_50_addr == 0xffffffff || cpu.cache.ram_l1_50_addr == word_addr) { cpu.cache.ram_l1_50_addr = word_addr; cpu.cache.ram_l1_50_val = val; return; }
else if (cpu.cache.ram_l1_66_addr == 0xffffffff || cpu.cache.ram_l1_66_addr == word_addr) { cpu.cache.ram_l1_66_addr = word_addr; cpu.cache.ram_l1_66_val = val; return; }
break;
case 3:
     if (cpu.cache.ram_l1_3_addr == 0xffffffff || cpu.cache.ram_l1_3_addr == word_addr) { cpu.cache.ram_l1_3_addr = word_addr; cpu.cache.ram_l1_3_val = val; return; }
else if (cpu.cache.ram_l1_19_addr == 0xffffffff || cpu.cache.ram_l1_19_addr == word_addr) { cpu.cache.ram_l1_19_addr = word_addr; cpu.cache.ram_l1_19_val = val; return; }
else if (cpu.cache.ram_l1_35_addr == 0xffffffff || cpu.cache.ram_l1_35_addr == word_addr) { cpu.cache.ram_l1_35_addr = word_addr; cpu.cache.ram_l1_35_val = val; return; }
else if (cpu.cache.ram_l1_51_addr == 0xffffffff || cpu.cache.ram_l1_51_addr == word_addr) { cpu.cache.ram_l1_51_addr = word_addr; cpu.cache.ram_l1_51_val = val; return; }
else if (cpu.cache.ram_l1_67_addr == 0xffffffff || cpu.cache.ram_l1_67_addr == word_addr) { cpu.cache.ram_l1_67_addr = word_addr; cpu.cache.ram_l1_67_val = val; return; }
break;
case 4:
     if (cpu.cache.ram_l1_4_addr == 0xffffffff || cpu.cache.ram_l1_4_addr == word_addr) { cpu.cache.ram_l1_4_addr = word_addr; cpu.cache.ram_l1_4_val = val; return; }
else if (cpu.cache.ram_l1_20_addr == 0xffffffff || cpu.cache.ram_l1_20_addr == word_addr) { cpu.cache.ram_l1_20_addr = word_addr; cpu.cache.ram_l1_20_val = val; return; }
else if (cpu.cache.ram_l1_36_addr == 0xffffffff || cpu.cache.ram_l1_36_addr == word_addr) { cpu.cache.ram_l1_36_addr = word_addr; cpu.cache.ram_l1_36_val = val; return; }
else if (cpu.cache.ram_l1_52_addr == 0xffffffff || cpu.cache.ram_l1_52_addr == word_addr) { cpu.cache.ram_l1_52_addr = word_addr; cpu.cache.ram_l1_52_val = val; return; }
else if (cpu.cache.ram_l1_68_addr == 0xffffffff || cpu.cache.ram_l1_68_addr == word_addr) { cpu.cache.ram_l1_68_addr = word_addr; cpu.cache.ram_l1_68_val = val; return; }
break;
case 5:
     if (cpu.cache.ram_l1_5_addr == 0xffffffff || cpu.cache.ram_l1_5_addr == word_addr) { cpu.cache.ram_l1_5_addr = word_addr; cpu.cache.ram_l1_5_val = val; return; }
else if (cpu.cache.ram_l1_21_addr == 0xffffffff || cpu.cache.ram_l1_21_addr == word_addr) { cpu.cache.ram_l1_21_addr = word_addr; cpu.cache.ram_l1_21_val = val; return; }
else if (cpu.cache.ram_l1_37_addr == 0xffffffff || cpu.cache.ram_l1_37_addr == word_addr) { cpu.cache.ram_l1_37_addr = word_addr; cpu.cache.ram_l1_37_val = val; return; }
else if (cpu.cache.ram_l1_53_addr == 0xffffffff || cpu.cache.ram_l1_53_addr == word_addr) { cpu.cache.ram_l1_53_addr = word_addr; cpu.cache.ram_l1_53_val = val; return; }
else if (cpu.cache.ram_l1_69_addr == 0xffffffff || cpu.cache.ram_l1_69_addr == word_addr) { cpu.cache.ram_l1_69_addr = word_addr; cpu.cache.ram_l1_69_val = val; return; }
break;
case 6:
     if (cpu.cache.ram_l1_6_addr == 0xffffffff || cpu.cache.ram_l1_6_addr == word_addr) { cpu.cache.ram_l1_6_addr = word_addr; cpu.cache.ram_l1_6_val = val; return; }
else if (cpu.cache.ram_l1_22_addr == 0xffffffff || cpu.cache.ram_l1_22_addr == word_addr) { cpu.cache.ram_l1_22_addr = word_addr; cpu.cache.ram_l1_22_val = val; return; }
else if (cpu.cache.ram_l1_38_addr == 0xffffffff || cpu.cache.ram_l1_38_addr == word_addr) { cpu.cache.ram_l1_38_addr = word_addr; cpu.cache.ram_l1_38_val = val; return; }
else if (cpu.cache.ram_l1_54_addr == 0xffffffff || cpu.cache.ram_l1_54_addr == word_addr) { cpu.cache.ram_l1_54_addr = word_addr; cpu.cache.ram_l1_54_val = val; return; }
else if (cpu.cache.ram_l1_70_addr == 0xffffffff || cpu.cache.ram_l1_70_addr == word_addr) { cpu.cache.ram_l1_70_addr = word_addr; cpu.cache.ram_l1_70_val = val; return; }
break;
case 7:
     if (cpu.cache.ram_l1_7_addr == 0xffffffff || cpu.cache.ram_l1_7_addr == word_addr) { cpu.cache.ram_l1_7_addr = word_addr; cpu.cache.ram_l1_7_val = val; return; }
else if (cpu.cache.ram_l1_23_addr == 0xffffffff || cpu.cache.ram_l1_23_addr == word_addr) { cpu.cache.ram_l1_23_addr = word_addr; cpu.cache.ram_l1_23_val = val; return; }
else if (cpu.cache.ram_l1_39_addr == 0xffffffff || cpu.cache.ram_l1_39_addr == word_addr) { cpu.cache.ram_l1_39_addr = word_addr; cpu.cache.ram_l1_39_val = val; return; }
else if (cpu.cache.ram_l1_55_addr == 0xffffffff || cpu.cache.ram_l1_55_addr == word_addr) { cpu.cache.ram_l1_55_addr = word_addr; cpu.cache.ram_l1_55_val = val; return; }
else if (cpu.cache.ram_l1_71_addr == 0xffffffff || cpu.cache.ram_l1_71_addr == word_addr) { cpu.cache.ram_l1_71_addr = word_addr; cpu.cache.ram_l1_71_val = val; return; }
break;
case 8:
     if (cpu.cache.ram_l1_8_addr == 0xffffffff || cpu.cache.ram_l1_8_addr == word_addr) { cpu.cache.ram_l1_8_addr = word_addr; cpu.cache.ram_l1_8_val = val; return; }
else if (cpu.cache.ram_l1_24_addr == 0xffffffff || cpu.cache.ram_l1_24_addr == word_addr) { cpu.cache.ram_l1_24_addr = word_addr; cpu.cache.ram_l1_24_val = val; return; }
else if (cpu.cache.ram_l1_40_addr == 0xffffffff || cpu.cache.ram_l1_40_addr == word_addr) { cpu.cache.ram_l1_40_addr = word_addr; cpu.cache.ram_l1_40_val = val; return; }
else if (cpu.cache.ram_l1_56_addr == 0xffffffff || cpu.cache.ram_l1_56_addr == word_addr) { cpu.cache.ram_l1_56_addr = word_addr; cpu.cache.ram_l1_56_val = val; return; }
else if (cpu.cache.ram_l1_72_addr == 0xffffffff || cpu.cache.ram_l1_72_addr == word_addr) { cpu.cache.ram_l1_72_addr = word_addr; cpu.cache.ram_l1_72_val = val; return; }
break;
case 9:
     if (cpu.cache.ram_l1_9_addr == 0xffffffff || cpu.cache.ram_l1_9_addr == word_addr) { cpu.cache.ram_l1_9_addr = word_addr; cpu.cache.ram_l1_9_val = val; return; }
else if (cpu.cache.ram_l1_25_addr == 0xffffffff || cpu.cache.ram_l1_25_addr == word_addr) { cpu.cache.ram_l1_25_addr = word_addr; cpu.cache.ram_l1_25_val = val; return; }
else if (cpu.cache.ram_l1_41_addr == 0xffffffff || cpu.cache.ram_l1_41_addr == word_addr) { cpu.cache.ram_l1_41_addr = word_addr; cpu.cache.ram_l1_41_val = val; return; }
else if (cpu.cache.ram_l1_57_addr == 0xffffffff || cpu.cache.ram_l1_57_addr == word_addr) { cpu.cache.ram_l1_57_addr = word_addr; cpu.cache.ram_l1_57_val = val; return; }
else if (cpu.cache.ram_l1_73_addr == 0xffffffff || cpu.cache.ram_l1_73_addr == word_addr) { cpu.cache.ram_l1_73_addr = word_addr; cpu.cache.ram_l1_73_val = val; return; }
break;
case 10:
     if (cpu.cache.ram_l1_10_addr == 0xffffffff || cpu.cache.ram_l1_10_addr == word_addr) { cpu.cache.ram_l1_10_addr = word_addr; cpu.cache.ram_l1_10_val = val; return; }
else if (cpu.cache.ram_l1_26_addr == 0xffffffff || cpu.cache.ram_l1_26_addr == word_addr) { cpu.cache.ram_l1_26_addr = word_addr; cpu.cache.ram_l1_26_val = val; return; }
else if (cpu.cache.ram_l1_42_addr == 0xffffffff || cpu.cache.ram_l1_42_addr == word_addr) { cpu.cache.ram_l1_42_addr = word_addr; cpu.cache.ram_l1_42_val = val; return; }
else if (cpu.cache.ram_l1_58_addr == 0xffffffff || cpu.cache.ram_l1_58_addr == word_addr) { cpu.cache.ram_l1_58_addr = word_addr; cpu.cache.ram_l1_58_val = val; return; }
else if (cpu.cache.ram_l1_74_addr == 0xffffffff || cpu.cache.ram_l1_74_addr == word_addr) { cpu.cache.ram_l1_74_addr = word_addr; cpu.cache.ram_l1_74_val = val; return; }
break;
case 11:
     if (cpu.cache.ram_l1_11_addr == 0xffffffff || cpu.cache.ram_l1_11_addr == word_addr) { cpu.cache.ram_l1_11_addr = word_addr; cpu.cache.ram_l1_11_val = val; return; }
else if (cpu.cache.ram_l1_27_addr == 0xffffffff || cpu.cache.ram_l1_27_addr == word_addr) { cpu.cache.ram_l1_27_addr = word_addr; cpu.cache.ram_l1_27_val = val; return; }
else if (cpu.cache.ram_l1_43_addr == 0xffffffff || cpu.cache.ram_l1_43_addr == word_addr) { cpu.cache.ram_l1_43_addr = word_addr; cpu.cache.ram_l1_43_val = val; return; }
else if (cpu.cache.ram_l1_59_addr == 0xffffffff || cpu.cache.ram_l1_59_addr == word_addr) { cpu.cache.ram_l1_59_addr = word_addr; cpu.cache.ram_l1_59_val = val; return; }
else if (cpu.cache.ram_l1_75_addr == 0xffffffff || cpu.cache.ram_l1_75_addr == word_addr) { cpu.cache.ram_l1_75_addr = word_addr; cpu.cache.ram_l1_75_val = val; return; }
break;
case 12:
     if (cpu.cache.ram_l1_12_addr == 0xffffffff || cpu.cache.ram_l1_12_addr == word_addr) { cpu.cache.ram_l1_12_addr = word_addr; cpu.cache.ram_l1_12_val = val; return; }
else if (cpu.cache.ram_l1_28_addr == 0xffffffff || cpu.cache.ram_l1_28_addr == word_addr) { cpu.cache.ram_l1_28_addr = word_addr; cpu.cache.ram_l1_28_val = val; return; }
else if (cpu.cache.ram_l1_44_addr == 0xffffffff || cpu.cache.ram_l1_44_addr == word_addr) { cpu.cache.ram_l1_44_addr = word_addr; cpu.cache.ram_l1_44_val = val; return; }
else if (cpu.cache.ram_l1_60_addr == 0xffffffff || cpu.cache.ram_l1_60_addr == word_addr) { cpu.cache.ram_l1_60_addr = word_addr; cpu.cache.ram_l1_60_val = val; return; }
else if (cpu.cache.ram_l1_76_addr == 0xffffffff || cpu.cache.ram_l1_76_addr == word_addr) { cpu.cache.ram_l1_76_addr = word_addr; cpu.cache.ram_l1_76_val = val; return; }
break;
case 13:
     if (cpu.cache.ram_l1_13_addr == 0xffffffff || cpu.cache.ram_l1_13_addr == word_addr) { cpu.cache.ram_l1_13_addr = word_addr; cpu.cache.ram_l1_13_val = val; return; }
else if (cpu.cache.ram_l1_29_addr == 0xffffffff || cpu.cache.ram_l1_29_addr == word_addr) { cpu.cache.ram_l1_29_addr = word_addr; cpu.cache.ram_l1_29_val = val; return; }
else if (cpu.cache.ram_l1_45_addr == 0xffffffff || cpu.cache.ram_l1_45_addr == word_addr) { cpu.cache.ram_l1_45_addr = word_addr; cpu.cache.ram_l1_45_val = val; return; }
else if (cpu.cache.ram_l1_61_addr == 0xffffffff || cpu.cache.ram_l1_61_addr == word_addr) { cpu.cache.ram_l1_61_addr = word_addr; cpu.cache.ram_l1_61_val = val; return; }
else if (cpu.cache.ram_l1_77_addr == 0xffffffff || cpu.cache.ram_l1_77_addr == word_addr) { cpu.cache.ram_l1_77_addr = word_addr; cpu.cache.ram_l1_77_val = val; return; }
break;
case 14:
     if (cpu.cache.ram_l1_14_addr == 0xffffffff || cpu.cache.ram_l1_14_addr == word_addr) { cpu.cache.ram_l1_14_addr = word_addr; cpu.cache.ram_l1_14_val = val; return; }
else if (cpu.cache.ram_l1_30_addr == 0xffffffff || cpu.cache.ram_l1_30_addr == word_addr) { cpu.cache.ram_l1_30_addr = word_addr; cpu.cache.ram_l1_30_val = val; return; }
else if (cpu.cache.ram_l1_46_addr == 0xffffffff || cpu.cache.ram_l1_46_addr == word_addr) { cpu.cache.ram_l1_46_addr = word_addr; cpu.cache.ram_l1_46_val = val; return; }
else if (cpu.cache.ram_l1_62_addr == 0xffffffff || cpu.cache.ram_l1_62_addr == word_addr) { cpu.cache.ram_l1_62_addr = word_addr; cpu.cache.ram_l1_62_val = val; return; }
else if (cpu.cache.ram_l1_78_addr == 0xffffffff || cpu.cache.ram_l1_78_addr == word_addr) { cpu.cache.ram_l1_78_addr = word_addr; cpu.cache.ram_l1_78_val = val; return; }
break;
case 15:
     if (cpu.cache.ram_l1_15_addr == 0xffffffff || cpu.cache.ram_l1_15_addr == word_addr) { cpu.cache.ram_l1_15_addr = word_addr; cpu.cache.ram_l1_15_val = val; return; }
else if (cpu.cache.ram_l1_31_addr == 0xffffffff || cpu.cache.ram_l1_31_addr == word_addr) { cpu.cache.ram_l1_31_addr = word_addr; cpu.cache.ram_l1_31_val = val; return; }
else if (cpu.cache.ram_l1_47_addr == 0xffffffff || cpu.cache.ram_l1_47_addr == word_addr) { cpu.cache.ram_l1_47_addr = word_addr; cpu.cache.ram_l1_47_val = val; return; }
else if (cpu.cache.ram_l1_63_addr == 0xffffffff || cpu.cache.ram_l1_63_addr == word_addr) { cpu.cache.ram_l1_63_addr = word_addr; cpu.cache.ram_l1_63_val = val; return; }
else if (cpu.cache.ram_l1_79_addr == 0xffffffff || cpu.cache.ram_l1_79_addr == word_addr) { cpu.cache.ram_l1_79_addr = word_addr; cpu.cache.ram_l1_79_val = val; return; }
break;

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
