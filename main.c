#include <stdio.h>
#include "process.h"
#include "scheduler.h"


/* =========================================================
   COPY PROCESSES
   ========================================================= */

static void copy_processes(
    Process destination[],
    Process source[],
    int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        destination[i] = source[i];
    }
}


/* =========================================================
   AVERAGE WAITING TIME
   ========================================================= */

static double average_waiting(
    Process processes[],
    int n)
{
    double total = 0.0;
    int i;

    for (i = 0; i < n; i++)
    {
        total += processes[i].waiting_time;
    }

    return total / n;
}


/* =========================================================
   AVERAGE TURNAROUND TIME
   ========================================================= */

static double average_turnaround(
    Process processes[],
    int n)
{
    double total = 0.0;
    int i;

    for (i = 0; i < n; i++)
    {
        total += processes[i].turnaround_time;
    }

    return total / n;
}


/* =========================================================
   AVERAGE RESPONSE TIME
   ========================================================= */

static double average_response(
    Process processes[],
    int n)
{
    double total = 0.0;
    int i;

    for (i = 0; i < n; i++)
    {
        total += processes[i].response_time;
    }

    return total / n;
}


/* =========================================================
   WORKLOAD ANALYSIS
   ========================================================= */

static void analyze_workload(
    Process processes[],
    int n)
{
    double total_burst = 0.0;

    int min_burst;
    int max_burst;

    int min_priority;
    int max_priority;

    int i;


    if (n <= 0)
    {
        printf(
            "\nNo processes available for analysis.\n"
        );

        return;
    }


    /* Initialize using first process */

    min_burst =
        processes[0].burst_time;

    max_burst =
        processes[0].burst_time;

    min_priority =
        processes[0].priority;

    max_priority =
        processes[0].priority;


    /* Analyze all processes */

    for (i = 0; i < n; i++)
    {
        total_burst +=
            processes[i].burst_time;


        if (processes[i].burst_time < min_burst)
        {
            min_burst =
                processes[i].burst_time;
        }


        if (processes[i].burst_time > max_burst)
        {
            max_burst =
                processes[i].burst_time;
        }


        if (processes[i].priority < min_priority)
        {
            min_priority =
                processes[i].priority;
        }


        if (processes[i].priority > max_priority)
        {
            max_priority =
                processes[i].priority;
        }
    }


    /* Display workload information */

    printf(
        "\n============================================\n"
        "             WORKLOAD ANALYSIS\n"
        "============================================\n"
    );


    printf(
        "\nNumber of Processes : %d\n",
        n
    );


    printf(
        "Average Burst Time  : %.2f\n",
        total_burst / n
    );


    printf(
        "Shortest Burst Time : %d\n",
        min_burst
    );


    printf(
        "Longest Burst Time  : %d\n",
        max_burst
    );


    printf(
        "Priority Range      : %d - %d\n",
        min_priority,
        max_priority
    );


    /* Workload classification */

    if ((max_burst - min_burst) >= 5)
    {
        printf(
            "Workload Type       : Mixed Burst Workload\n"
        );
    }
    else
    {
        printf(
            "Workload Type       : Similar Burst Workload\n"
        );
    }


    printf(
        "============================================\n"
    );
}


/* =========================================================
   AUTOMATIC SCHEDULING RECOMMENDATION
   =========================================================

   Score =
   60% Average Waiting Time
   40% Average Response Time

   Lower score = better performance.
   ========================================================= */

static void recommend_algorithm(
    Process fcfs[],
    Process sjf[],
    Process srtf[],
    Process priority[],
    Process rr[],
    int n)
{
    double fcfs_wt;
    double sjf_wt;
    double srtf_wt;
    double priority_wt;
    double rr_wt;

    double fcfs_rt;
    double sjf_rt;
    double srtf_rt;
    double priority_rt;
    double rr_rt;

    double fcfs_score;
    double sjf_score;
    double srtf_score;
    double priority_score;
    double rr_score;

    double best_score;

    int best_algorithm;


    /* Waiting times */

    fcfs_wt =
        average_waiting(fcfs, n);

    sjf_wt =
        average_waiting(sjf, n);

    srtf_wt =
        average_waiting(srtf, n);

    priority_wt =
        average_waiting(priority, n);

    rr_wt =
        average_waiting(rr, n);


    /* Response times */

    fcfs_rt =
        average_response(fcfs, n);

    sjf_rt =
        average_response(sjf, n);

    srtf_rt =
        average_response(srtf, n);

    priority_rt =
        average_response(priority, n);

    rr_rt =
        average_response(rr, n);


    /* Performance scores */

    fcfs_score =
        (0.60 * fcfs_wt) +
        (0.40 * fcfs_rt);

    sjf_score =
        (0.60 * sjf_wt) +
        (0.40 * sjf_rt);

    srtf_score =
        (0.60 * srtf_wt) +
        (0.40 * srtf_rt);

    priority_score =
        (0.60 * priority_wt) +
        (0.40 * priority_rt);

    rr_score =
        (0.60 * rr_wt) +
        (0.40 * rr_rt);


    /* Assume FCFS is best initially */

    best_score =
        fcfs_score;

    best_algorithm = 1;


    if (sjf_score < best_score)
    {
        best_score =
            sjf_score;

        best_algorithm = 2;
    }


    if (srtf_score < best_score)
    {
        best_score =
            srtf_score;

        best_algorithm = 3;
    }


    if (priority_score < best_score)
    {
        best_score =
            priority_score;

        best_algorithm = 4;
    }


    if (rr_score < best_score)
    {
        best_score =
            rr_score;

        best_algorithm = 5;
    }


    /* Display recommendation */

    printf(
        "\n============================================\n"
        "       AUTOMATIC SCHEDULING RECOMMENDATION\n"
        "============================================\n"
    );


    printf(
        "\nPerformance Scores\n"
    );


    printf(
        "Lower score = Better performance\n"
    );


    printf(
        "--------------------------------------------\n"
    );


    printf(
        "FCFS             : %.2f\n",
        fcfs_score
    );


    printf(
        "SJF              : %.2f\n",
        sjf_score
    );


    printf(
        "SRTF             : %.2f\n",
        srtf_score
    );


    printf(
        "Priority         : %.2f\n",
        priority_score
    );


    printf(
        "Round Robin      : %.2f\n",
        rr_score
    );


    printf(
        "\n--------------------------------------------\n"
    );


    printf(
        "RECOMMENDED ALGORITHM : "
    );


    switch (best_algorithm)
    {
        case 1:
            printf("FCFS\n");
            break;

        case 2:
            printf("SJF\n");
            break;

        case 3:
            printf("SRTF\n");
            break;

        case 4:
            printf("Priority Scheduling\n");
            break;

        case 5:
            printf("Round Robin\n");
            break;
    }


    printf(
        "PERFORMANCE SCORE     : %.2f\n",
        best_score
    );


    printf(
        "--------------------------------------------\n"
    );


    printf(
        "Recommendation Basis:\n"
        "60%% Waiting Time + 40%% Response Time\n"
    );


    printf(
        "\nReason: "
    );


    switch (best_algorithm)
    {
        case 1:
            printf(
                "FCFS produced the lowest combined "
                "waiting-time and response-time score.\n"
            );
            break;

        case 2:
            printf(
                "SJF produced the lowest combined "
                "waiting-time and response-time score.\n"
            );
            break;

        case 3:
            printf(
                "SRTF produced the lowest combined "
                "waiting-time and response-time score.\n"
            );
            break;

        case 4:
            printf(
                "Priority Scheduling produced the lowest "
                "combined waiting-time and response-time score.\n"
            );
            break;

        case 5:
            printf(
                "Round Robin produced the lowest combined "
                "waiting-time and response-time score.\n"
            );
            break;
    }


    printf(
        "============================================\n"
    );
}


/* =========================================================
   RUN ONE ALGORITHM
   ========================================================= */

static void run_algorithm(
    Process original[],
    int n,
    int choice)
{
    Process processes[MAX_PROCESSES];

    GanttChart chart;

    int quantum;


    copy_processes(
        processes,
        original,
        n
    );


    reset_processes(
        processes,
        n
    );


    /* FCFS */

    if (choice == 1)
    {
        fcfs(
            processes,
            n,
            &chart
        );


        display_results(
            processes,
            n,
            &chart,
            "FCFS"
        );


        display_system_metrics(
            processes,
            n
        );


        display_context_switches(
            &chart
        );
    }


    /* SJF */

    else if (choice == 2)
    {
        sjf(
            processes,
            n,
            &chart
        );


        display_results(
            processes,
            n,
            &chart,
            "SJF"
        );


        display_system_metrics(
            processes,
            n
        );


        display_context_switches(
            &chart
        );
    }


    /* SRTF */

    else if (choice == 3)
    {
        srtf(
            processes,
            n,
            &chart
        );


        display_results(
            processes,
            n,
            &chart,
            "SRTF"
        );


        display_system_metrics(
            processes,
            n
        );


        display_context_switches(
            &chart
        );
    }


    /* Priority Scheduling */

    else if (choice == 4)
    {
        priority_scheduling(
            processes,
            n,
            &chart
        );


        display_results(
            processes,
            n,
            &chart,
            "PRIORITY"
        );


        display_system_metrics(
            processes,
            n
        );


        display_context_switches(
            &chart
        );
    }


    /* Round Robin */

    else if (choice == 5)
    {
        printf(
            "\nEnter Time Quantum: "
        );


        scanf(
            "%d",
            &quantum
        );


        if (quantum <= 0)
        {
            printf(
                "\nQuantum must be greater than 0.\n"
            );

            return;
        }


        round_robin(
            processes,
            n,
            quantum,
            &chart
        );


        display_results(
            processes,
            n,
            &chart,
            "ROUND ROBIN"
        );


        display_system_metrics(
            processes,
            n
        );


        display_context_switches(
            &chart
        );
    }
}


/* =========================================================
   COMPARE ALL ALGORITHMS
   ========================================================= */

static void compare_algorithms(
    Process original[],
    int n)
{
    Process fcfs_processes[MAX_PROCESSES];

    Process sjf_processes[MAX_PROCESSES];

    Process srtf_processes[MAX_PROCESSES];

    Process priority_processes[MAX_PROCESSES];

    Process rr_processes[MAX_PROCESSES];

    GanttChart chart;

    int quantum;


    /* Copy processes */

    copy_processes(
        fcfs_processes,
        original,
        n
    );


    copy_processes(
        sjf_processes,
        original,
        n
    );


    copy_processes(
        srtf_processes,
        original,
        n
    );


    copy_processes(
        priority_processes,
        original,
        n
    );


    copy_processes(
        rr_processes,
        original,
        n
    );


    /* Reset */

    reset_processes(
        fcfs_processes,
        n
    );


    reset_processes(
        sjf_processes,
        n
    );


    reset_processes(
        srtf_processes,
        n
    );


    reset_processes(
        priority_processes,
        n
    );


    reset_processes(
        rr_processes,
        n
    );


    /* FCFS */

    fcfs(
        fcfs_processes,
        n,
        &chart
    );


    calculate_metrics(
        fcfs_processes,
        n
    );


    /* SJF */

    sjf(
        sjf_processes,
        n,
        &chart
    );


    calculate_metrics(
        sjf_processes,
        n
    );


    /* SRTF */

    srtf(
        srtf_processes,
        n,
        &chart
    );


    calculate_metrics(
        srtf_processes,
        n
    );


    /* Priority */

    priority_scheduling(
        priority_processes,
        n,
        &chart
    );


    calculate_metrics(
        priority_processes,
        n
    );


    /* Round Robin */

    printf(
        "\nEnter Round Robin Time Quantum: "
    );


    scanf(
        "%d",
        &quantum
    );


    if (quantum <= 0)
    {
        printf(
            "\nQuantum must be greater than 0.\n"
        );

        return;
    }


    round_robin(
        rr_processes,
        n,
        quantum,
        &chart
    );


    calculate_metrics(
        rr_processes,
        n
    );


    /* =====================================================
       CALCULATE AVERAGES
       ===================================================== */

    double fcfs_wt =
        average_waiting(
            fcfs_processes,
            n
        );


    double sjf_wt =
        average_waiting(
            sjf_processes,
            n
        );


    double srtf_wt =
        average_waiting(
            srtf_processes,
            n
        );


    double priority_wt =
        average_waiting(
            priority_processes,
            n
        );


    double rr_wt =
        average_waiting(
            rr_processes,
            n
        );


    double fcfs_tat =
        average_turnaround(
            fcfs_processes,
            n
        );


    double sjf_tat =
        average_turnaround(
            sjf_processes,
            n
        );


    double srtf_tat =
        average_turnaround(
            srtf_processes,
            n
        );


    double priority_tat =
        average_turnaround(
            priority_processes,
            n
        );


    double rr_tat =
        average_turnaround(
            rr_processes,
            n
        );


    double fcfs_rt =
        average_response(
            fcfs_processes,
            n
        );


    double sjf_rt =
        average_response(
            sjf_processes,
            n
        );


    double srtf_rt =
        average_response(
            srtf_processes,
            n
        );


    double priority_rt =
        average_response(
            priority_processes,
            n
        );


    double rr_rt =
        average_response(
            rr_processes,
            n
        );


    /* =====================================================
       PERFORMANCE COMPARISON
       ===================================================== */

    printf(
        "\n============================================\n"
        "        PERFORMANCE COMPARISON\n"
        "============================================\n"
    );


    printf(
        "\nAlgorithm\tAvg WT\tAvg TAT\tAvg RT\n"
    );


    printf(
        "--------------------------------------------\n"
    );


    printf(
        "FCFS\t\t%.2f\t%.2f\t%.2f\n",
        fcfs_wt,
        fcfs_tat,
        fcfs_rt
    );


    printf(
        "SJF\t\t%.2f\t%.2f\t%.2f\n",
        sjf_wt,
        sjf_tat,
        sjf_rt
    );


    printf(
        "SRTF\t\t%.2f\t%.2f\t%.2f\n",
        srtf_wt,
        srtf_tat,
        srtf_rt
    );


    printf(
        "Priority\t%.2f\t%.2f\t%.2f\n",
        priority_wt,
        priority_tat,
        priority_rt
    );


    printf(
        "Round Robin\t%.2f\t%.2f\t%.2f\n",
        rr_wt,
        rr_tat,
        rr_rt
    );


    /* =====================================================
       BEST AVERAGE WAITING TIME
       ===================================================== */

    double best = fcfs_wt;

    const char *best_algorithm = "FCFS";


    if (sjf_wt < best)
    {
        best = sjf_wt;
        best_algorithm = "SJF";
    }


    if (srtf_wt < best)
    {
        best = srtf_wt;
        best_algorithm = "SRTF";
    }


    if (priority_wt < best)
    {
        best = priority_wt;
        best_algorithm = "Priority";
    }


    if (rr_wt < best)
    {
        best = rr_wt;
        best_algorithm = "Round Robin";
    }


    printf(
        "\nBest Average Waiting Time : %s\n",
        best_algorithm
    );


    printf(
        "============================================\n"
    );


    /* =====================================================
       WORKLOAD ANALYSIS
       ===================================================== */

    analyze_workload(
        original,
        n
    );


    /* =====================================================
       AUTOMATIC RECOMMENDATION
       ===================================================== */

    recommend_algorithm(
        fcfs_processes,
        sjf_processes,
        srtf_processes,
        priority_processes,
        rr_processes,
        n
    );
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */

int main(void)
{
    Process processes[MAX_PROCESSES];

    int n;

    int choice;


    /* =====================================================
       TITLE
       ===================================================== */

    printf(
        "\n============================================\n"
        " PROCESS SCHEDULING SIMULATOR\n"
        " PERFORMANCE ANALYSIS TOOL USING C\n"
        "============================================\n"
    );


    /* =====================================================
       NUMBER OF PROCESSES
       ===================================================== */

    printf(
        "\nEnter number of processes (1-%d): ",
        MAX_PROCESSES
    );


    if (scanf("%d", &n) != 1)
    {
        printf(
            "\nInvalid input.\n"
        );

        return 1;
    }


    if (n < 1 || n > MAX_PROCESSES)
    {
        printf(
            "\nInvalid number of processes.\n"
        );

        return 1;
    }


    /* =====================================================
       INITIALIZE PROCESSES
       ===================================================== */

    initialize_processes(
        processes,
        n
    );


    /* =====================================================
       INPUT PROCESS DETAILS
       ===================================================== */

    input_processes(
        processes,
        n
    );


    /* =====================================================
       MAIN MENU
       ===================================================== */

    while (1)
    {
        printf(
            "\n\n========== MENU ==========\n"
        );


        printf(
            "1. FCFS\n"
            "2. SJF\n"
            "3. SRTF\n"
            "4. Priority Scheduling\n"
            "5. Round Robin\n"
            "6. Compare All Algorithms\n"
            "7. Display Processes\n"
            "0. Exit\n"
        );


        printf(
            "\nEnter choice: "
        );


        if (scanf("%d", &choice) != 1)
        {
            printf(
                "\nInvalid input.\n"
            );

            return 1;
        }


        /* EXIT */

        if (choice == 0)
        {
            printf(
                "\nProgram terminated.\n"
            );

            break;
        }


        /* INDIVIDUAL ALGORITHMS */

        if (choice >= 1 && choice <= 5)
        {
            run_algorithm(
                processes,
                n,
                choice
            );
        }


        /* COMPARE ALL */

        else if (choice == 6)
        {
            compare_algorithms(
                processes,
                n
            );
        }


        /* DISPLAY PROCESSES */

        else if (choice == 7)
        {
            display_processes(
                processes,
                n
            );
        }


        /* INVALID */

        else
        {
            printf(
                "\nInvalid choice.\n"
            );
        }
    }


    return 0;
}