#ifndef __IMM_GEN_H__
#define __IMM_GEN_H__

#include "Decoder.h"

#include <stdint.h>

#define R_type 1
#define I_type 2
#define S_type 3
#define SB_type 4
#define U_type 5
#define UJ_type 6

typedef int64_t Imm_Gen;

unsigned int power2(int START, int END);
unsigned int partial_imm(unsigned int instruction, int START, int END);
int get_imm(unsigned int instruction, unsigned int fmt_code);

int64_t generate_32_to_64bit(int immediate, unsigned int fmt_code);

unsigned int get_format(unsigned int opcode);

int64_t generate_immediate(Decoder decode);

#endif
