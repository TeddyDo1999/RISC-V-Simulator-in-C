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

unsigned int get_imm(unsigned int instruction, unsigned int fmt_code) {
    if (fmt_code == I_type)
    {
        return (instruction >> 20);
    }
    else if (fmt_code == S_type)
    {
        unsigned int imm_11_5 = partial_imm(instruction, 11, 5);
        unsigned int imm_4_0 = partial_imm(instruction,4,0);
        return ((imm_11_5 << 5) | imm_4_0);
    }
    else if (fmt_code == SB_type)
    {
        unsigned int imm_11 = partial_imm(instruction,11,11);
        unsigned int imm_10 = partial_imm(instruction,10,10);
        unsigned int imm_9_4 = partial_imm(instruction,9,4);
        unsigned int imm_3_0 = partial_imm(instruction,3,0);
        return ((imm_11 << 11) | (imm_10 << 10) | (imm_9_4 << 4) | imm_3_0);    
    }
    else if (fmt_code == U_type)
    {
        return (instruction >> 12);
    }
    else if (fmt_code == UJ_type)
    {
        unsigned int imm_19 = partial_imm(instruction,19,19);
        unsigned int imm_18_11 = partial_imm(instruction,18,11);
        unsigned int imm_10_10 = partial_imm(instruction,10,10);
        unsigned int imm_9_0 = partial_imm(instruction,9,0);
        return ((imm_19 << 19)|(imm_18_11 << 11)|(imm_10_10 << 10)|(imm_9_0));
    }
    else {
        return -1;
    }
}

int64_t generate_32_to_64bit(unsigned int immediate, unsigned int fmt_code) {
    unsigned int imm_bitcount;
    if ((fmt_code == U_type) || (fmt_code == UJ_type)) {
        imm_bitcount = 20;
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
        int64_t bit_base = 1;
        for (int i = 0; i < (64 - imm_bitcount); i++) {
            bit_base = (bit_base << 1) & 0x1;
        }
        int64_t immediate64 = (int64_t)((bit_base << imm_bitcount) & immediate);
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

int64_t generate_immediate(Decoder decode, int64_t Immediate) {
    unsigned int fmt_code = get_format(decode.opcode);
    unsigned int immediate = get_imm(decode.instruction, fmt_code);
    Immediate = generate_32_to_64bit(immediate,fmt_code);
}