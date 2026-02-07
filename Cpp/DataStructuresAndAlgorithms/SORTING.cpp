#include <iostream>
#include <vector>
using namespace std;

// ==========================================
// 1. UTILITY FUNCTIONS
// ==========================================

// Helper to swap two integers using Pointers
// We use pointers to manipulate the memory addresses directly.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper to print the array state
void printArray(int arr[], int size) {
    cout << "[ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

// Helper to copy an array (so we can reuse the unsorted data for each test)
void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// ==========================================
// 2. ITERATIVE SORTS (Simple, O(n^2))
// ==========================================

// --- BUBBLE SORT ---
// Logic: Repeatedly swap adjacent elements if they are in the wrong order.
// The largest element "bubbles" to the end in every pass.
void bubbleSort(int arr[], int n) {
    cout << "\n--- Running Bubble Sort ---" << endl;
    for (int i = 0; i < n - 1; i++) {
        // Optimization: Keep track if we swapped anything.
        // If we go through a whole loop with NO swaps, list is sorted.
        bool swapped = false;

        // Inner loop goes up to n-i-1 because the last i elements are already sorted.
        for (int j = 0; j < n - i - 1; j++) {
            
            // Pointer Logic: arr[j] is same as *(arr + j)
            if (arr[j] > arr[j + 1]) {
                // Swap neighbors
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        
        // Visualizing the pass
        cout << "Pass " << i + 1 << ": ";
        printArray(arr, n);

        if (!swapped) break; // Stop early if sorted
    }
}

// --- SELECTION SORT ---
// Logic: Find the minimum element in the unsorted part and put it at the beginning.
// This minimizes the number of swaps compared to Bubble Sort.
void selectionSort(int arr[], int n) {
    cout << "\n--- Running Selection Sort ---" << endl;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i; // Assume the first unsorted element is the minimum

        // Scan the rest of the array to find the true minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j; // Update index of new minimum
            }
        }

        // Swap the found minimum with the first element
        if (min_idx != i) {
            swap(&arr[min_idx], &arr[i]);
        }
        
        cout << "Moved " << arr[i] << " to pos " << i << ": ";
        printArray(arr, n);
    }
}

// --- INSERTION SORT ---
// Logic: Like sorting cards in your hand. Pick the next card and slide it 
// backwards into its correct sorted position.
void insertionSort(int arr[], int n) {
    cout << "\n--- Running Insertion Sort ---" << endl;
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // The card we are currently holding
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift right
            j = j - 1;
        }
        arr[j + 1] = key; // Place the key in the hole we made
        
        cout << "Inserted " << key << ": ";
        printArray(arr, n);
    }
}

// ==========================================
// 3. DIVIDE AND CONQUER SORTS (Fast, O(n log n))
// ==========================================

// --- MERGE SORT ---
// Logic: Recursively split the array in half until size 1.
// Then, "merge" the sorted halves back together.

// Helper function to merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    // Create temp arrays (on Heap)
    vector<int> L(n1), R(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements if any
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return; // Base case: Size 0 or 1

    int mid = left + (right - left) / 2;

    // Recursively sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
}

// --- QUICK SORT ---
// Logic: Pick a "Pivot". Reorder array so everything smaller than pivot is left,
// everything larger is right. Then recursively sort the two sides.

// Partition function using the last element as pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // Increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    // Place pivot in the correct position (i + 1)
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ==========================================
// 4. MAIN EXECUTION
// ==========================================
int main() {
    // The "Master" unsorted array
    const int SIZE = 6;
    int original[SIZE] = {64, 34, 25, 12, 22, 11};
    int workArr[SIZE]; // Buffer for sorting

    cout << "Original Array: ";
    printArray(original, SIZE);

    // 1. Bubble Sort
    copyArray(original, workArr, SIZE);
    bubbleSort(workArr, SIZE);

    // 2. Selection Sort
    copyArray(original, workArr, SIZE);
    selectionSort(workArr, SIZE);

    // 3. Insertion Sort
    copyArray(original, workArr, SIZE);
    insertionSort(workArr, SIZE);

    // 4. Merge Sort
    cout << "\n--- Running Merge Sort ---" << endl;
    copyArray(original, workArr, SIZE);
    mergeSort(workArr, 0, SIZE - 1);
    printArray(workArr, SIZE);

    // 5. Quick Sort
    cout << "\n--- Running Quick Sort ---" << endl;
    copyArray(original, workArr, SIZE);
    quickSort(workArr, 0, SIZE - 1);
    printArray(workArr, SIZE);

    return 0;
}