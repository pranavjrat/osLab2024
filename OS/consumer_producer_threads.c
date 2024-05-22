#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;

void *producer(void *arg){
    srand(time(nullptr));
    int i;
    for (i=0; i<10; i++){
        while(count >= BUFFER_SIZE);
        sleep(2);
        buffer[in] = rand()%100;
        printf("Produced: %d\n", buffer[in]);
        in = (in +1) % BUFFER_SIZE;
        count++;
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    srand(time(nullptr));
    int i;
    for (i = 0; i < 10; i++) {
        while (count == 0);
        sleep(2);
        printf("Consumed: %d\n", buffer[out]);
        out = (out + 1) % BUFFER_SIZE;
        count--;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&producer_thread, &attr, producer, NULL); // Create thread(thread name, value, function*, value)
    pthread_create(&consumer_thread, &attr, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);// Join to run thread concurrently


    return 0;
}