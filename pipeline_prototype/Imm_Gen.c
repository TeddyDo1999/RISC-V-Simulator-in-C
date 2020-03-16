#include "Imm_Gen.h"

unsigned int power2(int START, int END) {
    int counter = 0;
    int value = 1;
    int difference = START-END+1;
    for (counter; counter<difference;counter++) {
        value = value*2;
    }
    return value;
}

unsigned int partial_imm(unsigned int instruction, int START, int END) {
    unsigned int base = (int) (power2(START,END)-1) << END;
    unsigned int Imm_part = (instruction & base) >> END;
    return Imm_part;
}

int get_imm(unsigned int instruction, unsigned int fmt_code) {
    if (fmt_code == I_type)
    {
        return (instruction >> 20) & 0b111111111111;
    }
    else if (fmt_code == S_type)
    {
        int imm_11_5 = partial_imm(instruction, 31, 25);
        int imm_4_0 = partial_imm(instruction,11,7);
        return ((imm_11_5 << 5) | imm_4_0);
    }
    else if (fmt_code == SB_type)
    {
        int imm_12 = partial_imm(instruction,31,31);
        int imm_11 = partial_imm(instruction,7,7);
        int imm_10_5 = partial_imm(instruction,30,25);
        int imm_4_1 = partial_imm(instruction,11,8);
        return ((imm_12 << 13) | (imm_11 << 12) | (imm_10_5 << 6) | imm_4_1 << 2);    
    }
    else if (fmt_code == U_type)
    {
        int imm_31_12 = instruction >> 12;
        return (imm_31_12 << 12);
    }
    else if (fmt_code == UJ_type)
    {
        int imm_20 = partial_imm(instruction,31,31);
        int imm_19_12 = partial_imm(instruction,19,12);
        int imm_11_11 = partial_imm(instruction,20,20);
        int imm_10_1 = partial_imm(instruction,30,21);
        return ((imm_20 << 20)|(imm_19_12 << 12)|(imm_11_11 << 11)|(imm_10_1 << 1));
    }
    else {
        return -1;
    }
}

int64_t generate_32_to_64bit(int immediate, unsigned int fmt_code) {
    unsigned int imm_bitcount;
    if (fmt_code == U_type) {
        imm_bitcount = 32;
    }
    else if (fmt_code == UJ_type) {
        imm_bitcount = 21;
    }
    else if (fmt_code == SB_type) {
        imm_bitcount = 14;
    }
    else {
        imm_bitcount = 12;
    }
    unsigned int signed_bit = immediate >> (imm_bitcount-1);
    if (signed_bit == 0) {
        int64_t immediate64 = (int64_t) immediate;
        return immediate64;
    }
    else {
        int64_t bit_base = 0b1;
        for (int i = 0; i < (64 - imm_bitcount); i++) {
            bit_base = (bit_base << 1) | 0b1;
        }
        int64_t immediate64 = (int64_t)((bit_base << imm_bitcount) | immediate);
        return immediate64;
    }
}

unsigned int get_format(unsigned int opcode) {
        unsigned int opcode_5bits = opcode >> 2;
        unsigned int fmt_code = 0;
        switch (opcode_5bits)
        {
        case 0b01000:
                fmt_code = S_type;
                break;
        case 0b01100:
                fmt_code = R_type;
                break;
        case 0b01110:
                fmt_code = R_type;
                break;
        case 0b11000:
                fmt_code = SB_type;
                break;
        case 0b11011:
                fmt_code = UJ_type;
                break;         
        case 0b00101:
                fmt_code = U_type;
                break;
        case 0b01101:
                fmt_code = U_type;
                break;       
        default:
                fmt_code = I_type;
                break;
        }
        return fmt_code;
}

int64_t generate_immediate(Decoder decode) {
    unsigned int fmt_code = get_format(decode.opcode);
    int immediate = get_imm(decode.instruction, fmt_code);
    int64_t Immediate = generate_32_to_64bit(immediate,fmt_code);
    return Immediate;
}