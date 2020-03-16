#include "ALU_Control.h"

#define LD 20
#define ADDI 1
#define SLLI 2
#define XORI 3
#define ORI 4
#define ANDI 5
#define SD 6
#define ADD 7
#define SUB 8
#define SLL 9
#define XOR 10
#define SRL 11
#define OR 11
#define AND 12
#define JALR 13
#define JAL 14
#define SRLI 15
#define BEQ 16
#define BNE 17
#define BGE 18
#define BLT 19


unsigned int ALU_Control(unsigned int opcode, unsigned int func3, unsigned int func7) {
    if (opcode == LOAD){
        if (func3 == 3) {
            return LD;    
        }
    } 
    else if (opcode == ILOGIC ) {
        if (func3 == 0) {
            return ADDI;
        } else if (func3 == 1) {
            return SLLI;
        } else if (func3 == 4) {
            return XORI;
        } else if (func3 == 5) {
            if (func7 == 0) {
                return SRLI;
            } else if (func7 == 0x20) {
                printf("srai should be executed but we do not support this instruction!");
                return 0;
            }
        } else if (func3 == 6) {
            return ORI;
        } else if (func3 == 7) {
            return ANDI;
        }
    }
    
    else if (opcode == STORE) {
        if (func3 == 3){
            return SD;
        } else {
            printf("we do not support store instructions other than sd");
        }
    } else if (opcode == RLOGIC) {
        if (func3==0) {
            if (func7 == 0) {
                return ADD;
            } else if (func7 == 0x20) {
                return SUB;
            } else {
                printf("Error: no instr with opcode=0x23, func3=0, func7 != 0 | 20 ");
            }
        } else if (func3==1) {
            return SLL;
        } else if (func3==4) {
            return XOR;
        } else if (func3==5) {
            if (func7 == 0) {
                return SRL;
            } else {
                printf("Error: instr with opcode=0x33, func3=5, func7 != 0 not supported yet");
                return 0;
            } 
        } else if (func3 == 6) {
            return OR;
        } else if (func3 == 7) {
            return AND;
        }
    } 
    
    else if (opcode == SB ) {
        if (func3==0) {
            return BEQ;
        } else if (func3 == 1) {
            return BNE;
        } else if (func3 == 5) {
            return BGE;
        } else if (func3 == 4) {
            return BLT;
        }
    } 
    
    else if (opcode == UJ) {
        if ((func3!=0) || (func7!=0)) {
            printf("Invalid instr, no UJ type instr with func3 or func7");
            return 0;
        } else {
            return JAL;
        }
    } 
    
    else if (opcode == IJUMP) {
        if (func3 == 0) {
            return JALR;
        } else {
            printf("Instr type I(jump) other than JALR not supported");
            return 0;
        }
    }
}

void ALU_block(unsigned int operation,int64_t opr1, int64_t opr2, ALU *outSig){
    //ALU outSig;
    signed num=0; 
    if ((operation == LD) || (operation == ADDI) 
        || (operation == ADD) || (operation == SD)) {
       outSig->result = opr1 + opr2;
       outSig->zero = 0;
       // load from memory from location (rs1(opr1) + imm(opr2)) of data memory to register rd (not specified in this function, done by instruction mem block (write register ins[[11-7]). MemToReg =1 
    }
    else if ((operation == SLLI) || (operation == SLL)) {
        outSig->result = opr1 << opr2;
        outSig->zero = 0;
    } else if ((operation == XORI) || (operation == XOR)) {
        outSig->result = opr1 ^ opr2;
        outSig->zero = 0;
    } else if ((operation == ORI) || (operation == OR)) {
        outSig->result = opr1 | opr2;
        outSig->zero = 0;
    } else if (operation == ANDI) {
        outSig->result = opr1 & opr2;
        outSig->zero = 0;
    } else if (operation == SUB) {
        outSig->result = opr1 - opr2; 
        outSig->zero = 0; 
    }  else if ((operation == SRL) ||(operation == SRLI)) {
        outSig->result = opr1 >> opr2;
        outSig->zero = 0;
    } else if (operation == JALR) {
        outSig->result = opr1 + opr2;
        outSig->zero = 1;
    } else if (operation == JAL) {
        outSig->result = opr2;
        outSig->zero = 1;
    } else if (operation == BEQ) {
        if (opr1 == opr2) {
            outSig->result = 0;
            outSig->zero = 1;
        } else {
            outSig->result = 0;
            outSig->zero = 0;
        }
    } else if (operation == BNE) {
        if (opr1 == opr2) {
            outSig->result = 0;
            outSig->zero = 0;
        } else {
            outSig->result = 0;
            outSig->zero =1;
        }
    }  else if (operation == BGE) {
        if (opr1 >= opr2) {
            outSig->result = 0;
            outSig->zero = 1;
        } else {
            outSig->result = 0;
            outSig->zero = 0;
        }
    } else if (operation == BLT) {
        if (opr1 < opr2) {
            outSig->result = 0;
            outSig->zero = 1;
        } else {
            outSig->result = 0;
            outSig->zero = 0;
        }
    }

} //modify global var ALU


