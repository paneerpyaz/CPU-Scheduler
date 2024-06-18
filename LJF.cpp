#include "LJF.h"
void LJF(std::vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;
    std::vector<bool> completedProcess(n, false);

    while (completed != n) {
        int currentProcess = -1;
        int longestBurstTime = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !completedProcess[i]) {
                if (processes[i].burstTime > longestBurstTime) {
                    longestBurstTime = processes[i].burstTime;
                    currentProcess = i;
                }
                if (processes[i].burstTime == longestBurstTime && processes[i].arrivalTime < processes[currentProcess].arrivalTime) {
                    currentProcess = i;
                }
            }
        }
        if (currentProcess == -1) {
            currentTime++;
            continue;
        }
        processes[currentProcess].startTime = currentTime;
        currentTime += processes[currentProcess].burstTime;
        processes[currentProcess].completionTime = currentTime;
        processes[currentProcess].turnAroundTime = processes[currentProcess].completionTime - processes[currentProcess].arrivalTime;
        processes[currentProcess].waitingTime = processes[currentProcess].turnAroundTime - processes[currentProcess].burstTime;

        completedProcess[currentProcess] = true;
        completed++;
    }
}
