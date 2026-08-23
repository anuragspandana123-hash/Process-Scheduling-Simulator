# Process Scheduling Simulator & Performance Analysis Tool using C

## Overview

This project is a modular C-based CPU scheduling simulator designed
to simulate and analyze different process scheduling algorithms.

## Algorithms Implemented

- First Come First Served (FCFS)
- Shortest Job First (SJF)
- Priority Scheduling
- Round Robin

## Features

- Dynamic process input
- Arrival time and burst time handling
- Priority-based scheduling
- Configurable Round Robin time quantum
- Gantt chart generation
- Completion time calculation
- Turnaround time calculation
- Waiting time calculation
- Response time calculation
- Performance comparison

## Technologies

- C
- GCC
- VS Code

## C Concepts Used

- Structures
- Arrays
- Pointers
- Functions
- Header files
- Modular programming
- Static functions
- Command-line input/output

## Compilation

```bash
gcc -Wall -Wextra -std=c11 main.c process.c scheduler.c -o scheduler