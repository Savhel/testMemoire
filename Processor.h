//
// Created by PFI BERTO COMPUTER on 28/10/2024.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Process.h"


class Processor {
public:
    bool free ;
    Process* process ; // nullptr signifie que le processeur est libre

    Processor(bool free, Process* process) : free(free), process(nullptr) {};
};



#endif //PROCESSOR_H
