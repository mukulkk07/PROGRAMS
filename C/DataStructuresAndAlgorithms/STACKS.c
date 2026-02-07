#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- 1. DATA STRUCTURE DEFINITIONS ---

// Node structure represents a single element in the stack
struct Node {
    int data;
    struct Node* next;
};

// --- 2. CORE STACK OPERATIONS ---

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("\n[Error] Memory Allocation Failed! System out of memory.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Check if stack is empty
bool isEmpty(struct Node* top) {
    return (top == NULL);
}

// PUSH: Add element to top
void push(struct Node** top, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
    printf(">> Pushed %d onto the stack.\n", data);
}

// POP: Remove and return top element
int pop(struct Node** top) {
    if (isEmpty(*top)) {
        printf("\n[Error] Stack Underflow! Cannot pop from empty stack.\n");
        return INT_MIN; // Error code
    }
    struct Node* temp = *top;
    int poppedData = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedData;
}

// PEEK: View top element without removing
int peek(struct Node* top) {
    if (isEmpty(top)) {
        return INT_MIN;
    }
    return top->data;
}

// --- 3. UTILITY FUNCTIONS ---

// Display all elements
void display(struct Node* top) {
    if (isEmpty(top)) {
        printf("Stack is Empty.\n");
        return;
    }
    printf("Stack (Top -> Bottom): [ ");
    struct Node* temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        if (temp->next != NULL) printf("-> ");
        temp = temp->next;
    }
    printf("]\n");
}

// Get current size of stack
int getStackSize(struct Node* top) {
    int count = 0;
    while (top != NULL) {
        count++;
        top = top->next;
    }
    return count;
}

// Search for an element (Returns 1-based position from top, or -1 if not found)
int search(struct Node* top, int key) {
    int pos = 1;
    while (top != NULL) {
        if (top->data == key) return pos;
        top = top->next;
        pos++;
    }
    return -1;
}

// Clear the entire stack (Memory Management)
void clearStack(struct Node** top) {
    while (!isEmpty(*top)) {
        pop(top);
    }
    printf(">> Stack has been cleared and memory freed.\n");
}

// --- 4. ADVANCED ALGORITHMS ---

// Algorithm: Insert at Bottom (Helper for Reversal)
void insertAtBottom(struct Node** top, int item) {
    if (isEmpty(*top)) {
        push(top, item);
    } else {
        int temp = pop(top);
        insertAtBottom(top, item);
        push(top, temp);
    }
}

// Algorithm: Reverse Stack (Recursive)
void reverseStack(struct Node** top) {
    if (!isEmpty(*top)) {
        int temp = pop(top);
        reverseStack(top);
        insertAtBottom(top, temp);
    }
}

// Algorithm: Sort Stack (Using a temporary stack)
// Note: This logic moves elements between main stack and a temp stack to order them.
void sortStack(struct Node** top) {
    struct Node* tempStack = NULL;

    while (!isEmpty(*top)) {
        // Pop the first element from the main stack
        int temp = pop(top);

        // While temp stack is not empty and top of temp stack is greater than temp
        while (!isEmpty(tempStack) && peek(tempStack) > temp) {
            // Move elements from temp stack back to main stack
            push(top, pop(&tempStack));
        }

        // Push temp into tempStack
        push(&tempStack, temp);
    }

    // Move everything back to original stack
    *top = tempStack;
    printf(">> Stack sorted successfully.\n");
}

// --- 5. MAIN DRIVER ---

int main() {
    struct Node* stack = NULL; // Initialize Stack Pointer
    int choice, val, result;

    printf("=== MASTER STACK PROGRAM (Linked List Implementation) ===\n");

    while (1) {
        printf("\n--- Operations Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek (Top)\n");
        printf("4. Display Stack\n");
        printf("5. Stack Size\n");
        printf("6. Search Element\n");
        printf("7. Reverse Stack (Recursive Algo)\n");
        printf("8. Sort Stack (Ascending)\n");
        printf("9. Clear Stack\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
             printf("Invalid Input. Exiting.\n");
             break;
        }

        switch (choice) {
            case 1:
                printf("Enter integer to push: ");
                scanf("%d", &val);
                push(&stack, val);
                break;
            case 2:
                val = pop(&stack);
                if (val != INT_MIN) printf("Popped Value: %d\n", val);
                break;
            case 3:
                val = peek(stack);
                if (val != INT_MIN) printf("Top Element: %d\n", val);
                else printf("Stack is Empty.\n");
                break;
            case 4:
                display(stack);
                break;
            case 5:
                printf("Current Stack Size: %d\n", getStackSize(stack));
                break;
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &val);
                result = search(stack, val);
                if (result != -1) printf("Element found at position %d from top.\n", result);
                else printf("Element not found.\n");
                break;
            case 7:
                printf("Reversing stack...\n");
                reverseStack(&stack);
                display(stack);
                break;
            case 8:
                printf("Sorting stack...\n");
                sortStack(&stack);
                display(stack);
                break;
            case 9:
                clearStack(&stack);
                break;
            case 0:
                printf("Exiting... Cleaning up memory.\n");
                clearStack(&stack);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}