#include <iostream>
using namespace std;

class BinaryTree {
private:
    // 1. Internal Node Structure
    // Defined inside the class to keep it hidden/encapsulated
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

    Node* root;

    // --- Private Recursive Helper Functions ---
    // These do the actual work but are hidden from the user.

    // Recursive Insert for BST logic
    Node* insertHelper(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insertHelper(node->left, val);
        } else {
            node->right = insertHelper(node->right, val);
        }
        return node;
    }

    // Preorder: Root -> Left -> Right
    void printPreorderHelper(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        printPreorderHelper(node->left);
        printPreorderHelper(node->right);
    }

    // Inorder: Left -> Root -> Right
    void printInorderHelper(Node* node) {
        if (node == nullptr) return;
        printInorderHelper(node->left);
        cout << node->data << " ";
        printInorderHelper(node->right);
    }

    // Postorder: Left -> Right -> Root
    void printPostorderHelper(Node* node) {
        if (node == nullptr) return;
        printPostorderHelper(node->left);
        printPostorderHelper(node->right);
        cout << node->data << " ";
    }

    // Helper to delete nodes (destructor)
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    // Constructor
    BinaryTree() {
        root = nullptr;
    }

    // Destructor (to prevent memory leaks)
    ~BinaryTree() {
        destroyTree(root);
    }

    // --- Public Interface Functions ---
    // These allow the outside world to interact with the tree.

    void insert(int val) {
        root = insertHelper(root, val);
    }

    void displayPreorder() {
        cout << "Preorder:  ";
        printPreorderHelper(root);
        cout << endl;
    }

    void displayInorder() {
        cout << "Inorder:   ";
        printInorderHelper(root);
        cout << endl;
    }

    void displayPostorder() {
        cout << "Postorder: ";
        printPostorderHelper(root);
        cout << endl;
    }
};

// --- Main Menu Driver ---
int main() {
    BinaryTree tree;
    int choice, val;

    cout << "=== Binary Search Tree Master Program ===\n";
    cout << "1. Insert Node\n";
    cout << "2. Display Preorder\n";
    cout << "3. Display Inorder\n";
    cout << "4. Display Postorder\n";
    cout << "5. Display All\n";
    cout << "0. Exit\n";

    do {
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            case 2:
                tree.displayPreorder();
                break;
            case 3:
                tree.displayInorder();
                break;
            case 4:
                tree.displayPostorder();
                break;
            case 5:
                tree.displayPreorder();
                tree.displayInorder();
                tree.displayPostorder();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}