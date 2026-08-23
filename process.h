#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 20

typedef struct
{
    int pid;

    int arrival_time;
    int burst_time;
    int priority;

    int remaining_time;

    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

    int first_start_time;

    int completed;

} Process;

void initialize_processes(Process processes[], int n);

void input_processes(Process processes[], int n);

void reset_processes(Process processes[], int n);

void display_processes(Process processes[], int n);

#endif