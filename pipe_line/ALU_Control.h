#include "Controller.h"
#include "Decoder.h"


typedef struct{
    int64_t result;
    unsigned int zero;
} ALU; // output signals from ALU

unsigned int ALU_Control(unsigned int opcode, unsigned int func3, unsigned int func7);

void ALU_block(unsigned int operation,int64_t opr1, int64_t opr2, ALU *outSig);