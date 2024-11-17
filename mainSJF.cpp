//
// Created by PFI BERTO COMPUTER on 28/10/2024.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include "Process.h"
#include "MemoryBlock.h"
#include "Processor.h"
#include "usualFunction.h"

bool compareArrivalTimeSJF(const MemoryBlock& a, const MemoryBlock& b) {
    return a.process.burstTime < b.process.burstTime;
}
bool compareArrivalTimeSJFSJF(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

int mainSJF() {
    std::vector<Process> processList = {{1, 3, 0, 4}, {2, 5, 0, 2}, {3, 2, 1, 6}};
    for (auto& process : processList) process.remainingTime = process.burstTime;

    std::vector<MemoryBlock> memory = {{4,{0,100,0,0},0},{6,{0,100,0,0},0},{2,{0,100,0,0},0},{4,{0,100,0,0},0},{5,{0,100,0,0},0},};
    std::vector<Process> waitingQueue;
    Processor processor = {true, nullptr};

    int time = 0;
    bool allProcessesComplete = false;
    std::sort(processList.begin(), processList.end(), compareArrivalTimeSJFSJF);
    usualFunction::printProcesses(processList);

    while (!allProcessesComplete) {
        if (!processor.free) {
            usualFunction::printProcessor(processor);
            processor.process->remainingTime--;
            if (processor.process->remainingTime == 0) {
                processor.process->waitingTime = time - processor.process->arrivalTime - processor.process->burstTime;
                processor.process->turnAroundTime = processor.process->waitingTime + processor.process->burstTime;
                std::cout << "Fin du processus " << processor.process->pid << " après " << time << " secondes avec " << processor.process->waitingTime << " secondes d'attentes et " << processor.process->turnAroundTime << " secondes de temps de rotation" << std::endl;
                usualFunction::freeMemory(memory, processor.process);
                processList.erase(std::remove(processList.begin(), processList.end(), *processor.process), processList.end());
                processor.free = true;
                processor.process = nullptr;
            }
            if (!waitingQueue.empty()) {
                auto wait = waitingQueue.begin();
                while (wait != waitingQueue.end()) {
                    if (usualFunction::bestFit(memory, *wait)) {
                        wait = waitingQueue.erase(wait);
                    } else {
                        ++wait;
                    }
                    usualFunction::printMemory(memory);
                }
            }
        }

        auto it = processList.begin();
        while (it != processList.end()) {
            if ((*it).arrivalTime == time) {
                if (!usualFunction::bestFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
                it = processList.erase(it);
            } else {
                ++it;
            }
            usualFunction::printMemory(memory);
        }
        //le processeur libre ou pas peut perdre le processus en cours d'exécution pour prendre un autre de la memoire ayant un temps d'execution plus court

    if (processor.free) {
        std::sort(memory.begin(), memory.end(), compareArrivalTimeSJF);
        if (memory[0].process.pid != 0) {
            processor.free = false;
            processor.process = &memory[0].process;
        }
    }
        

        time++;
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        if (processor.free) {
            allProcessesComplete = true;
        }
    }

    std::cout << "Tous les processus sont terminés après " << time << " secondes." << std::endl;
    usualFunction::printProcessor(processor);
    usualFunction::printMemory(memory);
    usualFunction::printProcesses(processList);
    return 0;
}
