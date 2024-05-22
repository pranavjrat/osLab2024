#include<iostream>
#include<iomanip>
#include <queue>
#include <cstring>   // memset

using namespace std;

struct process {
  int at;
  int bt;
  int ct;
  int tt;
  int wt;
  int st;
};

int main() {
  int n, quantum;
  struct process p[50];
  float avgTurn, avgWaiting;
  int totalTAT = 0, rt[50];
  int totalWaiting = 0, index;

  cout << setprecision(2) << fixed;
  cout << "Enter the number of processes: ";
  cin >> n;
  cout << "Enter time quantum of CPU: ";
  cin >> quantum;

  // Use for loop to enter the details of the process
  //  like Arrival time and the Burst Time  
  for (int i = 0; i < n; i++) {
    cout << "Enter arrival time of process " << i + 1 << ": ";
    cin >> p[i].at;
    cout << "Enter burst time of process " << i + 1 << ": ";
    cin >> p[i].bt;
    rt[i] = p[i].bt;
    cout << endl;
  }


    // We will be using a FIFO queue to implement this algorithm
  queue < int > q;
  int current_time = 0;
  // Keep track of the time using a variable - current_time
  q.push(0);
  int completed = 0;
  int mark[100];
  memset(mark, 0, sizeof(mark));
  mark[0] = 1;   //to indicate the processes in the queue  

  while (completed != n) {
    // Give quantum unit of time to the process that is in the front
    //  of the queue and pop this process from the queue.
    // cout<<"index / q front is: "<<q.front()<<endl;
    index = q.front();
    q.pop();

    if (rt[index] == p[index].bt) {
      p[index].st = max(current_time, p[index].at);
      current_time = p[index].st;
    }

    if (0 < rt[index] - quantum) {
      rt[index] -= quantum;
      current_time += quantum;
    } else {
      current_time += rt[index];
      p[index].ct = current_time;
      p[index].tt = p[index].ct - p[index].at;
      p[index].wt = p[index].tt - p[index].bt;
      totalWaiting += p[index].wt;
      totalTAT += p[index].tt;
      completed++;
      rt[index] = 0;
    }

    // If some process has arrived when this process was executing,
    //  insert them into the queue. FCFS
    for (int i = 1; i < n; i++) {
      if (rt[i] > 0 && p[i].at <= current_time && mark[i] == 0) {
        mark[i] = 1;
        q.push(i);
      }
    }
    // If the current process has burst time remaining, 
    // push the process into the queue again.
    if (0 < rt[index]) q.push(index);

    // If the queue is empty,
    //  pick the first process from the list that is not completed.
    if (q.empty()) {
      for (int i = 1; i < n; i++) {
        if (0 < rt[i]) {
          mark[i] = 1;
          q.push(i);
          break;
        }
      }
    }
  }
  avgWaiting = (float) totalWaiting / n;
  avgTurn = (float) totalTAT / n;
  cout << endl;

   // To get the data of each process uncomment this. 
   cout<<"Process Id\t"<<"Arrival Time\t"<<"Burst Time\t"<<"Completion Time\t"<<" Turn around Time\t"<<"Waiting Time\t"<<"\n"<<endl;
   for(int i = 0; i < n; i++) {
       cout<<i+1<<"\t"<<"\t"<<p[i].at<<"\t"<<"\t"<<p[i].bt<<"\t"<<"\t"<<p[i].ct<<"\t"<<"\t"<<"\t"<<p[i].tt<<"\t"<<"\t"<<p[i].wt<<"\t"<<"\t"<<"\n"<<endl;
   }
  cout << "Average Waiting Time = " << avgWaiting << endl;
  cout << "Average Turnaround Time = " << avgTurn << endl;
  return 0;
}
