#ifndef __DECODER_H__
#define __DECODER_H__

#include <stdlib.h>
#include <stdio.h>

unsigned int get_opcode(unsigned int instruction);
unsigned int get_rd(unsigned int instruction);
unsigned int get_funct3(unsigned int instruction);
unsigned int get_rs1(unsigned int instruction);
unsigned int get_rs2(unsigned int instruction);
unsigned int get_funct7(unsigned int instruction);

typedef struct {
    unsigned int instruction;
    unsigned int opcode;
    unsigned int rd;
    unsigned int funct3;
    unsigned int rs1;
    unsigned int rs2;
    unsigned int funct7;
} Decoder;

Decoder decode_instruction(unsigned instruction);

#endif