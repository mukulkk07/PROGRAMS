/*
 * CSyntaxMaster.c
 * A complete tour of the C programming language in one file.
 *
 * TO COMPILE: gcc CSyntaxMaster.c -o master -Wall
 */

#include <stdio.h>      // Standard I/O (printf, fopen, etc.)
#include <stdlib.h>     // Memory management (malloc, free, atoi)
#include <string.h>     // String manipulation (strcpy, strlen)
#include <stdarg.h>     // Variadic functions (va_list)
#include <stdbool.h>    // Boolean type (since C99)

// ==========================================
// 1. PREPROCESSOR MACROS
// ==========================================
#define PI 3.14159                  // Constant macro
#define SQUARE(x) ((x) * (x))       // Function-like macro (use parentheses!)
#define DEBUG_MODE 1                // Conditional compilation flag

// ==========================================
// 2. ENUMS & TYPEDEFS
// ==========================================

// Enumeration: Named integer constants
typedef enum {
    STATUS_OK,
    STATUS_ERROR,
    STATUS_PENDING
} Status;

// Forward declaration of a struct
struct Point3D; 

// ==========================================
// 3. STRUCTS, UNIONS & BIT-FIELDS
// ==========================================

// Standard Struct
typedef struct {
    char name[50];
    int id;
    float salary;
} Employee;

// Bit-field Struct (Advanced memory optimization)
typedef struct {
    unsigned int is_visible : 1;    // Uses only 1 bit
    unsigned int is_active  : 1;    // Uses only 1 bit
    unsigned int layer_id   : 6;    // Uses 6 bits (values 0-63)
} Flags;

// Union: Memory shared between members (only one holds a value at a time)
typedef union {
    int integerValue;
    float floatValue;
    char strValue[4];
} DataConverter;

// ==========================================
// 4. FUNCTION PROTOTYPES
// ==========================================
void demo_basics(void);
void demo_pointers(void);
void demo_arrays_and_strings(void);
void demo_memory_management(void);
void demo_structs_unions(void);
void demo_variadic(int count, ...);
void callback_executor(void (*func)(int), int value); // Function pointer param

// Helper function definition
void print_int(int x) {
    printf("[Callback] Value received: %d\n", x);
}

// ==========================================
// 5. MAIN EXECUTION
// ==========================================

int main(int argc, char *argv[]) {
    printf("=== C Syntax Master Class ===\n\n");

    // Command Line Arguments Check
    if (argc > 1) {
        printf("Arguments passed: %s\n", argv[1]);
    }

    // --- Section Calls ---
    demo_basics();
    demo_pointers();
    demo_arrays_and_strings();
    demo_memory_management();
    demo_structs_unions();

    printf("--- 6. Variadic Functions ---\n");
    // Passing variable number of arguments
    demo_variadic(3, 10, 20, 30);
    printf("\n");

    printf("--- 7. Function Pointers ---\n");
    // Passing a function address to another function
    callback_executor(print_int, 99);
    printf("\n");

    printf("=== Program Complete ===\n");
    return STATUS_OK; // Returning enum value (0)
}

// ==========================================
// 6. DETAILED IMPLEMENTATIONS
// ==========================================

/* * A. Basic Types, Operators, and Control Flow
 */
void demo_basics(void) {
    printf("--- 1. Primitives & Logic ---\n");
    
    // Basic Types
    int integer = 42;
    double precise = 3.14159;
    char letter = 'C';
    _Bool flag = true; // Or just 'bool' if <stdbool.h> is included

    // Macro usage
    printf("Macro Check: SQUARE(5) = %d\n", SQUARE(5));

    // Ternary Operator
    int max = (integer > 10) ? integer : 10;
    
    // Control Flow: Switch
    switch(letter) {
        case 'A': printf("Grade A\n"); break;
        case 'C': printf("Grade C\n"); break;
        default:  printf("Unknown Grade\n");
    }

    // Control Flow: Loops
    printf("Looping: ");
    for(int i = 0; i < 3; i++) {
        if(i == 1) continue; // Skip iteration 1
        printf("%d ", i);
    }
    printf("\n\n");
}

/* * B. Pointers (The heart of C)
 */
void demo_pointers(void) {
    printf("--- 2. Pointers ---\n");
    
    int val = 100;
    int *ptr = &val;        // 'ptr' holds the address of 'val'
    int **pptr = &ptr;      // 'pptr' holds the address of 'ptr' (Double Pointer)

    printf("Value: %d\n", val);
    printf("Addr of val (&val): %p\n", (void*)&val);
    printf("Ptr value (ptr):    %p\n", (void*)ptr);
    printf("Dereference (*ptr): %d\n", *ptr);
    printf("Double Deref (**pptr): %d\n", **pptr);

    // Modifying via pointer
    *ptr = 200; 
    printf("New Value of val: %d\n\n", val);
}

/* * C. Arrays & String Manipulation
 */
void demo_arrays_and_strings(void) {
    printf("--- 3. Arrays & Strings ---\n");

    // Static Array
    int numbers[5] = {1, 2, 3, 4, 5};
    
    // Pointer Arithmetic
    // *(numbers + 2) is equivalent to numbers[2]
    printf("Array[2] via pointer arithmetic: %d\n", *(numbers + 2));

    // String (Character Array)
    char greeting[20] = "Hello";    // Modifiable (Stack)
    const char *msg = "World";      // Read-only (Data Segment)

    strcat(greeting, ", "); // Concatenate
    strcat(greeting, msg);

    printf("String: %s (Length: %zu)\n\n", greeting, strlen(greeting));
}

/* * D. Dynamic Memory (Heap Allocation)
 */
void demo_memory_management(void) {
    printf("--- 4. Dynamic Memory (malloc/free) ---\n");

    // Allocate memory for 5 integers
    int *arr = (int*)malloc(5 * sizeof(int));
    
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    // Initialize
    for(int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }

    // Reallocate (Resize memory block)
    int *temp = realloc(arr, 10 * sizeof(int));
    if (temp != NULL) {
        arr = temp;
    }

    printf("Heap Value[4]: %d\n", arr[4]);

    // ALWAYS free dynamically allocated memory
    free(arr); 
    arr = NULL; // Good practice to prevent dangling pointers
    printf("Memory freed.\n\n");
}

/* * E. Structs, Unions, and Typedefs
 */
void demo_structs_unions(void) {
    printf("--- 5. Structs & Unions ---\n");

    // Struct Usage
    Employee emp1;
    strcpy(emp1.name, "Alice"); // Must use strcpy for char arrays
    emp1.id = 101;
    emp1.salary = 50000.50;

    // Struct Pointer (Arrow Operator)
    Employee *pEmp = &emp1;
    printf("Struct: %s (ID: %d)\n", pEmp->name, pEmp->id);

    // Union Usage
    DataConverter dc;
    dc.integerValue = 65;
    printf("Union as Int: %d\n", dc.integerValue);
    // Interpreting the same bits as a string
    // 65 is ASCII 'A'. Note: Endianness affects this.
    printf("Union as Char: %c (Shared Memory)\n", dc.strValue[0]); 

    // Bit-fields
    Flags f = {1, 0, 55}; // Visible=1, Active=0, Layer=55
    printf("Bitfield: Visible=%d, Layer=%d\n\n", f.is_visible, f.layer_id);
}

/* * F. Variadic Functions (Variable Arguments)
 */
void demo_variadic(int count, ...) {
    va_list args;           // List pointer
    va_start(args, count);  // Initialize list

    printf("Variadic Args: ");
    for (int i = 0; i < count; i++) {
        // Retrieve next argument (must know type)
        int num = va_arg(args, int);
        printf("%d ", num);
    }
    
    va_end(args); // Clean up
    printf("\n");
}

/* * G. Function Pointers
 */
void callback_executor(void (*func)(int), int value) {
    // Calling the function passed as an argument
    func(value);
}