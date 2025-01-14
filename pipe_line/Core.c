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
    Addr next_PC;
    // (Step 1) Reading instruction from instruction memory and decode
    unsigned instruction = core->instr_mem->instructions[core->PC / 4].instruction;
    core->instr_mem->decoder = decode_instruction(instruction);

    // (Step 2) Obtain control signals (Branch, MemRed, MemWrite, etc.)
    get_ctrl_signal(core->instr_mem->decoder.opcode, &(core->controller));

    // (Step 3) Assign sources and destination to registers (fetch operands)
	fetch_operands(&(core->instr_mem->decoder), &(core->controller), &(core->regBlock));

    //(Step 4) Generate immediate from instruction
    core->immediate = generate_immediate(core->instr_mem->decoder);

	// (Step 5) ALU
	operation = ALU_Control(core->controller.ALUOp, core->instr_mem->decoder.funct3, core->instr_mem->decoder.funct7); 
	if (core->controller.ALUSrc == 0) {
		ALU_block(operation, *(core->regBlock.pt_rs1), *(core->regBlock.pt_rs2), &(core->alu));
	} else {
		ALU_block(operation, *(core->regBlock.pt_rs1), core->immediate, &(core->alu));
	}

    //(Step 6) Get next value of PC
    next_PC = get_next_PC(core->PC, core->immediate, core->controller.Branch, core->alu.zero, core->controller.ALUSrc, core->alu);
        
    // (Step 7) Write back , if else  to register or mem
    int64_t readDataFromMem = Data_Mem(core->controller.MemWrite, core->controller.MemRead, core->alu.result, 
            *(core->regBlock.pt_rs2), core->dataMem); //write to mem if memWrite=1, return data from Mem if memRead=1, return -1 if do not read

    if (core->controller.RegWrite == 1) {
          if (core->controller.MemtoReg == 1) {
              core->regBlock.pt_WriteData = &readDataFromMem;
              *core->regBlock.pt_rd = *(core->regBlock.pt_WriteData);
          } else {
              *core->regBlock.pt_rd = core->alu.result;
          }
  
          if (next_PC != (core->PC + 4)) {
          *core->regBlock.pt_rd = core->PC + 4;
          }
      }


	// (Step 8) Increment PC. FIXME, is it correct to always increment PC by 4?!
    core->PC = next_PC;
    ++core->clk;
    // Are we reaching the final instruction?
    if (core->PC > core->instr_mem->last->addr)
    {
        return false;
    }
    return true;
}



