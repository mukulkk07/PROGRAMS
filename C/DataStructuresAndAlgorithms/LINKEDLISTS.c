#include <stdio.h>
#include <stdlib.h>

/* --- 1. Structure Definition --- */
struct Node {
    int data;
    struct Node* next;
};

/* --- 2. Function Prototypes --- */
// Core Operations
struct Node* createNode(int data);
void insertAtBeginning(struct Node** head_ref, int new_data);
void insertAtEnd(struct Node** head_ref, int new_data);
void insertAfter(struct Node* prev_node, int new_data);
void deleteNode(struct Node** head_ref, int key);
void printList(struct Node* node);
int getCount(struct Node* head);
int search(struct Node* head, int x);
void freeList(struct Node** head_ref);

// Algorithms
void reverse(struct Node** head_ref);
void middleNode(struct Node* head);
int detectLoop(struct Node* head);
void removeDuplicates(struct Node* head);
void sortList(struct Node** head_ref); // Merge Sort wrapper
void getNthFromEnd(struct Node* head, int n);

// Helpers for Sorting
struct Node* sortedMerge(struct Node* a, struct Node* b);
void frontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef);
void mergeSort(struct Node** headRef);

/* --- 3. Main Driver Code --- */
int main() {
    struct Node* head = NULL;
    int choice, data, key, pos;

    while (1) {
        printf("\n\n--- MASTER LINKED LIST MENU ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete a Value\n");
        printf("4. Display List\n");
        printf("5. Search for Value\n");
        printf("6. Count Nodes\n");
        printf("7. Reverse List\n");
        printf("8. Find Middle Element\n");
        printf("9. Sort List (Merge Sort)\n");
        printf("10. Remove Duplicates\n");
        printf("11. Find Nth Node from End\n");
        printf("12. Detect Loop (Cycle)\n");
        printf("13. Clear List & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &key);
                deleteNode(&head, key);
                break;
            case 4:
                printList(head);
                break;
            case 5:
                printf("Enter value to search: ");
                scanf("%d", &key);
                pos = search(head, key);
                if (pos) printf("Found at position %d (1-based index)\n", pos);
                else printf("Not Found\n");
                break;
            case 6:
                printf("Total nodes: %d\n", getCount(head));
                break;
            case 7:
                reverse(&head);
                printf("List reversed.\n");
                printList(head);
                break;
            case 8:
                middleNode(head);
                break;
            case 9:
                mergeSort(&head);
                printf("List sorted.\n");
                printList(head);
                break;
            case 10:
                removeDuplicates(head);
                printf("Duplicates removed (from sorted list logic).\n");
                printList(head);
                break;
            case 11:
                printf("Enter N (position from end): ");
                scanf("%d", &pos);
                getNthFromEnd(head, pos);
                break;
            case 12:
                if (detectLoop(head)) printf("Loop Detected!\n");
                else printf("No Loop detected.\n");
                break;
            case 13:
                freeList(&head);
                printf("Memory freed. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

/* --- 4. Implementation Details --- */

// Helper to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 1. Insert at Beginning - O(1)
void insertAtBeginning(struct Node** head_ref, int new_data) {
    struct Node* new_node = createNode(new_data);
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// 2. Insert at End - O(N)
void insertAtEnd(struct Node** head_ref, int new_data) {
    struct Node* new_node = createNode(new_data);
    struct Node* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

// 3. Delete a Node by Key - O(N)
void deleteNode(struct Node** head_ref, int key) {
    struct Node *temp = *head_ref, *prev = NULL;

    // If head holds the key
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        printf("Deleted %d\n", key);
        return;
    }

    // Search for the key
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key not found.\n");
        return;
    }

    // Unlink and free
    prev->next = temp->next;
    free(temp);
    printf("Deleted %d\n", key);
}

// 4. Display List
void printList(struct Node* node) {
    printf("List: ");
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// 5. Search - O(N)
int search(struct Node* head, int x) {
    struct Node* current = head;
    int index = 1;
    while (current != NULL) {
        if (current->data == x)
            return index;
        current = current->next;
        index++;
    }
    return 0;
}

// 6. Get Count - O(N)
int getCount(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// 7. Reverse List - O(N)
void reverse(struct Node** head_ref) {
    struct Node* prev = NULL;
    struct Node* current = *head_ref;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next; // Store next
        current->next = prev; // Reverse pointer
        prev = current;       // Move pointers one position ahead
        current = next;
    }
    *head_ref = prev;
}

// 8. Find Middle Element (Tortoise and Hare Algorithm) - O(N)
void middleNode(struct Node* head) {
    struct Node *slow_ptr = head;
    struct Node *fast_ptr = head;

    if (head != NULL) {
        while (fast_ptr != NULL && fast_ptr->next != NULL) {
            fast_ptr = fast_ptr->next->next;
            slow_ptr = slow_ptr->next;
        }
        printf("The middle element is [%d]\n", slow_ptr->data);
    }
}

// 9. Sorting (Merge Sort) - O(N log N)
void mergeSort(struct Node** headRef) {
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;

    // Base case -- length 0 or 1
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    // Split head into 'a' and 'b' sublists
    frontBackSplit(head, &a, &b);

    // Recursively sort the sublists
    mergeSort(&a);
    mergeSort(&b);

    // Answer = merge the two sorted lists together
    *headRef = sortedMerge(a, b);
}

struct Node* sortedMerge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;

    if (a == NULL) return (b);
    if (b == NULL) return (a);

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return (result);
}

void frontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* fast;
    struct Node* slow;
    slow = source;
    fast = source->next;

    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// 10. Remove Duplicates (Assumes List is Sorted) - O(N)
void removeDuplicates(struct Node* head) {
    struct Node* current = head;
    struct Node* next_next;

    if (current == NULL) return;

    while (current->next != NULL) {
        if (current->data == current->next->data) {
            next_next = current->next->next;
            free(current->next);
            current->next = next_next;
        } else {
            current = current->next;
        }
    }
}

// 11. Get Nth Node From End - O(N)
void getNthFromEnd(struct Node* head, int n) {
    struct Node *main_ptr = head;
    struct Node *ref_ptr = head;
    int count = 0;

    if (head != NULL) {
        while (count < n) {
            if (ref_ptr == NULL) {
                printf("%d is greater than the no. of nodes in list\n", n);
                return;
            }
            ref_ptr = ref_ptr->next;
            count++;
        }
        while (ref_ptr != NULL) {
            main_ptr = main_ptr->next;
            ref_ptr = ref_ptr->next;
        }
        printf("Node %d from end is %d\n", n, main_ptr->data);
    }
}

// 12. Detect Loop (Floyd’s Cycle-Finding Algorithm)
int detectLoop(struct Node* head) {
    struct Node *slow_p = head, *fast_p = head;
    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p) {
            return 1;
        }
    }
    return 0;
}

// 13. Free List (Memory Management)
void freeList(struct Node** head_ref) {
    struct Node* current = *head_ref;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}