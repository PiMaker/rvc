#ifndef TYPES_H
#define TYPES_H



/* must match set/line count above, shift by two to ignore byte offset */
#define RAM_L1_TAG(a) ((a >> 2) & 0xf)


#define STALL_EXIT_CALL 1
#define STALL_CSR_CACHE 2
#define STALL_MEM_CACHE_L1 3
#define STALL_MEM_CACHE_L2 4
#define STALL_ILLEGAL_ENTRY_POINT 5
#define STALL_UART 6
#define STALL_FENCE 7
#define STALL_MEMOP_COPY 8



// STRUCT TYPES
typedef struct {
    uint csr_cache_0_addr; uint csr_cache_0_val;
    uint csr_cache_1_addr; uint csr_cache_1_val;
    uint csr_cache_2_addr; uint csr_cache_2_val;
    uint csr_cache_3_addr; uint csr_cache_3_val;
    uint csr_cache_4_addr; uint csr_cache_4_val;
    uint csr_cache_5_addr; uint csr_cache_5_val;
    uint csr_cache_6_addr; uint csr_cache_6_val;
    uint csr_cache_7_addr; uint csr_cache_7_val;
    uint csr_cache_8_addr; uint csr_cache_8_val;
    uint csr_cache_9_addr; uint csr_cache_9_val;
    uint csr_cache_10_addr; uint csr_cache_10_val;
    uint csr_cache_11_addr; uint csr_cache_11_val;
    uint csr_cache_12_addr; uint csr_cache_12_val;
    uint csr_cache_13_addr; uint csr_cache_13_val;
    uint csr_cache_14_addr; uint csr_cache_14_val;
    uint csr_cache_15_addr; uint csr_cache_15_val;
    uint ram_l1_0_addr; uint ram_l1_0_val;
    uint ram_l1_16_addr; uint ram_l1_16_val;
    uint ram_l1_32_addr; uint ram_l1_32_val;
    uint ram_l1_48_addr; uint ram_l1_48_val;
    uint ram_l1_64_addr; uint ram_l1_64_val;
    uint ram_l1_1_addr; uint ram_l1_1_val;
    uint ram_l1_17_addr; uint ram_l1_17_val;
    uint ram_l1_33_addr; uint ram_l1_33_val;
    uint ram_l1_49_addr; uint ram_l1_49_val;
    uint ram_l1_65_addr; uint ram_l1_65_val;
    uint ram_l1_2_addr; uint ram_l1_2_val;
    uint ram_l1_18_addr; uint ram_l1_18_val;
    uint ram_l1_34_addr; uint ram_l1_34_val;
    uint ram_l1_50_addr; uint ram_l1_50_val;
    uint ram_l1_66_addr; uint ram_l1_66_val;
    uint ram_l1_3_addr; uint ram_l1_3_val;
    uint ram_l1_19_addr; uint ram_l1_19_val;
    uint ram_l1_35_addr; uint ram_l1_35_val;
    uint ram_l1_51_addr; uint ram_l1_51_val;
    uint ram_l1_67_addr; uint ram_l1_67_val;
    uint ram_l1_4_addr; uint ram_l1_4_val;
    uint ram_l1_20_addr; uint ram_l1_20_val;
    uint ram_l1_36_addr; uint ram_l1_36_val;
    uint ram_l1_52_addr; uint ram_l1_52_val;
    uint ram_l1_68_addr; uint ram_l1_68_val;
    uint ram_l1_5_addr; uint ram_l1_5_val;
    uint ram_l1_21_addr; uint ram_l1_21_val;
    uint ram_l1_37_addr; uint ram_l1_37_val;
    uint ram_l1_53_addr; uint ram_l1_53_val;
    uint ram_l1_69_addr; uint ram_l1_69_val;
    uint ram_l1_6_addr; uint ram_l1_6_val;
    uint ram_l1_22_addr; uint ram_l1_22_val;
    uint ram_l1_38_addr; uint ram_l1_38_val;
    uint ram_l1_54_addr; uint ram_l1_54_val;
    uint ram_l1_70_addr; uint ram_l1_70_val;
    uint ram_l1_7_addr; uint ram_l1_7_val;
    uint ram_l1_23_addr; uint ram_l1_23_val;
    uint ram_l1_39_addr; uint ram_l1_39_val;
    uint ram_l1_55_addr; uint ram_l1_55_val;
    uint ram_l1_71_addr; uint ram_l1_71_val;
    uint ram_l1_8_addr; uint ram_l1_8_val;
    uint ram_l1_24_addr; uint ram_l1_24_val;
    uint ram_l1_40_addr; uint ram_l1_40_val;
    uint ram_l1_56_addr; uint ram_l1_56_val;
    uint ram_l1_72_addr; uint ram_l1_72_val;
    uint ram_l1_9_addr; uint ram_l1_9_val;
    uint ram_l1_25_addr; uint ram_l1_25_val;
    uint ram_l1_41_addr; uint ram_l1_41_val;
    uint ram_l1_57_addr; uint ram_l1_57_val;
    uint ram_l1_73_addr; uint ram_l1_73_val;
    uint ram_l1_10_addr; uint ram_l1_10_val;
    uint ram_l1_26_addr; uint ram_l1_26_val;
    uint ram_l1_42_addr; uint ram_l1_42_val;
    uint ram_l1_58_addr; uint ram_l1_58_val;
    uint ram_l1_74_addr; uint ram_l1_74_val;
    uint ram_l1_11_addr; uint ram_l1_11_val;
    uint ram_l1_27_addr; uint ram_l1_27_val;
    uint ram_l1_43_addr; uint ram_l1_43_val;
    uint ram_l1_59_addr; uint ram_l1_59_val;
    uint ram_l1_75_addr; uint ram_l1_75_val;
    uint ram_l1_12_addr; uint ram_l1_12_val;
    uint ram_l1_28_addr; uint ram_l1_28_val;
    uint ram_l1_44_addr; uint ram_l1_44_val;
    uint ram_l1_60_addr; uint ram_l1_60_val;
    uint ram_l1_76_addr; uint ram_l1_76_val;
    uint ram_l1_13_addr; uint ram_l1_13_val;
    uint ram_l1_29_addr; uint ram_l1_29_val;
    uint ram_l1_45_addr; uint ram_l1_45_val;
    uint ram_l1_61_addr; uint ram_l1_61_val;
    uint ram_l1_77_addr; uint ram_l1_77_val;
    uint ram_l1_14_addr; uint ram_l1_14_val;
    uint ram_l1_30_addr; uint ram_l1_30_val;
    uint ram_l1_46_addr; uint ram_l1_46_val;
    uint ram_l1_62_addr; uint ram_l1_62_val;
    uint ram_l1_78_addr; uint ram_l1_78_val;
    uint ram_l1_15_addr; uint ram_l1_15_val;
    uint ram_l1_31_addr; uint ram_l1_31_val;
    uint ram_l1_47_addr; uint ram_l1_47_val;
    uint ram_l1_63_addr; uint ram_l1_63_val;
    uint ram_l1_79_addr; uint ram_l1_79_val;
    uint ram_l1_last_addr;uint ram_l1_last_val;
} cache_t;

typedef struct {
    uint privilege;
} csr_state;

typedef struct {
    uint rbr_thr_ier_iir;
    uint lcr_mcr_lsr_scr;
    bool thre_ip;
    bool interrupting;
    uint input_tag;
} uart_state;

typedef struct {
    bool msip;
    uint mtimecmp_lo;
    uint mtimecmp_hi;
    uint mtime_lo;
    uint mtime_hi;
} clint_state;

typedef struct {
    uint ptr;
    uint buf0;
    uint buf1;
    uint buf2;
    uint buf3;
    uint buf4;
    uint buf5;
    uint buf6;
    uint buf7;
    uint buf8;
    uint buf9;
    uint buf10;
    uint buf11;
    uint buf12;
    uint buf13;
    uint buf14;
    uint buf15;
    uint buf16;
    uint buf17;
    uint buf18;
    uint buf19;
    uint buf20;
    uint buf21;
    uint buf22;
    uint buf23;
    uint buf24;
    uint buf25;
    uint buf26;
    uint buf27;
    uint buf28;
    uint buf29;
    uint buf30;
    uint buf31;
    uint buf32;
    uint buf33;
    uint buf34;
    uint buf35;
    uint buf36;
    uint buf37;
    uint buf38;
    uint buf39;
    uint buf40;
    uint buf41;
    uint buf42;
    uint buf43;
    uint buf44;
    uint buf45;
    uint buf46;
    uint buf47;
    uint buf48;
    uint buf49;
    uint buf50;
    uint buf51;
    uint buf52;
    uint buf53;
    uint buf54;
    uint buf55;
    uint buf56;
    uint buf57;
    uint buf58;
    uint buf59;
    uint buf60;
    uint buf61;
    uint buf62;
    uint buf63;
    
} uart_buffer;

typedef struct {
    uint mode;
    uint ppn;
} mmu_state;

typedef struct {
    uint stall;
    uint clock;
    uint commits;
    uint xreg0;
    uint xreg1;
    uint xreg2;
    uint xreg3;
    uint xreg4;
    uint xreg5;
    uint xreg6;
    uint xreg7;
    uint xreg8;
    uint xreg9;
    uint xreg10;
    uint xreg11;
    uint xreg12;
    uint xreg13;
    uint xreg14;
    uint xreg15;
    uint xreg16;
    uint xreg17;
    uint xreg18;
    uint xreg19;
    uint xreg20;
    uint xreg21;
    uint xreg22;
    uint xreg23;
    uint xreg24;
    uint xreg25;
    uint xreg26;
    uint xreg27;
    uint xreg28;
    uint xreg29;
    uint xreg30;
    uint xreg31;
    
    uint pc;
    csr_state csr;
    clint_state clint;
    uart_state uart;
    uart_buffer uart_buffer;
    mmu_state mmu;

    bool reservation_en;
    uint reservation_addr;

    uint memop_src_v;
    uint memop_dst_v;
    uint memop_src_p;
    uint memop_dst_p;
    uint memop_n;

    uint stall_count;
    uint trap_count;

    uint debug_do_tick;
    uint debug_last_ins;
    uint debug_last_stall;
    
    

    uint debug_arb_0;
    
    
    
    
    
    
    

    cache_t cache;
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
    uint mem_wr_addr;
    uint mem_wr_value;
    uint mem_wr_size;
    trap trap;
} ins_ret;

// GLOBAL STATICS
static cpu_t cpu;

// TYPE HELPERS
ins_ret ins_ret_noop() {
    ins_ret ret = (ins_ret)0;
    ret.pc_val = cpu.pc + 4;
    return ret;
}

uint sign_extend(uint x, uint b) {
    uint m = ((uint)1) << (b - 1);
    return (x ^ m) - m;
}

uint xreg(uint i) {
    #define C(x) case x: return cpu.xreg##x;
    if (i < 16) {
        [flatten]
        switch (i) {
            C(0) C(1) C(2) C(3)
            C(4) C(5) C(6) C(7)
            C(8) C(9) C(10) C(11)
            C(12) C(13) C(14) C(15)
        }
    } else {
        [flatten]
        switch (i) {
            C(16) C(17) C(18) C(19)
            C(20) C(21) C(22) C(23)
            C(24) C(25) C(26) C(27)
            C(28) C(29) C(30) C(31)
        }
    }
    return 0xdeadc0de;
    #undef C
}

// ENCODE/DECODE LOGIC (state serialization into self texture)



void decode(uint udonUartPtr) {
    cpu = (cpu_t)0;

    cpu.cache.csr_cache_0_addr = uint(4294967295);
    cpu.cache.csr_cache_0_val = uint(3735930846);
    cpu.cache.csr_cache_1_addr = uint(4294967295);
    cpu.cache.csr_cache_1_val = uint(3735930846);
    cpu.cache.csr_cache_2_addr = uint(4294967295);
    cpu.cache.csr_cache_2_val = uint(3735930846);
    cpu.cache.csr_cache_3_addr = uint(4294967295);
    cpu.cache.csr_cache_3_val = uint(3735930846);
    cpu.cache.csr_cache_4_addr = uint(4294967295);
    cpu.cache.csr_cache_4_val = uint(3735930846);
    cpu.cache.csr_cache_5_addr = uint(4294967295);
    cpu.cache.csr_cache_5_val = uint(3735930846);
    cpu.cache.csr_cache_6_addr = uint(4294967295);
    cpu.cache.csr_cache_6_val = uint(3735930846);
    cpu.cache.csr_cache_7_addr = uint(4294967295);
    cpu.cache.csr_cache_7_val = uint(3735930846);
    cpu.cache.csr_cache_8_addr = uint(4294967295);
    cpu.cache.csr_cache_8_val = uint(3735930846);
    cpu.cache.csr_cache_9_addr = uint(4294967295);
    cpu.cache.csr_cache_9_val = uint(3735930846);
    cpu.cache.csr_cache_10_addr = uint(4294967295);
    cpu.cache.csr_cache_10_val = uint(3735930846);
    cpu.cache.csr_cache_11_addr = uint(4294967295);
    cpu.cache.csr_cache_11_val = uint(3735930846);
    cpu.cache.csr_cache_12_addr = uint(4294967295);
    cpu.cache.csr_cache_12_val = uint(3735930846);
    cpu.cache.csr_cache_13_addr = uint(4294967295);
    cpu.cache.csr_cache_13_val = uint(3735930846);
    cpu.cache.csr_cache_14_addr = uint(4294967295);
    cpu.cache.csr_cache_14_val = uint(3735930846);
    cpu.cache.csr_cache_15_addr = uint(4294967295);
    cpu.cache.csr_cache_15_val = uint(3735930846);
    cpu.cache.ram_l1_0_addr = uint(4294967295);
    cpu.cache.ram_l1_0_val = uint(3735931102);
    cpu.cache.ram_l1_16_addr = uint(4294967295);
    cpu.cache.ram_l1_16_val = uint(3735931102);
    cpu.cache.ram_l1_32_addr = uint(4294967295);
    cpu.cache.ram_l1_32_val = uint(3735931102);
    cpu.cache.ram_l1_48_addr = uint(4294967295);
    cpu.cache.ram_l1_48_val = uint(3735931102);
    cpu.cache.ram_l1_64_addr = uint(4294967295);
    cpu.cache.ram_l1_64_val = uint(3735931102);
    cpu.cache.ram_l1_1_addr = uint(4294967295);
    cpu.cache.ram_l1_1_val = uint(3735931102);
    cpu.cache.ram_l1_17_addr = uint(4294967295);
    cpu.cache.ram_l1_17_val = uint(3735931102);
    cpu.cache.ram_l1_33_addr = uint(4294967295);
    cpu.cache.ram_l1_33_val = uint(3735931102);
    cpu.cache.ram_l1_49_addr = uint(4294967295);
    cpu.cache.ram_l1_49_val = uint(3735931102);
    cpu.cache.ram_l1_65_addr = uint(4294967295);
    cpu.cache.ram_l1_65_val = uint(3735931102);
    cpu.cache.ram_l1_2_addr = uint(4294967295);
    cpu.cache.ram_l1_2_val = uint(3735931102);
    cpu.cache.ram_l1_18_addr = uint(4294967295);
    cpu.cache.ram_l1_18_val = uint(3735931102);
    cpu.cache.ram_l1_34_addr = uint(4294967295);
    cpu.cache.ram_l1_34_val = uint(3735931102);
    cpu.cache.ram_l1_50_addr = uint(4294967295);
    cpu.cache.ram_l1_50_val = uint(3735931102);
    cpu.cache.ram_l1_66_addr = uint(4294967295);
    cpu.cache.ram_l1_66_val = uint(3735931102);
    cpu.cache.ram_l1_3_addr = uint(4294967295);
    cpu.cache.ram_l1_3_val = uint(3735931102);
    cpu.cache.ram_l1_19_addr = uint(4294967295);
    cpu.cache.ram_l1_19_val = uint(3735931102);
    cpu.cache.ram_l1_35_addr = uint(4294967295);
    cpu.cache.ram_l1_35_val = uint(3735931102);
    cpu.cache.ram_l1_51_addr = uint(4294967295);
    cpu.cache.ram_l1_51_val = uint(3735931102);
    cpu.cache.ram_l1_67_addr = uint(4294967295);
    cpu.cache.ram_l1_67_val = uint(3735931102);
    cpu.cache.ram_l1_4_addr = uint(4294967295);
    cpu.cache.ram_l1_4_val = uint(3735931102);
    cpu.cache.ram_l1_20_addr = uint(4294967295);
    cpu.cache.ram_l1_20_val = uint(3735931102);
    cpu.cache.ram_l1_36_addr = uint(4294967295);
    cpu.cache.ram_l1_36_val = uint(3735931102);
    cpu.cache.ram_l1_52_addr = uint(4294967295);
    cpu.cache.ram_l1_52_val = uint(3735931102);
    cpu.cache.ram_l1_68_addr = uint(4294967295);
    cpu.cache.ram_l1_68_val = uint(3735931102);
    cpu.cache.ram_l1_5_addr = uint(4294967295);
    cpu.cache.ram_l1_5_val = uint(3735931102);
    cpu.cache.ram_l1_21_addr = uint(4294967295);
    cpu.cache.ram_l1_21_val = uint(3735931102);
    cpu.cache.ram_l1_37_addr = uint(4294967295);
    cpu.cache.ram_l1_37_val = uint(3735931102);
    cpu.cache.ram_l1_53_addr = uint(4294967295);
    cpu.cache.ram_l1_53_val = uint(3735931102);
    cpu.cache.ram_l1_69_addr = uint(4294967295);
    cpu.cache.ram_l1_69_val = uint(3735931102);
    cpu.cache.ram_l1_6_addr = uint(4294967295);
    cpu.cache.ram_l1_6_val = uint(3735931102);
    cpu.cache.ram_l1_22_addr = uint(4294967295);
    cpu.cache.ram_l1_22_val = uint(3735931102);
    cpu.cache.ram_l1_38_addr = uint(4294967295);
    cpu.cache.ram_l1_38_val = uint(3735931102);
    cpu.cache.ram_l1_54_addr = uint(4294967295);
    cpu.cache.ram_l1_54_val = uint(3735931102);
    cpu.cache.ram_l1_70_addr = uint(4294967295);
    cpu.cache.ram_l1_70_val = uint(3735931102);
    cpu.cache.ram_l1_7_addr = uint(4294967295);
    cpu.cache.ram_l1_7_val = uint(3735931102);
    cpu.cache.ram_l1_23_addr = uint(4294967295);
    cpu.cache.ram_l1_23_val = uint(3735931102);
    cpu.cache.ram_l1_39_addr = uint(4294967295);
    cpu.cache.ram_l1_39_val = uint(3735931102);
    cpu.cache.ram_l1_55_addr = uint(4294967295);
    cpu.cache.ram_l1_55_val = uint(3735931102);
    cpu.cache.ram_l1_71_addr = uint(4294967295);
    cpu.cache.ram_l1_71_val = uint(3735931102);
    cpu.cache.ram_l1_8_addr = uint(4294967295);
    cpu.cache.ram_l1_8_val = uint(3735931102);
    cpu.cache.ram_l1_24_addr = uint(4294967295);
    cpu.cache.ram_l1_24_val = uint(3735931102);
    cpu.cache.ram_l1_40_addr = uint(4294967295);
    cpu.cache.ram_l1_40_val = uint(3735931102);
    cpu.cache.ram_l1_56_addr = uint(4294967295);
    cpu.cache.ram_l1_56_val = uint(3735931102);
    cpu.cache.ram_l1_72_addr = uint(4294967295);
    cpu.cache.ram_l1_72_val = uint(3735931102);
    cpu.cache.ram_l1_9_addr = uint(4294967295);
    cpu.cache.ram_l1_9_val = uint(3735931102);
    cpu.cache.ram_l1_25_addr = uint(4294967295);
    cpu.cache.ram_l1_25_val = uint(3735931102);
    cpu.cache.ram_l1_41_addr = uint(4294967295);
    cpu.cache.ram_l1_41_val = uint(3735931102);
    cpu.cache.ram_l1_57_addr = uint(4294967295);
    cpu.cache.ram_l1_57_val = uint(3735931102);
    cpu.cache.ram_l1_73_addr = uint(4294967295);
    cpu.cache.ram_l1_73_val = uint(3735931102);
    cpu.cache.ram_l1_10_addr = uint(4294967295);
    cpu.cache.ram_l1_10_val = uint(3735931102);
    cpu.cache.ram_l1_26_addr = uint(4294967295);
    cpu.cache.ram_l1_26_val = uint(3735931102);
    cpu.cache.ram_l1_42_addr = uint(4294967295);
    cpu.cache.ram_l1_42_val = uint(3735931102);
    cpu.cache.ram_l1_58_addr = uint(4294967295);
    cpu.cache.ram_l1_58_val = uint(3735931102);
    cpu.cache.ram_l1_74_addr = uint(4294967295);
    cpu.cache.ram_l1_74_val = uint(3735931102);
    cpu.cache.ram_l1_11_addr = uint(4294967295);
    cpu.cache.ram_l1_11_val = uint(3735931102);
    cpu.cache.ram_l1_27_addr = uint(4294967295);
    cpu.cache.ram_l1_27_val = uint(3735931102);
    cpu.cache.ram_l1_43_addr = uint(4294967295);
    cpu.cache.ram_l1_43_val = uint(3735931102);
    cpu.cache.ram_l1_59_addr = uint(4294967295);
    cpu.cache.ram_l1_59_val = uint(3735931102);
    cpu.cache.ram_l1_75_addr = uint(4294967295);
    cpu.cache.ram_l1_75_val = uint(3735931102);
    cpu.cache.ram_l1_12_addr = uint(4294967295);
    cpu.cache.ram_l1_12_val = uint(3735931102);
    cpu.cache.ram_l1_28_addr = uint(4294967295);
    cpu.cache.ram_l1_28_val = uint(3735931102);
    cpu.cache.ram_l1_44_addr = uint(4294967295);
    cpu.cache.ram_l1_44_val = uint(3735931102);
    cpu.cache.ram_l1_60_addr = uint(4294967295);
    cpu.cache.ram_l1_60_val = uint(3735931102);
    cpu.cache.ram_l1_76_addr = uint(4294967295);
    cpu.cache.ram_l1_76_val = uint(3735931102);
    cpu.cache.ram_l1_13_addr = uint(4294967295);
    cpu.cache.ram_l1_13_val = uint(3735931102);
    cpu.cache.ram_l1_29_addr = uint(4294967295);
    cpu.cache.ram_l1_29_val = uint(3735931102);
    cpu.cache.ram_l1_45_addr = uint(4294967295);
    cpu.cache.ram_l1_45_val = uint(3735931102);
    cpu.cache.ram_l1_61_addr = uint(4294967295);
    cpu.cache.ram_l1_61_val = uint(3735931102);
    cpu.cache.ram_l1_77_addr = uint(4294967295);
    cpu.cache.ram_l1_77_val = uint(3735931102);
    cpu.cache.ram_l1_14_addr = uint(4294967295);
    cpu.cache.ram_l1_14_val = uint(3735931102);
    cpu.cache.ram_l1_30_addr = uint(4294967295);
    cpu.cache.ram_l1_30_val = uint(3735931102);
    cpu.cache.ram_l1_46_addr = uint(4294967295);
    cpu.cache.ram_l1_46_val = uint(3735931102);
    cpu.cache.ram_l1_62_addr = uint(4294967295);
    cpu.cache.ram_l1_62_val = uint(3735931102);
    cpu.cache.ram_l1_78_addr = uint(4294967295);
    cpu.cache.ram_l1_78_val = uint(3735931102);
    cpu.cache.ram_l1_15_addr = uint(4294967295);
    cpu.cache.ram_l1_15_val = uint(3735931102);
    cpu.cache.ram_l1_31_addr = uint(4294967295);
    cpu.cache.ram_l1_31_val = uint(3735931102);
    cpu.cache.ram_l1_47_addr = uint(4294967295);
    cpu.cache.ram_l1_47_val = uint(3735931102);
    cpu.cache.ram_l1_63_addr = uint(4294967295);
    cpu.cache.ram_l1_63_val = uint(3735931102);
    cpu.cache.ram_l1_79_addr = uint(4294967295);
    cpu.cache.ram_l1_79_val = uint(3735931102);
    cpu.cache.ram_l1_last_addr = uint(4294967295);
    cpu.cache.ram_l1_last_val = uint(3735931358);
    cpu.csr.privilege = uint(idx_uint4(STATE_TEX[uint2(48, 0)], 2));
    cpu.uart.rbr_thr_ier_iir = uint(idx_uint4(STATE_TEX[uint2(48, 0)], 3));
    cpu.uart.lcr_mcr_lsr_scr = uint(idx_uint4(STATE_TEX[uint2(49, 0)], 0));
    cpu.uart.thre_ip = bool(idx_uint4(STATE_TEX[uint2(49, 0)], 1));
    cpu.uart.interrupting = bool(idx_uint4(STATE_TEX[uint2(49, 0)], 2));
    cpu.uart.input_tag = uint(idx_uint4(STATE_TEX[uint2(49, 0)], 3));
    cpu.clint.msip = bool(idx_uint4(STATE_TEX[uint2(50, 0)], 0));
    cpu.clint.mtimecmp_lo = uint(idx_uint4(STATE_TEX[uint2(50, 0)], 1));
    cpu.clint.mtimecmp_hi = uint(idx_uint4(STATE_TEX[uint2(50, 0)], 2));
    cpu.clint.mtime_lo = uint(idx_uint4(STATE_TEX[uint2(50, 0)], 3));
    cpu.clint.mtime_hi = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 0));
    cpu.uart_buffer.ptr = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 1));
    cpu.uart_buffer.buf0 = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 2));
    cpu.uart_buffer.buf1 = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 3));
    cpu.uart_buffer.buf2 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 0));
    cpu.uart_buffer.buf3 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 1));
    cpu.uart_buffer.buf4 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 2));
    cpu.uart_buffer.buf5 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 3));
    cpu.uart_buffer.buf6 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 0));
    cpu.uart_buffer.buf7 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 1));
    cpu.uart_buffer.buf8 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 2));
    cpu.uart_buffer.buf9 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 3));
    cpu.uart_buffer.buf10 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 0));
    cpu.uart_buffer.buf11 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 1));
    cpu.uart_buffer.buf12 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 2));
    cpu.uart_buffer.buf13 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 3));
    cpu.uart_buffer.buf14 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 0));
    cpu.uart_buffer.buf15 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 1));
    cpu.uart_buffer.buf16 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 2));
    cpu.uart_buffer.buf17 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 3));
    cpu.uart_buffer.buf18 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 0));
    cpu.uart_buffer.buf19 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 1));
    cpu.uart_buffer.buf20 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 2));
    cpu.uart_buffer.buf21 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 3));
    cpu.uart_buffer.buf22 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 0));
    cpu.uart_buffer.buf23 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 1));
    cpu.uart_buffer.buf24 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 2));
    cpu.uart_buffer.buf25 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 3));
    cpu.uart_buffer.buf26 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 0));
    cpu.uart_buffer.buf27 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 1));
    cpu.uart_buffer.buf28 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 2));
    cpu.uart_buffer.buf29 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 3));
    cpu.uart_buffer.buf30 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 0));
    cpu.uart_buffer.buf31 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 1));
    cpu.uart_buffer.buf32 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 2));
    cpu.uart_buffer.buf33 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 3));
    cpu.uart_buffer.buf34 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 0));
    cpu.uart_buffer.buf35 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 1));
    cpu.uart_buffer.buf36 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 2));
    cpu.uart_buffer.buf37 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 3));
    cpu.uart_buffer.buf38 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 0));
    cpu.uart_buffer.buf39 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 1));
    cpu.uart_buffer.buf40 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 2));
    cpu.uart_buffer.buf41 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 3));
    cpu.uart_buffer.buf42 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 0));
    cpu.uart_buffer.buf43 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 1));
    cpu.uart_buffer.buf44 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 2));
    cpu.uart_buffer.buf45 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 3));
    cpu.uart_buffer.buf46 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 0));
    cpu.uart_buffer.buf47 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 1));
    cpu.uart_buffer.buf48 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 2));
    cpu.uart_buffer.buf49 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 3));
    cpu.uart_buffer.buf50 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 0));
    cpu.uart_buffer.buf51 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 1));
    cpu.uart_buffer.buf52 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 2));
    cpu.uart_buffer.buf53 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 3));
    cpu.uart_buffer.buf54 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 0));
    cpu.uart_buffer.buf55 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 1));
    cpu.uart_buffer.buf56 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 2));
    cpu.uart_buffer.buf57 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 3));
    cpu.uart_buffer.buf58 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 0));
    cpu.uart_buffer.buf59 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 1));
    cpu.uart_buffer.buf60 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 2));
    cpu.uart_buffer.buf61 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 3));
    cpu.uart_buffer.buf62 = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 0));
    cpu.uart_buffer.buf63 = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 1));
    cpu.mmu.mode = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 2));
    cpu.mmu.ppn = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 3));
    cpu.stall = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 0));
    cpu.clock = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 1));
    cpu.commits = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 2));
    cpu.xreg0 = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 3));
    cpu.xreg1 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 0));
    cpu.xreg2 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 1));
    cpu.xreg3 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 2));
    cpu.xreg4 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 3));
    cpu.xreg5 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 0));
    cpu.xreg6 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 1));
    cpu.xreg7 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 2));
    cpu.xreg8 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 3));
    cpu.xreg9 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 0));
    cpu.xreg10 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 1));
    cpu.xreg11 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 2));
    cpu.xreg12 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 3));
    cpu.xreg13 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 0));
    cpu.xreg14 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 1));
    cpu.xreg15 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 2));
    cpu.xreg16 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 3));
    cpu.xreg17 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 0));
    cpu.xreg18 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 1));
    cpu.xreg19 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 2));
    cpu.xreg20 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 3));
    cpu.xreg21 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 0));
    cpu.xreg22 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 1));
    cpu.xreg23 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 2));
    cpu.xreg24 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 3));
    cpu.xreg25 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 0));
    cpu.xreg26 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 1));
    cpu.xreg27 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 2));
    cpu.xreg28 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 3));
    cpu.xreg29 = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 0));
    cpu.xreg30 = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 1));
    cpu.xreg31 = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 2));
    cpu.pc = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 3));
    cpu.reservation_en = bool(idx_uint4(STATE_TEX[uint2(77, 0)], 0));
    cpu.reservation_addr = uint(idx_uint4(STATE_TEX[uint2(77, 0)], 1));
    cpu.memop_src_v = uint(idx_uint4(STATE_TEX[uint2(77, 0)], 2));
    cpu.memop_dst_v = uint(idx_uint4(STATE_TEX[uint2(77, 0)], 3));
    cpu.memop_src_p = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 0));
    cpu.memop_dst_p = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 1));
    cpu.memop_n = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 2));
    cpu.stall_count = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 3));
    cpu.trap_count = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 0));
    cpu.debug_do_tick = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 1));
    cpu.debug_last_ins = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 2));
    cpu.debug_last_stall = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 3));
    cpu.debug_arb_0 = uint(idx_uint4(STATE_TEX[uint2(80, 0)], 0));


    if (cpu.stall == STALL_UART && udonUartPtr == cpu.uart_buffer.ptr) {
        cpu.stall = 0;
    }
}

#ifdef PASS_COMMIT
void decode_for_commit() {
    cpu = (cpu_t)0;

    cpu.cache.csr_cache_0_addr = uint(idx_uint4(STATE_TEX[uint2(0, 0)], 0));
    cpu.cache.csr_cache_0_val = uint(idx_uint4(STATE_TEX[uint2(0, 0)], 1));
    cpu.cache.csr_cache_1_addr = uint(idx_uint4(STATE_TEX[uint2(0, 0)], 2));
    cpu.cache.csr_cache_1_val = uint(idx_uint4(STATE_TEX[uint2(0, 0)], 3));
    cpu.cache.csr_cache_2_addr = uint(idx_uint4(STATE_TEX[uint2(1, 0)], 0));
    cpu.cache.csr_cache_2_val = uint(idx_uint4(STATE_TEX[uint2(1, 0)], 1));
    cpu.cache.csr_cache_3_addr = uint(idx_uint4(STATE_TEX[uint2(1, 0)], 2));
    cpu.cache.csr_cache_3_val = uint(idx_uint4(STATE_TEX[uint2(1, 0)], 3));
    cpu.cache.csr_cache_4_addr = uint(idx_uint4(STATE_TEX[uint2(2, 0)], 0));
    cpu.cache.csr_cache_4_val = uint(idx_uint4(STATE_TEX[uint2(2, 0)], 1));
    cpu.cache.csr_cache_5_addr = uint(idx_uint4(STATE_TEX[uint2(2, 0)], 2));
    cpu.cache.csr_cache_5_val = uint(idx_uint4(STATE_TEX[uint2(2, 0)], 3));
    cpu.cache.csr_cache_6_addr = uint(idx_uint4(STATE_TEX[uint2(3, 0)], 0));
    cpu.cache.csr_cache_6_val = uint(idx_uint4(STATE_TEX[uint2(3, 0)], 1));
    cpu.cache.csr_cache_7_addr = uint(idx_uint4(STATE_TEX[uint2(3, 0)], 2));
    cpu.cache.csr_cache_7_val = uint(idx_uint4(STATE_TEX[uint2(3, 0)], 3));
    cpu.cache.csr_cache_8_addr = uint(idx_uint4(STATE_TEX[uint2(4, 0)], 0));
    cpu.cache.csr_cache_8_val = uint(idx_uint4(STATE_TEX[uint2(4, 0)], 1));
    cpu.cache.csr_cache_9_addr = uint(idx_uint4(STATE_TEX[uint2(4, 0)], 2));
    cpu.cache.csr_cache_9_val = uint(idx_uint4(STATE_TEX[uint2(4, 0)], 3));
    cpu.cache.csr_cache_10_addr = uint(idx_uint4(STATE_TEX[uint2(5, 0)], 0));
    cpu.cache.csr_cache_10_val = uint(idx_uint4(STATE_TEX[uint2(5, 0)], 1));
    cpu.cache.csr_cache_11_addr = uint(idx_uint4(STATE_TEX[uint2(5, 0)], 2));
    cpu.cache.csr_cache_11_val = uint(idx_uint4(STATE_TEX[uint2(5, 0)], 3));
    cpu.cache.csr_cache_12_addr = uint(idx_uint4(STATE_TEX[uint2(6, 0)], 0));
    cpu.cache.csr_cache_12_val = uint(idx_uint4(STATE_TEX[uint2(6, 0)], 1));
    cpu.cache.csr_cache_13_addr = uint(idx_uint4(STATE_TEX[uint2(6, 0)], 2));
    cpu.cache.csr_cache_13_val = uint(idx_uint4(STATE_TEX[uint2(6, 0)], 3));
    cpu.cache.csr_cache_14_addr = uint(idx_uint4(STATE_TEX[uint2(7, 0)], 0));
    cpu.cache.csr_cache_14_val = uint(idx_uint4(STATE_TEX[uint2(7, 0)], 1));
    cpu.cache.csr_cache_15_addr = uint(idx_uint4(STATE_TEX[uint2(7, 0)], 2));
    cpu.cache.csr_cache_15_val = uint(idx_uint4(STATE_TEX[uint2(7, 0)], 3));
    cpu.cache.ram_l1_0_addr = uint(idx_uint4(STATE_TEX[uint2(8, 0)], 0));
    cpu.cache.ram_l1_0_val = uint(idx_uint4(STATE_TEX[uint2(8, 0)], 1));
    cpu.cache.ram_l1_16_addr = uint(idx_uint4(STATE_TEX[uint2(8, 0)], 2));
    cpu.cache.ram_l1_16_val = uint(idx_uint4(STATE_TEX[uint2(8, 0)], 3));
    cpu.cache.ram_l1_32_addr = uint(idx_uint4(STATE_TEX[uint2(9, 0)], 0));
    cpu.cache.ram_l1_32_val = uint(idx_uint4(STATE_TEX[uint2(9, 0)], 1));
    cpu.cache.ram_l1_48_addr = uint(idx_uint4(STATE_TEX[uint2(9, 0)], 2));
    cpu.cache.ram_l1_48_val = uint(idx_uint4(STATE_TEX[uint2(9, 0)], 3));
    cpu.cache.ram_l1_64_addr = uint(idx_uint4(STATE_TEX[uint2(10, 0)], 0));
    cpu.cache.ram_l1_64_val = uint(idx_uint4(STATE_TEX[uint2(10, 0)], 1));
    cpu.cache.ram_l1_1_addr = uint(idx_uint4(STATE_TEX[uint2(10, 0)], 2));
    cpu.cache.ram_l1_1_val = uint(idx_uint4(STATE_TEX[uint2(10, 0)], 3));
    cpu.cache.ram_l1_17_addr = uint(idx_uint4(STATE_TEX[uint2(11, 0)], 0));
    cpu.cache.ram_l1_17_val = uint(idx_uint4(STATE_TEX[uint2(11, 0)], 1));
    cpu.cache.ram_l1_33_addr = uint(idx_uint4(STATE_TEX[uint2(11, 0)], 2));
    cpu.cache.ram_l1_33_val = uint(idx_uint4(STATE_TEX[uint2(11, 0)], 3));
    cpu.cache.ram_l1_49_addr = uint(idx_uint4(STATE_TEX[uint2(12, 0)], 0));
    cpu.cache.ram_l1_49_val = uint(idx_uint4(STATE_TEX[uint2(12, 0)], 1));
    cpu.cache.ram_l1_65_addr = uint(idx_uint4(STATE_TEX[uint2(12, 0)], 2));
    cpu.cache.ram_l1_65_val = uint(idx_uint4(STATE_TEX[uint2(12, 0)], 3));
    cpu.cache.ram_l1_2_addr = uint(idx_uint4(STATE_TEX[uint2(13, 0)], 0));
    cpu.cache.ram_l1_2_val = uint(idx_uint4(STATE_TEX[uint2(13, 0)], 1));
    cpu.cache.ram_l1_18_addr = uint(idx_uint4(STATE_TEX[uint2(13, 0)], 2));
    cpu.cache.ram_l1_18_val = uint(idx_uint4(STATE_TEX[uint2(13, 0)], 3));
    cpu.cache.ram_l1_34_addr = uint(idx_uint4(STATE_TEX[uint2(14, 0)], 0));
    cpu.cache.ram_l1_34_val = uint(idx_uint4(STATE_TEX[uint2(14, 0)], 1));
    cpu.cache.ram_l1_50_addr = uint(idx_uint4(STATE_TEX[uint2(14, 0)], 2));
    cpu.cache.ram_l1_50_val = uint(idx_uint4(STATE_TEX[uint2(14, 0)], 3));
    cpu.cache.ram_l1_66_addr = uint(idx_uint4(STATE_TEX[uint2(15, 0)], 0));
    cpu.cache.ram_l1_66_val = uint(idx_uint4(STATE_TEX[uint2(15, 0)], 1));
    cpu.cache.ram_l1_3_addr = uint(idx_uint4(STATE_TEX[uint2(15, 0)], 2));
    cpu.cache.ram_l1_3_val = uint(idx_uint4(STATE_TEX[uint2(15, 0)], 3));
    cpu.cache.ram_l1_19_addr = uint(idx_uint4(STATE_TEX[uint2(16, 0)], 0));
    cpu.cache.ram_l1_19_val = uint(idx_uint4(STATE_TEX[uint2(16, 0)], 1));
    cpu.cache.ram_l1_35_addr = uint(idx_uint4(STATE_TEX[uint2(16, 0)], 2));
    cpu.cache.ram_l1_35_val = uint(idx_uint4(STATE_TEX[uint2(16, 0)], 3));
    cpu.cache.ram_l1_51_addr = uint(idx_uint4(STATE_TEX[uint2(17, 0)], 0));
    cpu.cache.ram_l1_51_val = uint(idx_uint4(STATE_TEX[uint2(17, 0)], 1));
    cpu.cache.ram_l1_67_addr = uint(idx_uint4(STATE_TEX[uint2(17, 0)], 2));
    cpu.cache.ram_l1_67_val = uint(idx_uint4(STATE_TEX[uint2(17, 0)], 3));
    cpu.cache.ram_l1_4_addr = uint(idx_uint4(STATE_TEX[uint2(18, 0)], 0));
    cpu.cache.ram_l1_4_val = uint(idx_uint4(STATE_TEX[uint2(18, 0)], 1));
    cpu.cache.ram_l1_20_addr = uint(idx_uint4(STATE_TEX[uint2(18, 0)], 2));
    cpu.cache.ram_l1_20_val = uint(idx_uint4(STATE_TEX[uint2(18, 0)], 3));
    cpu.cache.ram_l1_36_addr = uint(idx_uint4(STATE_TEX[uint2(19, 0)], 0));
    cpu.cache.ram_l1_36_val = uint(idx_uint4(STATE_TEX[uint2(19, 0)], 1));
    cpu.cache.ram_l1_52_addr = uint(idx_uint4(STATE_TEX[uint2(19, 0)], 2));
    cpu.cache.ram_l1_52_val = uint(idx_uint4(STATE_TEX[uint2(19, 0)], 3));
    cpu.cache.ram_l1_68_addr = uint(idx_uint4(STATE_TEX[uint2(20, 0)], 0));
    cpu.cache.ram_l1_68_val = uint(idx_uint4(STATE_TEX[uint2(20, 0)], 1));
    cpu.cache.ram_l1_5_addr = uint(idx_uint4(STATE_TEX[uint2(20, 0)], 2));
    cpu.cache.ram_l1_5_val = uint(idx_uint4(STATE_TEX[uint2(20, 0)], 3));
    cpu.cache.ram_l1_21_addr = uint(idx_uint4(STATE_TEX[uint2(21, 0)], 0));
    cpu.cache.ram_l1_21_val = uint(idx_uint4(STATE_TEX[uint2(21, 0)], 1));
    cpu.cache.ram_l1_37_addr = uint(idx_uint4(STATE_TEX[uint2(21, 0)], 2));
    cpu.cache.ram_l1_37_val = uint(idx_uint4(STATE_TEX[uint2(21, 0)], 3));
    cpu.cache.ram_l1_53_addr = uint(idx_uint4(STATE_TEX[uint2(22, 0)], 0));
    cpu.cache.ram_l1_53_val = uint(idx_uint4(STATE_TEX[uint2(22, 0)], 1));
    cpu.cache.ram_l1_69_addr = uint(idx_uint4(STATE_TEX[uint2(22, 0)], 2));
    cpu.cache.ram_l1_69_val = uint(idx_uint4(STATE_TEX[uint2(22, 0)], 3));
    cpu.cache.ram_l1_6_addr = uint(idx_uint4(STATE_TEX[uint2(23, 0)], 0));
    cpu.cache.ram_l1_6_val = uint(idx_uint4(STATE_TEX[uint2(23, 0)], 1));
    cpu.cache.ram_l1_22_addr = uint(idx_uint4(STATE_TEX[uint2(23, 0)], 2));
    cpu.cache.ram_l1_22_val = uint(idx_uint4(STATE_TEX[uint2(23, 0)], 3));
    cpu.cache.ram_l1_38_addr = uint(idx_uint4(STATE_TEX[uint2(24, 0)], 0));
    cpu.cache.ram_l1_38_val = uint(idx_uint4(STATE_TEX[uint2(24, 0)], 1));
    cpu.cache.ram_l1_54_addr = uint(idx_uint4(STATE_TEX[uint2(24, 0)], 2));
    cpu.cache.ram_l1_54_val = uint(idx_uint4(STATE_TEX[uint2(24, 0)], 3));
    cpu.cache.ram_l1_70_addr = uint(idx_uint4(STATE_TEX[uint2(25, 0)], 0));
    cpu.cache.ram_l1_70_val = uint(idx_uint4(STATE_TEX[uint2(25, 0)], 1));
    cpu.cache.ram_l1_7_addr = uint(idx_uint4(STATE_TEX[uint2(25, 0)], 2));
    cpu.cache.ram_l1_7_val = uint(idx_uint4(STATE_TEX[uint2(25, 0)], 3));
    cpu.cache.ram_l1_23_addr = uint(idx_uint4(STATE_TEX[uint2(26, 0)], 0));
    cpu.cache.ram_l1_23_val = uint(idx_uint4(STATE_TEX[uint2(26, 0)], 1));
    cpu.cache.ram_l1_39_addr = uint(idx_uint4(STATE_TEX[uint2(26, 0)], 2));
    cpu.cache.ram_l1_39_val = uint(idx_uint4(STATE_TEX[uint2(26, 0)], 3));
    cpu.cache.ram_l1_55_addr = uint(idx_uint4(STATE_TEX[uint2(27, 0)], 0));
    cpu.cache.ram_l1_55_val = uint(idx_uint4(STATE_TEX[uint2(27, 0)], 1));
    cpu.cache.ram_l1_71_addr = uint(idx_uint4(STATE_TEX[uint2(27, 0)], 2));
    cpu.cache.ram_l1_71_val = uint(idx_uint4(STATE_TEX[uint2(27, 0)], 3));
    cpu.cache.ram_l1_8_addr = uint(idx_uint4(STATE_TEX[uint2(28, 0)], 0));
    cpu.cache.ram_l1_8_val = uint(idx_uint4(STATE_TEX[uint2(28, 0)], 1));
    cpu.cache.ram_l1_24_addr = uint(idx_uint4(STATE_TEX[uint2(28, 0)], 2));
    cpu.cache.ram_l1_24_val = uint(idx_uint4(STATE_TEX[uint2(28, 0)], 3));
    cpu.cache.ram_l1_40_addr = uint(idx_uint4(STATE_TEX[uint2(29, 0)], 0));
    cpu.cache.ram_l1_40_val = uint(idx_uint4(STATE_TEX[uint2(29, 0)], 1));
    cpu.cache.ram_l1_56_addr = uint(idx_uint4(STATE_TEX[uint2(29, 0)], 2));
    cpu.cache.ram_l1_56_val = uint(idx_uint4(STATE_TEX[uint2(29, 0)], 3));
    cpu.cache.ram_l1_72_addr = uint(idx_uint4(STATE_TEX[uint2(30, 0)], 0));
    cpu.cache.ram_l1_72_val = uint(idx_uint4(STATE_TEX[uint2(30, 0)], 1));
    cpu.cache.ram_l1_9_addr = uint(idx_uint4(STATE_TEX[uint2(30, 0)], 2));
    cpu.cache.ram_l1_9_val = uint(idx_uint4(STATE_TEX[uint2(30, 0)], 3));
    cpu.cache.ram_l1_25_addr = uint(idx_uint4(STATE_TEX[uint2(31, 0)], 0));
    cpu.cache.ram_l1_25_val = uint(idx_uint4(STATE_TEX[uint2(31, 0)], 1));
    cpu.cache.ram_l1_41_addr = uint(idx_uint4(STATE_TEX[uint2(31, 0)], 2));
    cpu.cache.ram_l1_41_val = uint(idx_uint4(STATE_TEX[uint2(31, 0)], 3));
    cpu.cache.ram_l1_57_addr = uint(idx_uint4(STATE_TEX[uint2(32, 0)], 0));
    cpu.cache.ram_l1_57_val = uint(idx_uint4(STATE_TEX[uint2(32, 0)], 1));
    cpu.cache.ram_l1_73_addr = uint(idx_uint4(STATE_TEX[uint2(32, 0)], 2));
    cpu.cache.ram_l1_73_val = uint(idx_uint4(STATE_TEX[uint2(32, 0)], 3));
    cpu.cache.ram_l1_10_addr = uint(idx_uint4(STATE_TEX[uint2(33, 0)], 0));
    cpu.cache.ram_l1_10_val = uint(idx_uint4(STATE_TEX[uint2(33, 0)], 1));
    cpu.cache.ram_l1_26_addr = uint(idx_uint4(STATE_TEX[uint2(33, 0)], 2));
    cpu.cache.ram_l1_26_val = uint(idx_uint4(STATE_TEX[uint2(33, 0)], 3));
    cpu.cache.ram_l1_42_addr = uint(idx_uint4(STATE_TEX[uint2(34, 0)], 0));
    cpu.cache.ram_l1_42_val = uint(idx_uint4(STATE_TEX[uint2(34, 0)], 1));
    cpu.cache.ram_l1_58_addr = uint(idx_uint4(STATE_TEX[uint2(34, 0)], 2));
    cpu.cache.ram_l1_58_val = uint(idx_uint4(STATE_TEX[uint2(34, 0)], 3));
    cpu.cache.ram_l1_74_addr = uint(idx_uint4(STATE_TEX[uint2(35, 0)], 0));
    cpu.cache.ram_l1_74_val = uint(idx_uint4(STATE_TEX[uint2(35, 0)], 1));
    cpu.cache.ram_l1_11_addr = uint(idx_uint4(STATE_TEX[uint2(35, 0)], 2));
    cpu.cache.ram_l1_11_val = uint(idx_uint4(STATE_TEX[uint2(35, 0)], 3));
    cpu.cache.ram_l1_27_addr = uint(idx_uint4(STATE_TEX[uint2(36, 0)], 0));
    cpu.cache.ram_l1_27_val = uint(idx_uint4(STATE_TEX[uint2(36, 0)], 1));
    cpu.cache.ram_l1_43_addr = uint(idx_uint4(STATE_TEX[uint2(36, 0)], 2));
    cpu.cache.ram_l1_43_val = uint(idx_uint4(STATE_TEX[uint2(36, 0)], 3));
    cpu.cache.ram_l1_59_addr = uint(idx_uint4(STATE_TEX[uint2(37, 0)], 0));
    cpu.cache.ram_l1_59_val = uint(idx_uint4(STATE_TEX[uint2(37, 0)], 1));
    cpu.cache.ram_l1_75_addr = uint(idx_uint4(STATE_TEX[uint2(37, 0)], 2));
    cpu.cache.ram_l1_75_val = uint(idx_uint4(STATE_TEX[uint2(37, 0)], 3));
    cpu.cache.ram_l1_12_addr = uint(idx_uint4(STATE_TEX[uint2(38, 0)], 0));
    cpu.cache.ram_l1_12_val = uint(idx_uint4(STATE_TEX[uint2(38, 0)], 1));
    cpu.cache.ram_l1_28_addr = uint(idx_uint4(STATE_TEX[uint2(38, 0)], 2));
    cpu.cache.ram_l1_28_val = uint(idx_uint4(STATE_TEX[uint2(38, 0)], 3));
    cpu.cache.ram_l1_44_addr = uint(idx_uint4(STATE_TEX[uint2(39, 0)], 0));
    cpu.cache.ram_l1_44_val = uint(idx_uint4(STATE_TEX[uint2(39, 0)], 1));
    cpu.cache.ram_l1_60_addr = uint(idx_uint4(STATE_TEX[uint2(39, 0)], 2));
    cpu.cache.ram_l1_60_val = uint(idx_uint4(STATE_TEX[uint2(39, 0)], 3));
    cpu.cache.ram_l1_76_addr = uint(idx_uint4(STATE_TEX[uint2(40, 0)], 0));
    cpu.cache.ram_l1_76_val = uint(idx_uint4(STATE_TEX[uint2(40, 0)], 1));
    cpu.cache.ram_l1_13_addr = uint(idx_uint4(STATE_TEX[uint2(40, 0)], 2));
    cpu.cache.ram_l1_13_val = uint(idx_uint4(STATE_TEX[uint2(40, 0)], 3));
    cpu.cache.ram_l1_29_addr = uint(idx_uint4(STATE_TEX[uint2(41, 0)], 0));
    cpu.cache.ram_l1_29_val = uint(idx_uint4(STATE_TEX[uint2(41, 0)], 1));
    cpu.cache.ram_l1_45_addr = uint(idx_uint4(STATE_TEX[uint2(41, 0)], 2));
    cpu.cache.ram_l1_45_val = uint(idx_uint4(STATE_TEX[uint2(41, 0)], 3));
    cpu.cache.ram_l1_61_addr = uint(idx_uint4(STATE_TEX[uint2(42, 0)], 0));
    cpu.cache.ram_l1_61_val = uint(idx_uint4(STATE_TEX[uint2(42, 0)], 1));
    cpu.cache.ram_l1_77_addr = uint(idx_uint4(STATE_TEX[uint2(42, 0)], 2));
    cpu.cache.ram_l1_77_val = uint(idx_uint4(STATE_TEX[uint2(42, 0)], 3));
    cpu.cache.ram_l1_14_addr = uint(idx_uint4(STATE_TEX[uint2(43, 0)], 0));
    cpu.cache.ram_l1_14_val = uint(idx_uint4(STATE_TEX[uint2(43, 0)], 1));
    cpu.cache.ram_l1_30_addr = uint(idx_uint4(STATE_TEX[uint2(43, 0)], 2));
    cpu.cache.ram_l1_30_val = uint(idx_uint4(STATE_TEX[uint2(43, 0)], 3));
    cpu.cache.ram_l1_46_addr = uint(idx_uint4(STATE_TEX[uint2(44, 0)], 0));
    cpu.cache.ram_l1_46_val = uint(idx_uint4(STATE_TEX[uint2(44, 0)], 1));
    cpu.cache.ram_l1_62_addr = uint(idx_uint4(STATE_TEX[uint2(44, 0)], 2));
    cpu.cache.ram_l1_62_val = uint(idx_uint4(STATE_TEX[uint2(44, 0)], 3));
    cpu.cache.ram_l1_78_addr = uint(idx_uint4(STATE_TEX[uint2(45, 0)], 0));
    cpu.cache.ram_l1_78_val = uint(idx_uint4(STATE_TEX[uint2(45, 0)], 1));
    cpu.cache.ram_l1_15_addr = uint(idx_uint4(STATE_TEX[uint2(45, 0)], 2));
    cpu.cache.ram_l1_15_val = uint(idx_uint4(STATE_TEX[uint2(45, 0)], 3));
    cpu.cache.ram_l1_31_addr = uint(idx_uint4(STATE_TEX[uint2(46, 0)], 0));
    cpu.cache.ram_l1_31_val = uint(idx_uint4(STATE_TEX[uint2(46, 0)], 1));
    cpu.cache.ram_l1_47_addr = uint(idx_uint4(STATE_TEX[uint2(46, 0)], 2));
    cpu.cache.ram_l1_47_val = uint(idx_uint4(STATE_TEX[uint2(46, 0)], 3));
    cpu.cache.ram_l1_63_addr = uint(idx_uint4(STATE_TEX[uint2(47, 0)], 0));
    cpu.cache.ram_l1_63_val = uint(idx_uint4(STATE_TEX[uint2(47, 0)], 1));
    cpu.cache.ram_l1_79_addr = uint(idx_uint4(STATE_TEX[uint2(47, 0)], 2));
    cpu.cache.ram_l1_79_val = uint(idx_uint4(STATE_TEX[uint2(47, 0)], 3));
    cpu.cache.ram_l1_last_addr = uint(idx_uint4(STATE_TEX[uint2(48, 0)], 0));
    cpu.cache.ram_l1_last_val = uint(idx_uint4(STATE_TEX[uint2(48, 0)], 1));
    cpu.csr.privilege = uint(idx_uint4(STATE_TEX[uint2(48, 0)], 2));
    cpu.uart.rbr_thr_ier_iir = uint(idx_uint4(STATE_TEX[uint2(48, 0)], 3));
    cpu.uart.lcr_mcr_lsr_scr = uint(idx_uint4(STATE_TEX[uint2(49, 0)], 0));
    cpu.uart.thre_ip = bool(idx_uint4(STATE_TEX[uint2(49, 0)], 1));
    cpu.uart.interrupting = bool(idx_uint4(STATE_TEX[uint2(49, 0)], 2));
    cpu.uart.input_tag = uint(idx_uint4(STATE_TEX[uint2(49, 0)], 3));
    cpu.clint.msip = bool(idx_uint4(STATE_TEX[uint2(50, 0)], 0));
    cpu.clint.mtimecmp_lo = uint(idx_uint4(STATE_TEX[uint2(50, 0)], 1));
    cpu.clint.mtimecmp_hi = uint(idx_uint4(STATE_TEX[uint2(50, 0)], 2));
    cpu.clint.mtime_lo = uint(idx_uint4(STATE_TEX[uint2(50, 0)], 3));
    cpu.clint.mtime_hi = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 0));
    cpu.uart_buffer.ptr = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 1));
    cpu.uart_buffer.buf0 = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 2));
    cpu.uart_buffer.buf1 = uint(idx_uint4(STATE_TEX[uint2(51, 0)], 3));
    cpu.uart_buffer.buf2 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 0));
    cpu.uart_buffer.buf3 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 1));
    cpu.uart_buffer.buf4 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 2));
    cpu.uart_buffer.buf5 = uint(idx_uint4(STATE_TEX[uint2(52, 0)], 3));
    cpu.uart_buffer.buf6 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 0));
    cpu.uart_buffer.buf7 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 1));
    cpu.uart_buffer.buf8 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 2));
    cpu.uart_buffer.buf9 = uint(idx_uint4(STATE_TEX[uint2(53, 0)], 3));
    cpu.uart_buffer.buf10 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 0));
    cpu.uart_buffer.buf11 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 1));
    cpu.uart_buffer.buf12 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 2));
    cpu.uart_buffer.buf13 = uint(idx_uint4(STATE_TEX[uint2(54, 0)], 3));
    cpu.uart_buffer.buf14 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 0));
    cpu.uart_buffer.buf15 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 1));
    cpu.uart_buffer.buf16 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 2));
    cpu.uart_buffer.buf17 = uint(idx_uint4(STATE_TEX[uint2(55, 0)], 3));
    cpu.uart_buffer.buf18 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 0));
    cpu.uart_buffer.buf19 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 1));
    cpu.uart_buffer.buf20 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 2));
    cpu.uart_buffer.buf21 = uint(idx_uint4(STATE_TEX[uint2(56, 0)], 3));
    cpu.uart_buffer.buf22 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 0));
    cpu.uart_buffer.buf23 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 1));
    cpu.uart_buffer.buf24 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 2));
    cpu.uart_buffer.buf25 = uint(idx_uint4(STATE_TEX[uint2(57, 0)], 3));
    cpu.uart_buffer.buf26 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 0));
    cpu.uart_buffer.buf27 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 1));
    cpu.uart_buffer.buf28 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 2));
    cpu.uart_buffer.buf29 = uint(idx_uint4(STATE_TEX[uint2(58, 0)], 3));
    cpu.uart_buffer.buf30 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 0));
    cpu.uart_buffer.buf31 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 1));
    cpu.uart_buffer.buf32 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 2));
    cpu.uart_buffer.buf33 = uint(idx_uint4(STATE_TEX[uint2(59, 0)], 3));
    cpu.uart_buffer.buf34 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 0));
    cpu.uart_buffer.buf35 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 1));
    cpu.uart_buffer.buf36 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 2));
    cpu.uart_buffer.buf37 = uint(idx_uint4(STATE_TEX[uint2(60, 0)], 3));
    cpu.uart_buffer.buf38 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 0));
    cpu.uart_buffer.buf39 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 1));
    cpu.uart_buffer.buf40 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 2));
    cpu.uart_buffer.buf41 = uint(idx_uint4(STATE_TEX[uint2(61, 0)], 3));
    cpu.uart_buffer.buf42 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 0));
    cpu.uart_buffer.buf43 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 1));
    cpu.uart_buffer.buf44 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 2));
    cpu.uart_buffer.buf45 = uint(idx_uint4(STATE_TEX[uint2(62, 0)], 3));
    cpu.uart_buffer.buf46 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 0));
    cpu.uart_buffer.buf47 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 1));
    cpu.uart_buffer.buf48 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 2));
    cpu.uart_buffer.buf49 = uint(idx_uint4(STATE_TEX[uint2(63, 0)], 3));
    cpu.uart_buffer.buf50 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 0));
    cpu.uart_buffer.buf51 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 1));
    cpu.uart_buffer.buf52 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 2));
    cpu.uart_buffer.buf53 = uint(idx_uint4(STATE_TEX[uint2(64, 0)], 3));
    cpu.uart_buffer.buf54 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 0));
    cpu.uart_buffer.buf55 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 1));
    cpu.uart_buffer.buf56 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 2));
    cpu.uart_buffer.buf57 = uint(idx_uint4(STATE_TEX[uint2(65, 0)], 3));
    cpu.uart_buffer.buf58 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 0));
    cpu.uart_buffer.buf59 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 1));
    cpu.uart_buffer.buf60 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 2));
    cpu.uart_buffer.buf61 = uint(idx_uint4(STATE_TEX[uint2(66, 0)], 3));
    cpu.uart_buffer.buf62 = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 0));
    cpu.uart_buffer.buf63 = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 1));
    cpu.mmu.mode = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 2));
    cpu.mmu.ppn = uint(idx_uint4(STATE_TEX[uint2(67, 0)], 3));
    cpu.stall = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 0));
    cpu.clock = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 1));
    cpu.commits = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 2));
    cpu.xreg0 = uint(idx_uint4(STATE_TEX[uint2(68, 0)], 3));
    cpu.xreg1 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 0));
    cpu.xreg2 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 1));
    cpu.xreg3 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 2));
    cpu.xreg4 = uint(idx_uint4(STATE_TEX[uint2(69, 0)], 3));
    cpu.xreg5 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 0));
    cpu.xreg6 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 1));
    cpu.xreg7 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 2));
    cpu.xreg8 = uint(idx_uint4(STATE_TEX[uint2(70, 0)], 3));
    cpu.xreg9 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 0));
    cpu.xreg10 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 1));
    cpu.xreg11 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 2));
    cpu.xreg12 = uint(idx_uint4(STATE_TEX[uint2(71, 0)], 3));
    cpu.xreg13 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 0));
    cpu.xreg14 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 1));
    cpu.xreg15 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 2));
    cpu.xreg16 = uint(idx_uint4(STATE_TEX[uint2(72, 0)], 3));
    cpu.xreg17 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 0));
    cpu.xreg18 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 1));
    cpu.xreg19 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 2));
    cpu.xreg20 = uint(idx_uint4(STATE_TEX[uint2(73, 0)], 3));
    cpu.xreg21 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 0));
    cpu.xreg22 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 1));
    cpu.xreg23 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 2));
    cpu.xreg24 = uint(idx_uint4(STATE_TEX[uint2(74, 0)], 3));
    cpu.xreg25 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 0));
    cpu.xreg26 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 1));
    cpu.xreg27 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 2));
    cpu.xreg28 = uint(idx_uint4(STATE_TEX[uint2(75, 0)], 3));
    cpu.xreg29 = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 0));
    cpu.xreg30 = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 1));
    cpu.xreg31 = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 2));
    cpu.pc = uint(idx_uint4(STATE_TEX[uint2(76, 0)], 3));
    cpu.reservation_en = bool(idx_uint4(STATE_TEX[uint2(77, 0)], 0));
    cpu.reservation_addr = uint(idx_uint4(STATE_TEX[uint2(77, 0)], 1));
    cpu.memop_src_v = uint(idx_uint4(STATE_TEX[uint2(77, 0)], 2));
    cpu.memop_dst_v = uint(idx_uint4(STATE_TEX[uint2(77, 0)], 3));
    cpu.memop_src_p = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 0));
    cpu.memop_dst_p = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 1));
    cpu.memop_n = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 2));
    cpu.stall_count = uint(idx_uint4(STATE_TEX[uint2(78, 0)], 3));
    cpu.trap_count = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 0));
    cpu.debug_do_tick = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 1));
    cpu.debug_last_ins = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 2));
    cpu.debug_last_stall = uint(idx_uint4(STATE_TEX[uint2(79, 0)], 3));
    cpu.debug_arb_0 = uint(idx_uint4(STATE_TEX[uint2(80, 0)], 0));

}
#endif

bool pixel_has_state(uint2 pos) {
    
    return pos.y < 0 || (pos.y == 0 && pos.x <= 80);
}



/* void set_debug_arb() { */
/*      */
/*     cpu.debug_arb_0 = cpu.xreg0 ^ */
/*                                 cpu.xreg1 ^ */
/*                                 cpu.xreg2 ^ */
/*                                 cpu.xreg3; */
/*      */
/*     cpu.debug_arb_1 = cpu.xreg4 ^ */
/*                                 cpu.xreg5 ^ */
/*                                 cpu.xreg6 ^ */
/*                                 cpu.xreg7; */
/*      */
/*     cpu.debug_arb_2 = cpu.xreg8 ^ */
/*                                 cpu.xreg9 ^ */
/*                                 cpu.xreg10 ^ */
/*                                 cpu.xreg11; */
/*      */
/*     cpu.debug_arb_3 = cpu.xreg12 ^ */
/*                                 cpu.xreg13 ^ */
/*                                 cpu.xreg14 ^ */
/*                                 cpu.xreg15; */
/*      */
/*     cpu.debug_arb_4 = cpu.xreg16 ^ */
/*                                 cpu.xreg17 ^ */
/*                                 cpu.xreg18 ^ */
/*                                 cpu.xreg19; */
/*      */
/*     cpu.debug_arb_5 = cpu.xreg20 ^ */
/*                                 cpu.xreg21 ^ */
/*                                 cpu.xreg22 ^ */
/*                                 cpu.xreg23; */
/*      */
/*     cpu.debug_arb_6 = cpu.xreg24 ^ */
/*                                 cpu.xreg25 ^ */
/*                                 cpu.xreg26 ^ */
/*                                 cpu.xreg27; */
/*      */
/*     cpu.debug_arb_7 = cpu.xreg28 ^ */
/*                                 cpu.xreg29 ^ */
/*                                 cpu.xreg30 ^ */
/*                                 cpu.xreg31; */
/*      */
/* } */

uint4 encode(uint2 pos) {
    // fallback is passthrough
    uint4 ret = STATE_TEX[pos];

    uint pos_id = pos.x | (pos.y << 16);

    switch (pos_id) {
    case 0:
        ret.r = uint(cpu.cache.csr_cache_0_addr);
        ret.g = uint(cpu.cache.csr_cache_0_val);
        ret.b = uint(cpu.cache.csr_cache_1_addr);
        ret.a = uint(cpu.cache.csr_cache_1_val);
        return ret;
    case 1:
        ret.r = uint(cpu.cache.csr_cache_2_addr);
        ret.g = uint(cpu.cache.csr_cache_2_val);
        ret.b = uint(cpu.cache.csr_cache_3_addr);
        ret.a = uint(cpu.cache.csr_cache_3_val);
        return ret;
    case 10:
        ret.b = uint(cpu.cache.ram_l1_1_addr);
        ret.a = uint(cpu.cache.ram_l1_1_val);
        ret.r = uint(cpu.cache.ram_l1_64_addr);
        ret.g = uint(cpu.cache.ram_l1_64_val);
        return ret;
    case 11:
        ret.r = uint(cpu.cache.ram_l1_17_addr);
        ret.g = uint(cpu.cache.ram_l1_17_val);
        ret.b = uint(cpu.cache.ram_l1_33_addr);
        ret.a = uint(cpu.cache.ram_l1_33_val);
        return ret;
    case 12:
        ret.r = uint(cpu.cache.ram_l1_49_addr);
        ret.g = uint(cpu.cache.ram_l1_49_val);
        ret.b = uint(cpu.cache.ram_l1_65_addr);
        ret.a = uint(cpu.cache.ram_l1_65_val);
        return ret;
    case 13:
        ret.b = uint(cpu.cache.ram_l1_18_addr);
        ret.a = uint(cpu.cache.ram_l1_18_val);
        ret.r = uint(cpu.cache.ram_l1_2_addr);
        ret.g = uint(cpu.cache.ram_l1_2_val);
        return ret;
    case 14:
        ret.r = uint(cpu.cache.ram_l1_34_addr);
        ret.g = uint(cpu.cache.ram_l1_34_val);
        ret.b = uint(cpu.cache.ram_l1_50_addr);
        ret.a = uint(cpu.cache.ram_l1_50_val);
        return ret;
    case 15:
        ret.b = uint(cpu.cache.ram_l1_3_addr);
        ret.a = uint(cpu.cache.ram_l1_3_val);
        ret.r = uint(cpu.cache.ram_l1_66_addr);
        ret.g = uint(cpu.cache.ram_l1_66_val);
        return ret;
    case 16:
        ret.r = uint(cpu.cache.ram_l1_19_addr);
        ret.g = uint(cpu.cache.ram_l1_19_val);
        ret.b = uint(cpu.cache.ram_l1_35_addr);
        ret.a = uint(cpu.cache.ram_l1_35_val);
        return ret;
    case 17:
        ret.r = uint(cpu.cache.ram_l1_51_addr);
        ret.g = uint(cpu.cache.ram_l1_51_val);
        ret.b = uint(cpu.cache.ram_l1_67_addr);
        ret.a = uint(cpu.cache.ram_l1_67_val);
        return ret;
    case 18:
        ret.b = uint(cpu.cache.ram_l1_20_addr);
        ret.a = uint(cpu.cache.ram_l1_20_val);
        ret.r = uint(cpu.cache.ram_l1_4_addr);
        ret.g = uint(cpu.cache.ram_l1_4_val);
        return ret;
    case 19:
        ret.r = uint(cpu.cache.ram_l1_36_addr);
        ret.g = uint(cpu.cache.ram_l1_36_val);
        ret.b = uint(cpu.cache.ram_l1_52_addr);
        ret.a = uint(cpu.cache.ram_l1_52_val);
        return ret;
    case 2:
        ret.r = uint(cpu.cache.csr_cache_4_addr);
        ret.g = uint(cpu.cache.csr_cache_4_val);
        ret.b = uint(cpu.cache.csr_cache_5_addr);
        ret.a = uint(cpu.cache.csr_cache_5_val);
        return ret;
    case 20:
        ret.b = uint(cpu.cache.ram_l1_5_addr);
        ret.a = uint(cpu.cache.ram_l1_5_val);
        ret.r = uint(cpu.cache.ram_l1_68_addr);
        ret.g = uint(cpu.cache.ram_l1_68_val);
        return ret;
    case 21:
        ret.r = uint(cpu.cache.ram_l1_21_addr);
        ret.g = uint(cpu.cache.ram_l1_21_val);
        ret.b = uint(cpu.cache.ram_l1_37_addr);
        ret.a = uint(cpu.cache.ram_l1_37_val);
        return ret;
    case 22:
        ret.r = uint(cpu.cache.ram_l1_53_addr);
        ret.g = uint(cpu.cache.ram_l1_53_val);
        ret.b = uint(cpu.cache.ram_l1_69_addr);
        ret.a = uint(cpu.cache.ram_l1_69_val);
        return ret;
    case 23:
        ret.b = uint(cpu.cache.ram_l1_22_addr);
        ret.a = uint(cpu.cache.ram_l1_22_val);
        ret.r = uint(cpu.cache.ram_l1_6_addr);
        ret.g = uint(cpu.cache.ram_l1_6_val);
        return ret;
    case 24:
        ret.r = uint(cpu.cache.ram_l1_38_addr);
        ret.g = uint(cpu.cache.ram_l1_38_val);
        ret.b = uint(cpu.cache.ram_l1_54_addr);
        ret.a = uint(cpu.cache.ram_l1_54_val);
        return ret;
    case 25:
        ret.r = uint(cpu.cache.ram_l1_70_addr);
        ret.g = uint(cpu.cache.ram_l1_70_val);
        ret.b = uint(cpu.cache.ram_l1_7_addr);
        ret.a = uint(cpu.cache.ram_l1_7_val);
        return ret;
    case 26:
        ret.r = uint(cpu.cache.ram_l1_23_addr);
        ret.g = uint(cpu.cache.ram_l1_23_val);
        ret.b = uint(cpu.cache.ram_l1_39_addr);
        ret.a = uint(cpu.cache.ram_l1_39_val);
        return ret;
    case 27:
        ret.r = uint(cpu.cache.ram_l1_55_addr);
        ret.g = uint(cpu.cache.ram_l1_55_val);
        ret.b = uint(cpu.cache.ram_l1_71_addr);
        ret.a = uint(cpu.cache.ram_l1_71_val);
        return ret;
    case 28:
        ret.b = uint(cpu.cache.ram_l1_24_addr);
        ret.a = uint(cpu.cache.ram_l1_24_val);
        ret.r = uint(cpu.cache.ram_l1_8_addr);
        ret.g = uint(cpu.cache.ram_l1_8_val);
        return ret;
    case 29:
        ret.r = uint(cpu.cache.ram_l1_40_addr);
        ret.g = uint(cpu.cache.ram_l1_40_val);
        ret.b = uint(cpu.cache.ram_l1_56_addr);
        ret.a = uint(cpu.cache.ram_l1_56_val);
        return ret;
    case 3:
        ret.r = uint(cpu.cache.csr_cache_6_addr);
        ret.g = uint(cpu.cache.csr_cache_6_val);
        ret.b = uint(cpu.cache.csr_cache_7_addr);
        ret.a = uint(cpu.cache.csr_cache_7_val);
        return ret;
    case 30:
        ret.r = uint(cpu.cache.ram_l1_72_addr);
        ret.g = uint(cpu.cache.ram_l1_72_val);
        ret.b = uint(cpu.cache.ram_l1_9_addr);
        ret.a = uint(cpu.cache.ram_l1_9_val);
        return ret;
    case 31:
        ret.r = uint(cpu.cache.ram_l1_25_addr);
        ret.g = uint(cpu.cache.ram_l1_25_val);
        ret.b = uint(cpu.cache.ram_l1_41_addr);
        ret.a = uint(cpu.cache.ram_l1_41_val);
        return ret;
    case 32:
        ret.r = uint(cpu.cache.ram_l1_57_addr);
        ret.g = uint(cpu.cache.ram_l1_57_val);
        ret.b = uint(cpu.cache.ram_l1_73_addr);
        ret.a = uint(cpu.cache.ram_l1_73_val);
        return ret;
    case 33:
        ret.r = uint(cpu.cache.ram_l1_10_addr);
        ret.g = uint(cpu.cache.ram_l1_10_val);
        ret.b = uint(cpu.cache.ram_l1_26_addr);
        ret.a = uint(cpu.cache.ram_l1_26_val);
        return ret;
    case 34:
        ret.r = uint(cpu.cache.ram_l1_42_addr);
        ret.g = uint(cpu.cache.ram_l1_42_val);
        ret.b = uint(cpu.cache.ram_l1_58_addr);
        ret.a = uint(cpu.cache.ram_l1_58_val);
        return ret;
    case 35:
        ret.b = uint(cpu.cache.ram_l1_11_addr);
        ret.a = uint(cpu.cache.ram_l1_11_val);
        ret.r = uint(cpu.cache.ram_l1_74_addr);
        ret.g = uint(cpu.cache.ram_l1_74_val);
        return ret;
    case 36:
        ret.r = uint(cpu.cache.ram_l1_27_addr);
        ret.g = uint(cpu.cache.ram_l1_27_val);
        ret.b = uint(cpu.cache.ram_l1_43_addr);
        ret.a = uint(cpu.cache.ram_l1_43_val);
        return ret;
    case 37:
        ret.r = uint(cpu.cache.ram_l1_59_addr);
        ret.g = uint(cpu.cache.ram_l1_59_val);
        ret.b = uint(cpu.cache.ram_l1_75_addr);
        ret.a = uint(cpu.cache.ram_l1_75_val);
        return ret;
    case 38:
        ret.r = uint(cpu.cache.ram_l1_12_addr);
        ret.g = uint(cpu.cache.ram_l1_12_val);
        ret.b = uint(cpu.cache.ram_l1_28_addr);
        ret.a = uint(cpu.cache.ram_l1_28_val);
        return ret;
    case 39:
        ret.r = uint(cpu.cache.ram_l1_44_addr);
        ret.g = uint(cpu.cache.ram_l1_44_val);
        ret.b = uint(cpu.cache.ram_l1_60_addr);
        ret.a = uint(cpu.cache.ram_l1_60_val);
        return ret;
    case 4:
        ret.r = uint(cpu.cache.csr_cache_8_addr);
        ret.g = uint(cpu.cache.csr_cache_8_val);
        ret.b = uint(cpu.cache.csr_cache_9_addr);
        ret.a = uint(cpu.cache.csr_cache_9_val);
        return ret;
    case 40:
        ret.b = uint(cpu.cache.ram_l1_13_addr);
        ret.a = uint(cpu.cache.ram_l1_13_val);
        ret.r = uint(cpu.cache.ram_l1_76_addr);
        ret.g = uint(cpu.cache.ram_l1_76_val);
        return ret;
    case 41:
        ret.r = uint(cpu.cache.ram_l1_29_addr);
        ret.g = uint(cpu.cache.ram_l1_29_val);
        ret.b = uint(cpu.cache.ram_l1_45_addr);
        ret.a = uint(cpu.cache.ram_l1_45_val);
        return ret;
    case 42:
        ret.r = uint(cpu.cache.ram_l1_61_addr);
        ret.g = uint(cpu.cache.ram_l1_61_val);
        ret.b = uint(cpu.cache.ram_l1_77_addr);
        ret.a = uint(cpu.cache.ram_l1_77_val);
        return ret;
    case 43:
        ret.r = uint(cpu.cache.ram_l1_14_addr);
        ret.g = uint(cpu.cache.ram_l1_14_val);
        ret.b = uint(cpu.cache.ram_l1_30_addr);
        ret.a = uint(cpu.cache.ram_l1_30_val);
        return ret;
    case 44:
        ret.r = uint(cpu.cache.ram_l1_46_addr);
        ret.g = uint(cpu.cache.ram_l1_46_val);
        ret.b = uint(cpu.cache.ram_l1_62_addr);
        ret.a = uint(cpu.cache.ram_l1_62_val);
        return ret;
    case 45:
        ret.b = uint(cpu.cache.ram_l1_15_addr);
        ret.a = uint(cpu.cache.ram_l1_15_val);
        ret.r = uint(cpu.cache.ram_l1_78_addr);
        ret.g = uint(cpu.cache.ram_l1_78_val);
        return ret;
    case 46:
        ret.r = uint(cpu.cache.ram_l1_31_addr);
        ret.g = uint(cpu.cache.ram_l1_31_val);
        ret.b = uint(cpu.cache.ram_l1_47_addr);
        ret.a = uint(cpu.cache.ram_l1_47_val);
        return ret;
    case 47:
        ret.r = uint(cpu.cache.ram_l1_63_addr);
        ret.g = uint(cpu.cache.ram_l1_63_val);
        ret.b = uint(cpu.cache.ram_l1_79_addr);
        ret.a = uint(cpu.cache.ram_l1_79_val);
        return ret;
    case 48:
        ret.r = uint(cpu.cache.ram_l1_last_addr);
        ret.g = uint(cpu.cache.ram_l1_last_val);
        ret.b = uint(cpu.csr.privilege);
        ret.a = uint(cpu.uart.rbr_thr_ier_iir);
        return ret;
    case 49:
        ret.a = uint(cpu.uart.input_tag);
        ret.b = uint(cpu.uart.interrupting);
        ret.r = uint(cpu.uart.lcr_mcr_lsr_scr);
        ret.g = uint(cpu.uart.thre_ip);
        return ret;
    case 5:
        ret.r = uint(cpu.cache.csr_cache_10_addr);
        ret.g = uint(cpu.cache.csr_cache_10_val);
        ret.b = uint(cpu.cache.csr_cache_11_addr);
        ret.a = uint(cpu.cache.csr_cache_11_val);
        return ret;
    case 50:
        ret.r = uint(cpu.clint.msip);
        ret.a = uint(cpu.clint.mtime_lo);
        ret.b = uint(cpu.clint.mtimecmp_hi);
        ret.g = uint(cpu.clint.mtimecmp_lo);
        return ret;
    case 51:
        ret.r = uint(cpu.clint.mtime_hi);
        ret.b = uint(cpu.uart_buffer.buf0);
        ret.a = uint(cpu.uart_buffer.buf1);
        ret.g = uint(cpu.uart_buffer.ptr);
        return ret;
    case 52:
        ret.r = uint(cpu.uart_buffer.buf2);
        ret.g = uint(cpu.uart_buffer.buf3);
        ret.b = uint(cpu.uart_buffer.buf4);
        ret.a = uint(cpu.uart_buffer.buf5);
        return ret;
    case 53:
        ret.r = uint(cpu.uart_buffer.buf6);
        ret.g = uint(cpu.uart_buffer.buf7);
        ret.b = uint(cpu.uart_buffer.buf8);
        ret.a = uint(cpu.uart_buffer.buf9);
        return ret;
    case 54:
        ret.r = uint(cpu.uart_buffer.buf10);
        ret.g = uint(cpu.uart_buffer.buf11);
        ret.b = uint(cpu.uart_buffer.buf12);
        ret.a = uint(cpu.uart_buffer.buf13);
        return ret;
    case 55:
        ret.r = uint(cpu.uart_buffer.buf14);
        ret.g = uint(cpu.uart_buffer.buf15);
        ret.b = uint(cpu.uart_buffer.buf16);
        ret.a = uint(cpu.uart_buffer.buf17);
        return ret;
    case 56:
        ret.r = uint(cpu.uart_buffer.buf18);
        ret.g = uint(cpu.uart_buffer.buf19);
        ret.b = uint(cpu.uart_buffer.buf20);
        ret.a = uint(cpu.uart_buffer.buf21);
        return ret;
    case 57:
        ret.r = uint(cpu.uart_buffer.buf22);
        ret.g = uint(cpu.uart_buffer.buf23);
        ret.b = uint(cpu.uart_buffer.buf24);
        ret.a = uint(cpu.uart_buffer.buf25);
        return ret;
    case 58:
        ret.r = uint(cpu.uart_buffer.buf26);
        ret.g = uint(cpu.uart_buffer.buf27);
        ret.b = uint(cpu.uart_buffer.buf28);
        ret.a = uint(cpu.uart_buffer.buf29);
        return ret;
    case 59:
        ret.r = uint(cpu.uart_buffer.buf30);
        ret.g = uint(cpu.uart_buffer.buf31);
        ret.b = uint(cpu.uart_buffer.buf32);
        ret.a = uint(cpu.uart_buffer.buf33);
        return ret;
    case 6:
        ret.r = uint(cpu.cache.csr_cache_12_addr);
        ret.g = uint(cpu.cache.csr_cache_12_val);
        ret.b = uint(cpu.cache.csr_cache_13_addr);
        ret.a = uint(cpu.cache.csr_cache_13_val);
        return ret;
    case 60:
        ret.r = uint(cpu.uart_buffer.buf34);
        ret.g = uint(cpu.uart_buffer.buf35);
        ret.b = uint(cpu.uart_buffer.buf36);
        ret.a = uint(cpu.uart_buffer.buf37);
        return ret;
    case 61:
        ret.r = uint(cpu.uart_buffer.buf38);
        ret.g = uint(cpu.uart_buffer.buf39);
        ret.b = uint(cpu.uart_buffer.buf40);
        ret.a = uint(cpu.uart_buffer.buf41);
        return ret;
    case 62:
        ret.r = uint(cpu.uart_buffer.buf42);
        ret.g = uint(cpu.uart_buffer.buf43);
        ret.b = uint(cpu.uart_buffer.buf44);
        ret.a = uint(cpu.uart_buffer.buf45);
        return ret;
    case 63:
        ret.r = uint(cpu.uart_buffer.buf46);
        ret.g = uint(cpu.uart_buffer.buf47);
        ret.b = uint(cpu.uart_buffer.buf48);
        ret.a = uint(cpu.uart_buffer.buf49);
        return ret;
    case 64:
        ret.r = uint(cpu.uart_buffer.buf50);
        ret.g = uint(cpu.uart_buffer.buf51);
        ret.b = uint(cpu.uart_buffer.buf52);
        ret.a = uint(cpu.uart_buffer.buf53);
        return ret;
    case 65:
        ret.r = uint(cpu.uart_buffer.buf54);
        ret.g = uint(cpu.uart_buffer.buf55);
        ret.b = uint(cpu.uart_buffer.buf56);
        ret.a = uint(cpu.uart_buffer.buf57);
        return ret;
    case 66:
        ret.r = uint(cpu.uart_buffer.buf58);
        ret.g = uint(cpu.uart_buffer.buf59);
        ret.b = uint(cpu.uart_buffer.buf60);
        ret.a = uint(cpu.uart_buffer.buf61);
        return ret;
    case 67:
        ret.b = uint(cpu.mmu.mode);
        ret.a = uint(cpu.mmu.ppn);
        ret.r = uint(cpu.uart_buffer.buf62);
        ret.g = uint(cpu.uart_buffer.buf63);
        return ret;
    case 68:
        ret.g = uint(cpu.clock);
        ret.b = uint(cpu.commits);
        ret.r = uint(cpu.stall == STALL_CSR_CACHE ? 0 : (cpu.stall == STALL_MEM_CACHE_L1 ? 0 : cpu.stall));
        ret.a = uint(cpu.xreg0);
        return ret;
    case 69:
        ret.r = uint(cpu.xreg1);
        ret.g = uint(cpu.xreg2);
        ret.b = uint(cpu.xreg3);
        ret.a = uint(cpu.xreg4);
        return ret;
    case 7:
        ret.r = uint(cpu.cache.csr_cache_14_addr);
        ret.g = uint(cpu.cache.csr_cache_14_val);
        ret.b = uint(cpu.cache.csr_cache_15_addr);
        ret.a = uint(cpu.cache.csr_cache_15_val);
        return ret;
    case 70:
        ret.r = uint(cpu.xreg5);
        ret.g = uint(cpu.xreg6);
        ret.b = uint(cpu.xreg7);
        ret.a = uint(cpu.xreg8);
        return ret;
    case 71:
        ret.g = uint(cpu.xreg10);
        ret.b = uint(cpu.xreg11);
        ret.a = uint(cpu.xreg12);
        ret.r = uint(cpu.xreg9);
        return ret;
    case 72:
        ret.r = uint(cpu.xreg13);
        ret.g = uint(cpu.xreg14);
        ret.b = uint(cpu.xreg15);
        ret.a = uint(cpu.xreg16);
        return ret;
    case 73:
        ret.r = uint(cpu.xreg17);
        ret.g = uint(cpu.xreg18);
        ret.b = uint(cpu.xreg19);
        ret.a = uint(cpu.xreg20);
        return ret;
    case 74:
        ret.r = uint(cpu.xreg21);
        ret.g = uint(cpu.xreg22);
        ret.b = uint(cpu.xreg23);
        ret.a = uint(cpu.xreg24);
        return ret;
    case 75:
        ret.r = uint(cpu.xreg25);
        ret.g = uint(cpu.xreg26);
        ret.b = uint(cpu.xreg27);
        ret.a = uint(cpu.xreg28);
        return ret;
    case 76:
        ret.a = uint(cpu.pc);
        ret.r = uint(cpu.xreg29);
        ret.g = uint(cpu.xreg30);
        ret.b = uint(cpu.xreg31);
        return ret;
    case 77:
        ret.a = uint(cpu.memop_dst_v);
        ret.b = uint(cpu.memop_src_v);
        ret.g = uint(cpu.reservation_addr);
        ret.r = uint(cpu.reservation_en);
        return ret;
    case 78:
        ret.g = uint(cpu.memop_dst_p);
        ret.b = uint(cpu.memop_n);
        ret.r = uint(cpu.memop_src_p);
        ret.a = uint(cpu.stall_count);
        return ret;
    case 79:
        ret.g = uint(cpu.debug_do_tick);
        ret.b = uint(cpu.debug_last_ins);
        ret.a = uint(cpu.stall);
        ret.r = uint(cpu.trap_count);
        return ret;
    case 8:
        ret.r = uint(cpu.cache.ram_l1_0_addr);
        ret.g = uint(cpu.cache.ram_l1_0_val);
        ret.b = uint(cpu.cache.ram_l1_16_addr);
        ret.a = uint(cpu.cache.ram_l1_16_val);
        return ret;
    case 80:
        ret.r = uint(cpu.debug_arb_0);
        return ret;
    case 9:
        ret.r = uint(cpu.cache.ram_l1_32_addr);
        ret.g = uint(cpu.cache.ram_l1_32_val);
        ret.b = uint(cpu.cache.ram_l1_48_addr);
        ret.a = uint(cpu.cache.ram_l1_48_val);
        return ret;

    }

    return ret;
}

uint tex_get_csr(uint addr) {
    uint lin = (addr >> 2) + 324;
    uint idx = addr & 0x3;
    return idx_uint4(STATE_TEX[uint2(lin % 128, lin / 128)], idx);
}

#define RAM_ADDR(lin) uint2(lin % 2048, 128 + (lin / 2048))
#define RAM_MAX (2048 * (2048 - 128) * 4 * 4)


// Memory operations (should be in mem.h but cyclic dependencies...)

// Basic bloom filter to slightly optimize memory caching
#ifdef PASS_TICK
static uint mem_cache_bloom = 0;
#else
static uint mem_cache_bloom = 0xffffffff;
#endif

[noinline] // I'm pretty sure this does nothing, but see it as a prayer to the compiler gods
uint mem_get_cached_or_tex(uint addr) {
    // query L1 cache
    if ((addr & mem_cache_bloom) != addr) { /* not cached */ }
    else {
        [forcecase]
        switch (RAM_L1_TAG(addr)) {
case 0:
     if (cpu.cache.ram_l1_0_addr == addr) { return cpu.cache.ram_l1_0_val; }
else if (cpu.cache.ram_l1_16_addr == addr) { return cpu.cache.ram_l1_16_val; }
else if (cpu.cache.ram_l1_32_addr == addr) { return cpu.cache.ram_l1_32_val; }
else if (cpu.cache.ram_l1_48_addr == addr) { return cpu.cache.ram_l1_48_val; }
else if (cpu.cache.ram_l1_64_addr == addr) { return cpu.cache.ram_l1_64_val; }
break;
case 1:
     if (cpu.cache.ram_l1_1_addr == addr) { return cpu.cache.ram_l1_1_val; }
else if (cpu.cache.ram_l1_17_addr == addr) { return cpu.cache.ram_l1_17_val; }
else if (cpu.cache.ram_l1_33_addr == addr) { return cpu.cache.ram_l1_33_val; }
else if (cpu.cache.ram_l1_49_addr == addr) { return cpu.cache.ram_l1_49_val; }
else if (cpu.cache.ram_l1_65_addr == addr) { return cpu.cache.ram_l1_65_val; }
break;
case 2:
     if (cpu.cache.ram_l1_2_addr == addr) { return cpu.cache.ram_l1_2_val; }
else if (cpu.cache.ram_l1_18_addr == addr) { return cpu.cache.ram_l1_18_val; }
else if (cpu.cache.ram_l1_34_addr == addr) { return cpu.cache.ram_l1_34_val; }
else if (cpu.cache.ram_l1_50_addr == addr) { return cpu.cache.ram_l1_50_val; }
else if (cpu.cache.ram_l1_66_addr == addr) { return cpu.cache.ram_l1_66_val; }
break;
case 3:
     if (cpu.cache.ram_l1_3_addr == addr) { return cpu.cache.ram_l1_3_val; }
else if (cpu.cache.ram_l1_19_addr == addr) { return cpu.cache.ram_l1_19_val; }
else if (cpu.cache.ram_l1_35_addr == addr) { return cpu.cache.ram_l1_35_val; }
else if (cpu.cache.ram_l1_51_addr == addr) { return cpu.cache.ram_l1_51_val; }
else if (cpu.cache.ram_l1_67_addr == addr) { return cpu.cache.ram_l1_67_val; }
break;
case 4:
     if (cpu.cache.ram_l1_4_addr == addr) { return cpu.cache.ram_l1_4_val; }
else if (cpu.cache.ram_l1_20_addr == addr) { return cpu.cache.ram_l1_20_val; }
else if (cpu.cache.ram_l1_36_addr == addr) { return cpu.cache.ram_l1_36_val; }
else if (cpu.cache.ram_l1_52_addr == addr) { return cpu.cache.ram_l1_52_val; }
else if (cpu.cache.ram_l1_68_addr == addr) { return cpu.cache.ram_l1_68_val; }
break;
case 5:
     if (cpu.cache.ram_l1_5_addr == addr) { return cpu.cache.ram_l1_5_val; }
else if (cpu.cache.ram_l1_21_addr == addr) { return cpu.cache.ram_l1_21_val; }
else if (cpu.cache.ram_l1_37_addr == addr) { return cpu.cache.ram_l1_37_val; }
else if (cpu.cache.ram_l1_53_addr == addr) { return cpu.cache.ram_l1_53_val; }
else if (cpu.cache.ram_l1_69_addr == addr) { return cpu.cache.ram_l1_69_val; }
break;
case 6:
     if (cpu.cache.ram_l1_6_addr == addr) { return cpu.cache.ram_l1_6_val; }
else if (cpu.cache.ram_l1_22_addr == addr) { return cpu.cache.ram_l1_22_val; }
else if (cpu.cache.ram_l1_38_addr == addr) { return cpu.cache.ram_l1_38_val; }
else if (cpu.cache.ram_l1_54_addr == addr) { return cpu.cache.ram_l1_54_val; }
else if (cpu.cache.ram_l1_70_addr == addr) { return cpu.cache.ram_l1_70_val; }
break;
case 7:
     if (cpu.cache.ram_l1_7_addr == addr) { return cpu.cache.ram_l1_7_val; }
else if (cpu.cache.ram_l1_23_addr == addr) { return cpu.cache.ram_l1_23_val; }
else if (cpu.cache.ram_l1_39_addr == addr) { return cpu.cache.ram_l1_39_val; }
else if (cpu.cache.ram_l1_55_addr == addr) { return cpu.cache.ram_l1_55_val; }
else if (cpu.cache.ram_l1_71_addr == addr) { return cpu.cache.ram_l1_71_val; }
break;
case 8:
     if (cpu.cache.ram_l1_8_addr == addr) { return cpu.cache.ram_l1_8_val; }
else if (cpu.cache.ram_l1_24_addr == addr) { return cpu.cache.ram_l1_24_val; }
else if (cpu.cache.ram_l1_40_addr == addr) { return cpu.cache.ram_l1_40_val; }
else if (cpu.cache.ram_l1_56_addr == addr) { return cpu.cache.ram_l1_56_val; }
else if (cpu.cache.ram_l1_72_addr == addr) { return cpu.cache.ram_l1_72_val; }
break;
case 9:
     if (cpu.cache.ram_l1_9_addr == addr) { return cpu.cache.ram_l1_9_val; }
else if (cpu.cache.ram_l1_25_addr == addr) { return cpu.cache.ram_l1_25_val; }
else if (cpu.cache.ram_l1_41_addr == addr) { return cpu.cache.ram_l1_41_val; }
else if (cpu.cache.ram_l1_57_addr == addr) { return cpu.cache.ram_l1_57_val; }
else if (cpu.cache.ram_l1_73_addr == addr) { return cpu.cache.ram_l1_73_val; }
break;
case 10:
     if (cpu.cache.ram_l1_10_addr == addr) { return cpu.cache.ram_l1_10_val; }
else if (cpu.cache.ram_l1_26_addr == addr) { return cpu.cache.ram_l1_26_val; }
else if (cpu.cache.ram_l1_42_addr == addr) { return cpu.cache.ram_l1_42_val; }
else if (cpu.cache.ram_l1_58_addr == addr) { return cpu.cache.ram_l1_58_val; }
else if (cpu.cache.ram_l1_74_addr == addr) { return cpu.cache.ram_l1_74_val; }
break;
case 11:
     if (cpu.cache.ram_l1_11_addr == addr) { return cpu.cache.ram_l1_11_val; }
else if (cpu.cache.ram_l1_27_addr == addr) { return cpu.cache.ram_l1_27_val; }
else if (cpu.cache.ram_l1_43_addr == addr) { return cpu.cache.ram_l1_43_val; }
else if (cpu.cache.ram_l1_59_addr == addr) { return cpu.cache.ram_l1_59_val; }
else if (cpu.cache.ram_l1_75_addr == addr) { return cpu.cache.ram_l1_75_val; }
break;
case 12:
     if (cpu.cache.ram_l1_12_addr == addr) { return cpu.cache.ram_l1_12_val; }
else if (cpu.cache.ram_l1_28_addr == addr) { return cpu.cache.ram_l1_28_val; }
else if (cpu.cache.ram_l1_44_addr == addr) { return cpu.cache.ram_l1_44_val; }
else if (cpu.cache.ram_l1_60_addr == addr) { return cpu.cache.ram_l1_60_val; }
else if (cpu.cache.ram_l1_76_addr == addr) { return cpu.cache.ram_l1_76_val; }
break;
case 13:
     if (cpu.cache.ram_l1_13_addr == addr) { return cpu.cache.ram_l1_13_val; }
else if (cpu.cache.ram_l1_29_addr == addr) { return cpu.cache.ram_l1_29_val; }
else if (cpu.cache.ram_l1_45_addr == addr) { return cpu.cache.ram_l1_45_val; }
else if (cpu.cache.ram_l1_61_addr == addr) { return cpu.cache.ram_l1_61_val; }
else if (cpu.cache.ram_l1_77_addr == addr) { return cpu.cache.ram_l1_77_val; }
break;
case 14:
     if (cpu.cache.ram_l1_14_addr == addr) { return cpu.cache.ram_l1_14_val; }
else if (cpu.cache.ram_l1_30_addr == addr) { return cpu.cache.ram_l1_30_val; }
else if (cpu.cache.ram_l1_46_addr == addr) { return cpu.cache.ram_l1_46_val; }
else if (cpu.cache.ram_l1_62_addr == addr) { return cpu.cache.ram_l1_62_val; }
else if (cpu.cache.ram_l1_78_addr == addr) { return cpu.cache.ram_l1_78_val; }
break;
case 15:
     if (cpu.cache.ram_l1_15_addr == addr) { return cpu.cache.ram_l1_15_val; }
else if (cpu.cache.ram_l1_31_addr == addr) { return cpu.cache.ram_l1_31_val; }
else if (cpu.cache.ram_l1_47_addr == addr) { return cpu.cache.ram_l1_47_val; }
else if (cpu.cache.ram_l1_63_addr == addr) { return cpu.cache.ram_l1_63_val; }
else if (cpu.cache.ram_l1_79_addr == addr) { return cpu.cache.ram_l1_79_val; }
break;

        }

        if (cpu.cache.ram_l1_last_addr == addr) {
            return cpu.cache.ram_l1_last_val;
        }
    }

    uint idx = (addr >> 2) & 0x3;
    addr >>= 4;

    uint4 raw = STATE_TEX[RAM_ADDR(addr)];
    return idx_uint4(raw, idx);
}


#ifdef PASS_COMMIT
uint4 commit(uint2 pos) {
    if (pos.y < 128 && pos.x >= 128) {
        return (uint4)0;
    }

    // fallback is passthrough
    uint4 ret = STATE_TEX[pos];

    uint pos_id = pos.x | (pos.y << 16);

    // increment commits
    if (!_Init && pos_id == 68) {
        ++ret.b;
    }

    // clear stall
    if (pos_id == 68) {
        [flatten]
        switch (ret.r) {
            case STALL_MEM_CACHE_L2:
                ret.r = 0;
                break;
            case STALL_FENCE:
                ret.r = 0;
                break;
            case STALL_MEMOP_COPY: // will be handled now, so we can unset
                ret.r = 0;
                break;
        }
    }

    uint s_lin = pos.x + pos.y * 128;

    // CSR area
    if (s_lin >= 324 && s_lin < 1348) {
        uint addr = s_lin - 324;
        addr <<= 2;
        if      (cpu.cache.csr_cache_0_addr == addr + 0) { ret.x = cpu.cache.csr_cache_0_val; }
        else if (cpu.cache.csr_cache_0_addr == addr + 1) { ret.y = cpu.cache.csr_cache_0_val; }
        else if (cpu.cache.csr_cache_0_addr == addr + 2) { ret.z = cpu.cache.csr_cache_0_val; }
        else if (cpu.cache.csr_cache_0_addr == addr + 3) { ret.w = cpu.cache.csr_cache_0_val; }
        if      (cpu.cache.csr_cache_1_addr == addr + 0) { ret.x = cpu.cache.csr_cache_1_val; }
        else if (cpu.cache.csr_cache_1_addr == addr + 1) { ret.y = cpu.cache.csr_cache_1_val; }
        else if (cpu.cache.csr_cache_1_addr == addr + 2) { ret.z = cpu.cache.csr_cache_1_val; }
        else if (cpu.cache.csr_cache_1_addr == addr + 3) { ret.w = cpu.cache.csr_cache_1_val; }
        if      (cpu.cache.csr_cache_2_addr == addr + 0) { ret.x = cpu.cache.csr_cache_2_val; }
        else if (cpu.cache.csr_cache_2_addr == addr + 1) { ret.y = cpu.cache.csr_cache_2_val; }
        else if (cpu.cache.csr_cache_2_addr == addr + 2) { ret.z = cpu.cache.csr_cache_2_val; }
        else if (cpu.cache.csr_cache_2_addr == addr + 3) { ret.w = cpu.cache.csr_cache_2_val; }
        if      (cpu.cache.csr_cache_3_addr == addr + 0) { ret.x = cpu.cache.csr_cache_3_val; }
        else if (cpu.cache.csr_cache_3_addr == addr + 1) { ret.y = cpu.cache.csr_cache_3_val; }
        else if (cpu.cache.csr_cache_3_addr == addr + 2) { ret.z = cpu.cache.csr_cache_3_val; }
        else if (cpu.cache.csr_cache_3_addr == addr + 3) { ret.w = cpu.cache.csr_cache_3_val; }
        if      (cpu.cache.csr_cache_4_addr == addr + 0) { ret.x = cpu.cache.csr_cache_4_val; }
        else if (cpu.cache.csr_cache_4_addr == addr + 1) { ret.y = cpu.cache.csr_cache_4_val; }
        else if (cpu.cache.csr_cache_4_addr == addr + 2) { ret.z = cpu.cache.csr_cache_4_val; }
        else if (cpu.cache.csr_cache_4_addr == addr + 3) { ret.w = cpu.cache.csr_cache_4_val; }
        if      (cpu.cache.csr_cache_5_addr == addr + 0) { ret.x = cpu.cache.csr_cache_5_val; }
        else if (cpu.cache.csr_cache_5_addr == addr + 1) { ret.y = cpu.cache.csr_cache_5_val; }
        else if (cpu.cache.csr_cache_5_addr == addr + 2) { ret.z = cpu.cache.csr_cache_5_val; }
        else if (cpu.cache.csr_cache_5_addr == addr + 3) { ret.w = cpu.cache.csr_cache_5_val; }
        if      (cpu.cache.csr_cache_6_addr == addr + 0) { ret.x = cpu.cache.csr_cache_6_val; }
        else if (cpu.cache.csr_cache_6_addr == addr + 1) { ret.y = cpu.cache.csr_cache_6_val; }
        else if (cpu.cache.csr_cache_6_addr == addr + 2) { ret.z = cpu.cache.csr_cache_6_val; }
        else if (cpu.cache.csr_cache_6_addr == addr + 3) { ret.w = cpu.cache.csr_cache_6_val; }
        if      (cpu.cache.csr_cache_7_addr == addr + 0) { ret.x = cpu.cache.csr_cache_7_val; }
        else if (cpu.cache.csr_cache_7_addr == addr + 1) { ret.y = cpu.cache.csr_cache_7_val; }
        else if (cpu.cache.csr_cache_7_addr == addr + 2) { ret.z = cpu.cache.csr_cache_7_val; }
        else if (cpu.cache.csr_cache_7_addr == addr + 3) { ret.w = cpu.cache.csr_cache_7_val; }
        if      (cpu.cache.csr_cache_8_addr == addr + 0) { ret.x = cpu.cache.csr_cache_8_val; }
        else if (cpu.cache.csr_cache_8_addr == addr + 1) { ret.y = cpu.cache.csr_cache_8_val; }
        else if (cpu.cache.csr_cache_8_addr == addr + 2) { ret.z = cpu.cache.csr_cache_8_val; }
        else if (cpu.cache.csr_cache_8_addr == addr + 3) { ret.w = cpu.cache.csr_cache_8_val; }
        if      (cpu.cache.csr_cache_9_addr == addr + 0) { ret.x = cpu.cache.csr_cache_9_val; }
        else if (cpu.cache.csr_cache_9_addr == addr + 1) { ret.y = cpu.cache.csr_cache_9_val; }
        else if (cpu.cache.csr_cache_9_addr == addr + 2) { ret.z = cpu.cache.csr_cache_9_val; }
        else if (cpu.cache.csr_cache_9_addr == addr + 3) { ret.w = cpu.cache.csr_cache_9_val; }
        if      (cpu.cache.csr_cache_10_addr == addr + 0) { ret.x = cpu.cache.csr_cache_10_val; }
        else if (cpu.cache.csr_cache_10_addr == addr + 1) { ret.y = cpu.cache.csr_cache_10_val; }
        else if (cpu.cache.csr_cache_10_addr == addr + 2) { ret.z = cpu.cache.csr_cache_10_val; }
        else if (cpu.cache.csr_cache_10_addr == addr + 3) { ret.w = cpu.cache.csr_cache_10_val; }
        if      (cpu.cache.csr_cache_11_addr == addr + 0) { ret.x = cpu.cache.csr_cache_11_val; }
        else if (cpu.cache.csr_cache_11_addr == addr + 1) { ret.y = cpu.cache.csr_cache_11_val; }
        else if (cpu.cache.csr_cache_11_addr == addr + 2) { ret.z = cpu.cache.csr_cache_11_val; }
        else if (cpu.cache.csr_cache_11_addr == addr + 3) { ret.w = cpu.cache.csr_cache_11_val; }
        if      (cpu.cache.csr_cache_12_addr == addr + 0) { ret.x = cpu.cache.csr_cache_12_val; }
        else if (cpu.cache.csr_cache_12_addr == addr + 1) { ret.y = cpu.cache.csr_cache_12_val; }
        else if (cpu.cache.csr_cache_12_addr == addr + 2) { ret.z = cpu.cache.csr_cache_12_val; }
        else if (cpu.cache.csr_cache_12_addr == addr + 3) { ret.w = cpu.cache.csr_cache_12_val; }
        if      (cpu.cache.csr_cache_13_addr == addr + 0) { ret.x = cpu.cache.csr_cache_13_val; }
        else if (cpu.cache.csr_cache_13_addr == addr + 1) { ret.y = cpu.cache.csr_cache_13_val; }
        else if (cpu.cache.csr_cache_13_addr == addr + 2) { ret.z = cpu.cache.csr_cache_13_val; }
        else if (cpu.cache.csr_cache_13_addr == addr + 3) { ret.w = cpu.cache.csr_cache_13_val; }
        if      (cpu.cache.csr_cache_14_addr == addr + 0) { ret.x = cpu.cache.csr_cache_14_val; }
        else if (cpu.cache.csr_cache_14_addr == addr + 1) { ret.y = cpu.cache.csr_cache_14_val; }
        else if (cpu.cache.csr_cache_14_addr == addr + 2) { ret.z = cpu.cache.csr_cache_14_val; }
        else if (cpu.cache.csr_cache_14_addr == addr + 3) { ret.w = cpu.cache.csr_cache_14_val; }
        if      (cpu.cache.csr_cache_15_addr == addr + 0) { ret.x = cpu.cache.csr_cache_15_val; }
        else if (cpu.cache.csr_cache_15_addr == addr + 1) { ret.y = cpu.cache.csr_cache_15_val; }
        else if (cpu.cache.csr_cache_15_addr == addr + 2) { ret.z = cpu.cache.csr_cache_15_val; }
        else if (cpu.cache.csr_cache_15_addr == addr + 3) { ret.w = cpu.cache.csr_cache_15_val; }

    }

    // RAM
    if (pos.y >= 128) {
        uint2 pos_ram = uint2(pos.x, pos.y - 128);
        uint lin = pos_ram.x + pos_ram.y * 2048;

        if (_Init) {
            // init main memory from texture
            uint2 ram_dim;
            _Data_RAM_A.GetDimensions(ram_dim.x, ram_dim.y);

            // TODO: something feels off here... off by one, you might say...
            uint2 pos2 = uint2(lin % ram_dim.x, lin / ram_dim.x);
            pos2.y = ram_dim.y - pos2.y - 1;

            if (pos2.y >= ram_dim.y) {
                // zero unset memory
                ret = uint4(0, 0, 0, 0);
            } else {
                uint r = unpack_raw_float4(_Data_RAM_R[pos2]);
                uint g = unpack_raw_float4(_Data_RAM_G[pos2]);
                uint b = unpack_raw_float4(_Data_RAM_B[pos2]);
                uint a = unpack_raw_float4(_Data_RAM_A[pos2]);
                ret = uint4(r, g, b, a);
            }
        } else {
            lin <<= 4;

            if (cpu.stall == STALL_MEMOP_COPY &&
                (lin + (3 << 2)) >= cpu.memop_dst_p &&
                lin < (cpu.memop_dst_p + cpu.memop_n))
            {
                // we've found ourselves in a position for a memcpy, ignore cache and perform it
                // (a memop is always the last instruction in a commit cycle, so we know we have
                // higher priority than the L1 cache)
                [loop]
                for (uint icp = 0; icp < 4; icp++) {
                    uint lin_word = lin + (icp << 2);
                    if (lin_word >= cpu.memop_dst_p &&
                        lin_word < (cpu.memop_dst_p + cpu.memop_n))
                    {
                        uint offset = cpu.memop_dst_p - lin_word;
                        uint src = cpu.memop_src_p + offset;
                        uint transfer = mem_get_cached_or_tex(src);
                        switch (icp) {
                            case 0:
                                ret.r = transfer;
                                break;
                            case 1:
                                ret.g = transfer;
                                break;
                            case 2:
                                ret.b = transfer;
                                break;
                            case 3:
                                ret.a = transfer;
                                break;
                        }
                    }
                }
            }
            else
            {
            // write back L1 cache
                if      (cpu.cache.ram_l1_0_addr == lin) { ret.r = cpu.cache.ram_l1_0_val; }
                else if (cpu.cache.ram_l1_0_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_0_val; }
                else if (cpu.cache.ram_l1_0_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_0_val; }
                else if (cpu.cache.ram_l1_0_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_0_val; }
                if      (cpu.cache.ram_l1_16_addr == lin) { ret.r = cpu.cache.ram_l1_16_val; }
                else if (cpu.cache.ram_l1_16_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_16_val; }
                else if (cpu.cache.ram_l1_16_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_16_val; }
                else if (cpu.cache.ram_l1_16_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_16_val; }
                if      (cpu.cache.ram_l1_32_addr == lin) { ret.r = cpu.cache.ram_l1_32_val; }
                else if (cpu.cache.ram_l1_32_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_32_val; }
                else if (cpu.cache.ram_l1_32_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_32_val; }
                else if (cpu.cache.ram_l1_32_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_32_val; }
                if      (cpu.cache.ram_l1_48_addr == lin) { ret.r = cpu.cache.ram_l1_48_val; }
                else if (cpu.cache.ram_l1_48_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_48_val; }
                else if (cpu.cache.ram_l1_48_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_48_val; }
                else if (cpu.cache.ram_l1_48_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_48_val; }
                if      (cpu.cache.ram_l1_64_addr == lin) { ret.r = cpu.cache.ram_l1_64_val; }
                else if (cpu.cache.ram_l1_64_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_64_val; }
                else if (cpu.cache.ram_l1_64_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_64_val; }
                else if (cpu.cache.ram_l1_64_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_64_val; }
                if      (cpu.cache.ram_l1_1_addr == lin) { ret.r = cpu.cache.ram_l1_1_val; }
                else if (cpu.cache.ram_l1_1_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_1_val; }
                else if (cpu.cache.ram_l1_1_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_1_val; }
                else if (cpu.cache.ram_l1_1_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_1_val; }
                if      (cpu.cache.ram_l1_17_addr == lin) { ret.r = cpu.cache.ram_l1_17_val; }
                else if (cpu.cache.ram_l1_17_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_17_val; }
                else if (cpu.cache.ram_l1_17_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_17_val; }
                else if (cpu.cache.ram_l1_17_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_17_val; }
                if      (cpu.cache.ram_l1_33_addr == lin) { ret.r = cpu.cache.ram_l1_33_val; }
                else if (cpu.cache.ram_l1_33_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_33_val; }
                else if (cpu.cache.ram_l1_33_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_33_val; }
                else if (cpu.cache.ram_l1_33_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_33_val; }
                if      (cpu.cache.ram_l1_49_addr == lin) { ret.r = cpu.cache.ram_l1_49_val; }
                else if (cpu.cache.ram_l1_49_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_49_val; }
                else if (cpu.cache.ram_l1_49_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_49_val; }
                else if (cpu.cache.ram_l1_49_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_49_val; }
                if      (cpu.cache.ram_l1_65_addr == lin) { ret.r = cpu.cache.ram_l1_65_val; }
                else if (cpu.cache.ram_l1_65_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_65_val; }
                else if (cpu.cache.ram_l1_65_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_65_val; }
                else if (cpu.cache.ram_l1_65_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_65_val; }
                if      (cpu.cache.ram_l1_2_addr == lin) { ret.r = cpu.cache.ram_l1_2_val; }
                else if (cpu.cache.ram_l1_2_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_2_val; }
                else if (cpu.cache.ram_l1_2_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_2_val; }
                else if (cpu.cache.ram_l1_2_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_2_val; }
                if      (cpu.cache.ram_l1_18_addr == lin) { ret.r = cpu.cache.ram_l1_18_val; }
                else if (cpu.cache.ram_l1_18_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_18_val; }
                else if (cpu.cache.ram_l1_18_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_18_val; }
                else if (cpu.cache.ram_l1_18_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_18_val; }
                if      (cpu.cache.ram_l1_34_addr == lin) { ret.r = cpu.cache.ram_l1_34_val; }
                else if (cpu.cache.ram_l1_34_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_34_val; }
                else if (cpu.cache.ram_l1_34_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_34_val; }
                else if (cpu.cache.ram_l1_34_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_34_val; }
                if      (cpu.cache.ram_l1_50_addr == lin) { ret.r = cpu.cache.ram_l1_50_val; }
                else if (cpu.cache.ram_l1_50_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_50_val; }
                else if (cpu.cache.ram_l1_50_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_50_val; }
                else if (cpu.cache.ram_l1_50_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_50_val; }
                if      (cpu.cache.ram_l1_66_addr == lin) { ret.r = cpu.cache.ram_l1_66_val; }
                else if (cpu.cache.ram_l1_66_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_66_val; }
                else if (cpu.cache.ram_l1_66_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_66_val; }
                else if (cpu.cache.ram_l1_66_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_66_val; }
                if      (cpu.cache.ram_l1_3_addr == lin) { ret.r = cpu.cache.ram_l1_3_val; }
                else if (cpu.cache.ram_l1_3_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_3_val; }
                else if (cpu.cache.ram_l1_3_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_3_val; }
                else if (cpu.cache.ram_l1_3_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_3_val; }
                if      (cpu.cache.ram_l1_19_addr == lin) { ret.r = cpu.cache.ram_l1_19_val; }
                else if (cpu.cache.ram_l1_19_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_19_val; }
                else if (cpu.cache.ram_l1_19_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_19_val; }
                else if (cpu.cache.ram_l1_19_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_19_val; }
                if      (cpu.cache.ram_l1_35_addr == lin) { ret.r = cpu.cache.ram_l1_35_val; }
                else if (cpu.cache.ram_l1_35_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_35_val; }
                else if (cpu.cache.ram_l1_35_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_35_val; }
                else if (cpu.cache.ram_l1_35_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_35_val; }
                if      (cpu.cache.ram_l1_51_addr == lin) { ret.r = cpu.cache.ram_l1_51_val; }
                else if (cpu.cache.ram_l1_51_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_51_val; }
                else if (cpu.cache.ram_l1_51_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_51_val; }
                else if (cpu.cache.ram_l1_51_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_51_val; }
                if      (cpu.cache.ram_l1_67_addr == lin) { ret.r = cpu.cache.ram_l1_67_val; }
                else if (cpu.cache.ram_l1_67_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_67_val; }
                else if (cpu.cache.ram_l1_67_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_67_val; }
                else if (cpu.cache.ram_l1_67_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_67_val; }
                if      (cpu.cache.ram_l1_4_addr == lin) { ret.r = cpu.cache.ram_l1_4_val; }
                else if (cpu.cache.ram_l1_4_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_4_val; }
                else if (cpu.cache.ram_l1_4_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_4_val; }
                else if (cpu.cache.ram_l1_4_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_4_val; }
                if      (cpu.cache.ram_l1_20_addr == lin) { ret.r = cpu.cache.ram_l1_20_val; }
                else if (cpu.cache.ram_l1_20_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_20_val; }
                else if (cpu.cache.ram_l1_20_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_20_val; }
                else if (cpu.cache.ram_l1_20_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_20_val; }
                if      (cpu.cache.ram_l1_36_addr == lin) { ret.r = cpu.cache.ram_l1_36_val; }
                else if (cpu.cache.ram_l1_36_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_36_val; }
                else if (cpu.cache.ram_l1_36_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_36_val; }
                else if (cpu.cache.ram_l1_36_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_36_val; }
                if      (cpu.cache.ram_l1_52_addr == lin) { ret.r = cpu.cache.ram_l1_52_val; }
                else if (cpu.cache.ram_l1_52_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_52_val; }
                else if (cpu.cache.ram_l1_52_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_52_val; }
                else if (cpu.cache.ram_l1_52_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_52_val; }
                if      (cpu.cache.ram_l1_68_addr == lin) { ret.r = cpu.cache.ram_l1_68_val; }
                else if (cpu.cache.ram_l1_68_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_68_val; }
                else if (cpu.cache.ram_l1_68_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_68_val; }
                else if (cpu.cache.ram_l1_68_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_68_val; }
                if      (cpu.cache.ram_l1_5_addr == lin) { ret.r = cpu.cache.ram_l1_5_val; }
                else if (cpu.cache.ram_l1_5_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_5_val; }
                else if (cpu.cache.ram_l1_5_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_5_val; }
                else if (cpu.cache.ram_l1_5_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_5_val; }
                if      (cpu.cache.ram_l1_21_addr == lin) { ret.r = cpu.cache.ram_l1_21_val; }
                else if (cpu.cache.ram_l1_21_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_21_val; }
                else if (cpu.cache.ram_l1_21_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_21_val; }
                else if (cpu.cache.ram_l1_21_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_21_val; }
                if      (cpu.cache.ram_l1_37_addr == lin) { ret.r = cpu.cache.ram_l1_37_val; }
                else if (cpu.cache.ram_l1_37_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_37_val; }
                else if (cpu.cache.ram_l1_37_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_37_val; }
                else if (cpu.cache.ram_l1_37_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_37_val; }
                if      (cpu.cache.ram_l1_53_addr == lin) { ret.r = cpu.cache.ram_l1_53_val; }
                else if (cpu.cache.ram_l1_53_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_53_val; }
                else if (cpu.cache.ram_l1_53_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_53_val; }
                else if (cpu.cache.ram_l1_53_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_53_val; }
                if      (cpu.cache.ram_l1_69_addr == lin) { ret.r = cpu.cache.ram_l1_69_val; }
                else if (cpu.cache.ram_l1_69_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_69_val; }
                else if (cpu.cache.ram_l1_69_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_69_val; }
                else if (cpu.cache.ram_l1_69_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_69_val; }
                if      (cpu.cache.ram_l1_6_addr == lin) { ret.r = cpu.cache.ram_l1_6_val; }
                else if (cpu.cache.ram_l1_6_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_6_val; }
                else if (cpu.cache.ram_l1_6_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_6_val; }
                else if (cpu.cache.ram_l1_6_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_6_val; }
                if      (cpu.cache.ram_l1_22_addr == lin) { ret.r = cpu.cache.ram_l1_22_val; }
                else if (cpu.cache.ram_l1_22_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_22_val; }
                else if (cpu.cache.ram_l1_22_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_22_val; }
                else if (cpu.cache.ram_l1_22_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_22_val; }
                if      (cpu.cache.ram_l1_38_addr == lin) { ret.r = cpu.cache.ram_l1_38_val; }
                else if (cpu.cache.ram_l1_38_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_38_val; }
                else if (cpu.cache.ram_l1_38_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_38_val; }
                else if (cpu.cache.ram_l1_38_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_38_val; }
                if      (cpu.cache.ram_l1_54_addr == lin) { ret.r = cpu.cache.ram_l1_54_val; }
                else if (cpu.cache.ram_l1_54_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_54_val; }
                else if (cpu.cache.ram_l1_54_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_54_val; }
                else if (cpu.cache.ram_l1_54_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_54_val; }
                if      (cpu.cache.ram_l1_70_addr == lin) { ret.r = cpu.cache.ram_l1_70_val; }
                else if (cpu.cache.ram_l1_70_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_70_val; }
                else if (cpu.cache.ram_l1_70_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_70_val; }
                else if (cpu.cache.ram_l1_70_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_70_val; }
                if      (cpu.cache.ram_l1_7_addr == lin) { ret.r = cpu.cache.ram_l1_7_val; }
                else if (cpu.cache.ram_l1_7_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_7_val; }
                else if (cpu.cache.ram_l1_7_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_7_val; }
                else if (cpu.cache.ram_l1_7_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_7_val; }
                if      (cpu.cache.ram_l1_23_addr == lin) { ret.r = cpu.cache.ram_l1_23_val; }
                else if (cpu.cache.ram_l1_23_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_23_val; }
                else if (cpu.cache.ram_l1_23_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_23_val; }
                else if (cpu.cache.ram_l1_23_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_23_val; }
                if      (cpu.cache.ram_l1_39_addr == lin) { ret.r = cpu.cache.ram_l1_39_val; }
                else if (cpu.cache.ram_l1_39_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_39_val; }
                else if (cpu.cache.ram_l1_39_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_39_val; }
                else if (cpu.cache.ram_l1_39_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_39_val; }
                if      (cpu.cache.ram_l1_55_addr == lin) { ret.r = cpu.cache.ram_l1_55_val; }
                else if (cpu.cache.ram_l1_55_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_55_val; }
                else if (cpu.cache.ram_l1_55_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_55_val; }
                else if (cpu.cache.ram_l1_55_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_55_val; }
                if      (cpu.cache.ram_l1_71_addr == lin) { ret.r = cpu.cache.ram_l1_71_val; }
                else if (cpu.cache.ram_l1_71_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_71_val; }
                else if (cpu.cache.ram_l1_71_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_71_val; }
                else if (cpu.cache.ram_l1_71_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_71_val; }
                if      (cpu.cache.ram_l1_8_addr == lin) { ret.r = cpu.cache.ram_l1_8_val; }
                else if (cpu.cache.ram_l1_8_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_8_val; }
                else if (cpu.cache.ram_l1_8_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_8_val; }
                else if (cpu.cache.ram_l1_8_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_8_val; }
                if      (cpu.cache.ram_l1_24_addr == lin) { ret.r = cpu.cache.ram_l1_24_val; }
                else if (cpu.cache.ram_l1_24_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_24_val; }
                else if (cpu.cache.ram_l1_24_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_24_val; }
                else if (cpu.cache.ram_l1_24_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_24_val; }
                if      (cpu.cache.ram_l1_40_addr == lin) { ret.r = cpu.cache.ram_l1_40_val; }
                else if (cpu.cache.ram_l1_40_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_40_val; }
                else if (cpu.cache.ram_l1_40_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_40_val; }
                else if (cpu.cache.ram_l1_40_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_40_val; }
                if      (cpu.cache.ram_l1_56_addr == lin) { ret.r = cpu.cache.ram_l1_56_val; }
                else if (cpu.cache.ram_l1_56_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_56_val; }
                else if (cpu.cache.ram_l1_56_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_56_val; }
                else if (cpu.cache.ram_l1_56_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_56_val; }
                if      (cpu.cache.ram_l1_72_addr == lin) { ret.r = cpu.cache.ram_l1_72_val; }
                else if (cpu.cache.ram_l1_72_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_72_val; }
                else if (cpu.cache.ram_l1_72_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_72_val; }
                else if (cpu.cache.ram_l1_72_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_72_val; }
                if      (cpu.cache.ram_l1_9_addr == lin) { ret.r = cpu.cache.ram_l1_9_val; }
                else if (cpu.cache.ram_l1_9_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_9_val; }
                else if (cpu.cache.ram_l1_9_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_9_val; }
                else if (cpu.cache.ram_l1_9_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_9_val; }
                if      (cpu.cache.ram_l1_25_addr == lin) { ret.r = cpu.cache.ram_l1_25_val; }
                else if (cpu.cache.ram_l1_25_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_25_val; }
                else if (cpu.cache.ram_l1_25_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_25_val; }
                else if (cpu.cache.ram_l1_25_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_25_val; }
                if      (cpu.cache.ram_l1_41_addr == lin) { ret.r = cpu.cache.ram_l1_41_val; }
                else if (cpu.cache.ram_l1_41_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_41_val; }
                else if (cpu.cache.ram_l1_41_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_41_val; }
                else if (cpu.cache.ram_l1_41_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_41_val; }
                if      (cpu.cache.ram_l1_57_addr == lin) { ret.r = cpu.cache.ram_l1_57_val; }
                else if (cpu.cache.ram_l1_57_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_57_val; }
                else if (cpu.cache.ram_l1_57_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_57_val; }
                else if (cpu.cache.ram_l1_57_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_57_val; }
                if      (cpu.cache.ram_l1_73_addr == lin) { ret.r = cpu.cache.ram_l1_73_val; }
                else if (cpu.cache.ram_l1_73_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_73_val; }
                else if (cpu.cache.ram_l1_73_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_73_val; }
                else if (cpu.cache.ram_l1_73_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_73_val; }
                if      (cpu.cache.ram_l1_10_addr == lin) { ret.r = cpu.cache.ram_l1_10_val; }
                else if (cpu.cache.ram_l1_10_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_10_val; }
                else if (cpu.cache.ram_l1_10_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_10_val; }
                else if (cpu.cache.ram_l1_10_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_10_val; }
                if      (cpu.cache.ram_l1_26_addr == lin) { ret.r = cpu.cache.ram_l1_26_val; }
                else if (cpu.cache.ram_l1_26_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_26_val; }
                else if (cpu.cache.ram_l1_26_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_26_val; }
                else if (cpu.cache.ram_l1_26_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_26_val; }
                if      (cpu.cache.ram_l1_42_addr == lin) { ret.r = cpu.cache.ram_l1_42_val; }
                else if (cpu.cache.ram_l1_42_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_42_val; }
                else if (cpu.cache.ram_l1_42_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_42_val; }
                else if (cpu.cache.ram_l1_42_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_42_val; }
                if      (cpu.cache.ram_l1_58_addr == lin) { ret.r = cpu.cache.ram_l1_58_val; }
                else if (cpu.cache.ram_l1_58_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_58_val; }
                else if (cpu.cache.ram_l1_58_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_58_val; }
                else if (cpu.cache.ram_l1_58_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_58_val; }
                if      (cpu.cache.ram_l1_74_addr == lin) { ret.r = cpu.cache.ram_l1_74_val; }
                else if (cpu.cache.ram_l1_74_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_74_val; }
                else if (cpu.cache.ram_l1_74_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_74_val; }
                else if (cpu.cache.ram_l1_74_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_74_val; }
                if      (cpu.cache.ram_l1_11_addr == lin) { ret.r = cpu.cache.ram_l1_11_val; }
                else if (cpu.cache.ram_l1_11_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_11_val; }
                else if (cpu.cache.ram_l1_11_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_11_val; }
                else if (cpu.cache.ram_l1_11_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_11_val; }
                if      (cpu.cache.ram_l1_27_addr == lin) { ret.r = cpu.cache.ram_l1_27_val; }
                else if (cpu.cache.ram_l1_27_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_27_val; }
                else if (cpu.cache.ram_l1_27_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_27_val; }
                else if (cpu.cache.ram_l1_27_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_27_val; }
                if      (cpu.cache.ram_l1_43_addr == lin) { ret.r = cpu.cache.ram_l1_43_val; }
                else if (cpu.cache.ram_l1_43_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_43_val; }
                else if (cpu.cache.ram_l1_43_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_43_val; }
                else if (cpu.cache.ram_l1_43_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_43_val; }
                if      (cpu.cache.ram_l1_59_addr == lin) { ret.r = cpu.cache.ram_l1_59_val; }
                else if (cpu.cache.ram_l1_59_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_59_val; }
                else if (cpu.cache.ram_l1_59_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_59_val; }
                else if (cpu.cache.ram_l1_59_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_59_val; }
                if      (cpu.cache.ram_l1_75_addr == lin) { ret.r = cpu.cache.ram_l1_75_val; }
                else if (cpu.cache.ram_l1_75_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_75_val; }
                else if (cpu.cache.ram_l1_75_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_75_val; }
                else if (cpu.cache.ram_l1_75_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_75_val; }
                if      (cpu.cache.ram_l1_12_addr == lin) { ret.r = cpu.cache.ram_l1_12_val; }
                else if (cpu.cache.ram_l1_12_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_12_val; }
                else if (cpu.cache.ram_l1_12_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_12_val; }
                else if (cpu.cache.ram_l1_12_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_12_val; }
                if      (cpu.cache.ram_l1_28_addr == lin) { ret.r = cpu.cache.ram_l1_28_val; }
                else if (cpu.cache.ram_l1_28_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_28_val; }
                else if (cpu.cache.ram_l1_28_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_28_val; }
                else if (cpu.cache.ram_l1_28_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_28_val; }
                if      (cpu.cache.ram_l1_44_addr == lin) { ret.r = cpu.cache.ram_l1_44_val; }
                else if (cpu.cache.ram_l1_44_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_44_val; }
                else if (cpu.cache.ram_l1_44_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_44_val; }
                else if (cpu.cache.ram_l1_44_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_44_val; }
                if      (cpu.cache.ram_l1_60_addr == lin) { ret.r = cpu.cache.ram_l1_60_val; }
                else if (cpu.cache.ram_l1_60_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_60_val; }
                else if (cpu.cache.ram_l1_60_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_60_val; }
                else if (cpu.cache.ram_l1_60_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_60_val; }
                if      (cpu.cache.ram_l1_76_addr == lin) { ret.r = cpu.cache.ram_l1_76_val; }
                else if (cpu.cache.ram_l1_76_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_76_val; }
                else if (cpu.cache.ram_l1_76_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_76_val; }
                else if (cpu.cache.ram_l1_76_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_76_val; }
                if      (cpu.cache.ram_l1_13_addr == lin) { ret.r = cpu.cache.ram_l1_13_val; }
                else if (cpu.cache.ram_l1_13_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_13_val; }
                else if (cpu.cache.ram_l1_13_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_13_val; }
                else if (cpu.cache.ram_l1_13_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_13_val; }
                if      (cpu.cache.ram_l1_29_addr == lin) { ret.r = cpu.cache.ram_l1_29_val; }
                else if (cpu.cache.ram_l1_29_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_29_val; }
                else if (cpu.cache.ram_l1_29_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_29_val; }
                else if (cpu.cache.ram_l1_29_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_29_val; }
                if      (cpu.cache.ram_l1_45_addr == lin) { ret.r = cpu.cache.ram_l1_45_val; }
                else if (cpu.cache.ram_l1_45_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_45_val; }
                else if (cpu.cache.ram_l1_45_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_45_val; }
                else if (cpu.cache.ram_l1_45_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_45_val; }
                if      (cpu.cache.ram_l1_61_addr == lin) { ret.r = cpu.cache.ram_l1_61_val; }
                else if (cpu.cache.ram_l1_61_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_61_val; }
                else if (cpu.cache.ram_l1_61_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_61_val; }
                else if (cpu.cache.ram_l1_61_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_61_val; }
                if      (cpu.cache.ram_l1_77_addr == lin) { ret.r = cpu.cache.ram_l1_77_val; }
                else if (cpu.cache.ram_l1_77_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_77_val; }
                else if (cpu.cache.ram_l1_77_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_77_val; }
                else if (cpu.cache.ram_l1_77_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_77_val; }
                if      (cpu.cache.ram_l1_14_addr == lin) { ret.r = cpu.cache.ram_l1_14_val; }
                else if (cpu.cache.ram_l1_14_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_14_val; }
                else if (cpu.cache.ram_l1_14_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_14_val; }
                else if (cpu.cache.ram_l1_14_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_14_val; }
                if      (cpu.cache.ram_l1_30_addr == lin) { ret.r = cpu.cache.ram_l1_30_val; }
                else if (cpu.cache.ram_l1_30_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_30_val; }
                else if (cpu.cache.ram_l1_30_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_30_val; }
                else if (cpu.cache.ram_l1_30_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_30_val; }
                if      (cpu.cache.ram_l1_46_addr == lin) { ret.r = cpu.cache.ram_l1_46_val; }
                else if (cpu.cache.ram_l1_46_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_46_val; }
                else if (cpu.cache.ram_l1_46_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_46_val; }
                else if (cpu.cache.ram_l1_46_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_46_val; }
                if      (cpu.cache.ram_l1_62_addr == lin) { ret.r = cpu.cache.ram_l1_62_val; }
                else if (cpu.cache.ram_l1_62_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_62_val; }
                else if (cpu.cache.ram_l1_62_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_62_val; }
                else if (cpu.cache.ram_l1_62_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_62_val; }
                if      (cpu.cache.ram_l1_78_addr == lin) { ret.r = cpu.cache.ram_l1_78_val; }
                else if (cpu.cache.ram_l1_78_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_78_val; }
                else if (cpu.cache.ram_l1_78_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_78_val; }
                else if (cpu.cache.ram_l1_78_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_78_val; }
                if      (cpu.cache.ram_l1_15_addr == lin) { ret.r = cpu.cache.ram_l1_15_val; }
                else if (cpu.cache.ram_l1_15_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_15_val; }
                else if (cpu.cache.ram_l1_15_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_15_val; }
                else if (cpu.cache.ram_l1_15_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_15_val; }
                if      (cpu.cache.ram_l1_31_addr == lin) { ret.r = cpu.cache.ram_l1_31_val; }
                else if (cpu.cache.ram_l1_31_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_31_val; }
                else if (cpu.cache.ram_l1_31_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_31_val; }
                else if (cpu.cache.ram_l1_31_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_31_val; }
                if      (cpu.cache.ram_l1_47_addr == lin) { ret.r = cpu.cache.ram_l1_47_val; }
                else if (cpu.cache.ram_l1_47_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_47_val; }
                else if (cpu.cache.ram_l1_47_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_47_val; }
                else if (cpu.cache.ram_l1_47_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_47_val; }
                if      (cpu.cache.ram_l1_63_addr == lin) { ret.r = cpu.cache.ram_l1_63_val; }
                else if (cpu.cache.ram_l1_63_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_63_val; }
                else if (cpu.cache.ram_l1_63_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_63_val; }
                else if (cpu.cache.ram_l1_63_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_63_val; }
                if      (cpu.cache.ram_l1_79_addr == lin) { ret.r = cpu.cache.ram_l1_79_val; }
                else if (cpu.cache.ram_l1_79_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_79_val; }
                else if (cpu.cache.ram_l1_79_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_79_val; }
                else if (cpu.cache.ram_l1_79_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_79_val; }


                    if (cpu.cache.ram_l1_last_addr == lin           ) { ret.r = cpu.cache.ram_l1_last_val; }
                else if (cpu.cache.ram_l1_last_addr == lin + (1 << 2)) { ret.g = cpu.cache.ram_l1_last_val; }
                else if (cpu.cache.ram_l1_last_addr == lin + (2 << 2)) { ret.b = cpu.cache.ram_l1_last_val; }
                else if (cpu.cache.ram_l1_last_addr == lin + (3 << 2)) { ret.a = cpu.cache.ram_l1_last_val; }
            }
        }
    }

    return ret;
}
#endif

#endif

/*

C# layout:

    #region LOAD
    private const int UART_BUFFER_SIZE = 64;
    private int[] addr_lin(int lin) {
        int[] ret = new int[3];
        ret[2] = lin & 0x3; // c
        lin = lin >> 2;
        ret[0] = lin % 128; // x
        ret[1] = lin / 128; // y
        return ret;
    }
    private uint load_csr__privilege() { return decodePackedData(48, 0, 2); }
    private uint load_uart__rbr_thr_ier_iir() { return decodePackedData(48, 0, 3); }
    private uint load_uart__lcr_mcr_lsr_scr() { return decodePackedData(49, 0, 0); }
    private uint load_uart__thre_ip() { return decodePackedData(49, 0, 1); }
    private uint load_uart__interrupting() { return decodePackedData(49, 0, 2); }
    private uint load_uart__input_tag() { return decodePackedData(49, 0, 3); }
    private uint load_clint__msip() { return decodePackedData(50, 0, 0); }
    private uint load_clint__mtimecmp_lo() { return decodePackedData(50, 0, 1); }
    private uint load_clint__mtimecmp_hi() { return decodePackedData(50, 0, 2); }
    private uint load_clint__mtime_lo() { return decodePackedData(50, 0, 3); }
    private uint load_clint__mtime_hi() { return decodePackedData(51, 0, 0); }
    private uint load_uart_buffer__ptr() { return decodePackedData(51, 0, 1); }
    private uint load_mmu__mode() { return decodePackedData(67, 0, 2); }
    private uint load_mmu__ppn() { return decodePackedData(67, 0, 3); }
    private uint load_stall() { return decodePackedData(68, 0, 0); }
    private uint load_clock() { return decodePackedData(68, 0, 1); }
    private uint load_commits() { return decodePackedData(68, 0, 2); }
    private uint load_xreg0() { return decodePackedData(68, 0, 3); }
    private uint load_xreg1() { return decodePackedData(69, 0, 0); }
    private uint load_xreg2() { return decodePackedData(69, 0, 1); }
    private uint load_xreg3() { return decodePackedData(69, 0, 2); }
    private uint load_xreg4() { return decodePackedData(69, 0, 3); }
    private uint load_xreg5() { return decodePackedData(70, 0, 0); }
    private uint load_xreg6() { return decodePackedData(70, 0, 1); }
    private uint load_xreg7() { return decodePackedData(70, 0, 2); }
    private uint load_xreg8() { return decodePackedData(70, 0, 3); }
    private uint load_xreg9() { return decodePackedData(71, 0, 0); }
    private uint load_xreg10() { return decodePackedData(71, 0, 1); }
    private uint load_xreg11() { return decodePackedData(71, 0, 2); }
    private uint load_xreg12() { return decodePackedData(71, 0, 3); }
    private uint load_xreg13() { return decodePackedData(72, 0, 0); }
    private uint load_xreg14() { return decodePackedData(72, 0, 1); }
    private uint load_xreg15() { return decodePackedData(72, 0, 2); }
    private uint load_xreg16() { return decodePackedData(72, 0, 3); }
    private uint load_xreg17() { return decodePackedData(73, 0, 0); }
    private uint load_xreg18() { return decodePackedData(73, 0, 1); }
    private uint load_xreg19() { return decodePackedData(73, 0, 2); }
    private uint load_xreg20() { return decodePackedData(73, 0, 3); }
    private uint load_xreg21() { return decodePackedData(74, 0, 0); }
    private uint load_xreg22() { return decodePackedData(74, 0, 1); }
    private uint load_xreg23() { return decodePackedData(74, 0, 2); }
    private uint load_xreg24() { return decodePackedData(74, 0, 3); }
    private uint load_xreg25() { return decodePackedData(75, 0, 0); }
    private uint load_xreg26() { return decodePackedData(75, 0, 1); }
    private uint load_xreg27() { return decodePackedData(75, 0, 2); }
    private uint load_xreg28() { return decodePackedData(75, 0, 3); }
    private uint load_xreg29() { return decodePackedData(76, 0, 0); }
    private uint load_xreg30() { return decodePackedData(76, 0, 1); }
    private uint load_xreg31() { return decodePackedData(76, 0, 2); }
    private uint load_pc() { return decodePackedData(76, 0, 3); }
    private uint load_reservation_en() { return decodePackedData(77, 0, 0); }
    private uint load_reservation_addr() { return decodePackedData(77, 0, 1); }
    private uint load_memop_src_v() { return decodePackedData(77, 0, 2); }
    private uint load_memop_dst_v() { return decodePackedData(77, 0, 3); }
    private uint load_memop_src_p() { return decodePackedData(78, 0, 0); }
    private uint load_memop_dst_p() { return decodePackedData(78, 0, 1); }
    private uint load_memop_n() { return decodePackedData(78, 0, 2); }
    private uint load_stall_count() { return decodePackedData(78, 0, 3); }
    private uint load_trap_count() { return decodePackedData(79, 0, 0); }
    private uint load_debug_do_tick() { return decodePackedData(79, 0, 1); }
    private uint load_debug_last_ins() { return decodePackedData(79, 0, 2); }
    private uint load_debug_last_stall() { return decodePackedData(79, 0, 3); }
    private uint load_debug_arb_0() { return decodePackedData(80, 0, 0); }
    private uint load_csr(int addr) {
        int lin = (addr >> 2) + 324;
        return decodePackedData(lin % 128, lin / 128, addr & 0x3);
    }
    private uint getUartBuffer(int idx) {
        
        int lin = idx + 206;
        int[] acc = addr_lin(lin);
        return decodePackedData(acc[0], acc[1], acc[2]);
    }
    #endregion

*/
