#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- 1. DATA STRUCTURE DEFINITIONS ---

// Node represents a single piece of data
struct Node {
    int data;
    struct Node* next;
};

// Queue struct holds pointers to both ends for O(1) efficiency
struct Queue {
    struct Node *front;
    struct Node *rear;
};

// --- 2. CORE OPERATIONS ---

// Initialize a new Queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Check if queue is empty
bool isEmpty(struct Queue* q) {
    return (q->front == NULL);
}

// ENQUEUE: Add element to the Rear
void enqueue(struct Queue* q, int value) {
    // Create new node
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    if (!temp) {
        printf("[Error] Memory allocation failed!\n");
        return;
    }
    temp->data = value;
    temp->next = NULL;

    // If queue is empty, new node is both front and rear
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        printf(">> Enqueued %d (First Element).\n", value);
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
    printf(">> Enqueued %d.\n", value);
}

// DEQUEUE: Remove element from the Front
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("[Error] Queue Underflow! Nothing to remove.\n");
        return INT_MIN;
    }

    // Store previous front and move front one node ahead
    struct Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    // If front becomes NULL, then rear must also be NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

// PEEK FRONT: View the first element
int peekFront(struct Queue* q) {
    if (isEmpty(q)) return INT_MIN;
    return q->front->data;
}

// PEEK REAR: View the last element
int peekRear(struct Queue* q) {
    if (isEmpty(q)) return INT_MIN;
    return q->rear->data;
}

// --- 3. UTILITY FUNCTIONS ---

// Display the Queue
void display(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty.\n");
        return;
    }
    struct Node* temp = q->front;
    printf("Front -> [ ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        if (temp->next != NULL) printf("-> ");
        temp = temp->next;
    }
    printf("] <- Rear\n");
}

// Get Size of Queue
int getSize(struct Queue* q) {
    int count = 0;
    struct Node* temp = q->front;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Clear/Delete Queue
void clearQueue(struct Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    printf(">> Queue cleared and memory freed.\n");
}

// --- 4. ADVANCED ALGORITHMS ---

// Algorithm: Reverse Queue (Recursive)
// Note: Queues are FIFO. To reverse, we need to utilize the 
// system call stack (recursion) to hold values.
void reverseQueue(struct Queue* q) {
    if (isEmpty(q)) return;

    // 1. Remove front element
    int data = dequeue(q);

    // 2. Recursively call for remaining queue
    reverseQueue(q);

    // 3. Add the removed element back (it will now be added to the rear)
    // effectively reversing the order as the stack unwinds.
    enqueue(q, data);
}

// Algorithm: Search for an element (Linear Search)
int searchQueue(struct Queue* q, int key) {
    struct Node* temp = q->front;
    int pos = 1;
    while(temp != NULL) {
        if(temp->data == key) return pos;
        temp = temp->next;
        pos++;
    }
    return -1;
}

// --- 5. MAIN INTERFACE ---

int main() {
    struct Queue* q = createQueue();
    int choice, val, result;

    printf("=== MASTER QUEUE PROGRAM (Linked List Implementation) ===\n");
    printf("Efficient O(1) Enqueue and Dequeue\n");

    while (1) {
        printf("\n--- Queue Operations ---\n");
        printf("1. Enqueue (Insert)\n");
        printf("2. Dequeue (Remove)\n");
        printf("3. Peek Front\n");
        printf("4. Peek Rear\n");
        printf("5. Display Queue\n");
        printf("6. Check Size\n");
        printf("7. Search Element\n");
        printf("8. Reverse Queue (Algorithm)\n");
        printf("9. Clear Queue\n");
        printf("0. Exit\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) {
             printf("Invalid Input.\n");
             break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &val);
                enqueue(q, val);
                break;
            case 2:
                val = dequeue(q);
                if (val != INT_MIN) printf("Dequeued Value: %d\n", val);
                break;
            case 3:
                val = peekFront(q);
                if (val != INT_MIN) printf("Front Element: %d\n", val);
                else printf("Queue is Empty.\n");
                break;
            case 4:
                val = peekRear(q);
                if (val != INT_MIN) printf("Rear Element: %d\n", val);
                else printf("Queue is Empty.\n");
                break;
            case 5:
                display(q);
                break;
            case 6:
                printf("Current Queue Size: %d\n", getSize(q));
                break;
            case 7:
                printf("Enter value to search: ");
                scanf("%d", &val);
                result = searchQueue(q, val);
                if (result != -1) printf("Element found at position %d from Front.\n", result);
                else printf("Element not found.\n");
                break;
            case 8:
                printf("Reversing Queue...\n");
                reverseQueue(q);
                display(q);
                break;
            case 9:
                clearQueue(q);
                break;
            case 0:
                printf("Exiting...\n");
                clearQueue(q);
                free(q); // Free the shell struct
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }
    return 0;
}