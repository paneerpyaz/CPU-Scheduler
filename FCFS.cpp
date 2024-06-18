#include "FCFS.h"
#include <algorithm>

void FCFS(std::vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    auto cmp = [&](Process P1, Process P2) -> bool {
        return P1.arrivalTime < P2.arrivalTime;
    };
    std::sort(processes.begin(), processes.end(), cmp);
    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        currentTime += processes[i].burstTime;
    }
}
