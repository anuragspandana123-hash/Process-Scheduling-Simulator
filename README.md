# Process Scheduling Simulator & Performance Analysis Tool using C

## Overview

This project is a modular C-based CPU process scheduling simulator designed to simulate and analyze different CPU scheduling algorithms.

The simulator accepts process details such as Arrival Time, Burst Time, and Priority, and calculates important scheduling performance metrics. It also generates Gantt charts and provides a comparison of different scheduling algorithms.

The project provides a practical implementation of CPU scheduling concepts used in Operating Systems.

## Algorithms Implemented

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

```text
Process-Scheduling-Simulator/
│
├── main.c
├── process.c
├── process.h
├── scheduler.c
├── scheduler.h
└── README.md
## How It Works

1. The user enters the number of processes.
2. Arrival Time, Burst Time, and Priority are entered for each process.
3. The user selects a scheduling algorithm.
4. The selected algorithm schedules the processes.
5. The simulator generates a Gantt Chart.
6. Scheduling performance metrics are calculated.
7. The user can compare all scheduling algorithms.
8. Workload analysis and automatic scheduling recommendation are provided.

## Performance Metrics

The simulator calculates:

- Completion Time (CT)
- Turnaround Time (TAT)
- Waiting Time (WT)
- Response Time (RT)
- CPU Utilization
- Context Switches
- Average Waiting Time
- Average Turnaround Time
- Average Response Time

### Formulas

```text
Turnaround Time = Completion Time - Arrival Time

Waiting Time = Turnaround Time - Burst Time

Response Time = First Start Time - Arrival Time

##How to Run
#CLONE REPOSITORY
git clone <your-github-repository-link>
cd Process-Scheduling-Simulator

#TO COMPILE
gcc -Wall -Wextra -std=c11 main.c process.c scheduler.c -o scheduler

#TO RUN
scheduler.exe

## Sample Input

```text
Enter number of processes: 4

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
Priority: 3

Process 4:
Arrival Time: 3
Burst Time: 2
Priority: 2

##SAMPLE OUTPUT
Process Scheduling Simulator

Selected Algorithm: Round Robin
Time Quantum: 2

Gantt Chart:
| P1 | P2 | P3 | P4 | P1 | P2 | P3 | P3 |
0    2    4    6    8    10   11   13   19

Process    CT    TAT    WT    RT
P1         11     11     6     0
P2         13     12     9     1
P3         19     17     9     2
P4          8      5     3     3

Average Waiting Time   : 6.75
Average Turnaround Time: 11.25
Average Response Time  : 1.50
CPU Utilization        : 100%

## Applications

- Understanding CPU scheduling algorithms
- Performing Operating Systems laboratory experiments
- Comparing the performance of different scheduling algorithms
- Analyzing CPU workload behavior
- Learning modular C programming
- Demonstrating CPU scheduling concepts during technical interviews

