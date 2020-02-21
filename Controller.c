#include "Controller.h"
#include "Decoder.h"

// unsigned int check_one(unsigned int data, int BEGIN, int END) {
//     unsigned int checked_data = data;
//     checked_data >> END;
//     unsigned int bit1 = 1;
//     for (int i = 0; i < (BEGIN-END+1); i++) {
//         if ((checked_data & bit1) != bit1) {
//             return FALSE;
//         }
//         checked_data >> 1;
//     }
//     return TRUE;
// }

// unsigned int validate_opcode(unsigned int opcode) {
//     if (opcode != NULL) {
//         if (check_one(opcode,1,0) != FALSE) {
//             return TRUE;
//         }
//     }
//     return FALSE;
// }

void get_ctrl_signal(unsigned int opcode, Controller* Ctrl) {
    // if (validate_opcode(opcode) != TRUE) {
    //     printf("Invalid opcode");
    //     exit(EXIT_FAILURE);
    // }
    
    // Obtain ALUOp based on opcode
    switch (opcode) {
        case 0x03:
        // load function //
            Ctrl->ALUOp = LOAD;
            Ctrl->Branch = FALSE;
            Ctrl->MemtoReg = TRUE;
            Ctrl->MemRead = TRUE;
            Ctrl->MemWrite = FALSE;
            Ctrl->ALUSrc = TRUE;
            Ctrl->RegWrite = TRUE;
            break;
        case 0x13:
        // immediate-logical function //
            Ctrl->ALUOp = ILOGIC;
            Ctrl->Branch = FALSE;            
            Ctrl->MemtoReg = FALSE;
            Ctrl->MemRead = FALSE;
            Ctrl->MemWrite = FALSE;
            Ctrl->ALUSrc = TRUE;
            Ctrl->RegWrite = TRUE;
            break;
        case 0x23:
        // store function //
            Ctrl->ALUOp = STORE;
            Ctrl->Branch = FALSE;            
            Ctrl->MemtoReg = FALSE;
            Ctrl->MemRead = FALSE;
            Ctrl->MemWrite = TRUE;
            Ctrl->ALUSrc = TRUE;
            Ctrl->RegWrite = FALSE;
            break;
        case 0x33:
        // logical function //
            Ctrl->ALUOp = RLOGIC;
            Ctrl->Branch = FALSE;
            Ctrl->MemtoReg = FALSE;
            Ctrl->MemRead = FALSE;
            Ctrl->MemWrite = FALSE;
            Ctrl->ALUSrc = FALSE;
            Ctrl->RegWrite = TRUE;
            break;
        case 0x63:
        // branch function //
            Ctrl->ALUOp = SB;        
            Ctrl->Branch = TRUE;            
            Ctrl->MemtoReg = FALSE;
            Ctrl->MemRead = FALSE;
            Ctrl->MemWrite = FALSE;
            Ctrl->ALUSrc = TRUE;
            Ctrl->RegWrite = FALSE;
            break;
        case 0x67:
        // jump-and-link-register function //
            Ctrl->ALUOp = IJUMP;
            Ctrl->Branch = TRUE;
            Ctrl->MemtoReg = FALSE;
            Ctrl->MemRead = FALSE;
            Ctrl->MemWrite = FALSE;
            Ctrl->ALUSrc = FALSE;
            Ctrl->RegWrite = TRUE;
            break;
        case 0x6F:
        // jump-and-link function //
            Ctrl->ALUOp = UJ;
            Ctrl->Branch = TRUE;
            Ctrl->MemtoReg = FALSE;
            Ctrl->MemRead = FALSE;
            Ctrl->MemWrite = FALSE;
            Ctrl->ALUSrc = TRUE;
            Ctrl->RegWrite = TRUE;
            break;
    default:
        printf("Function not available!");
        exit(EXIT_FAILURE);
    }

}