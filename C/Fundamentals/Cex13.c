#include <stdio.h>

/* Define the maximum characters a phone screen can display for a name */
#define DISPLAY_LIMIT 20

int main() {
    char firstName[50], lastName[50], fullName[100];
    int i, j;
    int lenCount = 0; // To track the current length of fullName

    printf("=== Mobile Contact Manager ===\n");
    printf("(Max Display Limit: %d characters)\n", DISPLAY_LIMIT);

    /* 1. Input Names */
    printf("\nEnter First Name: ");
    scanf("%s", firstName);
    
    printf("Enter Last Name: ");
    scanf("%s", lastName);

    /* 2. Manual Concatenation Logic */
    
    // Step A: Copy First Name into Full Name
    // We start 'i' at 0 and copy until we hit the null terminator '\0'
    i = 0;
    while (firstName[i] != '\0') {
        fullName[lenCount] = firstName[i];
        i++;
        lenCount++;
    }

    // Step B: Add a space between names
    fullName[lenCount] = ' ';
    lenCount++;

    // Step C: Append Last Name to the end of Full Name
    // We use a new index 'j' for lastName, but keep incrementing 'lenCount'
    j = 0;
    while (lastName[j] != '\0') {
        fullName[lenCount] = lastName[j];
        j++;
        lenCount++;
    }

    // Step D: IMPORTANT - Add the Null Terminator
    // Strings in C must end with '\0' so the computer knows where they stop.
    fullName[lenCount] = '\0';

    /* 3. Validation & Output */
    printf("\n--- Processing Contact ---\n");
    printf("Combined Name: \"%s\"\n", fullName);
    printf("Total Length : %d characters\n", lenCount);

    if (lenCount <= DISPLAY_LIMIT) {
        printf("Status: [VALID] Name fits within the display limit.\n");
        printf("Saved to contacts successfully.\n");
    } else {
        printf("Status: [WARNING] Name exceeds the %d character limit!\n", DISPLAY_LIMIT);
        printf("Action: Name may be truncated on the mobile display.\n");
    }

    return 0;
}