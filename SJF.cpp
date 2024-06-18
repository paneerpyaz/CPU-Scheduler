#include "SJF.h"
#include<algorithm>

void SJF(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    int currentTime = 0;
    std::vector<bool> vis(processes.size(), false);
    processes[0].startTime = processes[0].arrivalTime;
    int cnt = 0;
    size_t i = 0;

    while (cnt < processes.size()) {
        if (vis[i]) {
            i++;
            continue;
        }
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        int idx = -1;
        int mn = 1e9;
        for (size_t j = 0; j < processes.size(); j++) {
            if (vis[j]) continue;
            if (processes[j].arrivalTime <= currentTime) {
                if (processes[j].burstTime < mn) {
                    idx = j;
                    mn = processes[j].burstTime;
                }
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        processes[idx].startTime = currentTime;
        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        processes[idx].turnAroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
        currentTime = processes[idx].completionTime;
        vis[idx] = true;
        cnt++;
        i = idx;
    }
}
