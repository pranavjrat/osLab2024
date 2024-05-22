#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

sem_t empty;
sem_t full;
sem_t mutex;

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void produce_item(int item) {
    printf("Producing item %d\n", item);
}

int consume_item() {
    printf("Consuming item %d\n", buffer[out]);
    return buffer[out];
}

void *producer(void *arg) {
    int item = 0;
    while (1) {
        sem_wait(&empty);
        sem_wait(&mutex);

            // sleep(2);
            produce_item(item);
            buffer[in] = item;
            in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        item++;
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        // sleep(2);
        int item = consume_item();
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        if(item == 5) break;
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&producer_thread, &attr, producer, NULL);
    pthread_create(&consumer_thread, &attr, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
