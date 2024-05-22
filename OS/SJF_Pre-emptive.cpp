#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX_BURST_TIME = 300;

typedef struct {
    int bt, at, id;
    int rt, tat, wt, ct; 
    bool completed;      // Flag to indicate whether the process has completed or not
} Process;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort_by_at(int n, Process *p) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].at < p[i].at) {
                swap(&p[i].id, &p[j].id);
                swap(&p[i].at, &p[j].at);
                swap(&p[i].bt, &p[j].bt);
                swap(&p[i].rt, &p[j].rt);

            }
        }
    }
}

int *sort_index(int n, int *arr) {
    int *idx = new int[n];
    for (int i = 0; i < n; i++) 
        idx[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[idx[i]] > arr[idx[j]])
                swap(&idx[i], &idx[j]);
        }
    }
    return idx; //returns the pointer to the sorted indexed array
}

void SJF_Pre_emptive(int n, Process *p) {
    sort_by_at(n, p);
    int current_time = p[0].at;
    bool all_completed = false;
    int total_tat = 0, total_wt = 0;

    while (!all_completed) {
        all_completed = true;
        int shortest_rt_index = -1;
        int min_burst = MAX_BURST_TIME; 

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= current_time && p[i].rt < min_burst) {
                min_burst = p[i].rt;
                shortest_rt_index = i;
                all_completed = false;
            }
        }

        if (all_completed) // If all processes are completed, break the loop
            break;

        // Execute the process with the shortest remaining burst time
        p[shortest_rt_index].rt--;
        current_time++;

        if (p[shortest_rt_index].rt == 0) {
            p[shortest_rt_index].completed = true;
            p[shortest_rt_index].tat = current_time - p[shortest_rt_index].at;
            p[shortest_rt_index].wt = p[shortest_rt_index].tat - p[shortest_rt_index].bt;
            p[shortest_rt_index].ct = current_time; // COMPLETION TIME
            total_tat += p[shortest_rt_index].tat;  
            total_wt += p[shortest_rt_index].wt;    
        }
    }

    cout << "\nSJF Preemptive Scheduling\n";
    cout << "PID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].bt << "\t\t" << p[i].at << "\t\t" << p[i].wt << "\t\t" << p[i].tat << "\t\t" << p[i].ct << endl;
    }
    cout << "\nAverage Waiting Time = " << static_cast<float>(total_wt) / n << endl;
    cout << "Average Turnaround Time = " << static_cast<float>(total_tat) / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process *p = (Process *)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        p[i].id = i+1;
        cout << "Enter the arrival time for P" << i + 1 << ": ";
        cin >> p[i].at;
        cout << "Enter the burst time for P" << i + 1 << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
        p[i].completed = false;
    }

    SJF_Pre_emptive(n, p);
    free(p);
    return 0;
}
