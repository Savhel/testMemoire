//
// Created by PFI BERTO COMPUTER on 28/10/2024.
//

#ifndef PROCESS_H
#define PROCESS_H



class Process {
public:
        int pid;
        int burstTime;
        int arrivalTime;
        int waitingTime ;
        int turnAroundTime ;
        int remainingTime;
        int length;
        int priority;
    Process(int pid, int burstTime, int arrivalTime, int length) : pid(pid), burstTime(burstTime), arrivalTime(arrivalTime), waitingTime(0),turnAroundTime(0), remainingTime(100), length(length),priority(0) {}

        bool operator==(const Process& other) const {
            return pid == other.pid;
        }
};



#endif //PROCESS_H
