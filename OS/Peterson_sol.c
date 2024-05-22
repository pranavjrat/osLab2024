#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
// int count = 0;
int turn;
int flag[2] = {0, 0};

void* producer(void *arg){
    while(1){
        flag[0] = 1;
        turn = 1;
            while(flag[1] && turn == 1 );
                buffer[in] = rand()%100;
                printf("Produced: %d\n", buffer[in]);
                in = (in +1) % BUFFER_SIZE;
                // count++;
            flag[0] = 0;
        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void *arg){
    while(1){
        flag[1] = 1;
        turn = 0;
            while(flag[0] && turn == 0);
                printf("Consumed: %d\n", buffer[out]);
                out = (out +1) % BUFFER_SIZE;
                // count--;
            flag[1] = 0;
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t t0, t1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&t0, &attr, producer, NULL);
    pthread_create(&t1, &attr, consumer, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

//only applicable to two threads
    return 0;    
}
