#include "Instruction.h"
#include "Imm_Gen.h"
#include "Controller.h"
#include "ALU_Control.h"

Addr get_next_PC(Addr PC, int64_t Immediate, unsigned int Branch, unsigned int Zero, unsigned int ALUSrc, ALU aluOut);