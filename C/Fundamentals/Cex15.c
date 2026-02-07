#include <stdio.h>

/* Function Prototype */
int binarySearch(int shelf[], int n, int searchID);

int main() {
    int n, i, searchID, result;

    printf("=== Digital Bookshelf System ===\n");
    
    // 1. Setup the Bookshelf
    printf("Enter total number of books: ");
    scanf("%d", &n);

    int shelf[n]; // Create array based on user size

    printf("\nNote: Please enter Book IDs in ASCENDING order (e.g., 101, 105, 110).\n");
    printf("--- Enter Book IDs ---\n");
    for (i = 0; i < n; i++) {
        printf("Book %d ID: ", i + 1);
        scanf("%d", &shelf[i]);
    }

    // 2. Input Search Query
    printf("\n--- Search Section ---\n");
    printf("Enter Book ID to search: ");
    scanf("%d", &searchID);

    // 3. Perform Binary Search
    result = binarySearch(shelf, n, searchID);

    // 4. Display Result
    if (result != -1) {
        printf("\n[Success] Book ID %d is AVAILABLE.\n", searchID);
        printf("Location: Position %d on the shelf.\n", result + 1);
    } else {
        printf("\n[Not Found] Book ID %d is NOT available in the system.\n", searchID);
    }

    return 0;
}

/* Binary Search Algorithm 
   Returns the index if found, -1 if not found.
*/
int binarySearch(int shelf[], int n, int searchID) {
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2; // Find the middle index

        // Case 1: The middle element is the book we want
        if (shelf[mid] == searchID) {
            return mid;
        }

        // Case 2: The ID is smaller than middle -> Search Left Half
        // We eliminate the entire right side of the array
        if (searchID < shelf[mid]) {
            high = mid - 1;
        }
        
        // Case 3: The ID is larger than middle -> Search Right Half
        // We eliminate the entire left side of the array
        else {
            low = mid + 1;
        }
    }

    // If we exit the loop, the book isn't there
    return -1;
}