#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include "Process.h"
#include "MemoryBlock.h"
#include "Processor.h"
#include "usualFunction.h"

bool compareArrivalTimeFCFS(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

int mainFCFS() {
    std::vector<Process> processList = {{1, 3, 0, 2}, {2, 5, 0, 6}, {3, 2, 1, 4}};
    for (auto& process : processList)
        process.remainingTime = process.burstTime;

    std::vector<MemoryBlock> memory = {{4,{0,0,0,0},0},{6,{0,0,0,0},0},{2,{0,0,0,0},0},{4,{0,0,0,0},0},{5,{0,0,0,0},0},};
    std::vector<Process> waitingQueue;
    Processor processor = {true, nullptr};

    std::sort(processList.begin(), processList.end(), compareArrivalTimeFCFS);
    int time = 0;
    bool allProcessesComplete = false;

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
                /*for (int i = 0; i < processList.size(); i++) {
                    if (processList[i] == *processor.process) {
                        processList.erase(processList.begin() + i);
                        break;
                    }
                }
                processor.free = true;
                processor.process = nullptr;*/
                processor.free = true;
                processor.process = nullptr;
            }
            if (!waitingQueue.empty()) {
                auto wait = waitingQueue.begin();
                while (wait != waitingQueue.end()) {
                    if (usualFunction::worstFit(memory, *wait)) {
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
                if (!usualFunction::worstFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
                it = processList.erase(it);
            } else {
                ++it;
            }
            usualFunction::printMemory(memory);
        }

        if (processor.free) {
            for (auto& block : memory) {
                if (block.process.pid != 0 && block.position == 1) {
                    processor.free = false;
                    processor.process = &block.process;
                    break;
                }
            }
        }

        time++;
        std::this_thread::sleep_for(std::chrono::seconds(2));
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
