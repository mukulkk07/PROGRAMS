#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* * MASTER BIT MANIPULATION SUITE
 * ----------------------------------------------------------------------
 * 1. Basic Operations (Get, Set, Clear, Toggle)
 * 2. Checks (Odd/Even, Power of 2, K-th Bit Set)
 * 3. Manipulations (Swap, Clear Last Bit, Reverse Bits)
 * 4. Advanced Algorithms (Count Set Bits, Find Unique, Power Set)
 * ----------------------------------------------------------------------
 */

/* --- Utility Functions --- */

/* Prints the binary representation of an integer (32-bit) */
void printBinary(int n) {
    int i;
    printf("Binary of %d: ", n);
    for (i = 31; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            printf("1");
        else
            printf("0");
        
        if (i % 8 == 0) printf(" "); // Space separator for readability
    }
    printf("\n");
}

/* ----------------------------------------------------------------------
 * 1. BASIC BIT OPERATIONS
 * ----------------------------------------------------------------------
 */

void getKthBit(int n, int k) {
    /* Right shift n by k and check last bit using AND 1 */
    int bit = (n >> k) & 1;
    printf("The %d-th bit is: %d\n", k, bit);
}

void setKthBit(int n, int k) {
    /* OR with 1 shifted left by k */
    int res = n | (1 << k);
    printf("Original: %d, After Setting %d-th bit: %d\n", n, k, res);
    printBinary(res);
}

void clearKthBit(int n, int k) {
    /* AND with NOT of (1 shifted left by k) */
    int res = n & ~(1 << k);
    printf("Original: %d, After Clearing %d-th bit: %d\n", n, k, res);
    printBinary(res);
}

void toggleKthBit(int n, int k) {
    /* XOR with 1 shifted left by k */
    int res = n ^ (1 << k);
    printf("Original: %d, After Toggling %d-th bit: %d\n", n, k, res);
    printBinary(res);
}

/* ----------------------------------------------------------------------
 * 2. CHECKS & PROPERTIES
 * ----------------------------------------------------------------------
 */

void checkEvenOdd(int n) {
    /* If last bit is 1, it's Odd. If 0, it's Even. */
    if (n & 1)
        printf("%d is Odd\n", n);
    else
        printf("%d is Even\n", n);
}

void checkPowerOfTwo(int n) {
    /* * Powers of 2 have exactly one bit set.
     * n & (n-1) removes the rightmost set bit.
     * If result is 0, it was a power of 2.
     */
    if (n > 0 && (n & (n - 1)) == 0)
        printf("%d is a Power of Two\n", n);
    else
        printf("%d is NOT a Power of Two\n", n);
}

/* ----------------------------------------------------------------------
 * 3. BIT TRICKS & MANIPULATIONS
 * ----------------------------------------------------------------------
 */

void swapNumbers(int a, int b) {
    printf("Before Swap: a = %d, b = %d\n", a, b);
    /* XOR Swap Algorithm */
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("After Swap:  a = %d, b = %d\n", a, b);
}

void clearRightmostSetBit(int n) {
    /* Useful for Fenwick Trees (Binary Indexed Trees) */
    int res = n & (n - 1);
    printf("Original: %d\n", n);
    printBinary(n);
    printf("Result after clearing rightmost set bit: %d\n", res);
    printBinary(res);
}

void countSetBits(int n) {
    /* Brian Kernighan’s Algorithm: O(number of set bits) */
    int count = 0;
    int temp = n;
    while (n > 0) {
        n = n & (n - 1); // Removes the rightmost set bit
        count++;
    }
    printf("Number of set bits (1s) in %d is: %d\n", temp, count);
}

/* ----------------------------------------------------------------------
 * 4. ADVANCED ALGORITHMS
 * ----------------------------------------------------------------------
 */

/* Finds the only number that appears once in an array where all others appear twice */
void findUniqueNumber() {
    int n, i, res = 0;
    int *arr;
    
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) return;
    
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) { printf("Memory Error\n"); return; }
    
    printf("Enter elements (Example: 2 3 5 2 3): ");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        res = res ^ arr[i]; /* XOR implies: A^A = 0, A^0 = A */
    }
    
    printf("The unique number is: %d\n", res);
    free(arr);
}

/* Generates all subsets of a set (Power Set) */
void generatePowerSet() {
    int n, i, j;
    char *arr;
    
    printf("Enter number of characters for set: ");
    if (scanf("%d", &n) != 1) return;
    
    arr = (char*)malloc(n * sizeof(char));
    printf("Enter %d characters (e.g., a b c): ", n);
    for(i = 0; i < n; i++) {
        scanf(" %c", &arr[i]); // Space before %c consumes whitespace
    }
    
    printf("\n--- Power Set ---\n");
    /* Total subsets = 2^n */
    int limit = 1 << n; 
    
    for (i = 0; i < limit; i++) {
        printf("{ ");
        for (j = 0; j < n; j++) {
            /* Check if j-th bit is set in counter i */
            if (i & (1 << j)) {
                printf("%c ", arr[j]);
            }
        }
        printf("}\n");
    }
    free(arr);
}

/* ----------------------------------------------------------------------
 * MAIN DRIVER
 * ----------------------------------------------------------------------
 */

int main() {
    int choice, n, k, a, b;

    while (1) {
        printf("\n============================================\n");
        printf("   MASTER BIT MANIPULATION SUITE\n");
        printf("============================================\n");
        printf(" 1. Get K-th Bit\n");
        printf(" 2. Set K-th Bit\n");
        printf(" 3. Clear K-th Bit\n");
        printf(" 4. Toggle K-th Bit\n");
        printf(" 5. Check Even/Odd\n");
        printf(" 6. Check Power of Two\n");
        printf(" 7. Count Set Bits (Kernighan's Algo)\n");
        printf(" 8. Swap Two Numbers (No Temp Var)\n");
        printf(" 9. Clear Rightmost Set Bit\n");
        printf("10. Find Unique Element (XOR Trick)\n");
        printf("11. Generate Power Set (Subsets)\n");
        printf(" 0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear buffer
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
        case 1: // Get
            printf("Enter Number and Bit Position (0-31): ");
            scanf("%d %d", &n, &k);
            printBinary(n);
            getKthBit(n, k);
            break;
        case 2: // Set
            printf("Enter Number and Bit Position (0-31): ");
            scanf("%d %d", &n, &k);
            printBinary(n);
            setKthBit(n, k);
            break;
        case 3: // Clear
            printf("Enter Number and Bit Position (0-31): ");
            scanf("%d %d", &n, &k);
            printBinary(n);
            clearKthBit(n, k);
            break;
        case 4: // Toggle
            printf("Enter Number and Bit Position (0-31): ");
            scanf("%d %d", &n, &k);
            printBinary(n);
            toggleKthBit(n, k);
            break;
        case 5: // Even/Odd
            printf("Enter Number: ");
            scanf("%d", &n);
            checkEvenOdd(n);
            break;
        case 6: // Power of 2
            printf("Enter Number: ");
            scanf("%d", &n);
            checkPowerOfTwo(n);
            break;
        case 7: // Count Bits
            printf("Enter Number: ");
            scanf("%d", &n);
            printBinary(n);
            countSetBits(n);
            break;
        case 8: // Swap
            printf("Enter two numbers: ");
            scanf("%d %d", &a, &b);
            swapNumbers(a, b);
            break;
        case 9: // Clear Rightmost
            printf("Enter Number: ");
            scanf("%d", &n);
            clearRightmostSetBit(n);
            break;
        case 10: // Unique Element
            findUniqueNumber();
            break;
        case 11: // Power Set
            generatePowerSet();
            break;
        default:
            printf("Invalid Option.\n");
        }
    }
    return 0;
}