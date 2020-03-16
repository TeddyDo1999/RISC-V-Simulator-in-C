#include "Core.h"


Core *initCore(Instruction_Memory *i_mem)
{
    Core *core = (Core *)malloc(sizeof(Core));
    core->clk = 0;
    core->PC = 0;
    core->instr_mem = i_mem;
    core->tick = tickFunc;

    core->IF_ID_pipeline.valid_bit = 0;
    core->ID_EX_pipeline.valid_bit = 0;
    core->EX_MEM_pipeline.valid_bit = 0;
    core->MEM_WB_pipeline.valid_bit = 0;

    return core;
}

// FIXME, implement this function
bool tickFunc(Core *core)
{
    // Steps may include
    unsigned int operation;
    Addr next_PC;

    // (Write-back stage) Write back data to register if needed
    int64_t WriteBack_data;
    if (core->MEM_WB_pipeline.valid_bit == 1) {
        if (core->MEM_WB_pipeline.controller.MemtoReg == 1) {
            WriteBack_data = core->MEM_WB_pipeline.val_dataMem;
        }
        else {
            WriteBack_data = core->MEM_WB_pipeline.ALU_result;
        }
        if (core->MEM_WB_pipeline.controller.RegWrite == 1) {
            core->regBlock.pt_WriteData = &WriteBack_data;
            core->regBlock.pt_rd = &(core->regBlock.REG_VAL[core->MEM_WB_pipeline.decoded_instruction.rd]);
            *core->regBlock.pt_rd = *(core->regBlock.pt_WriteData);
        }
    }

    // (Memory-access stage) Get data from memory to be written back to register
    if (core->EX_MEM_pipeline.valid_bit == 1) {
        int64_t readDataFromMem = Data_Mem(core->EX_MEM_pipeline.controller.MemWrite, 
            core->EX_MEM_pipeline.controller.MemRead, core->EX_MEM_pipeline.ALU_output.result,
            core->EX_MEM_pipeline.rs2_val, core->dataMem); //write to mem if memWrite=1, return data from Mem if memRead=1, return -1 if do not read

        core->MEM_WB_pipeline.ALU_result = core->alu.result;
        core->MEM_WB_pipeline.controller = core->EX_MEM_pipeline.controller;
        core->MEM_WB_pipeline.decoded_instruction = core->EX_MEM_pipeline.decoded_instruction;
        core->MEM_WB_pipeline.val_dataMem = readDataFromMem;
        core->MEM_WB_pipeline.valid_bit = 1;
    }
    else {
        core->MEM_WB_pipeline.valid_bit = 0;
    }


    // (Execute/Address-calculation stage) Execute instructed operation and output value
	// (Step 5) ALU
    if (core->ID_EX_pipeline.valid_bit == 1) {
        operation = ALU_Control(core->ID_EX_pipeline.controller.ALUOp, 
                    core->ID_EX_pipeline.decoded_instruction.funct3, 
                    core->ID_EX_pipeline.decoded_instruction.funct7); 
        if (core->ID_EX_pipeline.controller.ALUSrc == 0) {
            ALU_block(operation, core->ID_EX_pipeline.rs1_val, core->ID_EX_pipeline.rs2_val, &(core->alu));
        } else {
            ALU_block(operation, core->ID_EX_pipeline.rs1_val, core->ID_EX_pipeline.immediate_val, &(core->alu));
        }

        int64_t Shifted_Immediate = core->ID_EX_pipeline.immediate_val << 1;
        next_PC = core->ID_EX_pipeline.PC_val + Shifted_Immediate;

        core->EX_MEM_pipeline.ALU_output = core->alu;
        core->EX_MEM_pipeline.controller = core->ID_EX_pipeline.controller;
        core->EX_MEM_pipeline.decoded_instruction = core->ID_EX_pipeline.decoded_instruction;
        core->EX_MEM_pipeline.New_PC_val = next_PC;
        core->EX_MEM_pipeline.rs2_val = core->ID_EX_pipeline.rs2_val;
        core->EX_MEM_pipeline.valid_bit = 1;
    }
    else {
        core->EX_MEM_pipeline.valid_bit = 0;
    }


    // (Instruction decode/register file read)
    if (core->IF_ID_pipeline.valid_bit == 1) {
        // (Step 2) Obtain control signals (Branch, MemRed, MemWrite, etc.)
        get_ctrl_signal(core->IF_ID_pipeline.decoded_instruction.opcode, &(core->controller));

        // (Step 3) Assign sources and destination to registers (fetch operands)
        fetch_operands(&(core->IF_ID_pipeline.decoded_instruction), &(core->controller), &(core->regBlock));

        //(Step 4) Generate immediate from instruction
        core->immediate = generate_immediate(core->IF_ID_pipeline.decoded_instruction);

        core->ID_EX_pipeline.controller = core->controller;
        core->ID_EX_pipeline.decoded_instruction = core->IF_ID_pipeline.decoded_instruction;
        core->ID_EX_pipeline.immediate_val = core->immediate;
        core->ID_EX_pipeline.PC_val = core->IF_ID_pipeline.PC_value;
        core->ID_EX_pipeline.rs1_val = *(core->regBlock.pt_rs1);
        core->ID_EX_pipeline.rs2_val = *(core->regBlock.pt_rs2);
        core->ID_EX_pipeline.valid_bit = 1;
    }
    else {
        core->ID_EX_pipeline.valid_bit = 0;
    }


    // (Instruction fetch)
    if (core->PC > core->instr_mem->last->addr) {
        core->IF_ID_pipeline.valid_bit = 0;
    }
    else {
        // (Step 1) Reading instruction from instruction memory and decode
        unsigned instruction = core->instr_mem->instructions[core->PC / 4].instruction;
        core->instr_mem->decoder = decode_instruction(instruction);

        core->IF_ID_pipeline.decoded_instruction = core->instr_mem->decoder;
        core->IF_ID_pipeline.PC_value = core->PC;
        core->IF_ID_pipeline.valid_bit = 1;
    }

    // Get next value of PC
    if (core->EX_MEM_pipeline.controller.Branch & core->EX_MEM_pipeline.ALU_output.zero) {
        core->PC = core->EX_MEM_pipeline.New_PC_val;
    }
    else {
        core->PC = core->PC + 4;
    }
    ++core->clk;

    // Are we reaching the final instruction?
    if (core->PC > core->instr_mem->last->addr) {
        if (core->MEM_WB_pipeline.valid_bit != 1) {
            if (core->EX_MEM_pipeline.valid_bit != 1) {
                if (core->ID_EX_pipeline.valid_bit != 1) {
                    if (core->IF_ID_pipeline.valid_bit != 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}



