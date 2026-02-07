#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- 1. DATA STRUCTURE DEFINITIONS ---

#define LOAD_FACTOR_THRESHOLD 0.75
#define INITIAL_CAPACITY 10

// Node for Separate Chaining (Linked List)
struct Node {
    int key;
    int value;
    struct Node* next;
};

// Hash Table Structure
struct HashTable {
    struct Node** buckets; // Array of pointers to Nodes
    int capacity;          // Total slots in the array
    int size;              // Total elements currently stored
};

// --- 2. CORE UTILITIES ---

// Create a new Node
struct Node* createNode(int key, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Create/Initialize Table
struct HashTable* createTable(int capacity) {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    
    // Allocate memory for buckets and initialize to NULL
    ht->buckets = (struct Node**)calloc(capacity, sizeof(struct Node*));
    return ht;
}

// HASH FUNCTION: Maps a key to an index
// We use simple Modulo arithmetic here.
int hashFunction(int key, int capacity) {
    return abs(key) % capacity;
}

// --- 3. DYNAMIC RESIZING (REHASHING) ---

// Forward declaration needed for internal use
void insert(struct HashTable* ht, int key, int value);

// Resizes the table when Load Factor > 0.75
void rehash(struct HashTable* ht) {
    int oldCapacity = ht->capacity;
    struct Node** oldBuckets = ht->buckets;

    printf("\n[Notice] Load Factor High. Resizing table from %d to %d...\n", 
           oldCapacity, oldCapacity * 2);

    // 1. Update Table Properties
    ht->capacity *= 2;
    ht->size = 0; // Reset size, insert() will increment it back
    ht->buckets = (struct Node**)calloc(ht->capacity, sizeof(struct Node*));

    // 2. Move existing nodes to new buckets
    for (int i = 0; i < oldCapacity; i++) {
        struct Node* current = oldBuckets[i];
        while (current != NULL) {
            struct Node* temp = current;
            insert(ht, current->key, current->value); // Re-insert into new array
            current = current->next;
            free(temp); // Free the old node wrapper (insert creates a new one)
        }
    }
    free(oldBuckets); // Free the old array pointer
    printf("[Success] Table Resized.\n");
}

// --- 4. CORE OPERATIONS ---

// INSERT (or Update if key exists)
void insert(struct HashTable* ht, int key, int value) {
    // 1. Check Load Factor
    float loadFactor = (float)ht->size / ht->capacity;
    if (loadFactor > LOAD_FACTOR_THRESHOLD) {
        rehash(ht);
    }

    int index = hashFunction(key, ht->capacity);
    struct Node* current = ht->buckets[index];

    // 2. Update if Key already exists
    while (current != NULL) {
        if (current->key == key) {
            current->value = value; // Update value
            printf(">> Updated Key %d with new Value %d.\n", key, value);
            return;
        }
        current = current->next;
    }

    // 3. Insert new Key (at head of chain)
    struct Node* newNode = createNode(key, value);
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
    ht->size++;
    printf(">> Inserted { %d : %d } at Index %d.\n", key, value, index);
}

// SEARCH: Returns value or -1 if not found
int search(struct HashTable* ht, int key) {
    int index = hashFunction(key, ht->capacity);
    struct Node* current = ht->buckets[index];

    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Not found indicator
}

// DELETE: Removes a key-value pair
void deleteKey(struct HashTable* ht, int key) {
    int index = hashFunction(key, ht->capacity);
    struct Node* current = ht->buckets[index];
    struct Node* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            // Case: Head of list
            if (prev == NULL) {
                ht->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->size--;
            printf(">> Key %d deleted successfully.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf(">> Key %d not found.\n", key);
}

// --- 5. VISUALIZATION ---

void display(struct HashTable* ht) {
    printf("\n--- Hash Table Snapshot ---\n");
    printf("Capacity: %d | Size: %d | Load Factor: %.2f\n", 
           ht->capacity, ht->size, (float)ht->size/ht->capacity);
    
    for (int i = 0; i < ht->capacity; i++) {
        if (ht->buckets[i] == NULL) continue; // Skip empty buckets for cleaner view

        printf("Index %d: ", i);
        struct Node* current = ht->buckets[i];
        while (current != NULL) {
            printf("[K:%d V:%d] -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("---------------------------\n");
}

void cleanUp(struct HashTable* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        struct Node* current = ht->buckets[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

// --- 6. MAIN DRIVER ---

int main() {
    struct HashTable* ht = createTable(INITIAL_CAPACITY);
    int choice, key, val, result;

    printf("=== MASTER HASH TABLE (Separate Chaining) ===\n");

    while (1) {
        printf("\n1. Insert (Key, Value)\n2. Search (Key)\n");
        printf("3. Delete (Key)\n4. Display Table\n5. Exit\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter Key (int): ");
                scanf("%d", &key);
                printf("Enter Value (int): ");
                scanf("%d", &val);
                insert(ht, key, val);
                break;
            case 2:
                printf("Enter Key to Search: ");
                scanf("%d", &key);
                result = search(ht, key);
                if (result != -1) printf("Found! Value: %d\n", result);
                else printf("Key not found.\n");
                break;
            case 3:
                printf("Enter Key to Delete: ");
                scanf("%d", &key);
                deleteKey(ht, key);
                break;
            case 4:
                display(ht);
                break;
            case 5:
                printf("Exiting...\n");
                cleanUp(ht);
                exit(0);
            default:
                printf("Invalid Choice\n");
        }
    }
    return 0;
}