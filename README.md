# CPU Scheduler Application Report

Made for ACM Open Projects Summer of 2024

## Introduction

Operating systems play a crucial role in managing computer resources efficiently, with process scheduling being a fundamental component. The CPU Scheduler application presented in this report aims to simulate and evaluate various process scheduling algorithms through an intuitive user interface built using Electron and robust backend algorithms implemented in C++.

## Installation
- Compile the scheduler.cpp file using a compiler with C++ 11 or higher
- run npm install to install all dependencies
- run npm start to run the project 

### Purpose and Significance

The primary purpose of the CPU Scheduler application is to provide a platform for studying and comparing different process scheduling algorithms in a controlled environment. Process scheduling is critical for optimizing resource utilization and improving system performance by effectively allocating CPU time among competing processes. By implementing algorithms such as First-Come, First-Served (FCFS), Round Robin (RR), Shortest Job First (SJF), Priority Scheduling, and an automated scheduler, the application allows users to analyze their effectiveness under different scenarios.

Understanding the behavior and performance characteristics of these scheduling algorithms is essential for system administrators, software developers, and students studying operating systems. Through the CPU Scheduler application, users can visualize scheduling decisions using interactive Gantt charts, gaining insights into how different algorithms manage process execution and resource allocation.

### Technologies Used

The CPU Scheduler application leverages modern technologies to deliver a seamless user experience and robust backend processing:

- **Electron**: A framework for building cross-platform desktop applications using web technologies (HTML, CSS, JavaScript). Electron enables the creation of a responsive and interactive user interface.
  
- **C++**: Chosen for its efficiency and low-level system access, C++ forms the backbone of the application's backend, implementing process scheduling algorithms and performance metrics calculations.
  
- **D3.js**: A JavaScript library used for creating dynamic and interactive data visualizations. D3.js facilitates the graphical representation of process scheduling and performance metrics through Gantt charts.
  
- **IPC (Inter-Process Communication)**: Facilitates seamless communication between the Electron frontend and C++ backend, enabling real-time data exchange and synchronization for interactive visualization.

## System Architecture

The CPU Scheduler application is designed with a modular architecture that combines a frontend user interface developed using Electron with a backend implemented in C++. This section provides an overview of the system architecture, detailing the interaction between different components and their roles in ensuring efficient process scheduling and visualization.

### Overview

The architecture of the CPU Scheduler application comprises two main components:

- **Frontend (Electron)**
- **Backend (C++)**

### Frontend (Electron)

The frontend of the CPU Scheduler application is built using Electron, a framework that allows for the development of cross-platform desktop applications using web technologies such as HTML, CSS, and JavaScript.

- **User Interface**: The Electron frontend provides a graphical user interface (GUI) that allows users to interact with the application. It includes components such as dropdown menus for selecting scheduling algorithms, text areas for inputting process details, and buttons for initiating process scheduling.
  
- **Rendering Gantt Charts**: D3.js, a JavaScript library for visualizing data using web standards (SVG, CSS), is integrated into the Electron frontend. It dynamically renders Gantt charts based on the scheduling results received from the backend.
  
- **Inter-Process Communication (IPC)**: Electron facilitates IPC between the frontend and the backend, enabling real-time data exchange. This allows the frontend to send user inputs (selected algorithm and process details) to the backend for processing and receive scheduling results for visualization.

### Backend (C++)

The backend of the CPU Scheduler application is implemented in C++, chosen for its efficiency, low-level system access, and suitability for implementing process scheduling algorithms.

- **Process Scheduling Algorithms**: The C++ backend implements various process scheduling algorithms, including First-Come, First-Served (FCFS), Round Robin (RR), Shortest Job First (SJF), Priority Scheduling, and an automated scheduler that selects the algorithm based on input characteristics.
  
- **Performance Metrics Calculation**: After executing the scheduling algorithms, the backend calculates performance metrics such as average turnaround time, average waiting time, and scheduling overhead. These metrics are then passed back to the Electron frontend for display.
  
- **Execution and Communication**: The backend executes the selected scheduling algorithm on the provided process data. It communicates with the Electron frontend via IPC, sending JSON-formatted scheduling results back to the frontend for visualization and display.

### Interaction Flow

The interaction flow between the frontend and backend of the CPU Scheduler application is as follows:

1. The user selects a scheduling algorithm and enters process details (process ID, arrival time, burst time, priority) through the Electron frontend.
   
2. Upon clicking the "Run Scheduler" button, the frontend sends an IPC message containing the selected algorithm and process details to the backend.
   
3. The backend receives the IPC message, processes the scheduling request using the specified algorithm, and computes the necessary performance metrics.
   
4. After completing the scheduling process, the backend sends a response back to the Electron frontend, including JSON-formatted data containing scheduling results (processes details, performance metrics).
   
5. The Electron frontend receives the scheduling results, updates the GUI to display the process details and Gantt chart, and shows performance metrics such as average turnaround time, average waiting time, and scheduling overhead.

### Diagram

![a](https://github.com/cruelkratos/CPU-Scheduler/assets/116339436/18f541f4-05bb-46fc-b0f7-29c8509e9724)


Figure 1: High-level System Architecture of the CPU Scheduler Application

## Electron Frontend

The Electron frontend of the CPU Scheduler application provides a user-friendly interface for interacting with the scheduling algorithms implemented in the backend. This section outlines the architecture, features, and interaction flow of the Electron frontend.

### Architecture

The Electron frontend architecture consists of several key components:

#### User Interface (UI)

The UI component provides an interactive platform where users can select scheduling algorithms, input process details, and view scheduling results.

#### D3.js for Gantt Charts

D3.js is utilized to dynamically generate Gantt charts that visually represent the scheduling of processes over time.

#### Inter-Process Communication (IPC)

IPC facilitates communication between the Electron frontend and the C++ backend, enabling data exchange and result retrieval.

### Features

The Electron frontend offers several key features to enhance user interaction:

#### Algorithm Selection

Users can choose from various scheduling algorithms including FCFS, Round Robin, SJF, Priority Scheduling, or Automatic Scheduling (Auto).

#### Process Input

Provides a text area where users can input details such as Process ID, Arrival Time, Burst Time, and Priority for scheduling.

#### Run Scheduler Button

Initiates the execution of the selected scheduling algorithm based on the provided input.

#### Result Display

Displays detailed results including processes, average turnaround time, average waiting time, and scheduling overhead after executing the scheduler.

#### Gantt Chart Visualization

Utilizes D3.js to create interactive Gantt charts that visually illustrate the scheduling timeline of processes.

### Interaction Flow

The interaction flow of the Electron frontend is as follows:

#### User Interaction

Users interact with the UI by selecting an algorithm, entering process details, and triggering the scheduler.

#### IPC Handling

The selected algorithm and process input are sent via IPC to the C++ backend for execution.

#### Backend Processing

The C++ backend executes the chosen algorithm, computes metrics, and sends back the results via IPC to the Electron frontend.

#### Result Presentation

The UI updates to display the processed results, including textual details and visualizations (Gantt chart).

## C++ Backend

The C++ backend of the CPU Scheduler application serves as the core processing engine responsible for executing scheduling algorithms and computing metrics based on provided process data.

### Architecture

The backend architecture is structured to efficiently manage process scheduling and computation tasks:

#### Process Struct

Defines the `Process` struct containing attributes such as ID, Arrival Time, Burst Time, Priority, Completion Time, Waiting Time, Turnaround Time, and Start Time.

#### Algorithm Functions

Includes implementations for various scheduling algorithms:

- **First-Come, First-Served (FCFS)**: Executes processes based on their arrival times in a non-preemptive manner.
  
- **Round Robin (RR)**: Implements a preemptive scheduling algorithm where each process is assigned a fixed time slice (quantum) in a circular queue.
  
- **Shortest Job First (SJF)**: Schedules processes based on their burst times, either preemptively or non-preemptively.
  
- **Priority Scheduling**: Assigns priorities to processes and schedules them based on priority levels.
  
- **Automatic Scheduling (Auto)**: Selects an appropriate algorithm dynamically based on input process attributes to avoid starvation and optimize scheduling.

### Implementation Details

#### Input Parsing

Utilizes input parsing functions to convert user-provided process details from string format into `Process` structs.

#### Algorithm Execution

Each scheduling algorithm function processes the list of `Process` structs according to its scheduling logic:

- Calculates completion times, waiting times, and turnaround times for each process.
  
- Ensures proper handling of process arrival times and quantum slices (for RR).
  
- Manages scheduling overhead and algorithmic complexities.

#### Output Generation

Produces JSON-formatted output containing detailed scheduling results, including processes list, average turnaround time, average waiting time, and scheduling overhead.

### Performance Considerations

The backend is optimized for performance and scalability:

#### Algorithm Selection Logic

The `auto_schedule` function dynamically selects the most suitable scheduling algorithm based on input process characteristics to ensure efficient task scheduling.

#### Execution Time Metrics

Utilizes `std::chrono` library to measure and report scheduling overhead, providing insights into algorithm efficiency and performance.

## Integration via IPC

In the CPU Scheduler application, the frontend (Electron) and backend (C++) communicate using IPC mechanisms provided by Electron's `ipcRenderer` and `ipcMain` modules. IPC allows asynchronous communication between the Electron main process and the C++ backend process, facilitating data exchange and coordination of scheduling tasks.

### Electron Frontend

The Electron frontend serves as the user interface layer, implemented using HTML, CSS, and JavaScript. It utilizes the Electron framework to create a windowed
