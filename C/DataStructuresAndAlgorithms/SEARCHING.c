#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

// --- Function Prototypes ---
void displayArray(int arr[], int n);
void bubbleSort(int arr[], int n);
int linearSearch(int arr[], int n, int key);
int sentinelSearch(int arr[], int n, int key);
int binarySearch(int arr[], int left, int right, int key);
int jumpSearch(int arr[], int n, int key);
int interpolationSearch(int arr[], int n, int key);
int exponentialSearch(int arr[], int n, int key);

int main() {
    int *arr;
    int n, i, choice, key, result;
    bool isSorted = false;

    printf("==========================================\n");
    printf("   MASTER SEARCHING ALGORITHMS PROGRAM    \n");
    printf("==========================================\n");

    // Input Array
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    while (1) {
        printf("\n------------------------------------------\n");
        printf("Current Data: ");
        displayArray(arr, n);
        printf("------------------------------------------\n");
        printf("1. Linear Search\n");
        printf("2. Sentinel Search\n");
        printf("3. Binary Search (Requires Sorting)\n");
        printf("4. Jump Search (Requires Sorting)\n");
        printf("5. Interpolation Search (Requires Sorting)\n");
        printf("6. Exponential Search (Requires Sorting)\n");
        printf("7. Sort Array Manually\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 8) break;
        if (choice == 7) {
            bubbleSort(arr, n);
            isSorted = true;
            printf("Array sorted successfully.\n");
            continue;
        }

        printf("Enter element to search: ");
        scanf("%d", &key);

        // Auto-sort check for algorithms needing sorted data
        if (choice >= 3 && choice <= 6 && !isSorted) {
            printf("[NOTE] This algorithm requires sorted data. Sorting array now...\n");
            bubbleSort(arr, n);
            isSorted = true;
            displayArray(arr, n);
        }

        result = -1;
        switch (choice) {
            case 1:
                result = linearSearch(arr, n, key);
                break;
            case 2:
                result = sentinelSearch(arr, n, key);
                break;
            case 3:
                result = binarySearch(arr, 0, n - 1, key);
                break;
            case 4:
                result = jumpSearch(arr, n, key);
                break;
            case 5:
                result = interpolationSearch(arr, n, key);
                break;
            case 6:
                result = exponentialSearch(arr, n, key);
                break;
            default:
                printf("Invalid Choice!\n");
                continue;
        }

        if (result != -1)
            printf("\n>> Element %d found at Index: %d\n", key, result);
        else
            printf("\n>> Element %d NOT found in the array.\n", key);
    }

    free(arr);
    return 0;
}

// --- Helper Functions ---

// Utility to print array
void displayArray(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// Simple Bubble Sort to prepare data for advanced searches
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// --- Search Implementations ---

// 1. Linear Search: O(n)
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// 2. Sentinel Search: O(n) - slight optimization of Linear
int sentinelSearch(int arr[], int n, int key) {
    int last = arr[n - 1];
    arr[n - 1] = key; // Place sentinel
    int i = 0;

    while (arr[i] != key)
        i++;

    arr[n - 1] = last; // Restore original last element

    if ((i < n - 1) || (arr[n - 1] == key))
        return i;
    
    return -1;
}

// 3. Binary Search: O(log n)
int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// 4. Jump Search: O(sqrt(n))
int jumpSearch(int arr[], int n, int key) {
    int step = sqrt(n);
    int prev = 0;

    // Finding the block where element is present
    while (arr[MIN(step, n) - 1] < key) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    // Linear search within the block
    while (arr[prev] < key) {
        prev++;
        if (prev == MIN(step, n))
            return -1;
    }

    if (arr[prev] == key)
        return prev;

    return -1;
}

// 5. Interpolation Search: O(log(log n)) on average (uniform data)
int interpolationSearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }

        // Probing position formula
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low]));

        if (arr[pos] == key)
            return pos;

        if (arr[pos] < key)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

// 6. Exponential Search: O(log n)
// Finds range where element is present, then performs Binary Search
int exponentialSearch(int arr[], int n, int key) {
    if (arr[0] == key)
        return 0;

    int i = 1;
    while (i < n && arr[i] <= key)
        i = i * 2;

    return binarySearch(arr, i / 2, MIN(i, n - 1), key);
}