#include "LRTF.h"

void LRTF(std::vector<Process>& processes) {
    int n = processes.size();
    std::vector<int> remainingTime(n);
    std::vector<int> lastExecutionTime(n, 0);

    for (int i = 0; i < n; ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;

    while (completed != n) {
        int maxRemainingTime = -1;
        int currentProcess = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                if (remainingTime[i] > maxRemainingTime) {
                    maxRemainingTime = remainingTime[i];
                    currentProcess = i;
                }
            }
        }

        if (currentProcess == -1) {
            currentTime++;
            continue;
        }

        if (lastExecutionTime[currentProcess] == 0) {
            processes[currentProcess].startTime = currentTime;
        }

        remainingTime[currentProcess]--;
        currentTime++;

        if (remainingTime[currentProcess] == 0) {
            completed++;
            processes[currentProcess].completionTime = currentTime;
            processes[currentProcess].turnAroundTime = currentTime - processes[currentProcess].arrivalTime;
            processes[currentProcess].waitingTime = processes[currentProcess].turnAroundTime - processes[currentProcess].burstTime;
        }
    }
}
