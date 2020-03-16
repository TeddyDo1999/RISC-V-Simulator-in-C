
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
    core->regBlock.REG_VAL[0] = 0;
    core->regBlock.REG_VAL[1] = 0;
    core->regBlock.REG_VAL[2] = 10;
    core->regBlock.REG_VAL[3] = -15;
    core->regBlock.REG_VAL[4] = 20;
    core->regBlock.REG_VAL[5] = 30;
    core->regBlock.REG_VAL[6] = -35;

    core->dataMem[40].data = -63;
    core->dataMem[48].data = 63;

    while (core->tick(core));

    printf("Simulation is finished.\n");
    printf("x10 is %ld\n", core->regBlock.REG_VAL[10]);
    printf("x11 is %ld\n", core->regBlock.REG_VAL[11]);
    printf("x12 is %ld\n", core->regBlock.REG_VAL[12]);
    printf("x13 is %ld\n", core->regBlock.REG_VAL[13]);
    printf("x14 is %ld\n", core->regBlock.REG_VAL[14]);

    
    free(core);    

}
