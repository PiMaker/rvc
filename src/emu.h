#ifndef EMU_H
#define EMU_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "ins.h"
#include "mem.h"
#include "trap.h"
#include "csr.h"

#define AS_SIGNED(val) (*(int32_t*)&val)
#define AS_UNSIGNED(val) (*(uint*)&val)
const uint ZERO = 0;
const uint ONE = 1;

#define DEF(name, fmt_t, code) \
    void emu_##name(cpu_t *cpu, uint ins_word, ins_ret *ret, fmt_t ins) { code }

#define WR_RD(code) { ret->write_reg = ins.rd; ret->write_val = AS_UNSIGNED(code); }
#define WR_PC(code) { ret->pc_val = code; }
#define WR_CSR(code) { ret->csr_write = ins.csr; ret->csr_val = code; }

/*
 *   BEGIN INSTRUCTIONS
 */

DEF(add, FormatR, { // rv32i
    WR_RD(AS_SIGNED(cpu->xreg[ins.rs1]) + AS_SIGNED(cpu->xreg[ins.rs2]));
})
DEF(addi, FormatI, { // rv32i
    WR_RD(AS_SIGNED(cpu->xreg[ins.rs1]) + AS_SIGNED(ins.imm));
})
DEF(amoswap_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    mem_set_word(cpu, cpu->xreg[ins.rs1], cpu->xreg[ins.rs2]);
    WR_RD(tmp)
})
DEF(amoadd_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    mem_set_word(cpu, cpu->xreg[ins.rs1], cpu->xreg[ins.rs2] + tmp);
    WR_RD(tmp)
})
DEF(amoxor_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    mem_set_word(cpu, cpu->xreg[ins.rs1], cpu->xreg[ins.rs2] ^ tmp);
    WR_RD(tmp)
})
DEF(amoand_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    mem_set_word(cpu, cpu->xreg[ins.rs1], cpu->xreg[ins.rs2] & tmp);
    WR_RD(tmp)
})
DEF(amoor_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    mem_set_word(cpu, cpu->xreg[ins.rs1], cpu->xreg[ins.rs2] | tmp);
    WR_RD(tmp)
})
DEF(amomin_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    uint sec = cpu->xreg[ins.rs2];
    mem_set_word(cpu, cpu->xreg[ins.rs1], AS_SIGNED(sec) < AS_SIGNED(tmp) ? sec : tmp);
    WR_RD(tmp)
})
DEF(amomax_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    uint sec = cpu->xreg[ins.rs2];
    mem_set_word(cpu, cpu->xreg[ins.rs1], AS_SIGNED(sec) > AS_SIGNED(tmp) ? sec : tmp);
    WR_RD(tmp)
})
DEF(amominu_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    uint sec = cpu->xreg[ins.rs2];
    mem_set_word(cpu, cpu->xreg[ins.rs1], sec < tmp ? sec : tmp);
    WR_RD(tmp)
})
DEF(amomaxu_w, FormatR, { // rv32a
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1]);
    uint sec = cpu->xreg[ins.rs2];
    mem_set_word(cpu, cpu->xreg[ins.rs1], sec > tmp ? sec : tmp);
    WR_RD(tmp)
})
DEF(and, FormatR, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] & cpu->xreg[ins.rs2])
})
DEF(andi, FormatI, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] & ins.imm)
})
DEF(auipc, FormatU, { // rv32i
    WR_RD(cpu->pc + ins.imm)
})
DEF(beq, FormatB, { // rv32i
    if (cpu->xreg[ins.rs1] == cpu->xreg[ins.rs2]) {
        WR_PC(cpu->pc + ins.imm);
    }
})
DEF(bge, FormatB, { // rv32i
    if (AS_SIGNED(cpu->xreg[ins.rs1]) >= AS_SIGNED(cpu->xreg[ins.rs2])) {
        WR_PC(cpu->pc + ins.imm);
    }
})
DEF(bgeu, FormatB, { // rv32i
    if (AS_UNSIGNED(cpu->xreg[ins.rs1]) >= AS_UNSIGNED(cpu->xreg[ins.rs2])) {
        WR_PC(cpu->pc + ins.imm);
    }
})
DEF(blt, FormatB, { // rv32i
    if (AS_SIGNED(cpu->xreg[ins.rs1]) < AS_SIGNED(cpu->xreg[ins.rs2])) {
        WR_PC(cpu->pc + ins.imm);
    }
})
DEF(bltu, FormatB, { // rv32i
    if (AS_UNSIGNED(cpu->xreg[ins.rs1]) < AS_UNSIGNED(cpu->xreg[ins.rs2])) {
        WR_PC(cpu->pc + ins.imm);
    }
})
DEF(bne, FormatB, { // rv32i
    if (cpu->xreg[ins.rs1] != cpu->xreg[ins.rs2]) {
        WR_PC(cpu->pc + ins.imm);
    }
})
DEF(csrrc, FormatCSR, { // system
    uint rs = cpu->xreg[ins.rs];
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
    uint rs = cpu->xreg[ins.rs];
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
    WR_CSR(cpu->xreg[ins.rs]);
    WR_RD(ins.value)
})
DEF(csrrwi, FormatCSR, { // system
    WR_CSR(ins.rs);
    WR_RD(ins.value)
})
DEF(div, FormatR, { // rv32m
    uint dividend = cpu->xreg[ins.rs1];
    uint divisor = cpu->xreg[ins.rs2];
    uint result;
    if (divisor == 0) {
        result = 0xFFFFFFFF;
    } else if (dividend == 0x80000000 && divisor == 0xFFFFFFFF) {
        result = dividend;
    } else {
        int32_t tmp = AS_SIGNED(dividend) / AS_SIGNED(divisor);
        result = AS_UNSIGNED(tmp);
    }
    WR_RD(result)
})
DEF(divu, FormatR, { // rv32m
    uint dividend = cpu->xreg[ins.rs1];
    uint divisor = cpu->xreg[ins.rs2];
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
    if (cpu->xreg[17] == 93) {
        // EXIT CALL
        uint status = cpu->xreg[10] >> 1;
        printf("ecall EXIT = %d (0x%x)\n", status, status);
        exit(status);
    }

    ret->trap.en = true;
    ret->trap.value = cpu->pc;
    if (cpu->csr.privilege == PRIV_USER) {
        ret->trap.type = trap_EnvironmentCallFromUMode;
    } else if (cpu->csr.privilege == PRIV_SUPERVISOR) {
        ret->trap.type = trap_EnvironmentCallFromSMode;
    } else { // PRIV_MACHINE
        ret->trap.type = trap_EnvironmentCallFromMMode;
    }
})
DEF(fence, FormatEmpty, { // rv32i
    // skip
})
DEF(fence_i, FormatEmpty, { // rv32i
    // skip
})
DEF(jal, FormatJ, { // rv32i
    WR_RD(cpu->pc + 4);
    WR_PC(cpu->pc + ins.imm);
})
DEF(jalr, FormatI, { // rv32i
    WR_RD(cpu->pc + 4);
    WR_PC(cpu->xreg[ins.rs1] + ins.imm);
})
DEF(lb, FormatI, { // rv32i
    uint tmp = sign_extend(mem_get_byte(cpu, cpu->xreg[ins.rs1] + ins.imm), 8);
    WR_RD(tmp)
})
DEF(lbu, FormatI, { // rv32i
    uint tmp = mem_get_byte(cpu, cpu->xreg[ins.rs1] + ins.imm);
    WR_RD(tmp)
})
DEF(lh, FormatI, { // rv32i
    uint tmp = sign_extend(mem_get_half_word(cpu, cpu->xreg[ins.rs1] + ins.imm), 16);
    WR_RD(tmp)
})
DEF(lhu, FormatI, { // rv32i
    uint tmp = mem_get_half_word(cpu, cpu->xreg[ins.rs1] + ins.imm);
    WR_RD(tmp)
})
DEF(lr_w, FormatR, { // rv32a
    uint addr = cpu->xreg[ins.rs1];
    uint tmp = mem_get_word(cpu, addr);
    cpu->reservation_en = true;
    cpu->reservation_addr = addr;
    WR_RD(tmp)
})
DEF(lui, FormatU, { // rv32i
    WR_RD(ins.imm)
})
DEF(lw, FormatI, { // rv32i
    // would need sign extend for xlen > 32
    uint tmp = mem_get_word(cpu, cpu->xreg[ins.rs1] + ins.imm);
    WR_RD(tmp)
})
DEF(mret, FormatEmpty, { // system
    uint newpc = get_csr(cpu, CSR_MEPC, ret);
    if (!ret->trap.en) {
        uint status = read_csr_raw(cpu, CSR_MSTATUS);
        uint mpie = (status >> 7) & 1;
        uint mpp = (status >> 11) & 0x3;
        uint mprv = mpp == PRIV_MACHINE ? ((status >> 17) & 1) : 0;
        uint new_status = (status & ~0x21888) | (mprv << 17) | (mpie << 3) | (1 << 7);
        write_csr_raw(cpu, CSR_MSTATUS, new_status);
        cpu->csr.privilege = mpp;
        WR_PC(newpc)
    }
})
DEF(mul, FormatR, { // rv32m
    uint tmp = AS_SIGNED(cpu->xreg[ins.rs1]) * AS_SIGNED(cpu->xreg[ins.rs2]);
    WR_RD(tmp)
})
DEF(mulh, FormatR, { // rv32m
    uint tmp = ((int64_t)AS_SIGNED(cpu->xreg[ins.rs1]) * (int64_t)AS_SIGNED(cpu->xreg[ins.rs2])) >> 32;
    WR_RD(tmp)
})
DEF(mulhsu, FormatR, { // rv32m
    uint tmp = ((int64_t)AS_SIGNED(cpu->xreg[ins.rs1]) * (uint64_t)AS_UNSIGNED(cpu->xreg[ins.rs2])) >> 32;
    WR_RD(tmp)
})
DEF(mulhu, FormatR, { // rv32m
    uint tmp = ((uint64_t)AS_UNSIGNED(cpu->xreg[ins.rs1]) * (uint64_t)AS_UNSIGNED(cpu->xreg[ins.rs2])) >> 32;
    WR_RD(tmp)
})
DEF(or, FormatR, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] | cpu->xreg[ins.rs2])
})
DEF(ori, FormatI, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] | ins.imm)
})
DEF(rem, FormatR, { // rv32m
    uint dividend = cpu->xreg[ins.rs1];
    uint divisor = cpu->xreg[ins.rs2];
    uint result;
    if (divisor == 0) {
        result = dividend;
    } else if (dividend == 0x80000000 && divisor == 0xFFFFFFFF) {
        result = 0;
    } else {
        int32_t tmp = AS_SIGNED(dividend) % AS_SIGNED(divisor);
        result = AS_UNSIGNED(tmp);
    }
    WR_RD(result)
})
DEF(remu, FormatR, { // rv32m
    uint dividend = cpu->xreg[ins.rs1];
    uint divisor = cpu->xreg[ins.rs2];
    uint result;
    if (divisor == 0) {
        result = dividend;
    } else {
        result = dividend % divisor;
    }
    WR_RD(result)
})
DEF(sb, FormatS, { // rv32i
    mem_set_byte(cpu, cpu->xreg[ins.rs1] + ins.imm, cpu->xreg[ins.rs2]);
})
DEF(sc_w, FormatR, { // rv32a
    // I'm pretty sure this is not it chief, but it does the trick for now
    uint addr = cpu->xreg[ins.rs1];
    if (cpu->reservation_en && cpu->reservation_addr == addr) {
        mem_set_word(cpu, addr, cpu->xreg[ins.rs2]);
        cpu->reservation_en = false;
        WR_RD(ZERO)
    } else {
        WR_RD(ONE)
    }
})
DEF(sfence_vma, FormatEmpty, { // system
    // skip
})
DEF(sh, FormatS, { // rv32i
    mem_set_half_word(cpu, cpu->xreg[ins.rs1] + ins.imm, cpu->xreg[ins.rs2]);
})
DEF(sll, FormatR, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] << cpu->xreg[ins.rs2])
})
DEF(slli, FormatR, { // rv32i
    uint shamt = (ins_word >> 20) & 0x1F;
    WR_RD(cpu->xreg[ins.rs1] << shamt)
})
DEF(slt, FormatR, { // rv32i
    if (AS_SIGNED(cpu->xreg[ins.rs1]) < AS_SIGNED(cpu->xreg[ins.rs2])) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(slti, FormatI, { // rv32i
    if (AS_SIGNED(cpu->xreg[ins.rs1]) < AS_SIGNED(ins.imm)) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(sltiu, FormatI, { // rv32i
    if (AS_UNSIGNED(cpu->xreg[ins.rs1]) < AS_UNSIGNED(ins.imm)) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(sltu, FormatR, { // rv32i
    if (AS_UNSIGNED(cpu->xreg[ins.rs1]) < AS_UNSIGNED(cpu->xreg[ins.rs2])) {
        WR_RD(ONE)
    } else {
        WR_RD(ZERO)
    }
})
DEF(sra, FormatR, { // rv32i
    uint msr = cpu->xreg[ins.rs1] & 0x80000000;
    WR_RD(msr ? ~(~cpu->xreg[ins.rs1] >> cpu->xreg[ins.rs2]) :
                   cpu->xreg[ins.rs1] >> cpu->xreg[ins.rs2])
})
DEF(srai, FormatR, { // rv32i
    uint msr = cpu->xreg[ins.rs1] & 0x80000000;
    uint shamt = (ins_word >> 20) & 0x1F;
    WR_RD(msr ? ~(~cpu->xreg[ins.rs1] >> shamt) :
                   cpu->xreg[ins.rs1] >> shamt)
})
DEF(sret, FormatEmpty, { // system
    uint newpc = get_csr(cpu, CSR_SEPC, ret);
    if (!ret->trap.en) {
        uint status = read_csr_raw(cpu, CSR_SSTATUS);
        uint spie = (status >> 5) & 1;
        uint spp = (status >> 8) & 1;
        uint mprv = spp == PRIV_MACHINE ? ((status >> 17) & 1) : 0;
        uint new_status = (status & ~0x20122) | (mprv << 17) | (spie << 1) | (1 << 5);
        write_csr_raw(cpu, CSR_SSTATUS, new_status);
        cpu->csr.privilege = spp;
        WR_PC(newpc)
    }
})
DEF(srl, FormatR, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] >> cpu->xreg[ins.rs2])
})
DEF(srli, FormatR, { // rv32i
    uint shamt = (ins_word >> 20) & 0x1F;
    WR_RD(cpu->xreg[ins.rs1] >> shamt)
})
DEF(sub, FormatR, { // rv32i
    WR_RD(AS_SIGNED(cpu->xreg[ins.rs1]) - AS_SIGNED(cpu->xreg[ins.rs2]));
})
DEF(sw, FormatS, { // rv32i
    mem_set_word(cpu, cpu->xreg[ins.rs1] + ins.imm, cpu->xreg[ins.rs2]);
})
DEF(uret, FormatEmpty, { // system
    // unnecessary?
})
DEF(wfi, FormatEmpty, { // system
    // no-op is valid here, so skip
})
DEF(xor, FormatR, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] ^ cpu->xreg[ins.rs2])
})
DEF(xori, FormatI, { // rv32i
    WR_RD(cpu->xreg[ins.rs1] ^ ins.imm)
})

/*
 *   END INSTRUCTIONS
 */

#define pr_ins(name) if (VERBOSE >= 3) printf("INS %s (%08x)\n", #name, ins_word);

#define RUN(name, data, insf) case data : { \
    pr_ins(name) \
    emu_##name(cpu, ins_word, &ret, insf); \
    return ret; \
}
ins_ret ins_select(cpu_t *cpu, uint ins_word) {
    uint ins_masked;
    ins_ret ret = ins_ret_noop(cpu);

    FormatR ins_FormatR = parse_FormatR(ins_word);
    FormatI ins_FormatI = parse_FormatI(ins_word);
    FormatS ins_FormatS = parse_FormatS(ins_word);
    FormatU ins_FormatU = parse_FormatU(ins_word);
    FormatJ ins_FormatJ = parse_FormatJ(ins_word);
    FormatB ins_FormatB = parse_FormatB(ins_word);
    FormatCSR ins_FormatCSR = parse_FormatCSR(ins_word);
    FormatEmpty ins_FormatEmpty = parse_FormatEmpty(ins_word);

    if ((ins_word & 0x00000073) == 0x00000073) {
        // could be CSR instruction
        ins_FormatCSR.value = get_csr(cpu, ins_FormatCSR.csr, &ret);
    }

    ins_masked = ins_word & 0x0000007f;
    switch (ins_masked) {
        RUN(auipc, 0x00000017, ins_FormatU)
        RUN(jal, 0x0000006f, ins_FormatJ)
        RUN(lui, 0x00000037, ins_FormatU)
    }
    ins_masked = ins_word & 0x0000707f;
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
    switch (ins_masked) {
        RUN(lr_w, 0x1000202f, ins_FormatR)
    }
    ins_masked = ins_word & 0xfc00707f;
    switch (ins_masked) {
        RUN(slli, 0x00001013, ins_FormatR)
        RUN(srai, 0x40005013, ins_FormatR)
        RUN(srli, 0x00005013, ins_FormatR)
    }
    ins_masked = ins_word & 0xfe00707f;
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
    ins_masked = ins_word & 0xfe007fff;
    switch (ins_masked) {
        RUN(sfence_vma, 0x12000073, ins_FormatEmpty)
    }
    ins_masked = ins_word & 0xffffffff;
    switch (ins_masked) {
        RUN(ebreak, 0x00100073, ins_FormatEmpty)
        RUN(ecall, 0x00000073, ins_FormatEmpty)
        RUN(mret, 0x30200073, ins_FormatEmpty)
        RUN(sret, 0x10200073, ins_FormatEmpty)
        RUN(uret, 0x00200073, ins_FormatEmpty)
        RUN(wfi, 0x10500073, ins_FormatEmpty)
    }

    if (VERBOSE >= 1)
        printf("Invalid instruction: %08x\n", ins_word);
    ret.trap.en = true;
    ret.trap.type = trap_IllegalInstruction;
    ret.trap.value = ins_word;
    return ret;
}


void emulate(cpu_t *cpu) {
    uint ins_word = 0;
    ins_ret ret;
    if ((cpu->pc & 0x3) == 0) {
        ins_word = mem_get_word(cpu, cpu->pc);
        ret = ins_select(cpu, ins_word);

        if (ret.csr_write && !ret.trap.en) {
            set_csr(cpu, ret.csr_write, ret.csr_val, &ret);
        }

        if (!ret.trap.en && ret.write_reg < 32 && ret.write_reg > 0) {
            cpu->xreg[ret.write_reg] = ret.write_val;
        }
    } else {
        ret = ins_ret_noop(cpu);
        ret.trap.en = true;
        ret.trap.type = trap_InstructionAddressMisaligned;
        ret.trap.value = cpu->pc;
    }

    // handle CLINT IRQs
    if (cpu->clint.msip) {
        cpu->csr.data[CSR_MIP] |= MIP_MSIP;
    }

    cpu->clint.mtime_lo++;
    cpu->clint.mtime_hi += cpu->clint.mtime_lo == 0 ? 1 : 0;

    if (cpu->clint.mtimecmp_lo != 0 && cpu->clint.mtimecmp_hi != 0 && (cpu->clint.mtime_hi > cpu->clint.mtimecmp_hi || (cpu->clint.mtime_hi == cpu->clint.mtimecmp_hi && cpu->clint.mtime_lo >= cpu->clint.mtimecmp_lo))) {
        cpu->csr.data[CSR_MIP] |= MIP_MTIP;
    }

    uart_tick(cpu);
    if (cpu->uart.interrupting) {
        uint cur_mip = read_csr_raw(cpu, CSR_MIP);
        write_csr_raw(cpu, CSR_MIP, cur_mip | MIP_SEIP);
    }

    handle_irq_and_trap(cpu, &ret);

    // ret.pc_val should be set to pc+4 by default
    cpu->pc = ret.pc_val;
}

#endif
