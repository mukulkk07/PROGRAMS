/*
 * StudentDB.c
 * A complete database system using Linked Lists and File I/O.
 *
 * Concepts: structs, pointers, malloc/free, fopen/fclose, recursion.
 *
 * TO COMPILE: gcc StudentDB.c -o student_db
 */

#include <stdio.h>      // Input/Output
#include <stdlib.h>     // Malloc, Free, Exit
#include <string.h>     // String operations

// ==========================================
// 1. DATA STRUCTURES
// ==========================================

// Define the Student Node
typedef struct Student {
    int id;
    char name[50];
    float gpa;
    struct Student* next; // Pointer to the next student (Linked List)
} Student;

// ==========================================
// 2. FUNCTION PROTOTYPES
// ==========================================

Student* create_student(int id, const char* name, float gpa);
void append_student(Student** head, int id, const char* name, float gpa);
void print_list(Student* head);
void save_to_file(Student* head, const char* filename);
void load_from_file(Student** head, const char* filename);
void free_list(Student* head);
Student* find_highest_gpa(Student* head);

// ==========================================
// 3. MAIN APPLICATION LOOP
// ==========================================

int main() {
    Student* db_head = NULL; // The list starts empty
    const char* db_file = "database.txt";
    int choice;

    // Load existing data if available
    load_from_file(&db_head, db_file);

    printf("=== Student Management System (C) ===\n");

    while (1) {
        printf("\n1. Add Student\n2. View All\n3. Find Highest GPA\n4. Save & Exit\n");
        printf("Select: ");
        if (scanf("%d", &choice) != 1) break; // Exit if input is not a number

        if (choice == 1) {
            int id;
            float gpa;
            char name[50];
            
            printf("Enter ID: "); scanf("%d", &id);
            printf("Enter Name: "); scanf("%49s", name); // Limit input to 49 chars
            printf("Enter GPA: "); scanf("%f", &gpa);
            
            // Pass the address of the head pointer so we can modify the list
            append_student(&db_head, id, name, gpa);
            printf("[+] Student added.\n");

        } else if (choice == 2) {
            print_list(db_head);

        } else if (choice == 3) {
            Student* top = find_highest_gpa(db_head);
            if (top) printf("Top Student: %s (GPA: %.2f)\n", top->name, top->gpa);
            else     printf("List is empty.\n");

        } else if (choice == 4) {
            save_to_file(db_head, db_file);
            printf("[+] Data saved. Exiting...\n");
            break;
        }
    }

    // CLEANUP: Always free dynamic memory before exiting
    free_list(db_head);
    return 0;
}

// ==========================================
// 4. IMPLEMENTATION DETAILS
// ==========================================

/*
 * allocate_student:
 * Creates a new node on the heap using malloc.
 */
Student* create_student(int id, const char* name, float gpa) {
    // 1. Allocate memory size of the struct
    Student* new_node = (Student*)malloc(sizeof(Student));
    
    if (new_node == NULL) {
        printf("Critical Error: Memory allocation failed!\n");
        exit(1);
    }

    // 2. Set data
    new_node->id = id;
    new_node->gpa = gpa;
    
    // safe string copy
    strncpy(new_node->name, name, 49);
    new_node->name[49] = '\0'; // Ensure null-termination

    new_node->next = NULL; // Currently points to nothing
    return new_node;
}

/*
 * append_student:
 * Adds a node to the END of the list.
 * Takes a double pointer (Student**) because the 'head' itself might change.
 */
void append_student(Student** head, int id, const char* name, float gpa) {
    Student* new_node = create_student(id, name, gpa);

    // Case 1: List is empty
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    // Case 2: Traverse to the end
    Student* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Link the last node to the new node
    current->next = new_node;
}

/*
 * print_list:
 * Iterates through the pointers.
 */
void print_list(Student* head) {
    printf("\n--- Database Content ---\n");
    Student* current = head;
    while (current != NULL) {
        printf("ID: %d | Name: %-10s | GPA: %.2f\n", 
               current->id, current->name, current->gpa);
        current = current->next; // Move to next node
    }
    printf("------------------------\n");
}

/*
 * save_to_file:
 * Writes data in CSV format (ID,Name,GPA).
 */
void save_to_file(Student* head, const char* filename) {
    FILE* fp = fopen(filename, "w"); // "w" = write mode (overwrites)
    if (!fp) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    Student* current = head;
    while (current != NULL) {
        fprintf(fp, "%d,%s,%.2f\n", current->id, current->name, current->gpa);
        current = current->next;
    }
    fclose(fp);
}

/*
 * load_from_file:
 * Reads CSV format and rebuilds the linked list.
 */
void load_from_file(Student** head, const char* filename) {
    FILE* fp = fopen(filename, "r"); // "r" = read mode
    if (!fp) return; // File doesn't exist yet, that's fine.

    int id;
    char name[50];
    float gpa;

    // fscanf returns the number of items successfully read
    while (fscanf(fp, "%d,%49[^,],%f\n", &id, name, &gpa) == 3) {
        append_student(head, id, name, gpa);
    }
    fclose(fp);
    printf("[+] Database loaded from disk.\n");
}

/*
 * find_highest_gpa:
 * Simple logic to find the max value in a list.
 */
Student* find_highest_gpa(Student* head) {
    if (head == NULL) return NULL;

    Student* best = head;
    Student* current = head->next;

    while (current != NULL) {
        if (current->gpa > best->gpa) {
            best = current;
        }
        current = current->next;
    }
    return best;
}

/*
 * free_list:
 * CRITICAL in C: Manually release memory to prevent leaks.
 */
void free_list(Student* head) {
    Student* current = head;
    while (current != NULL) {
        Student* temp = current;
        current = current->next; // Save pointer to next
        free(temp);              // Free the current one
    }
}