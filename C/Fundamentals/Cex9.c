#include <stdio.h>

/* 1. Function Prototypes */
/* Call by Value: Receives copies of the data. Originals are safe. */
void previewSwap(float usd, float eur);

/* Call by Reference: Receives addresses of the data using pointers. Originals are modified. */
void confirmSwap(float *usdPtr, float *eurPtr);

int main() {
    float walletUSD = 100.00;
    float walletEUR = 85.00;
    int choice;

    printf("=== Currency Exchange System ===\n");

    while (1) {
        printf("\n--- Current Wallet ---\n");
        printf("USD: %.2f\n", walletUSD);
        printf("EUR: %.2f\n", walletEUR);

        printf("\nSelect Operation:\n");
        printf("1. Preview Swap (Simulation - Call by Value)\n");
        printf("2. Confirm Swap (Permanent - Call by Reference)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("Exiting system.\n");
            break;
        }

        switch (choice) {
            case 1:
                /* CALL BY VALUE: We pass the variables directly.
                   The function gets a copy. The original variables in main() remain untouched. */
                printf("\n--- SIMULATION MODE ---\n");
                previewSwap(walletUSD, walletEUR);
                
                printf("[Main]: Back in main menu. Wallet is UNCHANGED.\n");
                break;

            case 2:
                /* CALL BY REFERENCE: We pass the addresses using '&'.
                   The function gets pointers to the actual memory locations. */
                printf("\n--- EXECUTION MODE ---\n");
                confirmSwap(&walletUSD, &walletEUR);
                
                printf("[Main]: Back in main menu. Wallet is PERMANENTLY UPDATED.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

/* --- Function Definitions --- */

void previewSwap(float usd, float eur) {
    float temp;
    // Standard swap logic on local copies
    temp = usd;
    usd = eur;
    eur = temp;

    printf("Preview Result -> USD: %.2f | EUR: %.2f\n", usd, eur);
    printf("(Note: This change is local to this function only.)\n");
}

void confirmSwap(float *usdPtr, float *eurPtr) {
    float temp;
    // Swap logic using pointers (Dereferencing)
    // *usdPtr accesses the value at the memory address of walletUSD
    temp = *usdPtr;
    *usdPtr = *eurPtr;
    *eurPtr = temp;

    printf("Success! Currencies have been swapped in your account.\n");
}