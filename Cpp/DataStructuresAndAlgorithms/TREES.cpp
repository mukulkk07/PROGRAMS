#include <iostream>
#include <queue> // Required for Level Order Traversal
using namespace std;

// ==========================================
// 1. NODE DEFINITION
// ==========================================
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// ==========================================
// 2. BINARY SEARCH TREE (BST) CLASS
// ==========================================
class BST {
private:
    Node* root;

    // --- INTERNAL RECURSIVE HELPER FUNCTIONS ---
    // (We keep these private so the user doesn't have to deal with pointers)

    // Helper for Insertion
    Node* insertRec(Node* node, int val) {
        // Base Case: We found an empty spot! Create the node here.
        if (node == nullptr) {
            return new Node(val);
        }

        // Recursive Step: Decide to go Left or Right
        if (val < node->data) {
            node->left = insertRec(node->left, val); // Go Left
        } else if (val > node->data) {
            node->right = insertRec(node->right, val); // Go Right
        }
        // If val == node->data, we do nothing (no duplicates allowed)

        return node; // Return the unchanged node pointer
    }

    // Helper for Search
    bool searchRec(Node* node, int val) {
        // Base Case 1: Reached end of branch (Not found)
        if (node == nullptr) return false;
        
        // Base Case 2: Found it!
        if (node->data == val) return true;

        // Recursive Step
        if (val < node->data) {
            return searchRec(node->left, val);
        } else {
            return searchRec(node->right, val);
        }
    }

    // Helper to find the Minimum value (used in deletion)
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left; // Keep going left until you hit the wall
        }
        return node;
    }

    // Helper for Deletion
    Node* deleteRec(Node* node, int val) {
        // Base Case: Tree is empty or value not found
        if (node == nullptr) return node;

        // Step 1: Find the node to delete
        if (val < node->data) {
            node->left = deleteRec(node->left, val);
        } else if (val > node->data) {
            node->right = deleteRec(node->right, val);
        } else {
            // Step 2: We found the node! Now delete it.

            // Case A: No children (Leaf node)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case B: One child (Right only)
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Case C: One child (Left only)
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case D: Two children (The Tricky Part)
            else {
                // 1. Find the smallest value in the right subtree (Inorder Successor)
                Node* temp = findMin(node->right);

                // 2. Copy that value to the current node
                node->data = temp->data;

                // 3. Delete the duplicate node from the right subtree
                node->right = deleteRec(node->right, temp->data);
            }
        }
        return node;
    }

    // --- TRAVERSAL HELPERS ---

    // In-Order: Left -> Root -> Right (Result is Sorted!)
    void inorderRec(Node* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    // Pre-Order: Root -> Left -> Right (Good for copying trees)
    void preorderRec(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    // Post-Order: Left -> Right -> Root (Good for deleting trees)
    void postorderRec(Node* node) {
        if (node == nullptr) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

public:
    BST() { root = nullptr; }

    // --- PUBLIC INTERFACE ---

    void insert(int val) {
        root = insertRec(root, val);
        cout << "Inserted: " << val << endl;
    }

    bool search(int val) {
        return searchRec(root, val);
    }

    void deleteNode(int val) {
        root = deleteRec(root, val);
        cout << "Deleted: " << val << endl;
    }

    // --- TRAVERSALS ---

    void displayInOrder() {
        cout << "In-Order (Sorted): ";
        inorderRec(root);
        cout << endl;
    }

    void displayPreOrder() {
        cout << "Pre-Order: ";
        preorderRec(root);
        cout << endl;
    }

    void displayPostOrder() {
        cout << "Post-Order: ";
        postorderRec(root);
        cout << endl;
    }

    // Level Order (Breadth First Search) - Iterative approach using Queue
    void displayLevelOrder() {
        if (root == nullptr) return;
        cout << "Level-Order: ";
        
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        cout << endl;
    }
};

// ==========================================
// 3. MAIN EXECUTION
// ==========================================
int main() {
    BST tree;

    /* Constructing this Tree:
             50
           /    \
         30      70
        /  \    /  \
       20  40  60  80
    */

    cout << "--- Building Tree ---" << endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "\n--- Search ---" << endl;
    cout << "Is 40 in tree? " << (tree.search(40) ? "Yes" : "No") << endl;
    cout << "Is 90 in tree? " << (tree.search(90) ? "Yes" : "No") << endl;

    cout << "\n--- Traversals ---" << endl;
    tree.displayInOrder();   // 20 30 40 50 60 70 80
    tree.displayPreOrder();  // 50 30 20 40 70 60 80
    tree.displayPostOrder(); // 20 40 30 60 80 70 50
    tree.displayLevelOrder();// 50 30 70 20 40 60 80

    cout << "\n--- Deletion ---" << endl;
    // 1. Delete Leaf (20)
    tree.deleteNode(20);
    tree.displayInOrder();

    // 2. Delete Node with 1 Child (Let's pretend we had one, but here we delete 30 which has 1 child now that 20 is gone? No 30 has 40. Wait, 30 has child 40.)
    
    // 3. Delete Node with 2 Children (50 - The Root)
    // This will replace 50 with 60 (smallest in right subtree)
    tree.deleteNode(50);
    tree.displayInOrder(); // Should start with 60 now as root effectively

    return 0;
}