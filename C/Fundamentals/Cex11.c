#include <stdio.h>

/* Define constants for the size of the hall */
#define ROWS 5
#define COLS 5

/* Function Prototypes */
void displayChart(int chart[ROWS][COLS]);
void updateSeat(int chart[ROWS][COLS]);
void countSeats(int chart[ROWS][COLS]);

int main() {
    // 1. Initialize the 2D Array
    // 0 = Empty, 1 = Occupied. 
    // We initialize some seats as occupied for demonstration.
    int seatingChart[ROWS][COLS] = {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };

    int choice;

    printf("=== Library Reading Hall System ===\n");

    while (1) {
        printf("\n1. Show Seating Chart\n");
        printf("2. Update Seat Status (Book/Release)\n");
        printf("3. Count Available Seats\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayChart(seatingChart);
                break;
            case 2:
                updateSeat(seatingChart);
                break;
            case 3:
                countSeats(seatingChart);
                break;
            case 4:
                printf("Exiting System.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

/* --- Function Definitions --- */

void displayChart(int chart[ROWS][COLS]) {
    int i, j;
    printf("\n--- Current Seating Chart ---\n");
    printf("      Col 1 Col 2 Col 3 Col 4 Col 5\n");
    printf("      -----------------------------\n");

    for (i = 0; i < ROWS; i++) {
        printf("Row %d | ", i + 1); // Row Header
        for (j = 0; j < COLS; j++) {
            // Display the raw data (0 or 1)
            printf("  %d   ", chart[i][j]);
        }
        printf("\n");
    }
    printf("      -----------------------------\n");
    printf("Key: 0 = Empty, 1 = Occupied\n");
}

void updateSeat(int chart[ROWS][COLS]) {
    int r, c, status;
    
    printf("\n--- Update Seat Status ---\n");
    // User inputs 1-based index, we convert to 0-based
    printf("Enter Row number (1-%d): ", ROWS);
    scanf("%d", &r);
    printf("Enter Col number (1-%d): ", COLS);
    scanf("%d", &c);

    // Array Bounds Checking
    if (r < 1 || r > ROWS || c < 1 || c > COLS) {
        printf("Error: Invalid seat coordinates!\n");
        return;
    }

    // Adjust for 0-based indexing
    r--; 
    c--;

    printf("Enter new status (0 for Empty, 1 for Occupied): ");
    scanf("%d", &status);

    if (status == 0 || status == 1) {
        chart[r][c] = status;
        printf("Seat [Row %d, Col %d] updated successfully.\n", r + 1, c + 1);
    } else {
        printf("Error: Status must be 0 or 1.\n");
    }
}

void countSeats(int chart[ROWS][COLS]) {
    int i, j;
    int occupied = 0;
    int empty = 0;

    // Nested loop to traverse the 2D array
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (chart[i][j] == 1) {
                occupied++;
            } else {
                empty++;
            }
        }
    }

    printf("\n--- Hall Statistics ---\n");
    printf("Total Seats    : %d\n", ROWS * COLS);
    printf("Occupied Seats : %d\n", occupied);
    printf("Available Seats: %d\n", empty);
}