#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BUFFER_SIZE = 5;
int buffer[BUFFER_SIZE]; 
int in = 0, out = 0, count = 0; 

void producer(int numItems) {
    srand(time(nullptr));
    for (int i = 0; i < numItems; ++i) {
        int item = rand() % 100; 
        cout << "Producer produced: " << item << endl;

        while (count >= BUFFER_SIZE) {
            usleep(1000); 
        }
        buffer[in] = item; 
        in = (in + 1) % BUFFER_SIZE;
        ++count;

        usleep(2000); 
    }
}

void consumer(int numItems) {
    srand(time(nullptr));
    for (int i = 0; i < numItems; ++i) {
        while (count <= 0) {
            usleep(1000); 
        }
        int item = buffer[out]; 
        out = (out + 1) % BUFFER_SIZE; 
        --count;

        cout << "Consumer consumed: " << item << endl;
        usleep(2000); 
    }
}

int main() {
    char choice;
    int numProduce, numConsume;

    do {
        cout << "Do you want to produce (P), consume (C), or exit (E)? ";
        cin >> choice;

        switch(choice) {
            case 'P':
            case 'p':
                cout << "Enter the number of items to produce: ";
                cin >> numProduce;
                producer(numProduce);
                break;
            case 'C':
            case 'c':
                cout << "Enter the number of items to consume: ";
                cin >> numConsume;
                consumer(numConsume);
                break;
            case 'E':
            case 'e':
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 'E' && choice != 'e');

    return 0;
}