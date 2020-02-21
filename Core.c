#include "Core.h"


Core *initCore(Instruction_Memory *i_mem)
{
    Core *core = (Core *)malloc(sizeof(Core));
    core->clk = 0;
    core->PC = 0;
    core->instr_mem = i_mem;
    core->tick = tickFunc;

    return core;
}

// FIXME, implement this function
bool tickFunc(Core *core)
{
    // Steps may include
    unsigned int operation;
    // (Step 1) Reading instruction from instruction memory
    unsigned instruction = core->instr_mem->instructions[core->PC / 4].instruction;
    
    // (Step 2) Decode the instruction
    core->instr_mem->decoder = decode_instruction(instruction);

    // (Step 3) Obtain control signals (Branch, MemRed, MemWrite, etc.)
    get_ctrl_signal(core->instr_mem->decoder.opcode, &(core->controller));

	/**********Test fetch operand function *******************/
	//core->regBlock.REG_VAL[core->instr_mem->decoder.rd] = 5;
	/**********End test fetch ********************************/

    // (Step 4) Assign sources and destination to registers (fetch operands)
	fetch_operands(&(core->instr_mem->decoder), &(core->controller), &(core->regBlock));

    //(Step 5) Generate immediate from instruction
    core->immediate = generate_immediate(core->instr_mem->decoder);

	// (Step 6) ALU
	operation = ALU_Control(core->controller.ALUOp, core->instr_mem->decoder.funct3, core->instr_mem->decoder.funct7); 
	if (core->controller.ALUSrc == 0) {
		ALU_block(operation, *(core->regBlock.pt_rs1), *(core->regBlock.pt_rs2), &(core->alu));
	} else {
		ALU_block(operation, *(core->regBlock.pt_rs1), core->immediate, &(core->alu));
	}

	// (Step 7) Write back , if else  to register or mem
    int64_t readDataFromMem = Data_Mem(core->controller.MemWrite, core->controller.MemRead, core->alu.result, 
            *(core->regBlock.pt_rs2), core->dataMem); //write to mem if memWrite=1, return data from Mem if memRead=1, return -1 if do not read

	core->regBlock.pt_WriteData = &readDataFromMem;

    if (core->controller.MemtoReg == 1) {
        *core->regBlock.pt_rd = *(core->regBlock.pt_WriteData);
    } else {
        *core->regBlock.pt_rd = core->alu.result;
    }


	// (Step 8) Increment PC. FIXME, is it correct to always increment PC by 4?!
    core->PC = get_next_PC(core->PC, core->immediate, core->controller.Branch, core->alu.zero);

    ++core->clk;
    // Are we reaching the final instruction?
    if (core->PC > core->instr_mem->last->addr)
    {
        return false;
    }
    return true;
}



