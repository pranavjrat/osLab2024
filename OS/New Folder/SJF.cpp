#include <iostream>
using namespace std;

const int MAX_BURST_TIME = 300;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

void SJF(int n, int at[], int bt[]) {
    int *idx = sort_index(n, at);
    int completed[n], sum_bt = 0;
    
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
        sum_bt += bt[i];
    }
    
    int ct[n], tat[n], wt[n];
    int total_wt = 0, total_tat = 0;

    for (int current_time = at[idx[0]]; current_time < sum_bt;) {   //Initialise the current time when the first process arrives
        int shortest_bt_index = -1;
        int min_burst = MAX_BURST_TIME;

        for (int i = 0; i < n; i++) {
            if (at[idx[i]] <= current_time && !completed[idx[i]] && bt[idx[i]] < min_burst) {
                min_burst = bt[idx[i]];
                shortest_bt_index = idx[i];
            }
        }

        completed[shortest_bt_index] = 1;
        current_time += bt[shortest_bt_index];
        tat[shortest_bt_index] = current_time - at[shortest_bt_index];
        wt[shortest_bt_index] = tat[shortest_bt_index] - bt[shortest_bt_index];
        ct[shortest_bt_index] = current_time;
        total_wt += wt[shortest_bt_index];
        total_tat += tat[shortest_bt_index];
    
    }

    cout << "\nSJF Non-Preemptive Scheduling\n";
    cout << "PID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << bt[i] << "\t\t" << at[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << "\t\t" << ct[i] << endl;
    }

    cout << "\nAverage Waiting Time = " << static_cast<float>(total_wt) / n << endl;
    cout << "Average Turnaround Time = " << static_cast<float>(total_tat) / n << endl;

        delete[] idx;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    int bt[n], at[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time for p" << i + 1 << ":";
        cin >> at[i];
        cout << "Enter Burst Time for p" << i + 1 << ":";
        cin >> bt[i];
    }
    
    SJF(n, at, bt);
    return 0;
}
