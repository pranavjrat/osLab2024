#include <iostream>

using namespace std;

void insertionSort(int arr[], int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int p, int q, int r) {
    while (p != q + 1) {
        if (arr[p] > arr[q + 1]) {
            swap(arr[p], arr[q + 1]);
            if (arr[q + 1] > arr[q + 2]) {
                int temp = p;
                insertionSort(arr, q + 1, r);
                p = temp;
            }
        }
        p++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    cout << "Given array is \n";
    for (int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << endl;

    mergeSort(arr, 0, arrSize - 1);

    cout << "Sorted array is \n";
    for (int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
