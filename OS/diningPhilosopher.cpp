#include <iostream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <semaphore>
using namespace std;

#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5

pthread_t philosopher[NUM_PHILOSOPHERS];
std::binary_semaphore chopstick[NUM_CHOPSTICKS];

void* solution(void* i) {
    int philosopher_id = *(int*)i;
    chopstick[philosopher_id].acquire();
    chopstick[(philosopher_id + 1) % NUM_PHILOSOPHERS].acquire();
    cout << philosopher_id << " is eating!" << endl;
    sleep(2);
    chopstick[philosopher_id].release();
    chopstick[(philosopher_id + 1) % NUM_PHILOSOPHERS].release();
    cout << philosopher_id << " is thinking!" << endl;
    sleep(1);
    return nullptr;
}

int main() {
    for (int i = 0; i < NUM_CHOPSTICKS; i++) {
        chopstick[i].release(); // Initialize each binary semaphore to 1
    }

    int philosopher_ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosopher[i], NULL, solution, (void*)&philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosopher[i], NULL);
    }

    return 0;
}
