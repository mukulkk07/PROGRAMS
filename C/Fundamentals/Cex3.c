#include <stdio.h>
#include <string.h>

/* 1. Define Enum for Payment Type */
// Enums make the code readable by using words instead of magic numbers
typedef enum {
    CASH = 1,
    CREDIT,
    DEBIT
} PaymentType;

/* 2. Define Union for Payment Details */
// A union uses only as much memory as its largest member
typedef union {
    float cashAmount;       // Used if type is CASH
    char cardNumber[20];    // Used if type is CREDIT or DEBIT
} PaymentDetails;

/* 3. Define the main Structure */
typedef struct {
    PaymentType type;       // "Tag" to know which union member to use
    PaymentDetails info;    // The actual data storage
} Transaction;

int main() {
    Transaction t;
    int choice;

    // --- Input Phase ---
    printf("--- Payment Gateway ---\n");
    printf("Select Payment Method:\n");
    printf("1. Cash\n");
    printf("2. Credit Card\n");
    printf("3. Debit Card\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);

    // Assign the enum based on user input
    t.type = (PaymentType)choice;

    switch (t.type) {
        case CASH:
            printf("Enter Cash Amount Received: ");
            scanf("%f", &t.info.cashAmount);
            break;

        case CREDIT:
            printf("Enter Credit Card Number (16 digits): ");
            scanf("%s", t.info.cardNumber);
            break;

        case DEBIT:
            printf("Enter Debit Card Number (16 digits): ");
            scanf("%s", t.info.cardNumber);
            break;

        default:
            printf("Invalid selection.\n");
            return 1;
    }

    // --- Output Phase ---
    printf("\n--- Payment Receipt ---\n");
    printf("Method: ");

    // We check t.type to know how to interpret the data in t.info
    switch (t.type) {
        case CASH:
            printf("CASH\n");
            printf("Amount Received: $%.2f\n", t.info.cashAmount);
            break;

        case CREDIT:
            printf("CREDIT CARD\n");
            printf("Card Number: ****-****-****-%s\n", &t.info.cardNumber[12]); // Masking for realism
            break;

        case DEBIT:
            printf("DEBIT CARD\n");
            printf("Card Number: ****-****-****-%s\n", &t.info.cardNumber[12]);
            break;
    }

    // Size demonstration (Technical verification)
    printf("\n[System Info] Size of Union: %lu bytes\n", sizeof(t.info));
    
    return 0;
}