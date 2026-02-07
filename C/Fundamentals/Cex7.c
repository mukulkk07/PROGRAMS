#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

/* 1. Define the Patient Structure */
struct Patient {
    int id;
    char name[50];
    char disease[50];
    float totalBill;
};

/* 2. Global Variables */
// We use a global array to simulate a database accessible by all functions
struct Patient hospital[MAX_PATIENTS];
int patientCount = 0;

/* 3. Function Prototypes */
/* These tell the compiler that these functions exist and will be defined later */
void registerPatient();
void generateBill();
void printReport();

int main() {
    int choice;

    printf("=== City Hospital Management System ===\n");

    while (1) {
        printf("\n1. Register New Patient\n");
        printf("2. Generate/Update Bill\n");
        printf("3. Print Patient Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                generateBill();
                break;
            case 3:
                printReport();
                break;
            case 4:
                printf("Exiting System. Stay Healthy!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

/* 4. Function Definitions */

void registerPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Error: Hospital is at full capacity.\n");
        return;
    }

    struct Patient p;
    
    // Auto-generate ID (e.g., 101, 102...)
    p.id = 101 + patientCount;
    
    printf("\n--- Patient Registration ---\n");
    printf("Generated Patient ID: %d\n", p.id);
    
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", p.name); // Read string with spaces
    
    printf("Enter Disease/Condition: ");
    scanf(" %[^\n]", p.disease);
    
    p.totalBill = 0.0; // Initial bill is zero

    // Store in global array
    hospital[patientCount] = p;
    patientCount++;
    
    printf("Registration Successful!\n");
}

void generateBill() {
    int searchID, i, found = 0;
    float amount;

    printf("\n--- Billing Section ---\n");
    printf("Enter Patient ID to bill: ");
    scanf("%d", &searchID);

    for (i = 0; i < patientCount; i++) {
        if (hospital[i].id == searchID) {
            found = 1;
            printf("Patient Found: %s\n", hospital[i].name);
            printf("Current Bill: $%.2f\n", hospital[i].totalBill);
            
            printf("Enter charge to add: ");
            scanf("%f", &amount);
            
            if (amount > 0) {
                hospital[i].totalBill += amount;
                printf("Bill updated. New Total: $%.2f\n", hospital[i].totalBill);
            } else {
                printf("Error: Invalid amount.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Error: Patient ID %d not found.\n", searchID);
    }
}

void printReport() {
    int i;
    printf("\n--- Hospital Patient Report ---\n");
    printf("------------------------------------------------------------\n");
    printf("%-5s %-20s %-20s %-10s\n", "ID", "Name", "Disease", "Bill ($)");
    printf("------------------------------------------------------------\n");

    if (patientCount == 0) {
        printf("No records found.\n");
    } else {
        for (i = 0; i < patientCount; i++) {
            printf("%-5d %-20s %-20s %-10.2f\n", 
                   hospital[i].id, 
                   hospital[i].name, 
                   hospital[i].disease, 
                   hospital[i].totalBill);
        }
    }
    printf("------------------------------------------------------------\n");
}