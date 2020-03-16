#include "Data_Memory.h"

//The address is output from ALU, which was int64, which can also be used for address outputting purposes
// When used with this purpose, cast to uint64 to input to Data_mem function

int64_t Data_Mem(unsigned int memWrite, unsigned int memRead, uint64_t address, 
            int64_t writeData, Cell *mem) {
    int64_t readOut= -1;
    if (memWrite != 0){
        //Write is permitted. Let's write!
        mem[address].data = writeData;
    } else if (memRead != 0) {
        //Read is permitted
        readOut= mem[address].data;
    } else {
        //Do nothing
    }
    return readOut;
}
