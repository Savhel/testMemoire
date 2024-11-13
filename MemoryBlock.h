//
// Created by PFI BERTO COMPUTER on 28/10/2024.
//

#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H
#include "Process.h"


class MemoryBlock {
public:
    int size;
    Process process ;
    int position;

    MemoryBlock(int size, Process process, int position) : size(size), process(process), position(position) {}
};



#endif //MEMORYBLOCK_H
