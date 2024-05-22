#include <iostream>
#include <ctime>
using namespace std;

int main() {
    int nFrame, nReference;
    srand(time(NULL));
    
    cout << "Enter number of frames: ";
    cin >> nFrame;
    
    int freeFrame[nFrame];
    for(int i = 0; i < nFrame; i++) {
        freeFrame[i] = -1; // Initialize the frames to an invalid value
    }
    
    cout << "Enter size of reference string: ";
    cin >> nReference;
    int referenceString[nReference];
    cout<<"Refeerence String: ";
    for (int i = 0; i < nReference; i++) {
        referenceString[i] = (rand() % 10) + 1; // Random numbers between 1 and 10
        cout<<referenceString[i]<<" ";
    }
    cout<<endl;
    
    // int referenceString[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    // nReference = sizeof(referenceString) / sizeof(referenceString[0]);
    
    int count = 0;
    int index = 0; // To keep track of the FIFO index
    
    for (int i = 0; i < nReference; i++) {
        bool found = false;
        for (int j = 0; j < nFrame; j++) {
            if (freeFrame[j] == referenceString[i]) {
                found = true;
                break; // Page hit
            }
        }
        if (!found) {
            freeFrame[index] = referenceString[i]; // Replace the oldest page
            index = (index + 1) % nFrame; // Update the index in a circular manner
            count++; // Increment the page fault count
        }
    }
    
    cout << "No. of page faults: " << count << endl;

    return 0;
}
