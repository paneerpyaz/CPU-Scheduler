#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <cassert>

#include "Process.h"
#include "FCFS.h"
#include "LJF.h"
#include "SJF.h"
#include "LRTF.h"
#include "HRRN.h"
#include "FCFS.cpp"
#include "LJF.cpp"
#include "SJF.cpp"
#include "LRTF.cpp"
#include "HRRN.cpp"

using namespace std;

class ComparePriority {
public:
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority > p2.priority;  // Higher priority value means lower actual priority
    }
};
const double TIME_CUTOFF = 1.0;
const int ITERATIONS = 1e6;

vector<Process> parseInput(const string& input) {
    vector<Process> processes;
    stringstream ss(input);
    string processString;

    while (getline(ss, processString, ';')) {
        stringstream ps(processString);
        string token;
        Process process;

        getline(ps, token, ',');
        process.id = stoi(token);
        getline(ps, token, ',');
        process.arrivalTime = stoi(token);
        getline(ps, token, ',');
        process.burstTime = stoi(token);
        getline(ps, token, ',');
        process.priority = stoi(token);

        processes.push_back(process);
    }

    if (processes.empty()) {
        throw runtime_error("No valid process information found in the input.");
    }

    return processes;
}

const int THRESHOLD = 15;
const int LOAD = 5;

int main(int argc, char* argv[]) {
    if (argc<3) {
        cerr << "Usage: scheduler.exe <algorithm> <input>" << endl;
        return 1;
    }

    auto chrono_begin = chrono::steady_clock::now();
    string algorithm = argv[1];
    string input = argv[2];

    vector<Process> processes = parseInput(input);

    if (algorithm == "FCFS") {
        FCFS(processes);
    } else if (algorithm == "LJF") {
        LJF(processes);
    } else if (algorithm == "SJF") {
        SJF(processes);
    }else if (algorithm == "LRTF") {
        LRTF(processes);
    } else if (algorithm == "HRRN") {
        HRRN(processes);
    } else {
        cerr << "Invalid algorithm choice\n";
        return 1;
    }

    double totalTAT = 0;
    double totalWT = 0;
    int n = processes.size();

    for (const auto& process : processes) {
        totalTAT += process.turnAroundTime;
        totalWT += process.waitingTime;
    }

    double averageTAT = totalTAT / n;
    double averageWT = totalWT / n;
    
    

    cout << "{ \"processes\": [";
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << "{"<< "\"id\":" << processes[i].id << ","<< "\"arrivalTime\":" << processes[i].arrivalTime << ","<< "\"burstTime\":" << processes[i].burstTime << ","<< "\"priority\":" << processes[i].priority << ","<< "\"completionTime\":" << processes[i].completionTime << ","<< "\"waitingTime\":" << processes[i].waitingTime << ","<< "\"turnAroundTime\":" << processes[i].turnAroundTime<< "}";
        if (i < processes.size() - 1) {
            cout << ",";
        }
    }

    auto chrono_end = chrono::steady_clock::now();
    long double schedulingOverhead = 1e-12 * chrono::duration_cast<chrono::microseconds>(chrono_end - chrono_begin).count();
    cout << "],"
              << "\"averageTAT\": " << averageTAT << ","
              << "\"averageWT\": " << averageWT << ","
              << "\"schedulingOverhead\": " << schedulingOverhead << "}";
    cout.flush();
    return 0;
}
