#include <iomanip>
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

void printMemoryAllocation(int blockSize[], int processSize[], int blockAllocated[], int p) {
    cout << "\nProcess No.\tProcess Size\tBlock no.\tExternal Fragmentation\n";
    for (int i = 0; i < p; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (blockAllocated[i] != -1)
            cout << blockAllocated[i] + 1 << "\t";
        else {
            cout << "Not Allocated";
        }
        cout << "\t" << blockSize[i] << "\n";
    }
}

void firstFit(int blockSize[], int processSize[], int p, int b, int blockAllocated[]) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < b; j++) {
            if (blockSize[j] >= processSize[i]) {
                blockAllocated[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
}

void bestFit(int blockSize[], int processSize[], int p, int b, int blockAllocated[]) {
    for (int i = 0; i < p; i++) {
        int indexPlaced = -1;
        for (int j = 0; j < b; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (indexPlaced == -1)
                    indexPlaced = j;
                else if (blockSize[j] < blockSize[indexPlaced])
                    indexPlaced = j;
            }
        }
        blockAllocated[i] = indexPlaced;
        blockSize[indexPlaced] -= processSize[i];
    }
}

void worstFit(int blockSize[], int processSize[], int p, int b, int blockAllocated[]) {
    for (int i = 0; i < p; i++) {
        int indexPlaced = -1;
        for (int j = 0; j < b; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (indexPlaced == -1 || blockSize[j] > blockSize[indexPlaced]) {
                    indexPlaced = j;
                }
            }
        }
            blockAllocated[i] = indexPlaced;
            blockSize[indexPlaced] -= processSize[i];
    }
}

int main() {
    clock_t start, end;

    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426, 10};
    int numBlocks = sizeof(blockSize) / sizeof(blockSize[0]);
    int numProc = sizeof(processSize) / sizeof(processSize[0]);
    int blockAllocated[numProc];
    memset(blockAllocated, -1, sizeof(blockAllocated));

    start = clock();
    firstFit(blockSize, processSize, numProc, numBlocks, blockAllocated);
    end = clock();
    double time_taken_first_fit = double(end - start) / double(CLOCKS_PER_SEC);
    printMemoryAllocation(blockSize, processSize, blockAllocated, numProc);

    int blockSize2[] = {100, 500, 200, 300, 600};

    memcpy(blockSize, blockSize2, sizeof(blockSize));

    start = clock();
    bestFit(blockSize, processSize, numProc, numBlocks, blockAllocated);
    end = clock();
    double time_taken_best_fit = double(end - start) / double(CLOCKS_PER_SEC);
    printMemoryAllocation(blockSize, processSize, blockAllocated, numProc);

    memcpy(blockSize, blockSize2, sizeof(blockSize));
    start = clock();
    worstFit(blockSize, processSize, numProc, numBlocks, blockAllocated);
    end = clock();
    double time_taken_worst_fit = double(end - start) / double(CLOCKS_PER_SEC);
    printMemoryAllocation(blockSize, processSize, blockAllocated, numProc);

    cout << "First Fit took " << fixed << time_taken_first_fit << setprecision(6) << " seconds to execute." << endl;
    cout << "Best Fit took  " << fixed << time_taken_best_fit << setprecision(6) << " seconds to execute." << endl;
    cout << "Worst Fit took " << fixed << time_taken_worst_fit << setprecision(6) << " seconds to execute." << endl;

    return 0;
}
