#include <stdio.h>
#include <string.h> // Required for strstr() and strcspn()

int main() {
    char description[200];
    char keyword[50];
    char *result;

    printf("--- Course Search Engine ---\n");

    /* 1. Input the Course Description */
    printf("Enter the Course Description: ");
    // fgets allows reading a full sentence with spaces
    fgets(description, sizeof(description), stdin);

    // Remove the trailing newline character '\n' added by fgets
    description[strcspn(description, "\n")] = 0;

    /* 2. Input the Keyword */
    printf("Enter the keyword to search: ");
    scanf("%s", keyword);

    /* 3. Perform the Search */
    // strstr(haystack, needle) looks for 'keyword' inside 'description'
    // It returns a pointer to the first occurrence, or NULL if not found.
    result = strstr(description, keyword);

    /* 4. Display the Result */
    printf("\n--- Search Result ---\n");
    if (result != NULL) {
        printf("Success: The keyword \"%s\" was FOUND in the description.\n", keyword);
        // Optional: Show where it was found
        printf("Match found starting at index: %ld\n", result - description);
    } else {
        printf("result: The keyword \"%s\" was NOT FOUND.\n", keyword);
    }

    return 0;
}