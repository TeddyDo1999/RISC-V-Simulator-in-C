#ifndef __CORE_H__
#define __CORE_H__

#include "Instruction_Memory.h"
#include "Registers.h"
#include "Controller.h"
#include "Imm_Gen.h"
#include "Data_Memory.h"
#include "Decoder.h"
#include "Branch.h"
// #include "ALU_Control.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define BOOL bool

struct Core;
typedef struct Core Core;

typedef struct {
    int valid_bit; 
    Addr PC_value;
    Decoder decoded_instruction;
} IF_ID_reg;

typedef struct {
    int valid_bit;
    Controller controller;
    Addr PC_val;
    int64_t rs1_val, rs2_val;
    Imm_Gen immediate_val;
    Decoder decoded_instruction;
} ID_EX_reg;

typedef struct {
    int valid_bit;
    Controller controller;
    Addr New_PC_val;
    ALU ALU_output;
    int64_t rs2_val;
    Decoder decoded_instruction;
} EX_MEM_reg;

typedef struct {
    int valid_bit;
    Controller controller;
    int64_t val_dataMem;
    int64_t ALU_result;
    Decoder decoded_instruction;
} MEM_WB_reg;

typedef struct Core
{
    Tick clk; // Keep track of core clock
    Addr PC; // Keep track of program counter

    // TODO, define your components here
    // What else you need? Data memory? Register file?
    Instruction_Memory *instr_mem;
    IF_ID_reg IF_ID_pipeline;

    Controller controller;
    Register regBlock; // Cannot declare as "register" //
    Imm_Gen immediate;
    ID_EX_reg ID_EX_pipeline;

    ALU alu;
    EX_MEM_reg EX_MEM_pipeline;

    Cell dataMem[DATAMEM_SIZE];
    MEM_WB_reg MEM_WB_pipeline;

    // TODO, simulation function
    bool (*tick)(Core *core);
} Core;

Core *initCore(Instruction_Memory *i_mem);
bool tickFunc(Core *core);

#endif
