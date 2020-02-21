#include "Instruction.h"
#include "Imm_Gen.h"
#include "Controller.h"
#include "ALU_Control.c"

Addr get_next_PC(Addr PC, int64_t Immediate, unsigned int Branch, unsigned int Zero) {
    int64_t Shifted_Immediate = Immediate << 1;
    Addr JUMP_PC = PC + Immediate;
    Addr NEXT_PC = PC + 4;
    if (Branch & Zero) {
        return JUMP_PC;
    }
    else {
        return NEXT_PC;
    }
}