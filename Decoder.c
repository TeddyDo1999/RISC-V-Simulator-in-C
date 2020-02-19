#include "Decoder.h"

unsigned int get_opcode(unsigned int instruction) {
        unsigned int opcode_base, opcode;
        opcode_base = 0b1111111;
        opcode = opcode_base & instruction;
        return opcode;
}

unsigned int get_rd(unsigned int instruction) {
        unsigned int rd_base, rd;
        rd_base = 0b11111 << 7;
        rd = (rd_base & instruction) >> 7;
        return rd;
}

unsigned int get_funct3(unsigned int instruction) {
        unsigned int funct3_base, funct3;
        funct3_base = 0b111 << (7+5);
        funct3 = (funct3_base & instruction) >> (7+5);
        return funct3;
}

unsigned int get_rs1(unsigned int instruction) {
        unsigned int rs1_base, rs1;
        rs1_base = 0b11111 << (7+5+3);
        rs1 = (rs1_base & instruction) >> (7+5+3);
        return rs1;
}

unsigned int get_rs2(unsigned int instruction) {
        unsigned int rs2_base, rs2;
        rs2_base = 0b11111 << (7+5+3+5);
        rs2 = (rs2_base & instruction) >> (7+5+3+5);
        return rs2;
}

unsigned int get_funct7(unsigned int instruction) {
        unsigned int funct7_base, funct7;
        funct7_base = 0b1111111 << (7+5+3+5+5);
        funct7 = (funct7_base & instruction) >> (7+5+3+5+5);
        return funct7;
}

Decoder decode_instruction(unsigned int instruction) {
    Decoder Code;
    Code.instruction = instruction;
    Code.opcode = get_opcode(instruction);
    Code.rd = get_rd(instruction);
    Code.funct3 = get_funct3(instruction);
    Code.rs1 = get_rs1(instruction);
    Code.rs2 = get_rs2(instruction);
    Code.funct7 = get_funct7(instruction);
}
