#ifndef CSR_H
#define CSR_H



/* must match set/line count above, shift by two to ignore byte offset */
#define RAM_L1_TAG(a) ((a >> 2) & 0xf)


#define CSR_USTATUS 0x000
#define CSR_UIE 0x004
#define CSR_UTVEC 0x005
#define _CSR_USCRATCH 0x040
#define CSR_UEPC 0x041
#define CSR_UCAUSE 0x042
#define CSR_UTVAL 0x043
#define _CSR_UIP 0x044
#define CSR_SSTATUS 0x100
#define CSR_SEDELEG 0x102
#define CSR_SIDELEG 0x103
#define CSR_SIE 0x104
#define CSR_STVEC 0x105
#define _CSR_SSCRATCH 0x140
#define CSR_SEPC 0x141
#define CSR_SCAUSE 0x142
#define CSR_STVAL 0x143
#define CSR_SIP 0x144
#define CSR_SATP 0x180
#define CSR_MSTATUS 0x300
#define CSR_MISA 0x301
#define CSR_MEDELEG 0x302
#define CSR_MIDELEG 0x303
#define CSR_MIE 0x304
#define CSR_MTVEC 0x305
#define _CSR_MSCRATCH 0x340
#define CSR_MEPC 0x341
#define CSR_MCAUSE 0x342
#define CSR_MTVAL 0x343
#define CSR_MIP 0x344
#define _CSR_PMPCFG0 0x3a0
#define _CSR_PMPADDR0 0x3b0
#define CSR_MCYCLE 0xb00
#define CSR_CYCLE 0xc00
#define CSR_TIME 0xc01
#define _CSR_INSERT 0xc02
#define CSR_MHARTID 0xf14

#define CSR_MEMOP_OP 0x0b0
#define CSR_MEMOP_SRC 0x0b1
#define CSR_MEMOP_DST 0x0b2
#define CSR_MEMOP_N 0x0b3

bool has_csr_access_privilege(uint addr) {
    uint privilege = (addr >> 8) & 0x3;
    return privilege <= cpu.csr.privilege;
}

// SSTATUS, SIE, and SIP are subsets of MSTATUS, MIE, and MIP
uint read_csr_raw(uint address) {
    address &= 0x1fff;

    uint read_mask = 0xffffffff;

    [branch]
    switch (address) {
        case CSR_MISA: return 0x40141101; // 0b01000000000101000001000100000001 = RV32AIMSU
        case CSR_SSTATUS: address = CSR_MSTATUS; read_mask = 0x000de162; break;
        case CSR_SIE: address = CSR_MIE; read_mask = 0x222; break;
        case CSR_SIP: address = CSR_MIP; read_mask = 0x222; break;
        case CSR_TIME: return cpu.clint.mtime_lo;
        case CSR_MCYCLE: return cpu.clock;
        case CSR_CYCLE: return cpu.clock;
        case CSR_MHARTID: return 0;
        case CSR_SATP: return (cpu.mmu.mode << 31) | cpu.mmu.ppn;
    }

    uint ret;

    if (false) {}
    else if (cpu.cache.csr_cache_0_addr == address) { ret = cpu.cache.csr_cache_0_val; }
else if (cpu.cache.csr_cache_1_addr == address) { ret = cpu.cache.csr_cache_1_val; }
else if (cpu.cache.csr_cache_2_addr == address) { ret = cpu.cache.csr_cache_2_val; }
else if (cpu.cache.csr_cache_3_addr == address) { ret = cpu.cache.csr_cache_3_val; }
else if (cpu.cache.csr_cache_4_addr == address) { ret = cpu.cache.csr_cache_4_val; }
else if (cpu.cache.csr_cache_5_addr == address) { ret = cpu.cache.csr_cache_5_val; }
else if (cpu.cache.csr_cache_6_addr == address) { ret = cpu.cache.csr_cache_6_val; }
else if (cpu.cache.csr_cache_7_addr == address) { ret = cpu.cache.csr_cache_7_val; }
else if (cpu.cache.csr_cache_8_addr == address) { ret = cpu.cache.csr_cache_8_val; }
else if (cpu.cache.csr_cache_9_addr == address) { ret = cpu.cache.csr_cache_9_val; }
else if (cpu.cache.csr_cache_10_addr == address) { ret = cpu.cache.csr_cache_10_val; }
else if (cpu.cache.csr_cache_11_addr == address) { ret = cpu.cache.csr_cache_11_val; }
else if (cpu.cache.csr_cache_12_addr == address) { ret = cpu.cache.csr_cache_12_val; }
else if (cpu.cache.csr_cache_13_addr == address) { ret = cpu.cache.csr_cache_13_val; }
else if (cpu.cache.csr_cache_14_addr == address) { ret = cpu.cache.csr_cache_14_val; }
else if (cpu.cache.csr_cache_15_addr == address) { ret = cpu.cache.csr_cache_15_val; }

    else {
        // fallback, read value from CSR texture area
        ret = tex_get_csr(address);
    }

    return ret & read_mask;
}

void write_csr_raw(uint address, uint value) {
    uint where = address & 0x1fff;
    uint what = value;
    uint modify_mask = 0;
    ins_ret nop = ins_ret_noop();
    [branch]
    switch (address) {
        case CSR_SSTATUS:
            where = CSR_MSTATUS;
            modify_mask = 0x000de162;
            break;
        case CSR_SIE:
            where = CSR_MIE;
            modify_mask = 0x222;
            break;
        case CSR_SIP:
            where = CSR_MIP;
            modify_mask = 0x222;
            break;
        case CSR_MIDELEG:
            what &= 0x666; // from qemu
            break;
        case CSR_MEMOP_SRC:
            cpu.memop_src_v = what;
            return;
        case CSR_MEMOP_DST:
            cpu.memop_dst_v = what;
            return;
        case CSR_MEMOP_N:
            cpu.memop_n = what;
            return;
        case CSR_MEMOP_OP:
            cpu.stall = STALL_MEMOP_COPY;
            return;
    };

    if (modify_mask) {
        what = (read_csr_raw(where) & ~modify_mask) | (value & modify_mask);
    }

    if (false) {}
else if (cpu.cache.csr_cache_0_addr == 0xffffffff || cpu.cache.csr_cache_0_addr == where) { cpu.cache.csr_cache_0_addr = where; cpu.cache.csr_cache_0_val = what; return; }
else if (cpu.cache.csr_cache_1_addr == 0xffffffff || cpu.cache.csr_cache_1_addr == where) { cpu.cache.csr_cache_1_addr = where; cpu.cache.csr_cache_1_val = what; return; }
else if (cpu.cache.csr_cache_2_addr == 0xffffffff || cpu.cache.csr_cache_2_addr == where) { cpu.cache.csr_cache_2_addr = where; cpu.cache.csr_cache_2_val = what; return; }
else if (cpu.cache.csr_cache_3_addr == 0xffffffff || cpu.cache.csr_cache_3_addr == where) { cpu.cache.csr_cache_3_addr = where; cpu.cache.csr_cache_3_val = what; return; }
else if (cpu.cache.csr_cache_4_addr == 0xffffffff || cpu.cache.csr_cache_4_addr == where) { cpu.cache.csr_cache_4_addr = where; cpu.cache.csr_cache_4_val = what; return; }
else if (cpu.cache.csr_cache_5_addr == 0xffffffff || cpu.cache.csr_cache_5_addr == where) { cpu.cache.csr_cache_5_addr = where; cpu.cache.csr_cache_5_val = what; return; }
else if (cpu.cache.csr_cache_6_addr == 0xffffffff || cpu.cache.csr_cache_6_addr == where) { cpu.cache.csr_cache_6_addr = where; cpu.cache.csr_cache_6_val = what; return; }
else if (cpu.cache.csr_cache_7_addr == 0xffffffff || cpu.cache.csr_cache_7_addr == where) { cpu.cache.csr_cache_7_addr = where; cpu.cache.csr_cache_7_val = what; return; }
else if (cpu.cache.csr_cache_8_addr == 0xffffffff || cpu.cache.csr_cache_8_addr == where) { cpu.cache.csr_cache_8_addr = where; cpu.cache.csr_cache_8_val = what; return; }
else if (cpu.cache.csr_cache_9_addr == 0xffffffff || cpu.cache.csr_cache_9_addr == where) { cpu.cache.csr_cache_9_addr = where; cpu.cache.csr_cache_9_val = what; return; }
else if (cpu.cache.csr_cache_10_addr == 0xffffffff || cpu.cache.csr_cache_10_addr == where) { cpu.cache.csr_cache_10_addr = where; cpu.cache.csr_cache_10_val = what; return; }
else if (cpu.cache.csr_cache_11_addr == 0xffffffff || cpu.cache.csr_cache_11_addr == where) { cpu.cache.csr_cache_11_addr = where; cpu.cache.csr_cache_11_val = what; return; }
else if (cpu.cache.csr_cache_12_addr == 0xffffffff || cpu.cache.csr_cache_12_addr == where) { cpu.cache.csr_cache_12_addr = where; cpu.cache.csr_cache_12_val = what; return; }
else if (cpu.cache.csr_cache_13_addr == 0xffffffff || cpu.cache.csr_cache_13_addr == where) { cpu.cache.csr_cache_13_addr = where; cpu.cache.csr_cache_13_val = what; return; }
else if (cpu.cache.csr_cache_14_addr == 0xffffffff || cpu.cache.csr_cache_14_addr == where) { cpu.cache.csr_cache_14_addr = where; cpu.cache.csr_cache_14_val = what; return; }


    // cache overflow, stall to avoid fillup
    cpu.cache.csr_cache_15_addr = where;
    cpu.cache.csr_cache_15_val = what;
    cpu.stall = STALL_CSR_CACHE;
}


uint get_csr(uint address, inout ins_ret ret) {
    if (has_csr_access_privilege(address)) {
        uint r = read_csr_raw(address);
        return r;
    } else {
        ret.trap.en = true;
        ret.trap.type = trap_IllegalInstruction;
        ret.trap.value = cpu.pc;
        return 0;
    }
}

void set_csr(uint address, uint value, inout ins_ret ret) {
    bool read_only = ((address >> 10) & 0x3) == 0x3;
    if (has_csr_access_privilege(address) && !read_only) {
        if (address == CSR_SATP) {
            mmu_update(value);
            return;
        }
        write_csr_raw(address, value);
    } else {
        ret.trap.en = true;
        ret.trap.type = trap_IllegalInstruction;
        ret.trap.value = cpu.pc;
    }
}

#endif
