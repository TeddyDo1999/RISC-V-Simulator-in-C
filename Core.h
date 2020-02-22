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

typedef struct Core
{
    Tick clk; // Keep track of core clock
    Addr PC; // Keep track of program counter

    // TODO, define your components here
    // What else you need? Data memory? Register file?
    Instruction_Memory *instr_mem;
    Controller controller;
    Register regBlock; // Cannot declare as "register" //
    Cell dataMem[DATAMEM_SIZE]; 
    Imm_Gen immediate;
    ALU alu;

    // TODO, simulation function
    bool (*tick)(Core *core);
} Core;

Core *initCore(Instruction_Memory *i_mem);
bool tickFunc(Core *core);

#endif
