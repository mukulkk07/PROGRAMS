#include <stdio.h>

/* 1. Recursive Function Declaration */
/* This function calls itself to calculate n * (n-1) * (n-2)... * 1 */
unsigned long long factorial(int n);

int main() {
    int number;
    unsigned long long result;

    printf("--- Lottery Permutation Calculator Module ---\n");
    printf("Enter a positive integer to find its factorial: ");
    scanf("%d", &number);

    // Error handling for negative numbers
    if (number < 0) {
        printf("Error: Factorial of a negative number doesn't exist.\n");
    } else {
        // 2. Call the recursive function
        result = factorial(number);
        
        printf("\nFactorial of %d is: %llu\n", number, result);
        printf("(This value can now be used for nPr or nCr calculations)\n");
    }

    return 0;
}

/* 3. Recursive Function Definition */
unsigned long long factorial(int n) {
    // Base Case: Factorial of 0 or 1 is 1. 
    // This stops the recursion loops.
    if (n == 0 || n == 1) {
        return 1;
    } 
    // Recursive Case: n! = n * (n-1)!
    else {
        return n * factorial(n - 1);
    }
}