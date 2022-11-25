#ifndef TYPES_H
#define TYPES_H

#define glsl_mod(x,y) (((x)-(y)*floor((x)/(y)))) 



#define RAM_ADDR(lin) uint2(lin % 2048, 64 + (lin / 2048))
#define RAM_MAX (2048 * (4096 - 64) * 4 * 4)


/* shift by two to ignore byte offset */
#define RAM_L1_ARRAY_IDX(a) (((a >> 2) & 127) | (((a >> 11) & 0x3) << 7))


#define STALL_EXIT_CALL 1
#define STALL_CSR_CACHE 2
#define STALL_MEM_CACHE_L1 3
#define STALL_RESERVED 4
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
    uint mode;
    uint ppn;
} mmu_state;

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
    uint stall;
    uint clock;
    uint commits;
    uint xreg[32];
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

    uint rtc0;
    uint rtc1;

    float start_time_ref;

    uint debug_do_tick;
    uint debug_last_ins;
    uint debug_last_stall;
    
    

    uint debug_arb_0;
    /*  */
    /*  */
    /*  */
    /*  */
    /*  */
    /*  */
    /*  */

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

#ifdef PASS_TICK
static uint4 l1_cache[1024];
#endif

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
    return cpu.xreg[i];
}

// ENCODE/DECODE LOGIC (state serialization into self texture)

// csr_cache_start = 44 (addr=164)
// l1_cache_start = 1068 (addr=164)
// l1_cache_end = 2092 (addr=164)


#define STATE_WIDTH 64
#define STATE_HEIGHT 64

#ifdef PASS_TICK
void decode() {
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
    cpu.cache.ram_l1_last_addr = uint(4294967295);
    cpu.cache.ram_l1_last_val = uint(3735931358);
    cpu.csr.privilege = uint(idx_uint4(STATE_TEX(uint2(8, 0)), 2));
    cpu.uart.rbr_thr_ier_iir = uint(idx_uint4(STATE_TEX(uint2(8, 0)), 3));
    cpu.uart.lcr_mcr_lsr_scr = uint(idx_uint4(STATE_TEX(uint2(9, 0)), 0));
    cpu.uart.thre_ip = bool(idx_uint4(STATE_TEX(uint2(9, 0)), 1));
    cpu.uart.interrupting = bool(idx_uint4(STATE_TEX(uint2(9, 0)), 2));
    cpu.uart.input_tag = uint(idx_uint4(STATE_TEX(uint2(9, 0)), 3));
    cpu.clint.msip = bool(idx_uint4(STATE_TEX(uint2(10, 0)), 0));
    cpu.clint.mtimecmp_lo = uint(idx_uint4(STATE_TEX(uint2(10, 0)), 1));
    cpu.clint.mtimecmp_hi = uint(idx_uint4(STATE_TEX(uint2(10, 0)), 2));
    cpu.clint.mtime_lo = uint(idx_uint4(STATE_TEX(uint2(10, 0)), 3));
    cpu.clint.mtime_hi = uint(idx_uint4(STATE_TEX(uint2(11, 0)), 0));
    cpu.mmu.mode = uint(idx_uint4(STATE_TEX(uint2(11, 0)), 1));
    cpu.mmu.ppn = uint(idx_uint4(STATE_TEX(uint2(11, 0)), 2));
    cpu.uart_buffer.ptr = uint(4294967295);
    cpu.uart_buffer.buf0 = uint(0);
    cpu.uart_buffer.buf1 = uint(0);
    cpu.uart_buffer.buf2 = uint(0);
    cpu.uart_buffer.buf3 = uint(0);
    cpu.uart_buffer.buf4 = uint(0);
    cpu.uart_buffer.buf5 = uint(0);
    cpu.uart_buffer.buf6 = uint(0);
    cpu.uart_buffer.buf7 = uint(0);
    cpu.uart_buffer.buf8 = uint(0);
    cpu.uart_buffer.buf9 = uint(0);
    cpu.uart_buffer.buf10 = uint(0);
    cpu.uart_buffer.buf11 = uint(0);
    cpu.uart_buffer.buf12 = uint(0);
    cpu.uart_buffer.buf13 = uint(0);
    cpu.uart_buffer.buf14 = uint(0);
    cpu.uart_buffer.buf15 = uint(0);
    cpu.uart_buffer.buf16 = uint(0);
    cpu.uart_buffer.buf17 = uint(0);
    cpu.uart_buffer.buf18 = uint(0);
    cpu.uart_buffer.buf19 = uint(0);
    cpu.uart_buffer.buf20 = uint(0);
    cpu.uart_buffer.buf21 = uint(0);
    cpu.uart_buffer.buf22 = uint(0);
    cpu.uart_buffer.buf23 = uint(0);
    cpu.uart_buffer.buf24 = uint(0);
    cpu.uart_buffer.buf25 = uint(0);
    cpu.uart_buffer.buf26 = uint(0);
    cpu.uart_buffer.buf27 = uint(0);
    cpu.uart_buffer.buf28 = uint(0);
    cpu.uart_buffer.buf29 = uint(0);
    cpu.uart_buffer.buf30 = uint(0);
    cpu.uart_buffer.buf31 = uint(0);
    cpu.uart_buffer.buf32 = uint(0);
    cpu.uart_buffer.buf33 = uint(0);
    cpu.uart_buffer.buf34 = uint(0);
    cpu.uart_buffer.buf35 = uint(0);
    cpu.uart_buffer.buf36 = uint(0);
    cpu.uart_buffer.buf37 = uint(0);
    cpu.uart_buffer.buf38 = uint(0);
    cpu.uart_buffer.buf39 = uint(0);
    cpu.uart_buffer.buf40 = uint(0);
    cpu.uart_buffer.buf41 = uint(0);
    cpu.uart_buffer.buf42 = uint(0);
    cpu.uart_buffer.buf43 = uint(0);
    cpu.uart_buffer.buf44 = uint(0);
    cpu.uart_buffer.buf45 = uint(0);
    cpu.uart_buffer.buf46 = uint(0);
    cpu.uart_buffer.buf47 = uint(0);
    cpu.uart_buffer.buf48 = uint(0);
    cpu.uart_buffer.buf49 = uint(0);
    cpu.uart_buffer.buf50 = uint(0);
    cpu.uart_buffer.buf51 = uint(0);
    cpu.uart_buffer.buf52 = uint(0);
    cpu.uart_buffer.buf53 = uint(0);
    cpu.uart_buffer.buf54 = uint(0);
    cpu.uart_buffer.buf55 = uint(0);
    cpu.uart_buffer.buf56 = uint(0);
    cpu.uart_buffer.buf57 = uint(0);
    cpu.uart_buffer.buf58 = uint(0);
    cpu.uart_buffer.buf59 = uint(0);
    cpu.uart_buffer.buf60 = uint(0);
    cpu.uart_buffer.buf61 = uint(0);
    cpu.uart_buffer.buf62 = uint(0);
    cpu.uart_buffer.buf63 = uint(0);
    cpu.stall = uint(idx_uint4(STATE_TEX(uint2(28, 0)), 0));
    cpu.clock = uint(idx_uint4(STATE_TEX(uint2(28, 0)), 1));
    cpu.commits = uint(idx_uint4(STATE_TEX(uint2(28, 0)), 2));
    cpu.xreg[0] = uint(idx_uint4(STATE_TEX(uint2(28, 0)), 3));
    cpu.xreg[1] = uint(idx_uint4(STATE_TEX(uint2(29, 0)), 0));
    cpu.xreg[2] = uint(idx_uint4(STATE_TEX(uint2(29, 0)), 1));
    cpu.xreg[3] = uint(idx_uint4(STATE_TEX(uint2(29, 0)), 2));
    cpu.xreg[4] = uint(idx_uint4(STATE_TEX(uint2(29, 0)), 3));
    cpu.xreg[5] = uint(idx_uint4(STATE_TEX(uint2(30, 0)), 0));
    cpu.xreg[6] = uint(idx_uint4(STATE_TEX(uint2(30, 0)), 1));
    cpu.xreg[7] = uint(idx_uint4(STATE_TEX(uint2(30, 0)), 2));
    cpu.xreg[8] = uint(idx_uint4(STATE_TEX(uint2(30, 0)), 3));
    cpu.xreg[9] = uint(idx_uint4(STATE_TEX(uint2(31, 0)), 0));
    cpu.xreg[10] = uint(idx_uint4(STATE_TEX(uint2(31, 0)), 1));
    cpu.xreg[11] = uint(idx_uint4(STATE_TEX(uint2(31, 0)), 2));
    cpu.xreg[12] = uint(idx_uint4(STATE_TEX(uint2(31, 0)), 3));
    cpu.xreg[13] = uint(idx_uint4(STATE_TEX(uint2(32, 0)), 0));
    cpu.xreg[14] = uint(idx_uint4(STATE_TEX(uint2(32, 0)), 1));
    cpu.xreg[15] = uint(idx_uint4(STATE_TEX(uint2(32, 0)), 2));
    cpu.xreg[16] = uint(idx_uint4(STATE_TEX(uint2(32, 0)), 3));
    cpu.xreg[17] = uint(idx_uint4(STATE_TEX(uint2(33, 0)), 0));
    cpu.xreg[18] = uint(idx_uint4(STATE_TEX(uint2(33, 0)), 1));
    cpu.xreg[19] = uint(idx_uint4(STATE_TEX(uint2(33, 0)), 2));
    cpu.xreg[20] = uint(idx_uint4(STATE_TEX(uint2(33, 0)), 3));
    cpu.xreg[21] = uint(idx_uint4(STATE_TEX(uint2(34, 0)), 0));
    cpu.xreg[22] = uint(idx_uint4(STATE_TEX(uint2(34, 0)), 1));
    cpu.xreg[23] = uint(idx_uint4(STATE_TEX(uint2(34, 0)), 2));
    cpu.xreg[24] = uint(idx_uint4(STATE_TEX(uint2(34, 0)), 3));
    cpu.xreg[25] = uint(idx_uint4(STATE_TEX(uint2(35, 0)), 0));
    cpu.xreg[26] = uint(idx_uint4(STATE_TEX(uint2(35, 0)), 1));
    cpu.xreg[27] = uint(idx_uint4(STATE_TEX(uint2(35, 0)), 2));
    cpu.xreg[28] = uint(idx_uint4(STATE_TEX(uint2(35, 0)), 3));
    cpu.xreg[29] = uint(idx_uint4(STATE_TEX(uint2(36, 0)), 0));
    cpu.xreg[30] = uint(idx_uint4(STATE_TEX(uint2(36, 0)), 1));
    cpu.xreg[31] = uint(idx_uint4(STATE_TEX(uint2(36, 0)), 2));
    cpu.pc = uint(idx_uint4(STATE_TEX(uint2(36, 0)), 3));
    cpu.reservation_en = bool(idx_uint4(STATE_TEX(uint2(37, 0)), 0));
    cpu.reservation_addr = uint(idx_uint4(STATE_TEX(uint2(37, 0)), 1));
    cpu.memop_src_v = uint(idx_uint4(STATE_TEX(uint2(37, 0)), 2));
    cpu.memop_dst_v = uint(idx_uint4(STATE_TEX(uint2(37, 0)), 3));
    cpu.memop_src_p = uint(idx_uint4(STATE_TEX(uint2(38, 0)), 0));
    cpu.memop_dst_p = uint(idx_uint4(STATE_TEX(uint2(38, 0)), 1));
    cpu.memop_n = uint(idx_uint4(STATE_TEX(uint2(38, 0)), 2));
    cpu.stall_count = uint(idx_uint4(STATE_TEX(uint2(38, 0)), 3));
    cpu.trap_count = uint(idx_uint4(STATE_TEX(uint2(39, 0)), 0));
    cpu.rtc0 = uint(idx_uint4(STATE_TEX(uint2(39, 0)), 1));
    cpu.rtc1 = uint(idx_uint4(STATE_TEX(uint2(39, 0)), 2));
    cpu.start_time_ref = asfloat(idx_uint4(STATE_TEX(uint2(39, 0)), 3));
    cpu.debug_do_tick = uint(idx_uint4(STATE_TEX(uint2(40, 0)), 0));
    cpu.debug_last_ins = uint(idx_uint4(STATE_TEX(uint2(40, 0)), 1));
    cpu.debug_last_stall = uint(idx_uint4(STATE_TEX(uint2(40, 0)), 2));
    cpu.debug_arb_0 = uint(idx_uint4(STATE_TEX(uint2(40, 0)), 3));

}
#endif

#ifdef PASS_COMMIT
#define NEEDS_DFC
#endif
#ifdef PASS_FB
#define NEEDS_DFC
#endif

#ifdef NEEDS_DFC
void decode_for_commit() {
    cpu = (cpu_t)0;

    cpu.cache.csr_cache_0_addr = uint(idx_uint4(STATE_TEX_HART(uint2(0, 0), 0), 0));
    cpu.cache.csr_cache_0_val = uint(idx_uint4(STATE_TEX_HART(uint2(0, 0), 0), 1));
    cpu.cache.csr_cache_1_addr = uint(idx_uint4(STATE_TEX_HART(uint2(0, 0), 0), 2));
    cpu.cache.csr_cache_1_val = uint(idx_uint4(STATE_TEX_HART(uint2(0, 0), 0), 3));
    cpu.cache.csr_cache_2_addr = uint(idx_uint4(STATE_TEX_HART(uint2(1, 0), 0), 0));
    cpu.cache.csr_cache_2_val = uint(idx_uint4(STATE_TEX_HART(uint2(1, 0), 0), 1));
    cpu.cache.csr_cache_3_addr = uint(idx_uint4(STATE_TEX_HART(uint2(1, 0), 0), 2));
    cpu.cache.csr_cache_3_val = uint(idx_uint4(STATE_TEX_HART(uint2(1, 0), 0), 3));
    cpu.cache.csr_cache_4_addr = uint(idx_uint4(STATE_TEX_HART(uint2(2, 0), 0), 0));
    cpu.cache.csr_cache_4_val = uint(idx_uint4(STATE_TEX_HART(uint2(2, 0), 0), 1));
    cpu.cache.csr_cache_5_addr = uint(idx_uint4(STATE_TEX_HART(uint2(2, 0), 0), 2));
    cpu.cache.csr_cache_5_val = uint(idx_uint4(STATE_TEX_HART(uint2(2, 0), 0), 3));
    cpu.cache.csr_cache_6_addr = uint(idx_uint4(STATE_TEX_HART(uint2(3, 0), 0), 0));
    cpu.cache.csr_cache_6_val = uint(idx_uint4(STATE_TEX_HART(uint2(3, 0), 0), 1));
    cpu.cache.csr_cache_7_addr = uint(idx_uint4(STATE_TEX_HART(uint2(3, 0), 0), 2));
    cpu.cache.csr_cache_7_val = uint(idx_uint4(STATE_TEX_HART(uint2(3, 0), 0), 3));
    cpu.cache.csr_cache_8_addr = uint(idx_uint4(STATE_TEX_HART(uint2(4, 0), 0), 0));
    cpu.cache.csr_cache_8_val = uint(idx_uint4(STATE_TEX_HART(uint2(4, 0), 0), 1));
    cpu.cache.csr_cache_9_addr = uint(idx_uint4(STATE_TEX_HART(uint2(4, 0), 0), 2));
    cpu.cache.csr_cache_9_val = uint(idx_uint4(STATE_TEX_HART(uint2(4, 0), 0), 3));
    cpu.cache.csr_cache_10_addr = uint(idx_uint4(STATE_TEX_HART(uint2(5, 0), 0), 0));
    cpu.cache.csr_cache_10_val = uint(idx_uint4(STATE_TEX_HART(uint2(5, 0), 0), 1));
    cpu.cache.csr_cache_11_addr = uint(idx_uint4(STATE_TEX_HART(uint2(5, 0), 0), 2));
    cpu.cache.csr_cache_11_val = uint(idx_uint4(STATE_TEX_HART(uint2(5, 0), 0), 3));
    cpu.cache.csr_cache_12_addr = uint(idx_uint4(STATE_TEX_HART(uint2(6, 0), 0), 0));
    cpu.cache.csr_cache_12_val = uint(idx_uint4(STATE_TEX_HART(uint2(6, 0), 0), 1));
    cpu.cache.csr_cache_13_addr = uint(idx_uint4(STATE_TEX_HART(uint2(6, 0), 0), 2));
    cpu.cache.csr_cache_13_val = uint(idx_uint4(STATE_TEX_HART(uint2(6, 0), 0), 3));
    cpu.cache.csr_cache_14_addr = uint(idx_uint4(STATE_TEX_HART(uint2(7, 0), 0), 0));
    cpu.cache.csr_cache_14_val = uint(idx_uint4(STATE_TEX_HART(uint2(7, 0), 0), 1));
    cpu.cache.csr_cache_15_addr = uint(idx_uint4(STATE_TEX_HART(uint2(7, 0), 0), 2));
    cpu.cache.csr_cache_15_val = uint(idx_uint4(STATE_TEX_HART(uint2(7, 0), 0), 3));
    cpu.cache.ram_l1_last_addr = uint(idx_uint4(STATE_TEX_HART(uint2(8, 0), 0), 0));
    cpu.cache.ram_l1_last_val = uint(idx_uint4(STATE_TEX_HART(uint2(8, 0), 0), 1));
    cpu.csr.privilege = uint(idx_uint4(STATE_TEX_HART(uint2(8, 0), 0), 2));
    cpu.uart.rbr_thr_ier_iir = uint(idx_uint4(STATE_TEX_HART(uint2(8, 0), 0), 3));
    cpu.uart.lcr_mcr_lsr_scr = uint(idx_uint4(STATE_TEX_HART(uint2(9, 0), 0), 0));
    cpu.uart.thre_ip = bool(idx_uint4(STATE_TEX_HART(uint2(9, 0), 0), 1));
    cpu.uart.interrupting = bool(idx_uint4(STATE_TEX_HART(uint2(9, 0), 0), 2));
    cpu.uart.input_tag = uint(idx_uint4(STATE_TEX_HART(uint2(9, 0), 0), 3));
    cpu.clint.msip = bool(idx_uint4(STATE_TEX_HART(uint2(10, 0), 0), 0));
    cpu.clint.mtimecmp_lo = uint(idx_uint4(STATE_TEX_HART(uint2(10, 0), 0), 1));
    cpu.clint.mtimecmp_hi = uint(idx_uint4(STATE_TEX_HART(uint2(10, 0), 0), 2));
    cpu.clint.mtime_lo = uint(idx_uint4(STATE_TEX_HART(uint2(10, 0), 0), 3));
    cpu.clint.mtime_hi = uint(idx_uint4(STATE_TEX_HART(uint2(11, 0), 0), 0));
    cpu.mmu.mode = uint(idx_uint4(STATE_TEX_HART(uint2(11, 0), 0), 1));
    cpu.mmu.ppn = uint(idx_uint4(STATE_TEX_HART(uint2(11, 0), 0), 2));
    cpu.uart_buffer.ptr = uint(idx_uint4(STATE_TEX_HART(uint2(11, 0), 0), 3));
    cpu.uart_buffer.buf0 = uint(idx_uint4(STATE_TEX_HART(uint2(12, 0), 0), 0));
    cpu.uart_buffer.buf1 = uint(idx_uint4(STATE_TEX_HART(uint2(12, 0), 0), 1));
    cpu.uart_buffer.buf2 = uint(idx_uint4(STATE_TEX_HART(uint2(12, 0), 0), 2));
    cpu.uart_buffer.buf3 = uint(idx_uint4(STATE_TEX_HART(uint2(12, 0), 0), 3));
    cpu.uart_buffer.buf4 = uint(idx_uint4(STATE_TEX_HART(uint2(13, 0), 0), 0));
    cpu.uart_buffer.buf5 = uint(idx_uint4(STATE_TEX_HART(uint2(13, 0), 0), 1));
    cpu.uart_buffer.buf6 = uint(idx_uint4(STATE_TEX_HART(uint2(13, 0), 0), 2));
    cpu.uart_buffer.buf7 = uint(idx_uint4(STATE_TEX_HART(uint2(13, 0), 0), 3));
    cpu.uart_buffer.buf8 = uint(idx_uint4(STATE_TEX_HART(uint2(14, 0), 0), 0));
    cpu.uart_buffer.buf9 = uint(idx_uint4(STATE_TEX_HART(uint2(14, 0), 0), 1));
    cpu.uart_buffer.buf10 = uint(idx_uint4(STATE_TEX_HART(uint2(14, 0), 0), 2));
    cpu.uart_buffer.buf11 = uint(idx_uint4(STATE_TEX_HART(uint2(14, 0), 0), 3));
    cpu.uart_buffer.buf12 = uint(idx_uint4(STATE_TEX_HART(uint2(15, 0), 0), 0));
    cpu.uart_buffer.buf13 = uint(idx_uint4(STATE_TEX_HART(uint2(15, 0), 0), 1));
    cpu.uart_buffer.buf14 = uint(idx_uint4(STATE_TEX_HART(uint2(15, 0), 0), 2));
    cpu.uart_buffer.buf15 = uint(idx_uint4(STATE_TEX_HART(uint2(15, 0), 0), 3));
    cpu.uart_buffer.buf16 = uint(idx_uint4(STATE_TEX_HART(uint2(16, 0), 0), 0));
    cpu.uart_buffer.buf17 = uint(idx_uint4(STATE_TEX_HART(uint2(16, 0), 0), 1));
    cpu.uart_buffer.buf18 = uint(idx_uint4(STATE_TEX_HART(uint2(16, 0), 0), 2));
    cpu.uart_buffer.buf19 = uint(idx_uint4(STATE_TEX_HART(uint2(16, 0), 0), 3));
    cpu.uart_buffer.buf20 = uint(idx_uint4(STATE_TEX_HART(uint2(17, 0), 0), 0));
    cpu.uart_buffer.buf21 = uint(idx_uint4(STATE_TEX_HART(uint2(17, 0), 0), 1));
    cpu.uart_buffer.buf22 = uint(idx_uint4(STATE_TEX_HART(uint2(17, 0), 0), 2));
    cpu.uart_buffer.buf23 = uint(idx_uint4(STATE_TEX_HART(uint2(17, 0), 0), 3));
    cpu.uart_buffer.buf24 = uint(idx_uint4(STATE_TEX_HART(uint2(18, 0), 0), 0));
    cpu.uart_buffer.buf25 = uint(idx_uint4(STATE_TEX_HART(uint2(18, 0), 0), 1));
    cpu.uart_buffer.buf26 = uint(idx_uint4(STATE_TEX_HART(uint2(18, 0), 0), 2));
    cpu.uart_buffer.buf27 = uint(idx_uint4(STATE_TEX_HART(uint2(18, 0), 0), 3));
    cpu.uart_buffer.buf28 = uint(idx_uint4(STATE_TEX_HART(uint2(19, 0), 0), 0));
    cpu.uart_buffer.buf29 = uint(idx_uint4(STATE_TEX_HART(uint2(19, 0), 0), 1));
    cpu.uart_buffer.buf30 = uint(idx_uint4(STATE_TEX_HART(uint2(19, 0), 0), 2));
    cpu.uart_buffer.buf31 = uint(idx_uint4(STATE_TEX_HART(uint2(19, 0), 0), 3));
    cpu.uart_buffer.buf32 = uint(idx_uint4(STATE_TEX_HART(uint2(20, 0), 0), 0));
    cpu.uart_buffer.buf33 = uint(idx_uint4(STATE_TEX_HART(uint2(20, 0), 0), 1));
    cpu.uart_buffer.buf34 = uint(idx_uint4(STATE_TEX_HART(uint2(20, 0), 0), 2));
    cpu.uart_buffer.buf35 = uint(idx_uint4(STATE_TEX_HART(uint2(20, 0), 0), 3));
    cpu.uart_buffer.buf36 = uint(idx_uint4(STATE_TEX_HART(uint2(21, 0), 0), 0));
    cpu.uart_buffer.buf37 = uint(idx_uint4(STATE_TEX_HART(uint2(21, 0), 0), 1));
    cpu.uart_buffer.buf38 = uint(idx_uint4(STATE_TEX_HART(uint2(21, 0), 0), 2));
    cpu.uart_buffer.buf39 = uint(idx_uint4(STATE_TEX_HART(uint2(21, 0), 0), 3));
    cpu.uart_buffer.buf40 = uint(idx_uint4(STATE_TEX_HART(uint2(22, 0), 0), 0));
    cpu.uart_buffer.buf41 = uint(idx_uint4(STATE_TEX_HART(uint2(22, 0), 0), 1));
    cpu.uart_buffer.buf42 = uint(idx_uint4(STATE_TEX_HART(uint2(22, 0), 0), 2));
    cpu.uart_buffer.buf43 = uint(idx_uint4(STATE_TEX_HART(uint2(22, 0), 0), 3));
    cpu.uart_buffer.buf44 = uint(idx_uint4(STATE_TEX_HART(uint2(23, 0), 0), 0));
    cpu.uart_buffer.buf45 = uint(idx_uint4(STATE_TEX_HART(uint2(23, 0), 0), 1));
    cpu.uart_buffer.buf46 = uint(idx_uint4(STATE_TEX_HART(uint2(23, 0), 0), 2));
    cpu.uart_buffer.buf47 = uint(idx_uint4(STATE_TEX_HART(uint2(23, 0), 0), 3));
    cpu.uart_buffer.buf48 = uint(idx_uint4(STATE_TEX_HART(uint2(24, 0), 0), 0));
    cpu.uart_buffer.buf49 = uint(idx_uint4(STATE_TEX_HART(uint2(24, 0), 0), 1));
    cpu.uart_buffer.buf50 = uint(idx_uint4(STATE_TEX_HART(uint2(24, 0), 0), 2));
    cpu.uart_buffer.buf51 = uint(idx_uint4(STATE_TEX_HART(uint2(24, 0), 0), 3));
    cpu.uart_buffer.buf52 = uint(idx_uint4(STATE_TEX_HART(uint2(25, 0), 0), 0));
    cpu.uart_buffer.buf53 = uint(idx_uint4(STATE_TEX_HART(uint2(25, 0), 0), 1));
    cpu.uart_buffer.buf54 = uint(idx_uint4(STATE_TEX_HART(uint2(25, 0), 0), 2));
    cpu.uart_buffer.buf55 = uint(idx_uint4(STATE_TEX_HART(uint2(25, 0), 0), 3));
    cpu.uart_buffer.buf56 = uint(idx_uint4(STATE_TEX_HART(uint2(26, 0), 0), 0));
    cpu.uart_buffer.buf57 = uint(idx_uint4(STATE_TEX_HART(uint2(26, 0), 0), 1));
    cpu.uart_buffer.buf58 = uint(idx_uint4(STATE_TEX_HART(uint2(26, 0), 0), 2));
    cpu.uart_buffer.buf59 = uint(idx_uint4(STATE_TEX_HART(uint2(26, 0), 0), 3));
    cpu.uart_buffer.buf60 = uint(idx_uint4(STATE_TEX_HART(uint2(27, 0), 0), 0));
    cpu.uart_buffer.buf61 = uint(idx_uint4(STATE_TEX_HART(uint2(27, 0), 0), 1));
    cpu.uart_buffer.buf62 = uint(idx_uint4(STATE_TEX_HART(uint2(27, 0), 0), 2));
    cpu.uart_buffer.buf63 = uint(idx_uint4(STATE_TEX_HART(uint2(27, 0), 0), 3));
    cpu.stall = uint(idx_uint4(STATE_TEX_HART(uint2(28, 0), 0), 0));
    cpu.clock = uint(idx_uint4(STATE_TEX_HART(uint2(28, 0), 0), 1));
    cpu.commits = uint(idx_uint4(STATE_TEX_HART(uint2(28, 0), 0), 2));
    cpu.xreg[0] = uint(idx_uint4(STATE_TEX_HART(uint2(28, 0), 0), 3));
    cpu.xreg[1] = uint(idx_uint4(STATE_TEX_HART(uint2(29, 0), 0), 0));
    cpu.xreg[2] = uint(idx_uint4(STATE_TEX_HART(uint2(29, 0), 0), 1));
    cpu.xreg[3] = uint(idx_uint4(STATE_TEX_HART(uint2(29, 0), 0), 2));
    cpu.xreg[4] = uint(idx_uint4(STATE_TEX_HART(uint2(29, 0), 0), 3));
    cpu.xreg[5] = uint(idx_uint4(STATE_TEX_HART(uint2(30, 0), 0), 0));
    cpu.xreg[6] = uint(idx_uint4(STATE_TEX_HART(uint2(30, 0), 0), 1));
    cpu.xreg[7] = uint(idx_uint4(STATE_TEX_HART(uint2(30, 0), 0), 2));
    cpu.xreg[8] = uint(idx_uint4(STATE_TEX_HART(uint2(30, 0), 0), 3));
    cpu.xreg[9] = uint(idx_uint4(STATE_TEX_HART(uint2(31, 0), 0), 0));
    cpu.xreg[10] = uint(idx_uint4(STATE_TEX_HART(uint2(31, 0), 0), 1));
    cpu.xreg[11] = uint(idx_uint4(STATE_TEX_HART(uint2(31, 0), 0), 2));
    cpu.xreg[12] = uint(idx_uint4(STATE_TEX_HART(uint2(31, 0), 0), 3));
    cpu.xreg[13] = uint(idx_uint4(STATE_TEX_HART(uint2(32, 0), 0), 0));
    cpu.xreg[14] = uint(idx_uint4(STATE_TEX_HART(uint2(32, 0), 0), 1));
    cpu.xreg[15] = uint(idx_uint4(STATE_TEX_HART(uint2(32, 0), 0), 2));
    cpu.xreg[16] = uint(idx_uint4(STATE_TEX_HART(uint2(32, 0), 0), 3));
    cpu.xreg[17] = uint(idx_uint4(STATE_TEX_HART(uint2(33, 0), 0), 0));
    cpu.xreg[18] = uint(idx_uint4(STATE_TEX_HART(uint2(33, 0), 0), 1));
    cpu.xreg[19] = uint(idx_uint4(STATE_TEX_HART(uint2(33, 0), 0), 2));
    cpu.xreg[20] = uint(idx_uint4(STATE_TEX_HART(uint2(33, 0), 0), 3));
    cpu.xreg[21] = uint(idx_uint4(STATE_TEX_HART(uint2(34, 0), 0), 0));
    cpu.xreg[22] = uint(idx_uint4(STATE_TEX_HART(uint2(34, 0), 0), 1));
    cpu.xreg[23] = uint(idx_uint4(STATE_TEX_HART(uint2(34, 0), 0), 2));
    cpu.xreg[24] = uint(idx_uint4(STATE_TEX_HART(uint2(34, 0), 0), 3));
    cpu.xreg[25] = uint(idx_uint4(STATE_TEX_HART(uint2(35, 0), 0), 0));
    cpu.xreg[26] = uint(idx_uint4(STATE_TEX_HART(uint2(35, 0), 0), 1));
    cpu.xreg[27] = uint(idx_uint4(STATE_TEX_HART(uint2(35, 0), 0), 2));
    cpu.xreg[28] = uint(idx_uint4(STATE_TEX_HART(uint2(35, 0), 0), 3));
    cpu.xreg[29] = uint(idx_uint4(STATE_TEX_HART(uint2(36, 0), 0), 0));
    cpu.xreg[30] = uint(idx_uint4(STATE_TEX_HART(uint2(36, 0), 0), 1));
    cpu.xreg[31] = uint(idx_uint4(STATE_TEX_HART(uint2(36, 0), 0), 2));
    cpu.pc = uint(idx_uint4(STATE_TEX_HART(uint2(36, 0), 0), 3));
    cpu.reservation_en = bool(idx_uint4(STATE_TEX_HART(uint2(37, 0), 0), 0));
    cpu.reservation_addr = uint(idx_uint4(STATE_TEX_HART(uint2(37, 0), 0), 1));
    cpu.memop_src_v = uint(idx_uint4(STATE_TEX_HART(uint2(37, 0), 0), 2));
    cpu.memop_dst_v = uint(idx_uint4(STATE_TEX_HART(uint2(37, 0), 0), 3));
    cpu.memop_src_p = uint(idx_uint4(STATE_TEX_HART(uint2(38, 0), 0), 0));
    cpu.memop_dst_p = uint(idx_uint4(STATE_TEX_HART(uint2(38, 0), 0), 1));
    cpu.memop_n = uint(idx_uint4(STATE_TEX_HART(uint2(38, 0), 0), 2));
    cpu.stall_count = uint(idx_uint4(STATE_TEX_HART(uint2(38, 0), 0), 3));
    cpu.trap_count = uint(idx_uint4(STATE_TEX_HART(uint2(39, 0), 0), 0));
    cpu.rtc0 = uint(idx_uint4(STATE_TEX_HART(uint2(39, 0), 0), 1));
    cpu.rtc1 = uint(idx_uint4(STATE_TEX_HART(uint2(39, 0), 0), 2));
    cpu.start_time_ref = asfloat(idx_uint4(STATE_TEX_HART(uint2(39, 0), 0), 3));
    cpu.debug_do_tick = uint(idx_uint4(STATE_TEX_HART(uint2(40, 0), 0), 0));
    cpu.debug_last_ins = uint(idx_uint4(STATE_TEX_HART(uint2(40, 0), 0), 1));
    cpu.debug_last_stall = uint(idx_uint4(STATE_TEX_HART(uint2(40, 0), 0), 2));
    cpu.debug_arb_0 = uint(idx_uint4(STATE_TEX_HART(uint2(40, 0), 0), 3));

}
#endif

#ifdef PASS_TICK
bool pixel_has_state(uint2 pos) {
    // CSR data area and FB are not "state", they're only touched by commit
    uint lin = pos.x + 64 * pos.y;
    return lin < 44 || (lin >= 1068 && lin < 2092);
}

uint4 encode(uint2 pos) {
    // L1 cache
    uint s_lin = pos.x + pos.y * 64;
    if (s_lin >= 1068 && s_lin < 2092) {
        uint offset = s_lin - 1068;
        return l1_cache[offset];
    }

    // fallback is passthrough
    uint4 ret = STATE_TEX(pos);

    // cpu_t serialization
    uint pos_id = pos.x | (pos.y << 16);
    [forcecase]
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
        ret.r = uint(cpu.clint.msip);
        ret.a = uint(cpu.clint.mtime_lo);
        ret.b = uint(cpu.clint.mtimecmp_hi);
        ret.g = uint(cpu.clint.mtimecmp_lo);
        return ret;
    case 11:
        ret.r = uint(cpu.clint.mtime_hi);
        ret.g = uint(cpu.mmu.mode);
        ret.b = uint(cpu.mmu.ppn);
        ret.a = uint(cpu.uart_buffer.ptr);
        return ret;
    case 12:
        ret.r = uint(cpu.uart_buffer.buf0);
        ret.g = uint(cpu.uart_buffer.buf1);
        ret.b = uint(cpu.uart_buffer.buf2);
        ret.a = uint(cpu.uart_buffer.buf3);
        return ret;
    case 13:
        ret.r = uint(cpu.uart_buffer.buf4);
        ret.g = uint(cpu.uart_buffer.buf5);
        ret.b = uint(cpu.uart_buffer.buf6);
        ret.a = uint(cpu.uart_buffer.buf7);
        return ret;
    case 14:
        ret.b = uint(cpu.uart_buffer.buf10);
        ret.a = uint(cpu.uart_buffer.buf11);
        ret.r = uint(cpu.uart_buffer.buf8);
        ret.g = uint(cpu.uart_buffer.buf9);
        return ret;
    case 15:
        ret.r = uint(cpu.uart_buffer.buf12);
        ret.g = uint(cpu.uart_buffer.buf13);
        ret.b = uint(cpu.uart_buffer.buf14);
        ret.a = uint(cpu.uart_buffer.buf15);
        return ret;
    case 16:
        ret.r = uint(cpu.uart_buffer.buf16);
        ret.g = uint(cpu.uart_buffer.buf17);
        ret.b = uint(cpu.uart_buffer.buf18);
        ret.a = uint(cpu.uart_buffer.buf19);
        return ret;
    case 17:
        ret.r = uint(cpu.uart_buffer.buf20);
        ret.g = uint(cpu.uart_buffer.buf21);
        ret.b = uint(cpu.uart_buffer.buf22);
        ret.a = uint(cpu.uart_buffer.buf23);
        return ret;
    case 18:
        ret.r = uint(cpu.uart_buffer.buf24);
        ret.g = uint(cpu.uart_buffer.buf25);
        ret.b = uint(cpu.uart_buffer.buf26);
        ret.a = uint(cpu.uart_buffer.buf27);
        return ret;
    case 19:
        ret.r = uint(cpu.uart_buffer.buf28);
        ret.g = uint(cpu.uart_buffer.buf29);
        ret.b = uint(cpu.uart_buffer.buf30);
        ret.a = uint(cpu.uart_buffer.buf31);
        return ret;
    case 2:
        ret.r = uint(cpu.cache.csr_cache_4_addr);
        ret.g = uint(cpu.cache.csr_cache_4_val);
        ret.b = uint(cpu.cache.csr_cache_5_addr);
        ret.a = uint(cpu.cache.csr_cache_5_val);
        return ret;
    case 20:
        ret.r = uint(cpu.uart_buffer.buf32);
        ret.g = uint(cpu.uart_buffer.buf33);
        ret.b = uint(cpu.uart_buffer.buf34);
        ret.a = uint(cpu.uart_buffer.buf35);
        return ret;
    case 21:
        ret.r = uint(cpu.uart_buffer.buf36);
        ret.g = uint(cpu.uart_buffer.buf37);
        ret.b = uint(cpu.uart_buffer.buf38);
        ret.a = uint(cpu.uart_buffer.buf39);
        return ret;
    case 22:
        ret.r = uint(cpu.uart_buffer.buf40);
        ret.g = uint(cpu.uart_buffer.buf41);
        ret.b = uint(cpu.uart_buffer.buf42);
        ret.a = uint(cpu.uart_buffer.buf43);
        return ret;
    case 23:
        ret.r = uint(cpu.uart_buffer.buf44);
        ret.g = uint(cpu.uart_buffer.buf45);
        ret.b = uint(cpu.uart_buffer.buf46);
        ret.a = uint(cpu.uart_buffer.buf47);
        return ret;
    case 24:
        ret.r = uint(cpu.uart_buffer.buf48);
        ret.g = uint(cpu.uart_buffer.buf49);
        ret.b = uint(cpu.uart_buffer.buf50);
        ret.a = uint(cpu.uart_buffer.buf51);
        return ret;
    case 25:
        ret.r = uint(cpu.uart_buffer.buf52);
        ret.g = uint(cpu.uart_buffer.buf53);
        ret.b = uint(cpu.uart_buffer.buf54);
        ret.a = uint(cpu.uart_buffer.buf55);
        return ret;
    case 26:
        ret.r = uint(cpu.uart_buffer.buf56);
        ret.g = uint(cpu.uart_buffer.buf57);
        ret.b = uint(cpu.uart_buffer.buf58);
        ret.a = uint(cpu.uart_buffer.buf59);
        return ret;
    case 27:
        ret.r = uint(cpu.uart_buffer.buf60);
        ret.g = uint(cpu.uart_buffer.buf61);
        ret.b = uint(cpu.uart_buffer.buf62);
        ret.a = uint(cpu.uart_buffer.buf63);
        return ret;
    case 28:
        ret.g = uint(cpu.clock);
        ret.b = uint(cpu.commits);
        ret.r = uint(cpu.stall);
        ret.a = uint(cpu.xreg[0]);
        return ret;
    case 29:
        ret.r = uint(cpu.xreg[1]);
        ret.g = uint(cpu.xreg[2]);
        ret.b = uint(cpu.xreg[3]);
        ret.a = uint(cpu.xreg[4]);
        return ret;
    case 3:
        ret.r = uint(cpu.cache.csr_cache_6_addr);
        ret.g = uint(cpu.cache.csr_cache_6_val);
        ret.b = uint(cpu.cache.csr_cache_7_addr);
        ret.a = uint(cpu.cache.csr_cache_7_val);
        return ret;
    case 30:
        ret.r = uint(cpu.xreg[5]);
        ret.g = uint(cpu.xreg[6]);
        ret.b = uint(cpu.xreg[7]);
        ret.a = uint(cpu.xreg[8]);
        return ret;
    case 31:
        ret.g = uint(cpu.xreg[10]);
        ret.b = uint(cpu.xreg[11]);
        ret.a = uint(cpu.xreg[12]);
        ret.r = uint(cpu.xreg[9]);
        return ret;
    case 32:
        ret.r = uint(cpu.xreg[13]);
        ret.g = uint(cpu.xreg[14]);
        ret.b = uint(cpu.xreg[15]);
        ret.a = uint(cpu.xreg[16]);
        return ret;
    case 33:
        ret.r = uint(cpu.xreg[17]);
        ret.g = uint(cpu.xreg[18]);
        ret.b = uint(cpu.xreg[19]);
        ret.a = uint(cpu.xreg[20]);
        return ret;
    case 34:
        ret.r = uint(cpu.xreg[21]);
        ret.g = uint(cpu.xreg[22]);
        ret.b = uint(cpu.xreg[23]);
        ret.a = uint(cpu.xreg[24]);
        return ret;
    case 35:
        ret.r = uint(cpu.xreg[25]);
        ret.g = uint(cpu.xreg[26]);
        ret.b = uint(cpu.xreg[27]);
        ret.a = uint(cpu.xreg[28]);
        return ret;
    case 36:
        ret.a = uint(cpu.pc);
        ret.r = uint(cpu.xreg[29]);
        ret.g = uint(cpu.xreg[30]);
        ret.b = uint(cpu.xreg[31]);
        return ret;
    case 37:
        ret.a = uint(cpu.memop_dst_v);
        ret.b = uint(cpu.memop_src_v);
        ret.g = uint(cpu.reservation_addr);
        ret.r = uint(cpu.reservation_en);
        return ret;
    case 38:
        ret.g = uint(cpu.memop_dst_p);
        ret.b = uint(cpu.memop_n);
        ret.r = uint(cpu.memop_src_p);
        ret.a = uint(cpu.stall_count);
        return ret;
    case 39:
        ret.g = uint(cpu.rtc0);
        ret.b = uint(cpu.rtc1);
        ret.a = asuint(cpu.start_time_ref);
        ret.r = uint(cpu.trap_count);
        return ret;
    case 4:
        ret.r = uint(cpu.cache.csr_cache_8_addr);
        ret.g = uint(cpu.cache.csr_cache_8_val);
        ret.b = uint(cpu.cache.csr_cache_9_addr);
        ret.a = uint(cpu.cache.csr_cache_9_val);
        return ret;
    case 40:
        ret.a = uint(cpu.debug_arb_0);
        ret.r = uint(cpu.debug_do_tick);
        ret.g = uint(cpu.debug_last_ins);
        ret.b = uint(cpu.stall == 0 ? cpu.debug_last_stall : cpu.stall);
        return ret;
    case 5:
        ret.r = uint(cpu.cache.csr_cache_10_addr);
        ret.g = uint(cpu.cache.csr_cache_10_val);
        ret.b = uint(cpu.cache.csr_cache_11_addr);
        ret.a = uint(cpu.cache.csr_cache_11_val);
        return ret;
    case 6:
        ret.r = uint(cpu.cache.csr_cache_12_addr);
        ret.g = uint(cpu.cache.csr_cache_12_val);
        ret.b = uint(cpu.cache.csr_cache_13_addr);
        ret.a = uint(cpu.cache.csr_cache_13_val);
        return ret;
    case 7:
        ret.r = uint(cpu.cache.csr_cache_14_addr);
        ret.g = uint(cpu.cache.csr_cache_14_val);
        ret.b = uint(cpu.cache.csr_cache_15_addr);
        ret.a = uint(cpu.cache.csr_cache_15_val);
        return ret;
    case 8:
        ret.r = uint(cpu.cache.ram_l1_last_addr);
        ret.g = uint(cpu.cache.ram_l1_last_val);
        ret.b = uint(cpu.csr.privilege);
        ret.a = uint(cpu.uart.rbr_thr_ier_iir);
        return ret;
    case 9:
        ret.a = uint(cpu.uart.input_tag);
        ret.b = uint(cpu.uart.interrupting);
        ret.r = uint(cpu.uart.lcr_mcr_lsr_scr);
        ret.g = uint(cpu.uart.thre_ip);
        return ret;

    }

    return ret;
}

uint tex_get_csr(uint addr) {
    uint lin = (addr >> 2) + 44;
    uint idx = addr & 0x3;
    return idx_uint4(STATE_TEX(uint2(lin % 64, lin / 64)), idx);
}
#endif

uint mem_get_cached_or_tex_from_state_cache(uint addr) {
    // array-style L1 (direct texture access)
    for (uint i = 0; i < 2; i++) {
        uint arr_idx = RAM_L1_ARRAY_IDX(addr) + i * 512;
        uint lin = 1068 + arr_idx;
        uint4 cur = STATE_TEX_HART(uint2(lin % 64, lin / 64), 0);
             if (cur.x == addr) return cur.y;
        else if (cur.z == addr) return cur.w;
    }

    // query RAM texture
    uint idx = (addr >> 2) & 0x3;
    addr >>= 4;
    uint4 raw = STATE_TEX_HART(RAM_ADDR(addr), 0);
    return idx_uint4(raw, idx);
}

#ifdef PASS_COMMIT
uint mem_get_cached_or_tex_from_state_cache_or_mtd(uint addr) {
    if (addr & 0x80000000) {
        return mem_get_cached_or_tex_from_state_cache(addr & 0x7fffffff);
    } else if (addr & 0x40000000) {
        // query MTD/ROM
        uint mtd_addr = addr - 0x40000000;
        uint mtd_idx = (mtd_addr >> 2) & 0x3;
        mtd_addr = mtd_addr >> 4;
        uint2 mtd_lin = uint2(mtd_addr % m_dim.x, mtd_addr / m_dim.x);
        mtd_lin.y = m_dim.y - mtd_lin.y - 1;
        //[branch] if (mtd_lin.y >= m_dim.y) return 0;
        float4 full;
        [branch]
        switch (mtd_idx) {
            case 0:
                full = _Data_MTD_R[mtd_lin];
                break;
            case 1:
                full = _Data_MTD_G[mtd_lin];
                break;
            case 2:
                full = _Data_MTD_B[mtd_lin];
                break;
            case 3:
                full = _Data_MTD_A[mtd_lin];
                break;
        }
        return unpack_raw_float4(full);
    }
    return 0;
}

uint4 commit(uint2 pos) {
    if (pos.y < 64 && pos.x >= 64) {
        return (uint4)0;
    }

    // fallback is passthrough
    uint4 ret = STATE_TEX_HART(pos, 0);

    uint pos_id = pos.x | ((pos.y) << 16);

    // increment commits
    if (!_Init && pos_id == 28) {
        ++ret.b;
    }

    // clear stalls
    if (pos_id == 28) {
        switch (ret.r) {
            case STALL_CSR_CACHE:
                ret.r = 0;
                break;
            case STALL_MEM_CACHE_L1:
                ret.r = 0;
                break;
            case STALL_FENCE:
                ret.r = 0;
                break;
            case STALL_MEMOP_COPY: // will be handled now, so we can unset
                ret.r = 0;
                break;
            case STALL_UART:
                ret.r = 0;
                break;
        }
    }

    uint s_lin = pos.x + pos.y * 64;

    // CSR area
    if (s_lin >= 44 && s_lin < 1068) {
        uint addr = s_lin - 44;
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
    if (pos.y >= 64) {
        uint2 pos_ram = uint2(pos.x, pos.y - 64);
        uint lin = pos_ram.x + pos_ram.y * 2048;

        if (_Init) {
            // init main memory from texture
            uint2 ram_dim;
            _Data_RAM_A.GetDimensions(ram_dim.x, ram_dim.y);
            uint2 pos2 = uint2(pos.x, pos.y - 64);
            // something feels off here... off by one, you might say...
            // ...but this way it actually works
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
                        uint offset = lin_word - cpu.memop_dst_p;
                        uint src = cpu.memop_src_p + offset;
                        uint transfer = mem_get_cached_or_tex_from_state_cache_or_mtd(src);
                        set_idx_uint4(ret, transfer, icp);
                    }
                }
            } else {
                // write back L1 cache
                [loop]
                for (uint offset = 0; offset < 4; offset++) {
                    uint addr_off = lin + (offset << 2);
                    for (uint slice = 0; slice < 2; slice++) {
                        uint cache_idx = RAM_L1_ARRAY_IDX(addr_off) + slice * 512;
                        uint lin = 1068 + cache_idx;
                        uint4 cur = STATE_TEX_HART(uint2(lin % 64, lin / 64), 0);
                             if (cur.x == addr_off) { set_idx_uint4(ret, cur.y, offset); }
                        else if (cur.z == addr_off) { set_idx_uint4(ret, cur.w, offset); }
                    }
                }

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
    private const int STATE_WIDTH = 64;
    private const int STATE_HEIGHT = 64;
    private const int TOTAL_WIDTH = 2048;
    private const int TOTAL_HEIGHT = 4096;
    private int[] addr_lin(int lin) {
        int[] ret = new int[3];
        ret[2] = lin & 0x3; // c
        lin = lin >> 2;
        ret[0] = lin % 64; // x
        ret[1] = lin / 64; // y
        return ret;
    }
    private uint load_csr__privilege() { return decodePackedData(8, 0, 2); }
    private uint load_uart__rbr_thr_ier_iir() { return decodePackedData(8, 0, 3); }
    private uint load_uart__lcr_mcr_lsr_scr() { return decodePackedData(9, 0, 0); }
    private uint load_uart__thre_ip() { return decodePackedData(9, 0, 1); }
    private uint load_uart__interrupting() { return decodePackedData(9, 0, 2); }
    private uint load_uart__input_tag() { return decodePackedData(9, 0, 3); }
    private uint load_clint__msip() { return decodePackedData(10, 0, 0); }
    private uint load_clint__mtimecmp_lo() { return decodePackedData(10, 0, 1); }
    private uint load_clint__mtimecmp_hi() { return decodePackedData(10, 0, 2); }
    private uint load_clint__mtime_lo() { return decodePackedData(10, 0, 3); }
    private uint load_clint__mtime_hi() { return decodePackedData(11, 0, 0); }
    private uint load_mmu__mode() { return decodePackedData(11, 0, 1); }
    private uint load_mmu__ppn() { return decodePackedData(11, 0, 2); }
    private uint load_stall() { return decodePackedData(28, 0, 0); }
    private uint load_clock() { return decodePackedData(28, 0, 1); }
    private uint load_commits() { return decodePackedData(28, 0, 2); }
    private uint load_xreg0() { return decodePackedData(28, 0, 3); }
    private uint load_xreg1() { return decodePackedData(29, 0, 0); }
    private uint load_xreg2() { return decodePackedData(29, 0, 1); }
    private uint load_xreg3() { return decodePackedData(29, 0, 2); }
    private uint load_xreg4() { return decodePackedData(29, 0, 3); }
    private uint load_xreg5() { return decodePackedData(30, 0, 0); }
    private uint load_xreg6() { return decodePackedData(30, 0, 1); }
    private uint load_xreg7() { return decodePackedData(30, 0, 2); }
    private uint load_xreg8() { return decodePackedData(30, 0, 3); }
    private uint load_xreg9() { return decodePackedData(31, 0, 0); }
    private uint load_xreg10() { return decodePackedData(31, 0, 1); }
    private uint load_xreg11() { return decodePackedData(31, 0, 2); }
    private uint load_xreg12() { return decodePackedData(31, 0, 3); }
    private uint load_xreg13() { return decodePackedData(32, 0, 0); }
    private uint load_xreg14() { return decodePackedData(32, 0, 1); }
    private uint load_xreg15() { return decodePackedData(32, 0, 2); }
    private uint load_xreg16() { return decodePackedData(32, 0, 3); }
    private uint load_xreg17() { return decodePackedData(33, 0, 0); }
    private uint load_xreg18() { return decodePackedData(33, 0, 1); }
    private uint load_xreg19() { return decodePackedData(33, 0, 2); }
    private uint load_xreg20() { return decodePackedData(33, 0, 3); }
    private uint load_xreg21() { return decodePackedData(34, 0, 0); }
    private uint load_xreg22() { return decodePackedData(34, 0, 1); }
    private uint load_xreg23() { return decodePackedData(34, 0, 2); }
    private uint load_xreg24() { return decodePackedData(34, 0, 3); }
    private uint load_xreg25() { return decodePackedData(35, 0, 0); }
    private uint load_xreg26() { return decodePackedData(35, 0, 1); }
    private uint load_xreg27() { return decodePackedData(35, 0, 2); }
    private uint load_xreg28() { return decodePackedData(35, 0, 3); }
    private uint load_xreg29() { return decodePackedData(36, 0, 0); }
    private uint load_xreg30() { return decodePackedData(36, 0, 1); }
    private uint load_xreg31() { return decodePackedData(36, 0, 2); }
    private uint load_pc() { return decodePackedData(36, 0, 3); }
    private uint load_reservation_en() { return decodePackedData(37, 0, 0); }
    private uint load_reservation_addr() { return decodePackedData(37, 0, 1); }
    private uint load_memop_src_v() { return decodePackedData(37, 0, 2); }
    private uint load_memop_dst_v() { return decodePackedData(37, 0, 3); }
    private uint load_memop_src_p() { return decodePackedData(38, 0, 0); }
    private uint load_memop_dst_p() { return decodePackedData(38, 0, 1); }
    private uint load_memop_n() { return decodePackedData(38, 0, 2); }
    private uint load_stall_count() { return decodePackedData(38, 0, 3); }
    private uint load_trap_count() { return decodePackedData(39, 0, 0); }
    private uint load_rtc0() { return decodePackedData(39, 0, 1); }
    private uint load_rtc1() { return decodePackedData(39, 0, 2); }
    private uint load_start_time_ref() { return decodePackedData(39, 0, 3); }
    private uint load_debug_do_tick() { return decodePackedData(40, 0, 0); }
    private uint load_debug_last_ins() { return decodePackedData(40, 0, 1); }
    private uint load_debug_last_stall() { return decodePackedData(40, 0, 2); }
    private uint load_debug_arb_0() { return decodePackedData(40, 0, 3); }
    private uint load_csr(int addr) {
        int lin = (addr >> 2) + 44;
        return decodePackedData(lin % 64, lin / 64, addr & 0x3);
    }
    private uint load_l1_cache(int addr) {
        int lin = (addr >> 2) + 1068;
        return decodePackedData(lin % 64, lin / 64, addr & 0x3);
    }
    #endregion

*/
