#include<iostream>
#define NUM_PROCESS 4
#define NUM_RESOURCES 3
using namespace std;


int main(){
    int available[NUM_RESOURCES] = {4, 3, 2};
    int need[NUM_PROCESS][NUM_RESOURCES];
    int allocation[NUM_PROCESS][NUM_RESOURCES] ={ {2, 1, 0},   //Allocation Matrix
                                                {1, 2, 2},  
                                                {0, 2, 0},  
                                                {3, 0, 1} };
    int max[NUM_PROCESS][NUM_RESOURCES] ={  {8, 6, 3}, //MAX Matrix 
                                            {9, 4, 3}, 
                                            {5, 3, 3}, 
                                            {4, 2, 3} };

    for(int i = 0; i < NUM_PROCESS; i++){              //NEED matrix calculation
        for(int j = 0;j < NUM_RESOURCES;j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int flag;                   
    int ans[NUM_PROCESS];                       // The safe sequence
    int idx = 0;    
    int finish[NUM_PROCESS] = {0};             // The process nummber currently in safe sequence
    for(int k = 0; k < NUM_PROCESS; k++){       
        for(int i = 0;i < NUM_PROCESS; i++){   // Looks for a process from top to bottom
            if(finish[i] == 0){
                flag = 0;
                for(int j = 0; j < NUM_RESOURCES; j++){     // Check to add in the safe sequence
                    if(need[i][j] > available[j]){
                        flag = 1;
                        break;
                    }
                }
            if(flag == 0){
                ans[idx++] = i;                             // Add to safe sequence
                for(int x = 0; x < NUM_RESOURCES; x++){
                    available[x] += allocation[i][x];       //add the previous allocated resource to available
                }
                finish[i] = 1;                              
            }
            }
        }
    }
    bool flag2 = true;
    for(int i=0; i<NUM_PROCESS; i++)
    {
        if(finish[i] == 0)
        { 
            flag2 = false; 
            cout<<"System is in deadlock !!";
            break; 
        }
    }
    
    if(flag2==true)
    {
        cout<<"System  in safe state and following is the safe sequence: ";
        for(int i=0;i<NUM_PROCESS-1;i++)
        {
            cout<<"P"<<ans[i]<<" -> "; 
        }
        cout<<"P"<<ans[NUM_PROCESS-1]<<endl;
    }  
    
    return 0;
}