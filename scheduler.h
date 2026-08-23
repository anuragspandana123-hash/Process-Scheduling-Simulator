#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

#define MAX_GANTT 200

typedef struct
{
    int pid;
    int start_time;
    int end_time;

} GanttEntry;

typedef struct
{
    GanttEntry entries[MAX_GANTT];
    int count;

} GanttChart;


/* Gantt Chart */

void initialize_gantt(GanttChart *chart);

void display_gantt(GanttChart *chart);


/* Scheduling Algorithms */

void fcfs(
    Process processes[],
    int n,
    GanttChart *chart
);

void sjf(
    Process processes[],
    int n,
    GanttChart *chart
);

void srtf(
    Process processes[],
    int n,
    GanttChart *chart
);

void priority_scheduling(
    Process processes[],
    int n,
    GanttChart *chart
);

void round_robin(
    Process processes[],
    int n,
    int quantum,
    GanttChart *chart
);


/* Performance */

void calculate_metrics(
    Process processes[],
    int n
);

void display_results(
    Process processes[],
    int n,
    GanttChart *chart,
    const char *algorithm
);

void display_system_metrics(
    Process processes[],
    int n
);

void display_context_switches(
    GanttChart *chart
);

#endif