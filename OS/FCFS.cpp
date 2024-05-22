#include<iostream>
using namespace std;

void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int *sort_index(int n, int *arr){
    int *idx = new int[n];
    for(int i = 0;i<n;i++) idx[i] = i;
    for(int i = 0;i < n; i++){
        for(int j = i+1; j<n;j++){
            if(arr[idx[i]] > arr[idx[j]]) swap(&idx[i],&idx[j]);
        }
    }
    return idx; //returns the ptr to the sorted array index
}

void FCFS(int n, int at[], int bt[]){
    int *idx = sort_index(n,at);
    int ct[n],tat[n],wt[n];
    ct[idx[0]] = at[idx[0]] + bt[idx[0]];
    int total_wt = 0, total_tat = 0;
    for(int i = 1;i<n;i++) {
        ct[idx[i]] = ct[idx[i-1]] + bt[idx[i]];
    }
    for(int i = 0;i<n;i++) {
        tat[idx[i]] = ct[idx[i]] - at[idx[i]];
        wt[idx[i]] = tat[idx[i]] - bt[idx[i]];
        total_wt += wt[idx[i]];
        total_tat += tat[idx[i]];
    }
    cout<<"\nFCFS Scheduling\n";
    cout<<"Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (int i = 0; i < n; i++) {
        cout<<"P"<<i+1<<"\t"<<bt[i]<<"\t\t"<<at[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<"\t\t"<<ct[i]<<endl;;
    }

    cout<<"\nAverage Waiting Time = "<<static_cast<float>(total_wt) / n<<endl;
    cout<<"Average Turnaround Time = "<<static_cast<float>(total_tat) / n<<endl;
}

int main(){
    int n;
    cout<<"Enter the number of processes: ";cin>>n;
    int bt[n],at[n];
    for(int i=0;i<n;i++){
        cout<<"Enter Arrival Time for p"<<i+1<<":";cin>>at[i];
        cout<<"Enter Burst Time for p"<<i+1<<":";cin>>bt[i];
    }
    FCFS(n,at,bt);
    return 0;
}