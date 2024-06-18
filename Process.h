#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime = 0;
    int waitingTime = 0;
    int turnAroundTime = 0;
    int startTime = 0;
};

#endif
