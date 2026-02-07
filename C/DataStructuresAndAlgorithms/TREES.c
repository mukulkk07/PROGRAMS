#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- 1. DATA STRUCTURE DEFINITIONS ---

// Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Queue Node (For Level Order Traversal)
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

// Queue Structure
struct Queue {
    struct QueueNode *front, *rear;
};

// --- 2. QUEUE HELPER FUNCTIONS (For BFS) ---

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, struct Node* tNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = tNode;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

struct Node* dequeue(struct Queue* q) {
    if (q->front == NULL) return NULL;
    struct QueueNode* temp = q->front;
    struct Node* tNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return tNode;
}

bool isQueueEmpty(struct Queue* q) {
    return (q->front == NULL);
}

// --- 3. CORE TREE OPERATIONS ---

// Create a new Tree Node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory Error\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// INSERT (Recursive)
// Time Complexity: O(log n) avg, O(n) worst
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Duplicate value %d ignored.\n", value);
    }
    return root;
}

// SEARCH
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    
    if (key < root->data)
        return search(root->left, key);
    
    return search(root->right, key);
}

// FIND MIN (Helper for Delete)
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// FIND MAX
struct Node* findMax(struct Node* root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) root = root->right;
    return root;
}

// DELETE (Handles 3 cases: Leaf, One Child, Two Children)
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    // 1. Navigate to the node
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node found. 
        // Case 1: No child (Leaf) or One child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Two children
        // Get the Inorder Successor (smallest in the right subtree)
        struct Node* temp = findMin(root->right);

        // Copy the successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// --- 4. TRAVERSAL ALGORITHMS ---

// DFS: Pre-order (Root -> Left -> Right)
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// DFS: In-order (Left -> Root -> Right) - Always Sorted for BST
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// DFS: Post-order (Left -> Right -> Root)
void postOrder(struct Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// BFS: Level Order (Breadth First Search)
void levelOrder(struct Node* root) {
    if (root == NULL) return;
    struct Queue* q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        struct Node* current = dequeue(q);
        printf("%d ", current->data);

        if (current->left != NULL) enqueue(q, current->left);
        if (current->right != NULL) enqueue(q, current->right);
    }
    free(q); // Free queue shell
}

// --- 5. TREE ANALYTICS & ADVANCED ALGORITHMS ---

// Height of Tree (Longest path from root to leaf)
int getHeight(struct Node* root) {
    if (root == NULL) return -1; // -1 for edges, 0 for nodes logic
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

// Count Total Nodes
int countNodes(struct Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Algorithm: Mirror/Invert the Tree
void mirrorTree(struct Node* root) {
    if (root == NULL) return;
    
    // Swap left and right pointers
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recurse
    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Clean up memory
void destroyTree(struct Node* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

// --- 6. MAIN INTERFACE ---

int main() {
    struct Node* root = NULL;
    int choice, val;
    struct Node* searchRes;

    printf("=== MASTER BINARY SEARCH TREE (BST) PROGRAM ===\n");

    while (1) {
        printf("\n--- Tree Operations Menu ---\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Find Min & Max\n");
        printf("5. In-Order Traversal (Sorted)\n");
        printf("6. Pre-Order Traversal\n");
        printf("7. Post-Order Traversal\n");
        printf("8. Level-Order Traversal (BFS)\n");
        printf("9. Tree Height\n");
        printf("10. Count Nodes\n");
        printf("11. Mirror/Invert Tree\n");
        printf("0. Exit\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                printf("Inserted %d.\n", val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                printf("Deletion process complete for %d.\n", val);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                searchRes = search(root, val);
                if (searchRes) printf("Found %d in the tree.\n", searchRes->data);
                else printf("%d not found.\n", val);
                break;
            case 4:
                if (root) {
                    printf("Min: %d\n", findMin(root)->data);
                    printf("Max: %d\n", findMax(root)->data);
                } else printf("Tree is empty.\n");
                break;
            case 5:
                printf("In-Order: [ ");
                inOrder(root);
                printf("]\n");
                break;
            case 6:
                printf("Pre-Order: [ ");
                preOrder(root);
                printf("]\n");
                break;
            case 7:
                printf("Post-Order: [ ");
                postOrder(root);
                printf("]\n");
                break;
            case 8:
                printf("Level-Order: [ ");
                levelOrder(root);
                printf("]\n");
                break;
            case 9:
                printf("Height of Tree: %d\n", getHeight(root));
                break;
            case 10:
                printf("Total Nodes: %d\n", countNodes(root));
                break;
            case 11:
                printf("Inverting Tree...\n");
                mirrorTree(root);
                printf("Tree Inverted. Run Traversal to see changes.\n");
                break;
            case 0:
                printf("Exiting... clearing memory.\n");
                destroyTree(root);
                exit(0);
            default:
                printf("Invalid Choice.\n");
        }
    }
    return 0;
}