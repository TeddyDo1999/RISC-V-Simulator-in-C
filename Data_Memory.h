#ifndef __CELL_H__
#define __CELL_H__

#include <stdint.h>

#define DATAMEM_SIZE 256

typedef uint64_t Addr;
typedef uint64_t Tick; //Might not be necessary

typedef struct 
{
    int64_t data; 
    //This binary format of data stored in 1 cell    
    Addr addr;
} Cell;


//typedef Cell Data_mem[DATAMEM_SIZE];

int64_t Data_Mem(unsigned int memWrite, unsigned int memRead, uint64_t address, 
            int64_t writeData, Cell* mem);

#endif
