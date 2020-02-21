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
    // (Step 1) Reading instruction from instruction memory
    unsigned instruction = core->instr_mem->instructions[core->PC / 4].instruction;
    
    // (Step 2) Decode the instruction
    core->instr_mem->decoder = decode_instruction(instruction);

    // (Step 3) Obtain control signals (Branch, MemRed, MemWrite, etc.)
    get_ctrl_signal(core->instr_mem->decoder.opcode, &(core->controller));

	/**********Test fetch operand function *******************/
	core->regBlock.REG_VAL[core->instr_mem->decoder.rd] = 5;
	/**********End test fetch ********************************/

    // (Step 4) Assign sources and destination to registers (fetch operands)
	fetch_operands(&(core->instr_mem->decoder), &(core->controller), &(core->regBlock));

    // (Step N) Increment PC. FIXME, is it correct to always increment PC by 4?!
    core->PC = get_next_PC(core->PC, core->immediate, core->controller.Branch, core->ALU.zero);

    ++core->clk;
    // Are we reaching the final instruction?
    if (core->PC > core->instr_mem->last->addr)
    {
        return false;
    }
    return true;
}



