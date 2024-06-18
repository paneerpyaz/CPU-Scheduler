#include "HRRN.h"
#include<algorithm>

// HRRN function definition
void HRRN(std::vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    int completedCount = 0;
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    while (completedCount < n) {
        double maxResponseRatio = -1;
        int currentProcess = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].completionTime == 0) {
                int waitingTime = currentTime - processes[i].arrivalTime;
                double responseRatio = (waitingTime + processes[i].burstTime) / (double)processes[i].burstTime;

                if (responseRatio > maxResponseRatio) {
                    maxResponseRatio = responseRatio;
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

        completedCount++;
    }
}
