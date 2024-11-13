// //
// // Created by PFI BERTO COMPUTER on 27/10/2024.
// //
// #include <iostream>
// #include <vector>
// #include <algorithm>
//
// struct Process {
//     int pid; // ID du processus
//     int burstTime; // Temps d'exécution
//     int arrivalTime; // Temps d'arrivée
//     int waitingTime; // Temps d'attente
//     int turnAroundTime; // Temps de rotation
//     int remainingTime; // Temps restant
//     int priority; // Priorité
//     int lenght; //lenght du processus
// };
//
// struct MemoryBlock {
//     int size;
//     Process* process; // nullptr signifie que l'espace est libre
// };
//
// struct Processor {
//     bool free;
//     Process* process; // nullptr signifie que le processeur est libre
// };
//
// bool compareArrivalTimetest(const Process& a, const Process& b) {
//     return a.arrivalTime < b.arrivalTime;
// }
//
// void printProcessestest(const std::vector<Process>& processes) {
//     for (const auto& process : processes) {
//         std::cout << "Processus ID: " << process.pid
//                   << ", lenght: " << process.burstTime
//                   << ", Temps d'arrivée: " << process.arrivalTime
//                   << std::endl;
//     }
// }
//
// void printMemorytest(const std::vector<MemoryBlock>& memory) {
//     for (const auto& block : memory) {
//         if (block.process == nullptr) {
//             std::cout << "[Libre: " << block.size << "] ";
//         } else {
//             std::cout << "[Processus " << block.process->pid << ": " << block.size << "] ";
//         }
//     }
//     std::cout << std::endl;
// }
//
// void printProcessortest(const Processor& processor) {
//     if (processor.free) {
//         std::cout << "Le processeur est libre" << std::endl;
//     } else {
//         std::cout << "Le processeur exécute le processus " << processor.process->pid << std::endl;
//     }
// }
//
// bool firstFittest(std::vector<MemoryBlock>& memory, Process* process) {
//     for (auto it = memory.begin(); it != memory.end(); ++it) {
//         if (it->process == nullptr && it->size >= process->burstTime) {
//             if (it->size > process->burstTime) {
//                 memory.insert(it, {process->burstTime, process});
//                 it->size -= process->burstTime;
//             } else {
//                 it->process = process;
//             }
//             return true;
//         }
//     }
//     return false;
// }
//
// void freeMemorytest(std::vector<MemoryBlock>& memory, Process* process) {
//     for (int i = 0; i < memory.size(); ++i) {
//         if (memory[i].process == process) {
//             memory[i].process = nullptr;
//             //se rassurer que seuls les derniers espaces sont vides si la memoire a des espaces vides
//             for (int j = i + 1; j < memory.size(); ++j) {
//                 memory[j - 1] = memory[j];
//             }
//             memory[memory.size() - 1].process = nullptr;
//             return;
//         }
//     }
//     // for (auto it = memory.begin(); it != memory.end(); ++it) {
//     //     if (it->process == process) {
//     //         it->process = nullptr;
//     //         if (it != memory.begin() && std::prev(it)->process == nullptr) {
//     //             std::prev(it)->size += it->size;
//     //             it = memory.erase(it);
//     //         }
//     //         if (it != memory.end() && std::next(it) != memory.end() && std::next(it)->process == nullptr) {
//     //             it->size += std::next(it)->size;
//     //             memory.erase(std::next(it));
//     //         }
//     //         return;
//     //     }
//     // }
// }
//
// int main() {
//     std::vector<Process> processList = {{1, 10, 0, 0, 0, 10, 1}, {2, 15, 2, 0, 0, 15, 2}, {3, 5, 4, 0, 0, 5, 3}};
//     std::vector<MemoryBlock> memory = {{4, nullptr}, {6   , nullptr}, {4, nullptr},{2, nullptr},{5, nullptr}}; // Initialiser avec un bloc libre de 100 unités
//     std::vector<Process*> waitingQueue;
//     Processor processor = {true, nullptr}; // Le processeur est initialement libre
//
//     std::ranges::sort(processList, compareArrivalTimetest);
//
//     for (int i = 0; i <= 500; ++i) {
//         //verifier si le processeur est libre
//         if (!processor.free) {
//             processor.process->remainingTime--;
//             if (processor.process->remainingTime == 0) {
//                 processor.process->waitingTime = i - processor.process->arrivalTime - processor.process->burstTime;
//                 processor.process->turnAroundTime = processor.process->waitingTime + processor.process->burstTime;
//                 std::cout << "Fin du processus " << processor.process->pid << std::endl;
//                 freeMemorytest(memory, processor.process);
//                 processor.free = true;
//                 processor.process = nullptr;
//             }
//         }
//         //verifies si la file d'attente a des processus si oui on tente de les charger en memoire
//         if (!waitingQueue.empty()) {
//             for (auto it = waitingQueue.begin(); it != waitingQueue.end(); ++it) {
//                 for(auto & j : memory){
//                     if((*it)->lenght <= j.size && j.process == nullptr){
//                         j.process = *it;
//                         waitingQueue.erase(it);
//                         break;
//                     }
//                 }
//             }
//         }
//         //verifies si la memoire a un espace vide et peut contenir le processus qui est la (FF)
//         for(auto & j : memory){
//             if(processList[i].lenght <= j.size && j.process == nullptr && processList[i].arrivalTime == i){
//                 j.process = &processList[i];
//                 break;
//             }
//         }
//         //si le processeur est libre on lui donne un processus
//         if (processor.free) {
//             processor.free = false;
//             processor.process = memory[0].process;
//         }
//         if (waitingQueue.empty() && memory.empty()) {
//             break;
//         }
//         std::cout << "Temps: " << i << std::endl;
//         printProcessestest(processList);
//         printMemorytest(memory);
//         printProcessortest(processor);
//     }
//     printProcessortest(processor);
//     printMemorytest(memory);
//
//     return 0;
// }
