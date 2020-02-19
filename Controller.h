#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <stdlib.h>
#include "Decoder.h"

#define LOAD 0
#define ILOGIC 1
#define STORE 2
#define RLOGIC 3
#define SB 4
#define IJUMP 5
#define UJ 6

#define FALSE 0
#define TRUE 1

typedef unsigned int control_signal;

unsigned int check_one(unsigned int data, int BEGIN, int END);
unsigned int validate_opcode(unsigned int opcode);
void get_ctrl_signal(unsigned int opcode, Controller Ctrl);

typedef struct {
    unsigned int ALUOp;
    control_signal Branch;
    control_signal MemRead;
    control_signal MemtoReg;
    control_signal MemWrite;
    control_signal ALUSrc;
    control_signal RegWrite;
} Controller;


#endif