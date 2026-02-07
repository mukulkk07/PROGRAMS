#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// --- Structure for Max-Min Algorithm ---
struct Pair {
    int min;
    int max;
};

// --- Function Prototypes ---
// Utility
void printArray(int arr[], int n);
void swap(int* a, int* b);
void resetArray(int original[], int work[], int n);

// Algorithms
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

int binarySearchRecursive(int arr[], int left, int right, int key);

struct Pair findMaxMin(int arr[], int low, int high);

long long power(int base, int exp);

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);

int main() {
    int *masterArr, *workArr;
    int n, i, choice, key, base, exp, disks;
    int result;
    struct Pair minMax;

    printf("==========================================\n");
    printf("   MASTER DIVIDE & CONQUER PROGRAM        \n");
    printf("==========================================\n");

    // Initial Array Input
    printf("Enter size of array elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    masterArr = (int*)malloc(n * sizeof(int));
    workArr = (int*)malloc(n * sizeof(int));

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &masterArr[i]);
    }
    resetArray(masterArr, workArr, n);

    while (1) {
        printf("\n------------------------------------------\n");
        printf("Current Array Data: ");
        printArray(workArr, n);
        printf("------------------------------------------\n");
        printf("1. Merge Sort       (Sorting)\n");
        printf("2. Quick Sort       (Sorting)\n");
        printf("3. Binary Search    (Searching - Requires Sort)\n");
        printf("4. Max-Min Algo     (Optimization)\n");
        printf("5. Power Function   (Math: x^n)\n");
        printf("6. Tower of Hanoi   (Logic Puzzle)\n");
        printf("7. Reset Array Data\n");
        printf("8. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        if (choice == 8) break;

        switch (choice) {
            case 1:
                printf(">> Running Merge Sort...\n");
                mergeSort(workArr, 0, n - 1);
                printf("Sorted: ");
                printArray(workArr, n);
                break;

            case 2:
                printf(">> Running Quick Sort...\n");
                quickSort(workArr, 0, n - 1);
                printf("Sorted: ");
                printArray(workArr, n);
                break;

            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                // D&C Binary Search requires sorted data
                // We sort it silently if needed for the demo
                quickSort(workArr, 0, n - 1); 
                result = binarySearchRecursive(workArr, 0, n - 1, key);
                if (result != -1)
                    printf(">> Found %d at index %d (after sorting).\n", key, result);
                else
                    printf(">> Element %d not found.\n", key);
                break;

            case 4:
                // We use the master (unsorted) array to prove it works on any data
                minMax = findMaxMin(masterArr, 0, n - 1);
                printf(">> Minimum element is %d\n", minMax.min);
                printf(">> Maximum element is %d\n", minMax.max);
                break;

            case 5:
                printf("Enter Base (x): ");
                scanf("%d", &base);
                printf("Enter Exponent (n): ");
                scanf("%d", &exp);
                printf(">> %d^%d = %lld\n", base, exp, power(base, exp));
                break;

            case 6:
                printf("Enter number of disks: ");
                scanf("%d", &disks);
                printf(">> Sequence of moves:\n");
                towerOfHanoi(disks, 'A', 'C', 'B'); // A=Start, C=End, B=Aux
                break;

            case 7:
                resetArray(masterArr, workArr, n);
                printf(">> Array reset to original input.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }
    }

    free(masterArr);
    free(workArr);
    return 0;
}

// --- Helper Functions ---
void printArray(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("]\n");
}

void resetArray(int original[], int work[], int n) {
    for (int i = 0; i < n; i++) work[i] = original[i];
}

void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

// ==========================================
// 1. MERGE SORT (Divide & Conquer Sorting)
// ==========================================
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Divide
        mergeSort(arr, left, mid);           // Conquer Left
        mergeSort(arr, mid + 1, right);      // Conquer Right
        merge(arr, left, mid, right);        // Combine
    }
}

// ==========================================
// 2. QUICK SORT (Divide & Conquer Sorting)
// ==========================================
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Divide (Partitioning)
        quickSort(arr, low, pi - 1);        // Conquer Left
        quickSort(arr, pi + 1, high);       // Conquer Right
    }
}

// ==========================================
// 3. BINARY SEARCH (Recursive D&C)
// ==========================================
int binarySearchRecursive(int arr[], int left, int right, int key) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) return mid;
        
        // Divide: Check left or right subarray
        if (arr[mid] > key)
            return binarySearchRecursive(arr, left, mid - 1, key);
        
        return binarySearchRecursive(arr, mid + 1, right, key);
    }
    return -1;
}

// ==========================================
// 4. MAX-MIN ALGORITHM (Optimization)
// ==========================================
// Finds min and max in T(n) = 3n/2 - 2 comparisons
struct Pair findMaxMin(int arr[], int low, int high) {
    struct Pair minmax, mml, mmr;
    int mid;

    // Case 1: Only one element
    if (low == high) {
        minmax.max = arr[low];
        minmax.min = arr[low];
        return minmax;
    }

    // Case 2: Two elements
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            minmax.max = arr[low];
            minmax.min = arr[high];
        } else {
            minmax.max = arr[high];
            minmax.min = arr[low];
        }
        return minmax;
    }

    // Case 3: More than two elements - DIVIDE
    mid = (low + high) / 2;
    mml = findMaxMin(arr, low, mid);      // Conquer Left
    mmr = findMaxMin(arr, mid + 1, high); // Conquer Right

    // COMBINE
    if (mml.min < mmr.min) minmax.min = mml.min;
    else minmax.min = mmr.min;

    if (mml.max > mmr.max) minmax.max = mml.max;
    else minmax.max = mmr.max;

    return minmax;
}

// ==========================================
// 5. POWER FUNCTION (Binary Exponentiation)
// ==========================================
// Calculates x^n in O(log n) time
long long power(int base, int exp) {
    if (exp == 0) return 1;
    
    // Divide: Calculate power(base, exp/2)
    long long temp = power(base, exp / 2);
    
    // Combine
    if (exp % 2 == 0)
        return temp * temp;
    else
        return base * temp * temp;
}

// ==========================================
// 6. TOWER OF HANOI
// ==========================================
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        printf(" Move disk 1 from rod %c to rod %c\n", from_rod, to_rod);
        return;
    }
    // Move n-1 disks from A to B
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    
    // Move nth disk from A to C
    printf(" Move disk %d from rod %c to rod %c\n", n, from_rod, to_rod);
    
    // Move n-1 disks from B to C
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}