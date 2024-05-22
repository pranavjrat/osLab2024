#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// Function to find the index of the page that will not be used for the longest period of time
int findOptimalReplacementIndex(vector<int>& freeFrame, vector<int>& referenceString, int currentIndex) {
    int farthest = currentIndex;
    int index = -1;

    for (int i = 0; i < freeFrame.size(); i++) {
        int j;
        for (j = currentIndex; j < referenceString.size(); j++) {
            if (freeFrame[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        // If the page is not found in the future, return this index
        if (j == referenceString.size()) {
            return i;
        }
    }

    // If all frames will be used again, replace the farthest one
    return (index == -1) ? 0 : index;
}

int main() {
    int nFrame, nReference;
    srand(time(NULL));
    
    cout << "Enter number of frames: ";
    cin >> nFrame;
    
    vector<int> freeFrame(nFrame, -1); // Initialize the frames to an invalid value
    
    // Predefined reference string
    vector<int> referenceString = {3, 2, 1, 3, 4, 1, 6, 2, 4, 3, 4, 2, 1};
    nReference = referenceString.size();
    
    int count = 0; // Counter for page faults
    
    // Process each page in the reference string
    for (int i = 0; i < nReference; i++) {
        bool found = false;
        
        // Check if the page is already in one of the frames (page hit)
        for (int j = 0; j < nFrame; j++) {
            if (freeFrame[j] == referenceString[i]) {
                found = true;
                break;
            }
        }
        
        // If the page is not found in the frames (page fault)
        if (!found) {
            if (count < nFrame) {
                // If there's an empty frame, use it
                freeFrame[count] = referenceString[i];
            } else {
                // Find the frame to replace using the optimal algorithm
                int replaceIndex = findOptimalReplacementIndex(freeFrame, referenceString, i + 1);
                freeFrame[replaceIndex] = referenceString[i];
            }
            count++; // Increment the page fault count
        }
    }
    
    // Display the total number of page faults
    cout << "No. of page faults: " << count << endl;

    return 0;
}
