#include <stdio.h>

/* Define constants for the scale of operations */
#define NUM_BRANCHES 3
#define NUM_PRODUCTS 4

int main() {
    // 1. Declare Arrays
    // Matrix to store units shipped: Rows = Branches, Cols = Products
    int shipped[NUM_BRANCHES][NUM_PRODUCTS];
    
    // Array to store price per unit for each product
    float price[NUM_PRODUCTS];
    
    // Array to store the final calculated revenue for each branch
    float totalRevenue[NUM_BRANCHES];

    int i, j;

    printf("=== Warehouse Management System ===\n");
    printf("Configuration: %d Branches, %d Products\n", NUM_BRANCHES, NUM_PRODUCTS);

    /* 2. Input: Revenue per Unit (Prices) */
    printf("\n--- Step 1: Set Product Prices ---\n");
    for (j = 0; j < NUM_PRODUCTS; j++) {
        printf("Enter revenue per unit for Product %d: $", j + 1);
        scanf("%f", &price[j]);
    }

    /* 3. Input: Units Shipped (Inventory Matrix) */
    printf("\n--- Step 2: Enter Shipping Data ---\n");
    for (i = 0; i < NUM_BRANCHES; i++) {
        printf("\n[Branch %d] Enter units shipped:\n", i + 1);
        for (j = 0; j < NUM_PRODUCTS; j++) {
            printf("  Product %d count: ", j + 1);
            scanf("%d", &shipped[i][j]);
        }
    }

    /* 4. Calculation: Compute Total Revenue */
    // Logic: Sum of (Units of Product P * Price of Product P) for all products
    for (i = 0; i < NUM_BRANCHES; i++) {
        totalRevenue[i] = 0.0; // Reset sum for this branch
        for (j = 0; j < NUM_PRODUCTS; j++) {
            totalRevenue[i] += shipped[i][j] * price[j];
        }
    }

    /* 5. Output: Final Report */
    printf("\n\n================ REVENUE REPORT ================\n");
    printf("Branch      Details (Units * Price)          Total Revenue\n");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < NUM_BRANCHES; i++) {
        printf("Branch %d    ", i + 1);
        printf("$%-30.2f  ", totalRevenue[i]); // Display calculated total
        
        // Logic to determine performance status
        if (totalRevenue[i] > 5000) {
            printf("[Top Performer]\n");
        } else {
            printf("\n");
        }
    }
    printf("------------------------------------------------------------\n");

    return 0;
}