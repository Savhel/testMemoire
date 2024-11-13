//
// Created by PFI BERTO COMPUTER on 28/10/2024.
//

#ifndef USUALFUNCTION_H
#define USUALFUNCTION_H
#include <vector>
#include <iostream>
#include "Process.h"
#include "MemoryBlock.h"
#include "Processor.h"


class usualFunction {

public:
static void printProcesses(const std::vector<Process>& processes) {
    for (const auto& process : processes) {
        std::cout << "Processus ID: " << process.pid
                  << ", Longueur: " << process.length
                  << ", Temps d'arrivée: " << process.arrivalTime
                  << ", Temps d'exécution: " << process.burstTime
                  << std::endl;
    }
}

static void printMemory(std::vector<MemoryBlock>& memory) {
    for (const auto& block : memory) {
        if (block.process.pid == 0) {
            std::cout << "[Libre: " << block.size << "] ";
        } else {
            std::cout << "[Processus " << block.process.pid << ": " << block.size << "] ";
        }
    }
    std::cout << std::endl;
}

static void printProcessor(Processor& processor) {
    if (processor.free) {
        std::cout << "Le processeur est libre" << std::endl;
    } else {
        std::cout << "Le processeur exécute le processus " << processor.process->pid <<" il lui reste " << processor.process->remainingTime << std::endl;
    }
}
static void rotateProcessesMemory(std::vector<MemoryBlock>& memory) {
    MemoryBlock temp = memory[0];
    int indice = 0 ;
    for (int i = 1; i < memory.size(); i++) {
        if (memory[i].process.pid != 0) {
            memory[i - 1 ] = memory[i];
            indice = i;
        }
    }
    memory[indice] = temp;
}

static bool firstFit(std::vector<MemoryBlock>& memory, Process process) {
    int i = 0;
    for (auto& block : memory) {
        if (block.process.pid != 0) {
            i++;
        }
    }
    for (auto& block : memory) {
        if (block.process.pid == 0 && block.size >= process.length) {
            block.process = process;
            block.position = i+1;
            return true;
        }
    }
    return false;
}
static bool bestFit(std::vector<MemoryBlock>& memory, Process process) {
    int test = INT_MAX;
    int indiceMin = INT_MAX, i = 0;
    for (int j = 0; j < memory.size(); j++) {
        if (memory[j].size >= process.length && test >= memory[j].size - process.length && memory[j].process.pid == 0 && memory[j].position == 0 && memory[j].size >= process.length ) {
            test =  memory[j].size - process.length;
            indiceMin = j;
        }
    }
    for (auto& block : memory) {
        if (block.process.pid != 0) {
            i++;
        }
    }
    if (indiceMin != INT_MAX) {
        memory[indiceMin].position = i+1;
        memory[indiceMin].process = process;
        return true;
    }
    return false;
}
static bool worstFit(std::vector<MemoryBlock>& memory, Process process) {
    int test = -1;
    int indiceMin = INT_MAX, i = 0;
    for (int j = 0; j < memory.size(); j++) {
        if (memory[j].size >= process.length && test <= memory[j].size - process.length && memory[j].process.pid == 0 && memory[j].position == 0 && memory[j].size >= process.length ) {
            test =  memory[j].size - process.length;
            indiceMin = j;
        }
    }
    for (auto& block : memory) {
        if (block.process.pid != 0) {
            i++;
        }
    }
    if (indiceMin != INT_MAX) {
        memory[indiceMin].position = i+1;
        memory[indiceMin].process = process;
        return true;
    }
    return false;
}

static void freeMemory(std::vector<MemoryBlock>& memory, Process* process) {
    for (auto& block : memory) {
        if (block.process == *process) {
            block.process = {0,100,0,0};
            block.position = 0;
            break;
        }
    }
    for (auto& block : memory) {
        if (block.position != 0) {
            block.position--;
        }
    }
}
};



#endif //USUALFUNCTION_H
