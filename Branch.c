#include "Branch.h"

Addr get_next_PC(Addr PC, int64_t Immediate, unsigned int Branch, unsigned int Zero, unsigned int ALUSrc, ALU aluOut) {
    int64_t Shifted_Immediate = Immediate << 1;
    Addr JUMP_PC = PC + Shifted_Immediate;
    Addr NEXT_PC = PC + 4;
    Addr JUMP_PC2 = aluOut.result*4;
    if (Branch & Zero) {
        if (ALUSrc == 0) {
            return JUMP_PC;
        } else  {
            return JUMP_PC2;
        }
    }
    else {
        return NEXT_PC;
    }
}