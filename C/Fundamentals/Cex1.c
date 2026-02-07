#include <stdio.h>

/* 1. Define the Structure */
struct Employee {
    int empID;
    char name[50];
    float salary;
};

int main() {
    int n, i;

    // 2. Ask user for the number of employees
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    // 3. Declare an array of structures
    // We create an array 'emp' of size 'n' to store the details
    struct Employee emp[n];

    // 4. Input Loop: Get details for each employee
    printf("\n--- Enter Employee Details ---\n");
    for (i = 0; i < n; i++) {
        printf("\nEmployee %d:\n", i + 1);
        
        printf("Enter EmpID: ");
        scanf("%d", &emp[i].empID);
        
        printf("Enter Name: ");
        scanf("%s", emp[i].name); // Note: scanf("%s") stops at whitespace
        
        printf("Enter Salary: ");
        scanf("%f", &emp[i].salary);
    }

    // 5. Output Loop: Display the details
    printf("\n\n--- Employee Records ---\n");
    printf("--------------------------------------------------\n");
    // %-10d means left-align integer within 10 spaces
    // %-20s means left-align string within 20 spaces
    // %.2f means print float with 2 decimal places
    printf("%-10s %-20s %-10s\n", "EmpID", "Name", "Salary");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %.2f\n", emp[i].empID, emp[i].name, emp[i].salary);
    }
    printf("--------------------------------------------------\n");

    return 0;
}