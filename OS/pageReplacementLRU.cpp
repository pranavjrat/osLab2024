#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int nFrame, nReference;
    
    cout << "Enter number of frames: ";
    cin >> nFrame;
    
    vector<int> freeFrame(nFrame, -1); // Initialize the frames to an invalid value
    
    // Predefined reference string
    vector<int> referenceString = {3, 2, 1, 3, 1, 6, 2};
    nReference = referenceString.size();
    
    int count = 0; // Counter for page faults
    unordered_map<int, int> lruTracker; // To track the usage of pages

    for (int i = 0; i < nReference; i++) {
        bool found = false;
        
        // Check if the page is already in one of the frames (page hit)
        for (int j = 0; j < nFrame; j++) {
            if (freeFrame[j] == referenceString[i]) {
                found = true;
                lruTracker[referenceString[i]] = i; // Update the most recent usage time
                break;
            }
        }
        
        // If the page is not found in the frames (page fault)
        if (!found) {
            if (count < nFrame) {
                // If there's an empty frame, use it
                freeFrame[count] = referenceString[i];
                lruTracker[referenceString[i]] = i;
            } else {
                // Find the least recently used page
                int lruIndex = 0;
                for (int j = 1; j < nFrame; j++) {
                    if (lruTracker[freeFrame[j]] < lruTracker[freeFrame[lruIndex]]) {
                        lruIndex = j;
                    }
                }
                // Replace the LRU page with the new page
                lruTracker.erase(freeFrame[lruIndex]); // Remove the old page from the tracker
                freeFrame[lruIndex] = referenceString[i];
                lruTracker[referenceString[i]] = i; // Update the tracker with the new page
            }
            count++; // Increment the page fault count
        }
    }
    
    // Display the total number of page faults
    cout << "No. of page faults: " << count << endl;

    return 0;
}
