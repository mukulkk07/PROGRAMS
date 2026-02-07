#include <stdio.h>

/* 1. Define the Structure */
struct Student {
    char name[50];
    char usn[20];  // USN is alphanumeric, so we use a char array
    float marks;
};

int main() {
    // 2. Declare a structure variable for one student
    struct Student s;

    printf("--- Enter Student Information ---\n");

    // 3. Input Data
    // We use a space before %[^\n] to consume any buffer characters safely
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name); 

    printf("Enter USN: ");
    scanf("%s", s.usn);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    // 4. Display Data
    printf("\n--- Student Details ---\n");
    printf("Name  : %s\n", s.name);
    printf("USN   : %s\n", s.usn);
    printf("Marks : %.2f\n", s.marks);

    return 0;
}