#ifndef INS_H
#define INS_H

typedef struct {
    uint rs1;
    uint rs2;
    uint imm;
} FormatB;

FormatB parse_FormatB(uint word) {
    FormatB ret;
    ret.rs1 = (word >> 15) & 0x1f;
    ret.rs2 = (word >> 20) & 0x1f;
    ret.imm = (word & 0x80000000 ? 0xfffff000 : 0) |
        ((word << 4) & 0x00000800) |
        ((word >> 20) & 0x000007e0) |
        ((word >> 7) & 0x0000001e);
    return ret;
}

typedef struct {
    uint csr;
    uint rs;
    uint rd;
    uint value;
} FormatCSR;

FormatCSR parse_FormatCSR(uint word) {
    FormatCSR ret;
    ret.csr = (word >> 20) & 0xfff;
    ret.rs = (word >> 15) & 0x1f;
    ret.rd = (word >> 7) & 0x1f;
    return ret;
}

typedef struct {
    uint rd;
    uint rs1;
    uint imm;
} FormatI;

FormatI parse_FormatI(uint word) {
    FormatI ret;
    ret.rd = (word >> 7) & 0x1f;
    ret.rs1 = (word >> 15) & 0x1f;
    ret.imm = (word & 0x80000000 ? 0xfffff800 : 0) |
        ((word >> 20) & 0x000007ff);
    return ret;
}

typedef struct {
    uint rd;
    uint imm;
} FormatJ;

FormatJ parse_FormatJ(uint word) {
    FormatJ ret;
    ret.rd = (word >> 7) & 0x1f;
    ret.imm = (word & 0x80000000 ? 0xfff00000 : 0) |
        (word & 0x000ff000) |
        ((word & 0x00100000) >> 9) |
        ((word & 0x7fe00000) >> 20);
    return ret;
}

typedef struct {
    uint rd;
    uint rs1;
    uint rs2;
    uint rs3;
} FormatR;

FormatR parse_FormatR(uint word) {
    FormatR ret;
    ret.rd = (word >> 7) & 0x1f;
    ret.rs1 = (word >> 15) & 0x1f;
    ret.rs2 = (word >> 20) & 0x1f;
    ret.rs3 = (word >> 27) & 0x1f;
    return ret;
}

typedef struct {
    uint rs2;
    uint addr;
} FormatS;

FormatS parse_FormatS(uint word) {
    FormatS ret;
    uint rs1 = (word >> 15) & 0x1f;
    ret.rs2 = (word >> 20) & 0x1f;
    uint imm = (word & 0x80000000 ? 0xfffff000 : 0) |
        ((word >> 20) & 0xfe0) |
        ((word >> 7) & 0x1f);
    // special case, FormatS is always treated this way:
    ret.addr = xreg(rs1) + imm;
    return ret;
}

typedef struct {
    uint rd;
    uint imm;
} FormatU;

FormatU parse_FormatU(uint word) {
    FormatU ret;
    ret.rd = (word >> 7) & 0x1f;
    ret.imm = word & 0xfffff000;
    return ret;
}

typedef struct {
} FormatEmpty;

FormatEmpty parse_FormatEmpty(uint word) {
    FormatEmpty ret;
    return ret;
}

#endif
