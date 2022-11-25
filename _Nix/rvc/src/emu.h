#ifndef EMU_H
#define EMU_H

#include "mmu.h"

#define AS_SIGNED(val) (asint(val))
#define AS_UNSIGNED(val) (asuint(val))

// this is just a leftover from C, where AS_SIGNED/AS_UNSIGNED needed this as consts
// please don't judge me
#define ZERO 0
#define ONE 1

#define DEF(name, fmt_t, code) \
    void emu_##name(uint ins_word, inout ins_ret ret, fmt_t ins) { code }

#define WR_RD(code) { ret.write_reg = ins.rd; ret.write_val = AS_UNSIGNED(code); }
#define WR_PC(code) { ret.pc_val = AS_UNSIGNED(code); }
#define WR_CSR(code) { ret.csr_write = ins.csr; ret.csr_val = AS_UNSIGNED(code); }
#define WR_MEM(addr, code, size) { ret.mem_wr_addr = addr; ret.mem_wr_size = size; ret.mem_wr_value = AS_UNSIGNED(code); }

/*
 *   BEGIN INSTRUCTIONS
 */

static uint prepared_mem_val;

DEF(add, FormatR, { // rv32i
    WR_RD(AS_SIGNED(xreg(ins.rs1)) + AS_SIGNED(xreg(ins.rs2)));
})
DEF(addi, FormatI, { // rv32i
    WR_RD(AS_SIGNED(xreg(ins.rs1)) + AS_SIGNED(ins.imm));
})
DEF(amoswap_w, FormatR, { // rv32a
    uint tmp = prepared_mem_val;
    WR_MEM(xreg(ins.rs1), (xreg(ins.rs2)), 32)
    WR_RD(tmp)
})
DEF(amoadd_w, FormatR, { // rv32a
    WR_MEM(xreg(ins.rs1), (xreg(ins.rs2) + prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(amoxor_w, FormatR, { // rv32a
    WR_MEM(xreg(ins.rs1), (xreg(ins.rs2) ^ prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(amoand_w, FormatR, { // rv32a
    WR_MEM(xreg(ins.rs1), (xreg(ins.rs2) & prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(amoor_w, FormatR, { // rv32a
    WR_MEM(xreg(ins.rs1), (xreg(ins.rs2) | prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(amomin_w, FormatR, { // rv32a
    uint sec = xreg(ins.rs2);
    WR_MEM(xreg(ins.rs1), (AS_SIGNED(sec) < AS_SIGNED(prepared_mem_val) ? sec : prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(amomax_w, FormatR, { // rv32a
    uint sec = xreg(ins.rs2);
    WR_MEM(xreg(ins.rs1), (AS_SIGNED(sec) > AS_SIGNED(prepared_mem_val) ? sec : prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(amominu_w, FormatR, { // rv32a
    uint sec = xreg(ins.rs2);
    WR_MEM(xreg(ins.rs1), (AS_UNSIGNED(sec) < AS_UNSIGNED(prepared_mem_val) ? sec : prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(amomaxu_w, FormatR, { // rv32a
    uint sec = xreg(ins.rs2);
    WR_MEM(xreg(ins.rs1), (AS_UNSIGNED(sec) > AS_UNSIGNED(prepared_mem_val) ? sec : prepared_mem_val), 32)
    WR_RD(prepared_mem_val)
})
DEF(and, FormatR, { // rv32i
    WR_RD(xreg(ins.rs1) & xreg(ins.rs2))
})
DEF(andi, FormatI, { // rv32i
    WR_RD(xreg(ins.rs1) & ins.imm)
})
DEF(auipc, FormatU, { // rv32i
    WR_RD(cpu.pc + ins.imm)
})
DEF(beq, FormatB, { // rv32i
    if (xreg(ins.rs1) == xreg(ins.rs2)) {
        WR_PC(cpu.pc + ins.imm);
    }
})
DEF(bge, FormatB, { // rv32i
    if (AS_SIGNED(xreg(ins.rs1)) >= AS_SIGNED(xreg(ins.rs2))) {
        WR_PC(cpu.pc + ins.imm);
    }
})
DEF(bgeu, FormatB, { // rv32i
    if (AS_UNSIGNED(xreg(ins.rs1)) >= AS_UNSIGNED(xreg(ins.rs2))) {
        WR_PC(cpu.pc + ins.imm);
    }
})
DEF(blt, FormatB, { // rv32i
    if (AS_SIGNED(xreg(ins.rs1)) < AS_SIGNED(xreg(ins.rs2))) {
        WR_PC(cpu.pc + ins.imm);
    }
})
DEF(bltu, FormatB, { // rv32i
    if (AS_UNSIGNED(xreg(ins.rs1)) < AS_UNSIGNED(xreg(ins.rs2))) {
        WR_PC(cpu.pc + ins.imm);
    }
})
DEF(bne, FormatB, { // rv32i
    if (xreg(ins.rs1) != xreg(ins.rs2)) {
        WR_PC(cpu.pc + ins.imm);
    }
})
DEF(csrrc, FormatCSR, { // system
    uint rs = xreg(ins.rs);
    if (rs != 0) {
        WR_CSR(ins.value & ~rs);
    }
    WR_RD(ins.value)
})
DEF(csrrci, FormatCSR, { // system
    if (ins.rs != 0) {
        WR_CSR(ins.value & (~ins.rs));
    }
    WR_RD(ins.value)
})
DEF(csrrs, FormatCSR, { // system
    uint rs = xreg(ins.rs);
    if (rs != 0) {
        WR_CSR(ins.value | rs);
    }
    WR_RD(ins.value)
})
DEF(csrrsi, FormatCSR, { // system
    if (ins.rs != 0) {
        WR_CSR(ins.value | ins.rs);
    }
    WR_RD(ins.value)
})
DEF(csrrw, FormatCSR, { // system
    WR_CSR(xreg(ins.rs));
    WR_RD(ins.value)
})
DEF(csrrwi, FormatCSR, { // system
    WR_CSR(ins.rs);
    WR_RD(ins.value)
})
DEF(div, FormatR, { // rv32m
    uint dividend = xreg(ins.rs1);
    uint divisor = xreg(ins.rs2);
    uint result;
    if (divisor == 0) {
        result = 0xFFFFFFFF;
    } else if (dividend == 0x80000000 && divisor == 0xFFFFFFFF) {
        result = dividend;
    } else {
        int tmp = AS_SIGNED(dividend) / AS_SIGNED(divisor);
        result = AS_UNSIGNED(tmp);
    }
    WR_RD(result)
})
DEF(divu, FormatR, { // rv32m
    uint dividend = xreg(ins.rs1);
    uint divisor = xreg(ins.rs2);
    uint result;
    if (divisor == 0) {
        result = 0xFFFFFFFF;
    } else {
        result = dividend / divisor;
    }
    WR_RD(result)
})
DEF(ebreak, FormatEmpty, { // system
    // unnecessary?
})
DEF(ecall, FormatEmpty, { // system
    /* if (xreg(17) == 93) { */
    /*     // EXIT CALL - only used for self-tests */
    /*     uint status = xreg(10); */
    /*     cpu.stall = STALL_EXIT_CALL; */
    /*     write_csr_raw(0x200, status); */
    /* } else { */
    ret.trap.en = true;
    ret.trap.value = cpu.pc;
    if (cpu.csr.privilege == PRIV_USER) {
        ret.trap.type = trap_EnvironmentCallFromUMode;
    } else if (cpu.csr.privilege == PRIV_SUPERVISOR) {
        ret.trap.type = trap_EnvironmentCallFromSMode;
    } else { // PRIV_MACHINE
        ret.trap.type = trap_EnvironmentCallFromMMode;
    }
    /* } */
})
DEF(fence, FormatEmpty, { // rv32i
    // skip
})
DEF(fence_i, FormatEmpty, { // rv32i
    cpu.stall = STALL_FENCE;
})
DEF(jal, FormatJ, { // rv32i
    WR_RD(cpu.pc + 4);
    WR_PC(cpu.pc + ins.imm);
})
DEF(jalr, FormatI, { // rv32i
    WR_RD(cpu.pc + 4);
    WR_PC(xreg(ins.rs1) + ins.imm);
})
DEF(lb, FormatI, { // rv32i
    uint tmp = sign_extend(prepared_mem_val & 0xff, 8);
    WR_RD(tmp)
})
DEF(lbu, FormatI, { // rv32i
    uint tmp = prepared_mem_val & 0xff;
    WR_RD(tmp)
})
DEF(lh, FormatI, { // rv32i
    uint tmp = sign_extend(prepared_mem_val & 0xffff, 16);
    WR_RD(tmp)
})
DEF(lhu, FormatI, { // rv32i
    uint tmp = prepared_mem_val & 0xffff;
    WR_RD(tmp)
})
DEF(lr_w, FormatR, { // rv32a
    uint addr = xreg(ins.rs1);
    uint tmp = prepared_mem_val;
    cpu.reservation_en = true;
    cpu.reservation_addr = addr;
    WR_RD(tmp)
})
DEF(lui, FormatU, { // rv32i
    WR_RD(ins.imm)
})
DEF(lw, FormatI, { // rv32i
    // would need sign extend for xlen > 32
    WR_RD(prepared_mem_val)
})
DEF(mret, FormatEmpty, { // system
    uint newpc = get_csr(CSR_MEPC, ret);
    if (!ret.trap.en) {
        uint status = read_csr_raw(CSR_MSTATUS);
        uint mpie = (status >> 7) & 1;
        uint mpp = (status >> 11) & 0x3;
        uint mprv = mpp == PRIV_MACHINE ? ((status >> 17) & 1) : 0;
        uint new_status = (status & ~0x21888) | (mprv << 17) | (mpie << 3) | (1 << 7);
        write_csr_raw(CSR_MSTATUS, new_status);
        cpu.csr.privilege = mpp;
        WR_PC(newpc)
    }
})
DEF(mul, FormatR, { // rv32m
    uint tmp = AS_SIGNED(xreg(ins.rs1)) * AS_SIGNED(xreg(ins.rs2));
    WR_RD(tmp)
})
DEF(mulh, FormatR, { // rv32m
    // FIXME: mulh-family instructions have to use double precision floating points internally atm...
    // umul/imul (https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/umul--sm4---asm-)
    // do exist, but appear to be unusable?
    precise double op1 = AS_SIGNED(xreg(ins.rs1));
    precise double op2 = AS_SIGNED(xreg(ins.rs2));
    uint tmp = uint((op1 * op2) / 4294967296.0l); // '/ 4294967296' == '>> 32'
    WR_RD(tmp)
})
DEF(mulhsu, FormatR, { // rv32m
    // is the signed/unsigned stuff even correct? who knows...
    precise double op1 = AS_SIGNED(xreg(ins.rs1));
    precise double op2 = AS_UNSIGNED(xreg(ins.rs2));
    uint tmp = uint((op1 * op2) / 4294967296.0l); // '/ 4294967296' == '>> 32'
    WR_RD(tmp)
})
DEF(mulhu, FormatR, { // rv32m
    precise double op1 = AS_UNSIGNED(xreg(ins.rs1));
    precise double op2 = AS_UNSIGNED(xreg(ins.rs2));
    uint tmp = uint((op1 * op2) / 4294967296.0l); // '/ 4294967296' == '>> 32'
    WR_RD(tmp)
})
DEF(or, FormatR, { // rv32i
    WR_RD(xreg(ins.rs1) | xreg(ins.rs2))
})
DEF(ori, FormatI, { // rv32i
    WR_RD(xreg(ins.rs1) | ins.imm)
})
DEF(rem, FormatR, { // rv32m
    uint dividend = xreg(ins.rs1);
    uint divisor = xreg(ins.rs2);
    uint result;
    if (divisor == 0) {
        result = dividend;
    } else if (dividend == 0x80000000 && divisor == 0xFFFFFFFF) {
        result = 0;
    } else {
        int tmp = AS_SIGNED(dividend) % AS_SIGNED(divisor);
        result = AS_UNSIGNED(tmp);
    }
    WR_RD(result)
})
DEF(remu, FormatR, { // rv32m
    uint dividend = xreg(ins.rs1);
    uint divisor = xreg(ins.rs2);
    uint result;
    if (divisor == 0) {
        result = dividend;
    } else {
        result = dividend % divisor;
    }
    WR_RD(result)
})
DEF(sb, FormatS, { // rv32i
    WR_MEM(ins.addr, xreg(ins.rs2), 8)
})
DEF(sc_w, FormatR, { // rv32a
    // I'm pretty sure this is not it chief, but it does the trick for now
    uint addr = xreg(ins.rs1);
    if (cpu.reservation_en && cpu.reservation_addr == addr) {
        WR_MEM(addr, xreg(ins.rs2), 32);
        cpu.reservation_en = false;
        WR_RD(ZERO)
    } else {
        WR_RD(ONE)
    }
})
DEF(sfence_vma, FormatEmpty, { // system
    /* cpu.stall = STALL_FENCE; */
})
DEF(sh, FormatS, { // rv32i
    WR_MEM(ins.addr, xreg(ins.rs2), 16)
})
DEF(sll, FormatR, { // rv32i
    WR_RD(xreg(ins.rs1) << xreg(ins.rs2))
})
DEF(slli, FormatR, { // rv32i
    uint shamt = (ins_word >> 20) & 0x1F;
    WR_RD(xreg(ins.rs1) << shamt)
})
DEF(slt, FormatR, { // rv32i
    if (AS_SIGNED(xreg(ins.rs1)) < AS_SIGNED(xreg(ins.rs2))) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(slti, FormatI, { // rv32i
    if (AS_SIGNED(xreg(ins.rs1)) < AS_SIGNED(ins.imm)) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(sltiu, FormatI, { // rv32i
    if (AS_UNSIGNED(xreg(ins.rs1)) < AS_UNSIGNED(ins.imm)) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(sltu, FormatR, { // rv32i
    if (AS_UNSIGNED(xreg(ins.rs1)) < AS_UNSIGNED(xreg(ins.rs2))) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(sra, FormatR, { // rv32i
    uint msr = xreg(ins.rs1) & 0x80000000;
    WR_RD(msr ? ~(~xreg(ins.rs1) >> xreg(ins.rs2)) :
                   xreg(ins.rs1) >> xreg(ins.rs2))
})
DEF(srai, FormatR, { // rv32i
    uint msr = xreg(ins.rs1) & 0x80000000;
    uint shamt = (ins_word >> 20) & 0x1F;
    WR_RD(msr ? ~(~xreg(ins.rs1) >> shamt) :
                   xreg(ins.rs1) >> shamt)
})
DEF(sret, FormatEmpty, { // system
    uint newpc = get_csr(CSR_SEPC, ret);
    if (!ret.trap.en) {
        uint status = read_csr_raw(CSR_SSTATUS);
        uint spie = (status >> 5) & 1;
        uint spp = (status >> 8) & 1;
        uint mprv = spp == PRIV_MACHINE ? ((status >> 17) & 1) : 0;
        uint new_status = (status & ~0x20122) | (mprv << 17) | (spie << 1) | (1 << 5);
        write_csr_raw(CSR_SSTATUS, new_status);
        cpu.csr.privilege = spp;
        WR_PC(newpc)
    }
})
DEF(srl, FormatR, { // rv32i
    WR_RD(xreg(ins.rs1) >> xreg(ins.rs2))
})
DEF(srli, FormatR, { // rv32i
    uint shamt = (ins_word >> 20) & 0x1F;
    WR_RD(xreg(ins.rs1) >> shamt)
})
DEF(sub, FormatR, { // rv32i
    WR_RD(AS_SIGNED(xreg(ins.rs1)) - AS_SIGNED(xreg(ins.rs2)));
})
DEF(sw, FormatS, { // rv32i
    WR_MEM(ins.addr, xreg(ins.rs2), 32)
})
DEF(uret, FormatEmpty, { // system
    // unnecessary?
})
DEF(wfi, FormatEmpty, { // system
    // no-op is valid here, so skip
})
DEF(xor, FormatR, { // rv32i
    WR_RD(xreg(ins.rs1) ^ xreg(ins.rs2))
})
DEF(xori, FormatI, { // rv32i
    WR_RD(xreg(ins.rs1) ^ ins.imm)
})

/*
 *   END INSTRUCTIONS
 */

#define RUN(name, data, insf) case data : { \
    emu_##name(ins_word, ret, insf); \
    return ret; \
}
ins_ret ins_select(uint ins_word, inout ins_ret ret) {
    uint ins_masked;

    FormatEmpty ins_FormatEmpty = parse_FormatEmpty(ins_word);
    FormatCSR ins_FormatCSR = parse_FormatCSR(ins_word);
    FormatI ins_FormatI = parse_FormatI(ins_word);
    FormatU ins_FormatU = parse_FormatU(ins_word);

    /*
       NOTE: The switch statements below can't all use [forcecase].
       While this would be best for performance (according to my testing),
       it breaks compilation very badly, so only do it for the bigger ones.
    */

    ins_masked = ins_word & 0x0000007f;
    [branch]
    switch (ins_masked) {
        RUN(auipc, 0x00000017, ins_FormatU)
        RUN(jal, 0x0000006f, parse_FormatJ(ins_word))
        RUN(lui, 0x00000037, ins_FormatU)
    }

    FormatR ins_FormatR = parse_FormatR(ins_word);

    ins_masked = ins_word & 0xfe00707f;
    [forcecase]
    switch (ins_masked) {
        RUN(add, 0x00000033, ins_FormatR)
        RUN(and, 0x00007033, ins_FormatR)
        RUN(div, 0x02004033, ins_FormatR)
        RUN(divu, 0x02005033, ins_FormatR)
        RUN(mul, 0x02000033, ins_FormatR)
        RUN(mulh, 0x02001033, ins_FormatR)
        RUN(mulhsu, 0x02002033, ins_FormatR)
        RUN(mulhu, 0x02003033, ins_FormatR)
        RUN(or, 0x00006033, ins_FormatR)
        RUN(rem, 0x02006033, ins_FormatR)
        RUN(remu, 0x02007033, ins_FormatR)
        RUN(sll, 0x00001033, ins_FormatR)
        RUN(slt, 0x00002033, ins_FormatR)
        RUN(sltu, 0x00003033, ins_FormatR)
        RUN(sra, 0x40005033, ins_FormatR)
        RUN(srl, 0x00005033, ins_FormatR)
        RUN(sub, 0x40000033, ins_FormatR)
        RUN(xor, 0x00004033, ins_FormatR)
    }

    FormatS ins_FormatS = parse_FormatS(ins_word);
    FormatB ins_FormatB = parse_FormatB(ins_word);

    // since function calls are all inlined we perform memory accesses
    // all together, this way mem_get_word only has to exist once
    // (though this might cause some unnecessary accesses too)
    uint do_mem_read = 0;
    if ((ins_word & 0x0000007f) == 0x00000003) {
        // lX memory read
        do_mem_read = xreg(ins_FormatI.rs1) + ins_FormatI.imm;
    } else if ((ins_word & 0x0000202f) == 0x0000202f) {
        // atomic memory read
        do_mem_read = xreg(ins_FormatR.rs1);
    }
    if (do_mem_read) {
        /* cpu.debug_arb_3 = do_mem_read; */

        uint prepared_read_addr = mmu_translate(ret, do_mem_read, MMU_ACCESS_READ);
        if (ret.trap.en) {
            return ret;
        }
        // take care of unaligned memory reads using a loop
        // so mem_get_word isn't inlined twice
        uint w1 = 0, w2 = 0;
        [loop]
        for (uint ui = 0; ui < ((prepared_read_addr & 0x3) ? 2 : 1); ui++) {
            uint tmp = mem_get_word((prepared_read_addr & (~0x3)) + 0x4 * ui);
            [flatten]
            if (ui) { w2 = tmp; }
            else { w1 = tmp; }
        }
        prepared_mem_val = w1 >> ((do_mem_read & 0x3) * 8);
        prepared_mem_val |= w2 << ((4 - (do_mem_read & 0x3)) * 8);

        /* cpu.debug_arb_4 = w1; */
        /* cpu.debug_arb_5 = w2; */
        /* cpu.debug_arb_6 = prepared_read_addr; */
        /* cpu.debug_arb_7 = prepared_mem_val; */
    }

    if ((ins_word & 0x00000073) == 0x00000073) {
        // could be CSR instruction
        ins_FormatCSR.value = get_csr(ins_FormatCSR.csr, ret);
    }

    ins_masked = ins_word & 0x0000707f;
    [forcecase]
    switch (ins_masked) {
        RUN(addi, 0x00000013, ins_FormatI)
        RUN(andi, 0x00007013, ins_FormatI)
        RUN(beq, 0x00000063, ins_FormatB)
        RUN(bge, 0x00005063, ins_FormatB)
        RUN(bgeu, 0x00007063, ins_FormatB)
        RUN(blt, 0x00004063, ins_FormatB)
        RUN(bltu, 0x00006063, ins_FormatB)
        RUN(bne, 0x00001063, ins_FormatB)
        RUN(csrrc, 0x00003073, ins_FormatCSR)
        RUN(csrrci, 0x00007073, ins_FormatCSR)
        RUN(csrrs, 0x00002073, ins_FormatCSR)
        RUN(csrrsi, 0x00006073, ins_FormatCSR)
        RUN(csrrw, 0x00001073, ins_FormatCSR)
        RUN(csrrwi, 0x00005073, ins_FormatCSR)
        RUN(fence, 0x0000000f, ins_FormatEmpty)
        RUN(fence_i, 0x0000100f, ins_FormatEmpty)
        RUN(jalr, 0x00000067, ins_FormatI)
        RUN(lb, 0x00000003, ins_FormatI)
        RUN(lbu, 0x00004003, ins_FormatI)
        RUN(lh, 0x00001003, ins_FormatI)
        RUN(lhu, 0x00005003, ins_FormatI)
        RUN(lw, 0x00002003, ins_FormatI)
        RUN(ori, 0x00006013, ins_FormatI)
        RUN(sb, 0x00000023, ins_FormatS)
        RUN(sh, 0x00001023, ins_FormatS)
        RUN(slti, 0x00002013, ins_FormatI)
        RUN(sltiu, 0x00003013, ins_FormatI)
        RUN(sw, 0x00002023, ins_FormatS)
        RUN(xori, 0x00004013, ins_FormatI)
    }

    ins_masked = ins_word & 0xf800707f;
    [forcecase]
    switch (ins_masked) {
        RUN(amoswap_w, 0x0800202f, ins_FormatR)
        RUN(amoadd_w, 0x0000202f, ins_FormatR)
        RUN(amoxor_w, 0x2000202f, ins_FormatR)
        RUN(amoand_w, 0x6000202f, ins_FormatR)
        RUN(amoor_w, 0x4000202f, ins_FormatR)
        RUN(amomin_w, 0x8000202f, ins_FormatR)
        RUN(amomax_w, 0xa000202f, ins_FormatR)
        RUN(amominu_w, 0xc000202f, ins_FormatR)
        RUN(amomaxu_w, 0xe000202f, ins_FormatR)
        RUN(sc_w, 0x1800202f, ins_FormatR)
    }
    ins_masked = ins_word & 0xf9f0707f;
    [branch]
    switch (ins_masked) {
        RUN(lr_w, 0x1000202f, ins_FormatR)
    }
    ins_masked = ins_word & 0xfc00707f;
    [branch]
    switch (ins_masked) {
        RUN(slli, 0x00001013, ins_FormatR)
        RUN(srai, 0x40005013, ins_FormatR)
        RUN(srli, 0x00005013, ins_FormatR)
    }
    ins_masked = ins_word & 0xfe007fff;
    [branch]
    switch (ins_masked) {
        RUN(sfence_vma, 0x12000073, ins_FormatEmpty)
    }
    ins_masked = ins_word & 0xffffffff;
    [branch]
    switch (ins_masked) {
        RUN(ebreak, 0x00100073, ins_FormatEmpty)
        RUN(ecall, 0x00000073, ins_FormatEmpty)
        RUN(mret, 0x30200073, ins_FormatEmpty)
        RUN(sret, 0x10200073, ins_FormatEmpty)
        RUN(uret, 0x00200073, ins_FormatEmpty)
        RUN(wfi, 0x10500073, ins_FormatEmpty)
    }

    ret.trap.en = true;
    ret.trap.type = trap_IllegalInstruction;
    ret.trap.value = ins_word;
    return ret;
}


void emulate() {
    uint ins_word = 0;
    ins_ret ret = ins_ret_noop();
    bool mtip_reset = false;
    if ((cpu.pc & 0x3) == 0) {
        uint ins_addr = mmu_translate(ret, cpu.pc, MMU_ACCESS_FETCH);

        if (!ret.trap.en) {
            ins_word = mem_get_instruction(ins_addr);
            cpu.debug_last_ins = ins_word;

            ret = ins_select(ins_word, ret);

            if (ret.csr_write && !ret.trap.en) {
                set_csr(ret.csr_write, ret.csr_val, ret);

                if (cpu.stall == STALL_MEMOP_COPY) {
                    [loop]
                    for (uint imc = 0; imc < 2; imc++) {
                        uint phys = mmu_translate(ret,
                            imc == 0 ? cpu.memop_src_v : cpu.memop_dst_v,
                            imc == 0 ? MMU_ACCESS_READ : MMU_ACCESS_WRITE);
                        if (ret.trap.en) break;
                        if (imc == 0) {
                            cpu.memop_src_p = phys;
                        } else {
                            // Note: This only allows targets within RAM
                            cpu.memop_dst_p = phys & 0x7fffffff;
                        }
                    }
                }
            }

            if (ret.mem_wr_size && !ret.trap.en) {
                uint write_addr = mmu_translate(ret, ret.mem_wr_addr, MMU_ACCESS_WRITE);
                if (!ret.trap.en) {
                    mem_set(write_addr, ret.mem_wr_value, ret.mem_wr_size / 8);

                    // MTIP (machine timer interrupt pending) resets when mtimecmp is written
                    if (write_addr == 0x02004000) {
                        mtip_reset = true;
                    }
                }
            }

            if (!ret.trap.en && ret.write_reg) {
                #define C(x) case x: cpu.xreg[x] = ret.write_val; break;
                if (ret.write_reg < 16) {
                    [flatten]
                    switch (ret.write_reg) {
                              C(1)  C(2)  C(3)
                        C(4)  C(5)  C(6)  C(7)
                        C(8)  C(9)  C(10) C(11)
                        C(12) C(13) C(14) C(15)
                    }
                } else {
                    [flatten]
                    switch (ret.write_reg) {
                        C(16) C(17) C(18) C(19)
                        C(20) C(21) C(22) C(23)
                        C(24) C(25) C(26) C(27)
                        C(28) C(29) C(30) C(31)
                    }
                }
                #undef C
            }
        }
    } else {
        ret.trap.en = true;
        ret.trap.type = trap_InstructionAddressMisaligned;
        ret.trap.value = cpu.pc;
    }

    // handle CLINT IRQs
    uint mip_override = read_csr_raw(CSR_MIP);
    if (cpu.clint.msip) {
        mip_override |= MIP_MSIP;
    }

    double mtime = (double)_Time.x * 1000000.0 * 0.1;
    cpu.clint.mtime_lo = (uint)(floor(glsl_mod(mtime, 4294967296.0))); // & 0xffffffff
    cpu.clint.mtime_hi = (uint)(mtime / 4294967296.0); // >> 32

    if ((cpu.clint.mtimecmp_lo != 0 || cpu.clint.mtimecmp_hi != 0) && (cpu.clint.mtime_hi > cpu.clint.mtimecmp_hi || (cpu.clint.mtime_hi == cpu.clint.mtimecmp_hi && cpu.clint.mtime_lo >= cpu.clint.mtimecmp_lo))) {
        mip_override |= MIP_MTIP;
    }
    [flatten]
    if (mtip_reset) {
        mip_override &= ~MIP_MTIP;
    }

    uart_tick();
    //if (cpu.uart.interrupting) {
    //    mip_override |= MIP_SEIP;
    //}

    /* if (ret.trap.en && cpu.clock <= 1) { */
    /*     cpu.stall = STALL_ILLEGAL_ENTRY_POINT; */
    /*     cpu.stall_count = ins_word; */
    /*     cpu.trap_count = cpu.pc; */
    /* } */

    // will write CSR_MIP if necessary
    handle_irq_and_trap(ret, mip_override);

    /* if (ret.pc_val & 0x3) { */
    /*     cpu.debug_arb_0 = ret.pc_val; */
    /*     cpu.debug_arb_1 = ret.trap.en; */
    /*     cpu.debug_arb_2 = ret.trap.type; */
    /*     cpu.debug_arb_3 = ret.trap.value; */
    /*     cpu.debug_do_tick = 0xffffffff; */
    /*     _DoTick = cpu.debug_do_tick; */
    /*     cpu.stall = STALL_FENCE; */
    /* } */

    // ret.pc_val should be set to pc+4 by default
    cpu.pc = ret.pc_val;
}

#endif
