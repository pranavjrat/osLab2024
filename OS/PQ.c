#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int burst;
    int priority;
    int remaining_time;
    int completed;
    int WT;
    int TA;
} Process;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void SJF(int n, Process *p) {
    int TWT = 0, TAT = 0;
    int curr_time = 0;
    int completed_processes = 0;

    // Sort processes based on priority
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                swap(&p[i].priority, &p[j].priority);
                swap(&p[i].burst, &p[j].burst);
                swap(&p[i].id, &p[j].id);
            }
        }
        p[i].remaining_time = p[i].burst;
        p[i].completed = 0;
    }

    while (completed_processes < n) {
        int min_burst_index = -1;
        int min_burst = 1000;

        // Find the process with the minimum remaining burst time and highest priority
        for (int i = 0; i < n; i++) {
            if (p[i].priority <= curr_time && p[i].remaining_time < min_burst && !p[i].completed) {
                min_burst = p[i].remaining_time;
                min_burst_index = i;
            }
        }

        // If no process is found, move time forward to the next priority arrival
        if (min_burst_index == -1) {
            int next_priority = 1000;
            for (int i = 0; i < n; i++) {
                if (p[i].priority < next_priority && !p[i].completed) {
                    next_priority = p[i].priority;
                }
            }
            curr_time = next_priority;
        } else {
            // Execute the process with the minimum remaining burst time
            p[min_burst_index].remaining_time--;
            curr_time++;

            // If the process is completed, calculate waiting and turnaround times
            if (p[min_burst_index].remaining_time == 0) {
                p[min_burst_index].completed = 1;
                p[min_burst_index].TA = curr_time - p[min_burst_index].priority;
                p[min_burst_index].WT = p[min_burst_index].TA - p[min_burst_index].burst;

                TWT += p[min_burst_index].WT;
                TAT += p[min_burst_index].TA;

                completed_processes++;
            }
        }
    }

    printf("\nSJF Scheduling (Preemptive based on Priority)\n");
    
    printf("Process\tBurst Time\tpriority Time\tWT Time\t  TA Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t  %d\n", p[i].id, p[i].burst, p[i].priority, p[i].WT, p[i].TA);
    }

    printf("\nAverage WT Time = %.2f\n", (float)TWT / n);
    printf("Average TA Time = %.2f\n", (float)TAT / n);
    
    
}

int main() {
    int n;
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    Process *p = (Process*)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        printf("Enter Process id: ");
        scanf("%d", &p[i].id);
       
        printf("Burst time for p%d: ", p[i].id);
        scanf("%d", &p[i].burst);

        printf("priority time for p%d: ", p[i].id);
        scanf("%d", &p[i].priority);

        p[i].completed = 0;
        p[i].WT = 0;
        p[i].TA = 0;
    }

    SJF(n, p);

    free(p);
    return 0;
}
