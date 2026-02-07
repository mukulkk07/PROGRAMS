#include <stdio.h>

/* 1. Define the Book Structure */
struct Book {
    char title[100];
    char author[50];
    int year;
};

int main() {
    int n, i;

    // 2. Ask for the number of books
    printf("Enter the number of books: ");
    scanf("%d", &n);

    // 3. Create an array of structures
    struct Book library[n];

    // 4. Input Loop
    printf("\n--- Enter Book Details ---\n");
    for (i = 0; i < n; i++) {
        printf("\nBook %d:\n", i + 1);

        printf("Enter Title: ");
        // " %[^\n]" reads a string with spaces until the user presses Enter
        scanf(" %[^\n]", library[i].title);

        printf("Enter Author: ");
        scanf(" %[^\n]", library[i].author);

        printf("Enter Publication Year: ");
        scanf("%d", &library[i].year);
    }

    // 5. Output Loop
    printf("\n\n--- Library Collection ---\n");
    printf("------------------------------------------------------------\n");
    // Formatted output: %-30s aligns text to the left in a 30-char wide field
    printf("%-30s %-20s %-6s\n", "Title", "Author", "Year");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-30s %-20s %d\n", library[i].title, library[i].author, library[i].year);
    }
    printf("------------------------------------------------------------\n");

    return 0;
}