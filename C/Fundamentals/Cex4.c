#include <stdio.h>

/* Global variable to maintain balance for simplicity in this example */
float currentBalance = 0.0f;

/* --- 1. Function Prototypes --- */
/* All functions must share the same signature (return type and parameters) 
   to be stored in the same function pointer array. */
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    /* --- 2. Declare Array of Function Pointers --- */
    /* syntax: return_type (*array_name[])() 
       This array 'operations' holds addresses of functions that return void.
       Index 0 -> deposit, Index 1 -> withdraw, Index 2 -> balanceEnquiry
    */
    void (*operations[])() = {deposit, withdraw, balanceEnquiry};

    int choice;

    printf("=== Welcome to C-Bank ===\n");

    while (1) {
        printf("\nSelect Operation:\n");
        printf("0. Deposit\n");
        printf("1. Withdraw\n");
        printf("2. Balance Enquiry\n");
        printf("3. Exit\n");
        printf("Enter your choice (0-3): ");
        scanf("%d", &choice);

        // --- 3. Invoke Function via Pointer ---
        if (choice >= 0 && choice <= 2) {
            /* This single line replaces a switch-case.
               It jumps directly to the function at index 'choice'. */
            (*operations[choice])();
        } 
        else if (choice == 3) {
            printf("Exiting... Thank you for banking with us.\n");
            break;
        } 
        else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/* --- 4. Function Definitions --- */

void deposit() {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    
    if (amount > 0) {
        currentBalance += amount;
        printf("Success! Deposited $%.2f\n", amount);
    } else {
        printf("Error: Amount must be positive.\n");
    }
}

void withdraw() {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= currentBalance) {
        currentBalance -= amount;
        printf("Success! Withdrawn $%.2f\n", amount);
    } else if (amount > currentBalance) {
        printf("Error: Insufficient funds!\n");
    } else {
        printf("Error: Invalid amount.\n");
    }
}

void balanceEnquiry() {
    printf("--- Account Summary ---\n");
    printf("Current Balance: $%.2f\n", currentBalance);
}