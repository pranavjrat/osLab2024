#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 5

void producer(int write_fd, int producer_id) {
    int i;
    for (i = 0; i < 5; ++i) {
        printf("Producer %d producing item %d\n", producer_id, i);
        write(write_fd, &i, sizeof(int));
        sleep(rand() % 2);  // Simulate some work
    }
    close(write_fd);
}

void consumer(int read_fd, int consumer_id) {
    int item;
    while (read(read_fd, &item, sizeof(int)) > 0) {
        printf("Consumer %d consuming item %d\n", consumer_id, item);
        sleep(rand() % 2);  // Simulate some work
    }
    close(read_fd);
}

int main() {
    int pipefd[2];
    pid_t producer_pid, consumer_pid;
    int i;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));  // Initialize random seed

    for (i = 0; i < 2; ++i) {
        producer_pid = fork();
        if (producer_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (producer_pid == 0) {  // Child process (producer)
            close(pipefd[0]);  // Close the read end
            producer(pipefd[1], i);
            exit(EXIT_SUCCESS);
        }
    }

    for (i = 0; i < 3; ++i) {
        consumer_pid = fork();
        if (consumer_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (consumer_pid == 0) {  // Child process (consumer)
            close(pipefd[1]);  // Close the write end
            consumer(pipefd[0], i);
            exit(EXIT_SUCCESS);
        }
    }

    // Close the pipe in the parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for all child processes to finish
    for (i = 0; i < 5; ++i) {
        wait(NULL);
    }

    return 0;
}