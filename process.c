#include <stdio.h>
#include "process.h"

void initialize_processes(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;

        processes[i].arrival_time = 0;
        processes[i].burst_time = 0;
        processes[i].priority = 0;

        processes[i].remaining_time = 0;

        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = -1;

        processes[i].first_start_time = -1;

        processes[i].completed = 0;
    }
}

void input_processes(Process processes[], int n)
{
    printf("\n========== PROCESS INPUT ==========\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nP%d\n", processes[i].pid);

        do
        {
            printf("Arrival Time : ");
            scanf("%d", &processes[i].arrival_time);

            if (processes[i].arrival_time < 0)
                printf("Arrival time cannot be negative.\n");

        } while (processes[i].arrival_time < 0);

        do
        {
            printf("Burst Time   : ");
            scanf("%d", &processes[i].burst_time);

            if (processes[i].burst_time <= 0)
                printf("Burst time must be greater than 0.\n");

        } while (processes[i].burst_time <= 0);

        do
        {
            printf("Priority     : ");
            scanf("%d", &processes[i].priority);

            if (processes[i].priority <= 0)
                printf("Priority must be positive.\n");

        } while (processes[i].priority <= 0);
    }
}

void reset_processes(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time =
            processes[i].burst_time;

        processes[i].completion_time = 0;

        processes[i].turnaround_time = 0;

        processes[i].waiting_time = 0;

        processes[i].response_time = -1;

        processes[i].first_start_time = -1;

        processes[i].completed = 0;
    }
}

void display_processes(Process processes[], int n)
{
    printf("\n");

    printf("PID\tArrival\tBurst\tPriority\n");

    printf("--------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf(
            "P%d\t%d\t%d\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].priority
        );
    }
}