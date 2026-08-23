#include <stdio.h>
#include "scheduler.h"


/* =========================================================
   ADD ENTRY TO GANTT CHART
   ========================================================= */

static void add_gantt(
    GanttChart *chart,
    int pid,
    int start,
    int end)
{
    if (start >= end)
        return;

    /* Merge consecutive execution of same process */

    if (chart->count > 0)
    {
        GanttEntry *last =
            &chart->entries[chart->count - 1];

        if (last->pid == pid &&
            last->end_time == start)
        {
            last->end_time = end;
            return;
        }
    }

    if (chart->count >= MAX_GANTT)
        return;

    chart->entries[chart->count].pid = pid;
    chart->entries[chart->count].start_time = start;
    chart->entries[chart->count].end_time = end;

    chart->count++;
}


/* =========================================================
   INITIALIZE GANTT
   ========================================================= */

void initialize_gantt(GanttChart *chart)
{
    chart->count = 0;
}


/* =========================================================
   DISPLAY GANTT
   ========================================================= */

void display_gantt(GanttChart *chart)
{
    printf("\nGANTT CHART\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < chart->count; i++)
    {
        if (chart->entries[i].pid == 0)
            printf("| IDLE ");
        else
            printf("| P%d ", chart->entries[i].pid);
    }

    printf("|\n");

    if (chart->count > 0)
    {
        for (int i = 0; i < chart->count; i++)
        {
            printf(
                "%-7d",
                chart->entries[i].start_time
            );
        }

        printf(
            "%d\n",
            chart->entries[chart->count - 1].end_time
        );
    }
}


/* =========================================================
   FCFS
   ========================================================= */

void fcfs(
    Process processes[],
    int n,
    GanttChart *chart)
{
    int time = 0;
    int completed = 0;

    initialize_gantt(chart);

    while (completed < n)
    {
        int selected = -1;
        int earliest_arrival = 1000000;

        for (int i = 0; i < n; i++)
        {
            if (!processes[i].completed &&
                processes[i].arrival_time <= time)
            {
                if (processes[i].arrival_time <
                    earliest_arrival)
                {
                    earliest_arrival =
                        processes[i].arrival_time;

                    selected = i;
                }
            }
        }

        /* CPU idle */

        if (selected == -1)
        {
            int next_arrival = 1000000;

            for (int i = 0; i < n; i++)
            {
                if (!processes[i].completed &&
                    processes[i].arrival_time <
                    next_arrival)
                {
                    next_arrival =
                        processes[i].arrival_time;
                }
            }

            add_gantt(
                chart,
                0,
                time,
                next_arrival
            );

            time = next_arrival;
            continue;
        }

        int start = time;

        processes[selected].first_start_time =
            time;

        processes[selected].response_time =
            time -
            processes[selected].arrival_time;

        time += processes[selected].burst_time;

        processes[selected].completion_time =
            time;

        processes[selected].completed = 1;

        completed++;

        add_gantt(
            chart,
            processes[selected].pid,
            start,
            time
        );
    }
}


/* =========================================================
   SJF - NON PREEMPTIVE
   ========================================================= */

void sjf(
    Process processes[],
    int n,
    GanttChart *chart)
{
    int time = 0;
    int completed = 0;

    initialize_gantt(chart);

    while (completed < n)
    {
        int selected = -1;

        for (int i = 0; i < n; i++)
        {
            if (!processes[i].completed &&
                processes[i].arrival_time <= time)
            {
                if (selected == -1 ||
                    processes[i].burst_time <
                    processes[selected].burst_time)
                {
                    selected = i;
                }
            }
        }

        /* CPU idle */

        if (selected == -1)
        {
            int next_arrival = 1000000;

            for (int i = 0; i < n; i++)
            {
                if (!processes[i].completed &&
                    processes[i].arrival_time <
                    next_arrival)
                {
                    next_arrival =
                        processes[i].arrival_time;
                }
            }

            add_gantt(
                chart,
                0,
                time,
                next_arrival
            );

            time = next_arrival;
            continue;
        }

        int start = time;

        processes[selected].first_start_time =
            time;

        processes[selected].response_time =
            time -
            processes[selected].arrival_time;

        time += processes[selected].burst_time;

        processes[selected].completion_time =
            time;

        processes[selected].completed = 1;

        completed++;

        add_gantt(
            chart,
            processes[selected].pid,
            start,
            time
        );
    }
}


/* =========================================================
   SRTF - SHORTEST REMAINING TIME FIRST
   PREEMPTIVE
   ========================================================= */

void srtf(
    Process processes[],
    int n,
    GanttChart *chart)
{
    int time = 0;
    int completed = 0;

    initialize_gantt(chart);

    /* Initialize remaining time */

    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time =
            processes[i].burst_time;

        processes[i].first_start_time = -1;
        processes[i].completed = 0;
    }

    while (completed < n)
    {
        int selected = -1;

        /* Find shortest remaining process */

        for (int i = 0; i < n; i++)
        {
            if (!processes[i].completed &&
                processes[i].arrival_time <= time &&
                processes[i].remaining_time > 0)
            {
                if (selected == -1 ||
                    processes[i].remaining_time <
                    processes[selected].remaining_time)
                {
                    selected = i;
                }
                else if (
                    processes[i].remaining_time ==
                    processes[selected].remaining_time)
                {
                    /* Tie: earlier arrival */

                    if (processes[i].arrival_time <
                        processes[selected].arrival_time)
                    {
                        selected = i;
                    }
                }
            }
        }

        /* CPU idle */

        if (selected == -1)
        {
            int next_arrival = 1000000;

            for (int i = 0; i < n; i++)
            {
                if (!processes[i].completed &&
                    processes[i].remaining_time > 0 &&
                    processes[i].arrival_time > time)
                {
                    if (processes[i].arrival_time <
                        next_arrival)
                    {
                        next_arrival =
                            processes[i].arrival_time;
                    }
                }
            }

            add_gantt(
                chart,
                0,
                time,
                next_arrival
            );

            time = next_arrival;
            continue;
        }

        /* First CPU execution */

        if (processes[selected].first_start_time == -1)
        {
            processes[selected].first_start_time =
                time;

            processes[selected].response_time =
                time -
                processes[selected].arrival_time;
        }

        /*
         * Execute exactly one time unit.
         * This provides preemption.
         */

        int start = time;

        time++;

        processes[selected].remaining_time--;

        add_gantt(
            chart,
            processes[selected].pid,
            start,
            time
        );

        /* Check completion */

        if (processes[selected].remaining_time == 0)
        {
            processes[selected].completion_time =
                time;

            processes[selected].completed = 1;

            completed++;
        }
    }
}


/* =========================================================
   PRIORITY SCHEDULING
   LOWER NUMBER = HIGHER PRIORITY
   ========================================================= */

void priority_scheduling(
    Process processes[],
    int n,
    GanttChart *chart)
{
    int time = 0;
    int completed = 0;

    initialize_gantt(chart);

    while (completed < n)
    {
        int selected = -1;

        for (int i = 0; i < n; i++)
        {
            if (!processes[i].completed &&
                processes[i].arrival_time <= time)
            {
                if (selected == -1 ||
                    processes[i].priority <
                    processes[selected].priority)
                {
                    selected = i;
                }
            }
        }

        /* CPU idle */

        if (selected == -1)
        {
            int next_arrival = 1000000;

            for (int i = 0; i < n; i++)
            {
                if (!processes[i].completed &&
                    processes[i].arrival_time <
                    next_arrival)
                {
                    next_arrival =
                        processes[i].arrival_time;
                }
            }

            add_gantt(
                chart,
                0,
                time,
                next_arrival
            );

            time = next_arrival;
            continue;
        }

        int start = time;

        processes[selected].first_start_time =
            time;

        processes[selected].response_time =
            time -
            processes[selected].arrival_time;

        time += processes[selected].burst_time;

        processes[selected].completion_time =
            time;

        processes[selected].completed = 1;

        completed++;

        add_gantt(
            chart,
            processes[selected].pid,
            start,
            time
        );
    }
}


/* =========================================================
   ROUND ROBIN
   ========================================================= */

void round_robin(
    Process processes[],
    int n,
    int quantum,
    GanttChart *chart)
{
    int queue[1000];

    int front = 0;
    int rear = 0;

    int time = 0;
    int completed = 0;

    int added[MAX_PROCESSES] = {0};

    initialize_gantt(chart);

    while (completed < n)
    {
        /* Add arrived processes */

        for (int i = 0; i < n; i++)
        {
            if (!added[i] &&
                processes[i].arrival_time <= time)
            {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        /* CPU idle */

        if (front == rear)
        {
            int next_arrival = 1000000;

            for (int i = 0; i < n; i++)
            {
                if (!added[i] &&
                    processes[i].arrival_time <
                    next_arrival)
                {
                    next_arrival =
                        processes[i].arrival_time;
                }
            }

            add_gantt(
                chart,
                0,
                time,
                next_arrival
            );

            time = next_arrival;
            continue;
        }

        int index = queue[front++];

        /* First execution */

        if (processes[index].first_start_time == -1)
        {
            processes[index].first_start_time =
                time;

            processes[index].response_time =
                time -
                processes[index].arrival_time;
        }

        int execution_time =
            processes[index].remaining_time;

        if (execution_time > quantum)
            execution_time = quantum;

        int start = time;

        time += execution_time;

        processes[index].remaining_time -=
            execution_time;

        add_gantt(
            chart,
            processes[index].pid,
            start,
            time
        );

        /* Add newly arrived processes */

        for (int i = 0; i < n; i++)
        {
            if (!added[i] &&
                processes[i].arrival_time <= time)
            {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        /* Not finished */

        if (processes[index].remaining_time > 0)
        {
            queue[rear++] = index;
        }
        else
        {
            processes[index].completion_time =
                time;

            processes[index].completed = 1;

            completed++;
        }
    }
}


/* =========================================================
   CALCULATE METRICS
   ========================================================= */

void calculate_metrics(
    Process processes[],
    int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time =
            processes[i].completion_time -
            processes[i].arrival_time;

        processes[i].waiting_time =
            processes[i].turnaround_time -
            processes[i].burst_time;
    }
}


/* =========================================================
   DISPLAY RESULTS
   ========================================================= */

void display_results(
    Process processes[],
    int n,
    GanttChart *chart,
    const char *algorithm)
{
    double total_waiting = 0;
    double total_turnaround = 0;
    double total_response = 0;

    calculate_metrics(
        processes,
        n
    );

    printf(
        "\n============================================\n"
    );

    printf(
        "           %s RESULTS\n",
        algorithm
    );

    printf(
        "============================================\n"
    );

    printf(
        "\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n"
    );

    printf(
        "------------------------------------------------\n"
    );

    for (int i = 0; i < n; i++)
    {
        printf(
            "P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time,
            processes[i].response_time
        );

        total_waiting +=
            processes[i].waiting_time;

        total_turnaround +=
            processes[i].turnaround_time;

        total_response +=
            processes[i].response_time;
    }

    printf(
        "\nAverage Waiting Time    : %.2f",
        total_waiting / n
    );

    printf(
        "\nAverage Turnaround Time : %.2f",
        total_turnaround / n
    );

    printf(
        "\nAverage Response Time   : %.2f\n",
        total_response / n
    );

    display_gantt(chart);
}


/* =========================================================
   SYSTEM PERFORMANCE METRICS
   ========================================================= */

void display_system_metrics(
    Process processes[],
    int n)
{
    if (n <= 0)
        return;

    int total_burst = 0;

    int first_arrival =
        processes[0].arrival_time;

    int last_completion =
        processes[0].completion_time;

    for (int i = 0; i < n; i++)
    {
        total_burst +=
            processes[i].burst_time;

        if (processes[i].arrival_time <
            first_arrival)
        {
            first_arrival =
                processes[i].arrival_time;
        }

        if (processes[i].completion_time >
            last_completion)
        {
            last_completion =
                processes[i].completion_time;
        }
    }

    int total_time =
        last_completion -
        first_arrival;

    double cpu_utilization = 0.0;

    if (total_time > 0)
    {
        cpu_utilization =
            ((double)total_burst /
             total_time) * 100.0;
    }

    printf(
        "\n============================================\n"
        "        SYSTEM PERFORMANCE METRICS\n"
        "============================================\n"
    );

    printf(
        "Total CPU Burst Time : %d\n",
        total_burst
    );

    printf(
        "Total Execution Time : %d\n",
        total_time
    );

    printf(
        "CPU Utilization      : %.2f%%\n",
        cpu_utilization
    );

    printf(
        "============================================\n"
    );
}


/* =========================================================
   CONTEXT SWITCH COUNT
   ========================================================= */

void display_context_switches(
    GanttChart *chart)
{
    int context_switches = 0;

    for (int i = 1; i < chart->count; i++)
    {
        int previous_pid =
            chart->entries[i - 1].pid;

        int current_pid =
            chart->entries[i].pid;

        /*
         * Count only process-to-process changes.
         * IDLE is not counted as a context switch.
         */

        if (previous_pid != 0 &&
            current_pid != 0 &&
            previous_pid != current_pid)
        {
            context_switches++;
        }
    }

    printf(
        "\nContext Switches : %d\n",
        context_switches
    );
}