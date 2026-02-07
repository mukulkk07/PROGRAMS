#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* * ----------------------------------------------------------------------
 * MASTER RANDOMIZED ALGORITHM SUITE
 * ----------------------------------------------------------------------
 * 1. Randomized Quicksort (Las Vegas - Sorting)
 * 2. Randomized Selection/Quickselect (Las Vegas - Searching)
 * 3. Monte Carlo Pi Estimation (Monte Carlo - Numerical)
 * 4. Fermat Primality Test (Monte Carlo - One-sided Error)
 * ----------------------------------------------------------------------
 */

/* --- Utility Functions --- */

/* Generates a random integer between min and max (inclusive) */
int randomRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

/* Swaps two integers */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Modular Exponentiation for Primality Test: (base^exp) % mod */
unsigned long long power(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return res;
}

/* ----------------------------------------------------------------------
 * 1. RANDOMIZED QUICKSORT (Las Vegas)
 * ----------------------------------------------------------------------
 * Uses a random pivot to avoid worst-case O(N^2) time on sorted arrays.
 * Expected Time Complexity: O(N log N)
 */

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1);
    int j;
    
    for (j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int partition_r(int arr[], int low, int high) {
    /* Pick a random number between low and high */
    int random = randomRange(low, high);
    
    /* Swap A[random] with A[high] */
    swap(&arr[random], &arr[high]);
    
    return partition(arr, low, high);
}

void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_r(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

/* ----------------------------------------------------------------------
 * 2. RANDOMIZED SELECTION / QUICKSELECT (Las Vegas)
 * ----------------------------------------------------------------------
 * Finds the k-th smallest element in an unordered list.
 * Expected Time Complexity: O(N)
 */

int randomizedSelect(int arr[], int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        /* Partition the array around a random pivot */
        int index = partition_r(arr, low, high);

        /* If pivot is at the k-th position */
        if (index - low == k - 1)
            return arr[index];

        /* If pivot is greater, recurse left */
        if (index - low > k - 1)
            return randomizedSelect(arr, low, index - 1, k);

        /* Else recurse right */
        return randomizedSelect(arr, index + 1, high, k - index + low - 1);
    }
    return -1; // Error code
}

/* ----------------------------------------------------------------------
 * 3. MONTE CARLO PI ESTIMATION (Monte Carlo)
 * ----------------------------------------------------------------------
 * Uses random sampling to estimate the value of Pi.
 * Relies on the ratio of points falling inside a unit circle vs a square.
 */

void estimatePi() {
    long long interval, i;
    double rand_x, rand_y, origin_dist, pi;
    long long circle_points = 0;
    long long square_points = 0;

    printf("Enter number of iterations (e.g., 100000): ");
    if (scanf("%lld", &interval) != 1) return;

    /* Initialize square points to total intervals */
    square_points = interval;

    for (i = 0; i < interval; i++) {
        /* Generate random x and y between 0 and 1 */
        rand_x = (double)rand() / RAND_MAX;
        rand_y = (double)rand() / RAND_MAX;

        /* Check if point lies inside the circle: x^2 + y^2 <= 1 */
        origin_dist = rand_x * rand_x + rand_y * rand_y;

        if (origin_dist <= 1)
            circle_points++;
    }

    /* Pi = 4 * (Points inside Circle / Total Points) */
    pi = (double)(4 * circle_points) / square_points;

    printf("\nEstimated Pi after %lld iterations: %lf", interval, pi);
    printf("\nActual Pi: 3.141592...\n");
}

/* ----------------------------------------------------------------------
 * 4. FERMAT PRIMALITY TEST (Monte Carlo - One-sided Error)
 * ----------------------------------------------------------------------
 * Probabilistic test to determine if a number is prime.
 * If output is "Composite", it is definitely composite.
 * If output is "Prime", it is likely prime (false positives exist: Carmichael numbers).
 * Complexity: O(k * log n) where k is number of iterations.
 */

void fermatPrimalityTest() {
    unsigned long long n;
    int k, i;
    
    printf("Enter number to test for primality: ");
    if (scanf("%llu", &n) != 1) return;
    
    printf("Enter number of iterations (higher = more accurate, e.g., 5): ");
    if (scanf("%d", &k) != 1) return;

    /* Corner cases */
    if (n <= 1 || n == 4) {
        printf("%llu is Composite.\n", n);
        return;
    }
    if (n <= 3) {
        printf("%llu is Prime.\n", n);
        return;
    }

    /* Run the test k times */
    for (i = 0; i < k; i++) {
        /* Pick a random number 'a' in range [2, n-2] */
        unsigned long long a = 2 + rand() % (n - 4);
        
        /* Fermat's Little Theorem: If n is prime, a^(n-1) % n == 1 */
        if (power(a, n - 1, n) != 1) {
            printf("%llu is Composite.\n", n);
            return;
        }
    }
    
    printf("%llu is PROBABLY Prime (Passed %d iterations).\n", n, k);
}

/* ----------------------------------------------------------------------
 * MAIN DRIVER
 * ----------------------------------------------------------------------
 */

int main() {
    int choice, n, i, k, result;
    int *arr;

    /* Seed the random number generator once */
    srand(time(0));

    while (1) {
        printf("\n============================================\n");
        printf("   MASTER RANDOMIZED ALGORITHM SUITE\n");
        printf("============================================\n");
        printf("1. Randomized Quicksort (Sorting)\n");
        printf("2. Randomized Selection (Find Kth Smallest)\n");
        printf("3. Estimate Pi (Monte Carlo Simulation)\n");
        printf("4. Fermat Primality Test (Number Theory)\n");
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
        case 1:
            printf("Enter number of elements: ");
            if (scanf("%d", &n) == 1 && n > 0) {
                arr = (int*)malloc(n * sizeof(int));
                printf("Enter %d elements:\n", n);
                for (i = 0; i < n; i++) scanf("%d", &arr[i]);
                
                randomizedQuickSort(arr, 0, n - 1);
                
                printf("Sorted Array: ");
                for (i = 0; i < n; i++) printf("%d ", arr[i]);
                printf("\n");
                free(arr);
            }
            break;

        case 2:
            printf("Enter number of elements: ");
            if (scanf("%d", &n) == 1 && n > 0) {
                arr = (int*)malloc(n * sizeof(int));
                printf("Enter %d elements:\n", n);
                for (i = 0; i < n; i++) scanf("%d", &arr[i]);
                
                printf("Enter k (1 to %d): ", n);
                if (scanf("%d", &k) == 1 && k > 0 && k <= n) {
                    /* Create a copy because selection modifies the array order */
                    int *tempArr = (int*)malloc(n * sizeof(int));
                    for(i=0; i<n; i++) tempArr[i] = arr[i];

                    result = randomizedSelect(tempArr, 0, n - 1, k);
                    printf("The %d-th smallest element is: %d\n", k, result);
                    
                    free(tempArr);
                } else {
                    printf("Invalid k!\n");
                }
                free(arr);
            }
            break;

        case 3:
            estimatePi();
            break;

        case 4:
            fermatPrimalityTest();
            break;

        default:
            printf("Invalid Option.\n");
        }
    }
    return 0;
}