
#include <stdio.h>

#include "Core.h"
#include "Parser.h"

int main(int argc, const char *argv[])
{	
    if (argc != 2)
    {
        printf("Usage: %s %s\n", argv[0], "<trace-file>");

        return 0;
    }

    /* Task One */
    // (1) parse and translate all the assembly instructions into binary format;
    // (2) store the translated binary instructions into instruction memory.

    Instruction_Memory instr_mem;
    instr_mem.last = NULL;
    loadInstructions(&instr_mem, argv[1]);
        
    /* Task Two */
    // implement Core.{h,c}
    Core *core = initCore(&instr_mem);

    
    /* Task Three - Simulation */
    uint64_t arr[] = {16,128,8,4};
    core->regBlock.REG_VAL[0] = 0;
    core->regBlock.REG_VAL[25] = 4;
    core->regBlock.REG_VAL[10] = 4;
    core->regBlock.REG_VAL[22] = 1;
    
    for (int i=0; i<4; i++) {
        core->dataMem[i].data = arr[i];
    }

    while (core->tick(core));

    printf("Simulation is finished.\n");
    printf("x9 is %ld\n", core->regBlock.REG_VAL[9]);
    printf("x11 is %ld\n", core->regBlock.REG_VAL[11]);

    
    free(core);    

}
