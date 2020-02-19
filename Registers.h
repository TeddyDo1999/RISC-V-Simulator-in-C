#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdint.h>
#include "Controller.h"
#include "Decoder.h"

#define NUM_OF_REGS 64

extern const char* REGISTER_NAME[NUM_OF_REGS];

typedef struct {
    uint64_t REG_VAL[NUM_OF_REGS]; // Declare number of registers and size 
    uint64_t *pt_rd, *pt_rs1, *pt_rs2; // pointers to destination's and sources' registers 
    control_signal *pt_RegWrite; // pointer to RegWrite control signal 
    uint64_t *pt_WriteData; // poitner to data to be written to registers
} Register;

// Fetch registers to operands //
void fetch_operands(Decoder decode, Controller Ctrl, Register Reg);

// NEED STORE / WRITEBACK FUNCTION HERE //

#endif
