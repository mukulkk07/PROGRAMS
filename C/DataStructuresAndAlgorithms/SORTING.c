#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Function Prototypes ---
void printArray(int arr[], int n);
void copyArray(int source[], int dest[], int n);
void swap(int* a, int* b);

// Sorting Algorithms
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void shellSort(int arr[], int n);

// Divide & Conquer / Advanced
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);

int main() {
    int *masterArr, *workArr;
    int n, i, choice;

    printf("==========================================\n");
    printf("     MASTER SORTING ALGORITHMS PROGRAM    \n");
    printf("==========================================\n");

    // 1. Input Data Phase
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    masterArr = (int*)malloc(n * sizeof(int));
    workArr = (int*)malloc(n * sizeof(int));

    if (masterArr == NULL || workArr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &masterArr[i]);
    }

    // 2. Menu Loop
    while (1) {
        // Always reset workArr to the original unsorted state before specific operations
        copyArray(masterArr, workArr, n);

        printf("\n------------------------------------------\n");
        printf("Original Set: ");
        printArray(masterArr, n);
        printf("------------------------------------------\n");
        printf("Choose Algorithm to Sort:\n");
        printf("1. Bubble Sort      (O(n^2))\n");
        printf("2. Selection Sort   (O(n^2))\n");
        printf("3. Insertion Sort   (O(n^2))\n");
        printf("4. Shell Sort       (Gap-based Insertion)\n");
        printf("5. Merge Sort       (O(n log n))\n");
        printf("6. Quick Sort       (O(n log n))\n");
        printf("7. Heap Sort        (O(n log n))\n");
        printf("8. Enter New Data\n");
        printf("9. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        if (choice == 9) break;

        if (choice == 8) {
             printf("Enter new number of elements: ");
             scanf("%d", &n);
             masterArr = (int*)realloc(masterArr, n * sizeof(int));
             workArr = (int*)realloc(workArr, n * sizeof(int));
             printf("Enter %d integers:\n", n);
             for (i = 0; i < n; i++) scanf("%d", &masterArr[i]);
             continue;
        }

        printf("\n>> Sorting...\n");
        
        switch (choice) {
            case 1: bubbleSort(workArr, n); break;
            case 2: selectionSort(workArr, n); break;
            case 3: insertionSort(workArr, n); break;
            case 4: shellSort(workArr, n); break;
            case 5: mergeSort(workArr, 0, n - 1); break;
            case 6: quickSort(workArr, 0, n - 1); break;
            case 7: heapSort(workArr, n); break;
            default: printf("Invalid Choice\n"); continue;
        }

        printf(">> Sorted Result: ");
        printArray(workArr, n);
    }

    free(masterArr);
    free(workArr);
    return 0;
}

// --- Helper Functions ---

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("]\n");
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
}

// --- Sorting Implementations ---

// 1. Bubble Sort
// Pushes largest element to the end in every pass
void bubbleSort(int arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) break; // Optimization
    }
}

// 2. Selection Sort
// Selects the smallest element and puts it at the beginning
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

// 3. Insertion Sort
// Picks an element and inserts it into the correctly sorted sequence
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 4. Shell Sort
// Optimization of Insertion Sort using gaps
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 5. Merge Sort
// Divide and Conquer: Recursive splitting and merging
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
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

    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
    free(L); free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 6. Quick Sort
// Divide and Conquer: Partitioning around a pivot
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
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 7. Heap Sort
// Tree-based sort: Builds a max heap and extracts max
void heapify(int arr[], int n, int i) {
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]); // Move current root to end
        heapify(arr, i, 0);     // call max heapify on the reduced heap
    }
}