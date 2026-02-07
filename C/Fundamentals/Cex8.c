#include <stdio.h>

/* 1. Function Prototypes */

// Call by Value: Receives a COPY of the balance
void previewTransaction(float balanceCopy, float amount);

// Call by Reference: Receives the ADDRESS of the balance
void performTransaction(float *balancePtr, float amount);

int main() {
    float mainBalance = 5000.00; // Initial actual balance
    float amount;
    int choice;

    printf("=== ATM System: Value vs Reference ===\n");

    while (1) {
        printf("\nCurrent Account Balance: $%.2f\n", mainBalance);
        printf("1. Preview Withdrawal (Simulation - Safe Mode)\n");
        printf("2. Actual Withdrawal (Update Balance)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        printf("Enter amount: ");
        scanf("%f", &amount);

        switch (choice) {
            case 1:
                // PASS BY VALUE: We pass 'mainBalance' directly.
                // The function gets a copy; 'mainBalance' inside main() is NOT changed.
                previewTransaction(mainBalance, amount);
                
                // Proof that balance didn't change
                printf("\n[Main]: Back in main menu. Balance is still $%.2f\n", mainBalance);
                break;

            case 2:
                // PASS BY REFERENCE: We pass the address '&mainBalance'.
                // The function can now modify the variable directly.
                performTransaction(&mainBalance, amount);
                
                // Proof that balance changed
                printf("\n[Main]: Back in main menu. Balance is updated to $%.2f\n", mainBalance);
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

/* --- Function Definitions --- */

/* Call by Value Implementation 
   Useful for: Simulations, calculations that shouldn't alter original data
*/
void previewTransaction(float balanceCopy, float amount) {
    printf("\n--- PREVIEW MODE ---\n");
    if (amount > balanceCopy) {
        printf("Simulation Result: Insufficient funds.\n");
    } else {
        balanceCopy = balanceCopy - amount;
        printf("If you withdraw $%.2f, your balance WILL become $%.2f\n", amount, balanceCopy);
        printf("(Note: No actual money was deducted yet.)\n");
    }
}

/* Call by Reference Implementation 
   Useful for: Actual updates, modifying state
*/
void performTransaction(float *balancePtr, float amount) {
    printf("\n--- TRANSACTION MODE ---\n");
    // We use the dereference operator (*) to access the value at the address
    if (amount > *balancePtr) {
        printf("Transaction Failed: Insufficient funds.\n");
    } else {
        *balancePtr = *balancePtr - amount; // This modifies 'mainBalance' in main()
        printf("Success! Please take your cash.\n");
        printf("New Balance inside function: $%.2f\n", *balancePtr);
    }
}