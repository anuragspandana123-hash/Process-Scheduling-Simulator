# Process Scheduling Simulator & Performance Analysis Tool using C

## Overview

This project is a modular C-based CPU Process Scheduling Simulator designed to simulate and analyze different CPU scheduling algorithms.

The simulator accepts process details such as Arrival Time, Burst Time, and Priority, and calculates important scheduling performance metrics. It also generates Gantt Charts and provides a comparison of different scheduling algorithms.

The project provides a practical implementation of CPU scheduling concepts used in Operating Systems and demonstrates the use of modular programming in C.

## Algorithms Implemented

The simulator implements the following CPU scheduling algorithms:

- First Come First Served (FCFS)
- Shortest Job First (SJF)
- Shortest Remaining Time First (SRTF)
- Priority Scheduling
- Round Robin

## Features

- Dynamic process input
- Arrival Time and Burst Time handling
- Priority-based scheduling
- Configurable Round Robin Time Quantum
- Gantt Chart generation
- Completion Time calculation
- Turnaround Time calculation
- Waiting Time calculation
- Response Time calculation
- CPU Utilization calculation
- Context Switch calculation
- Average Waiting Time calculation
- Average Turnaround Time calculation
- Average Response Time calculation
- Performance comparison of scheduling algorithms
- Automatic scheduling recommendation
- Workload analysis

## Technologies Used

- C Programming
- GCC Compiler
- Visual Studio Code

## C Concepts Used

- Structures
- Arrays
- Pointers
- Functions
- Header Files
- Modular Programming
- Static Functions
- Command-Line Input/Output

## Project Structure

Process-Scheduling-Simulator/
│
├── main.c
├── process.c
├── process.h
├── scheduler.c
├── scheduler.h
└── README.md

## Project Flow

START
  ↓
Enter Number of Processes
  ↓
Enter Arrival Time, Burst Time & Priority
  ↓
Display Main Menu
  ↓
Select Scheduling Algorithm
  ↓
FCFS / SJF / SRTF / Priority / Round Robin
  ↓
Schedule Processes
  ↓
Generate Gantt Chart
  ↓
Calculate CT, TAT, WT, RT
  ↓
Calculate CPU Utilization & Context Switches
  ↓
Compare Algorithms
  ↓
Workload Analysis
  ↓
Automatic Scheduling Recommendation
  ↓
Display Results
  ↓
END

## How It Works

1. The user enters the number of processes.
2. Arrival Time, Burst Time, and Priority are entered for each process.
3. The user selects a CPU scheduling algorithm.
4. The selected algorithm schedules the processes according to its scheduling policy.
5. The simulator generates a Gantt Chart representing the execution order.
6. Completion Time, Turnaround Time, Waiting Time, and Response Time are calculated.
7. CPU Utilization and Context Switches are calculated for performance analysis.
8. The user can compare the performance of different scheduling algorithms.
9. Workload characteristics are analyzed to understand scheduling behavior.
10. The simulator provides a scheduling recommendation based on performance results.

## Performance Metrics

The simulator calculates the following performance metrics:

- Completion Time (CT)
- Turnaround Time (TAT)
- Waiting Time (WT)
- Response Time (RT)
- Average Waiting Time
- Average Turnaround Time
- Average Response Time
- CPU Utilization
- Context Switches

### Formulas

Turnaround Time (TAT) = Completion Time - Arrival Time

Waiting Time (WT) = Turnaround Time - Burst Time

Response Time (RT) = First Start Time - Arrival Time

Average Waiting Time = Total Waiting Time / Number of Processes

Average Turnaround Time = Total Turnaround Time / Number of Processes

Average Response Time = Total Response Time / Number of Processes

CPU Utilization = (CPU Busy Time / Total CPU Time) × 100

## How to Run

### 1. Compile the Project

Make sure GCC is installed and open the project folder in the terminal.

Compile all C source files using:

```bash
gcc -Wall -Wextra -std=c11 main.c process.c scheduler.c -o scheduler

##Run the program
scheduler.exe

## Sample Input / Output

### Sample Input

```text
============================================
 PROCESS SCHEDULING SIMULATOR
 PERFORMANCE ANALYSIS TOOL USING C
============================================

Enter number of processes (1-100): 4

Process 1:
Arrival Time: 0
Burst Time: 5
Priority: 2

Process 2:
Arrival Time: 1
Burst Time: 3
Priority: 1

Process 3:
Arrival Time: 2
Burst Time: 8
Priority: 4

Process 4:
Arrival Time: 3
Burst Time: 6
Priority: 3

========== MENU ==========

1. FCFS
2. SJF
3. SRTF
4. Priority Scheduling
5. Round Robin
6. Compare All Algorithms
7. Display Processes
0. Exit

Enter choice: 6

Enter Round Robin Time Quantum: 2

##Sample Output
============================================
        PERFORMANCE COMPARISON
============================================

Algorithm       Avg WT    Avg TAT    Avg RT
--------------------------------------------
FCFS            5.75      11.25      5.75
SJF             5.00      10.50      5.00
SRTF            3.75       9.25      1.50
Priority        6.50      12.00      6.50
Round Robin     7.50      13.00      2.75

Best Average Waiting Time : SRTF

============================================
       AUTOMATIC SCHEDULING RECOMMENDATION
============================================

Performance Scores
--------------------------------------------
FCFS             : 5.75
SJF              : 5.00
SRTF             : 2.85
Priority         : 6.50
Round Robin      : 5.60

--------------------------------------------
RECOMMENDED ALGORITHM : SRTF
PERFORMANCE SCORE     : 2.85
--------------------------------------------

Reason: SRTF gives the best combined
waiting-time and response-time result
for this workload.

============================================
#Note:-
The simulator recommends the algorithm with the lowest weighted performance score based on average waiting time and response time.

## Applications

- Understanding CPU Scheduling:Helps users understand how different CPU scheduling algorithms manage processes and allocate CPU time.
- Operating Systems Laboratory: Useful for practical experiments involving FCFS, SJF, SRTF, Priority Scheduling, and Round Robin.
- Performance Comparison: Enables comparison of scheduling algorithms using waiting time, turnaround time, and response time.
- Workload Analysis: Helps analyze process workloads using burst time, priority, and other scheduling parameters.
- Technical Demonstration: Can be used for academic presentations, project demonstrations, and technical interviews.

## Limitations

- The project is a "simulation-based system" and does not perform actual CPU process scheduling.
- It does not interact directly with the operating system's real process scheduler.
- Context-switch overhead is represented as a calculated metric rather than a complete hardware-level simulation.
- Performance results depend on the process parameters provided by the user.
- The automatic recommendation is based on the project's defined weighted performance score and may vary for different workloads.

## Future Enhancements

- Graphical User Interface: Develop an interactive GUI for process input and scheduling visualization.
- Advanced Scheduling Algorithms: Add Multilevel Queue and Multilevel Feedback Queue scheduling.
- Multi-Core Simulation: Extend the simulator to support scheduling across multiple CPU cores.
- Advanced Visualization: Add graphical Gantt charts, performance graphs, and animated process execution.
- Data Export and Reporting: Add options to export scheduling results and generate detailed performance reports.

## Learning Outcomes

- Gained practical understanding of "CPU scheduling algorithms" used in Operating Systems.
- Learned to calculate and analyze Completion Time, Turnaround Time, Waiting Time, and Response Time**.
- Improved practical knowledge of structures, arrays, pointers, functions, and header files** in C.
- Learned to implement modular programming by organizing a project into multiple source and header files.
- Developed skills in algorithm design, performance analysis, testing, debugging, and technical documentation.

## Author

Anurag Maranur 
Electronics and Communication Engineering (ECE) Student  
Embedded Systems & C Programming Enthusiast

