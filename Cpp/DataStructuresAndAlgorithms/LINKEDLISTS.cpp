#include <iostream>
using namespace std;

// ==========================================
// 1. NODE DEFINITION
// ==========================================
// A Linked List is made of "Nodes".
// Each Node contains two things: data and a pointer to the next Node.
struct Node {
    int data;       // The actual value (e.g., 10, 20)
    Node* next;     // The pointer that connects this node to the next one

    // Constructor: This runs automatically when we create a "new Node(val)"
    Node(int val) {
        data = val;
        next = nullptr; // By default, a new node points to nothing (NULL)
    }
};

// ==========================================
// 2. LINKED LIST CLASS
// ==========================================
// This class manages the chain of nodes. It keeps track of the 'head'.
class LinkedList {
private:
    Node* head; // The entry point. If we lose 'head', we lose the whole list.

public:
    // Constructor: Runs when we write "LinkedList list;"
    LinkedList() {
        head = nullptr; // The list starts empty
    }

    // --- INSERTION OPERATIONS ---

    // Scenario: Add a new value to the VERY START of the list.
    void insertAtHead(int val) {
        // Step 1: Create a new node in memory
        Node* newNode = new Node(val);

        // Step 2: Point the new node's 'next' to the current head
        // (If list is 5->NULL, newNode becomes 10->5->NULL)
        newNode->next = head;

        // Step 3: Update the 'head' pointer to point to this new node
        // Now, the list starts at our new node.
        head = newNode;
        
        cout << "Inserted " << val << " at head." << endl;
    }

    // Scenario: Add a new value to the VERY END of the list.
    void insertAtTail(int val) {
        // Step 1: Create the new node
        Node* newNode = new Node(val);

        // Edge Case: If the list is empty, the new node becomes the head
        if (head == nullptr) {
            head = newNode;
            return;
        }

        // Step 2: We need to find the last node.
        // We cannot move 'head' because we will lose the list.
        // So, we make a temporary pointer called 'temp' that starts at 'head'.
        Node* temp = head;

        // Step 3: Traverse the list until we find the last node.
        // The last node is the one where 'next' is NULL.
        while (temp->next != nullptr) {
            temp = temp->next; // Move temp to the next node
        }

        // Step 4: Link the last node to our new node
        temp->next = newNode;
        
        cout << "Inserted " << val << " at tail." << endl;
    }

    // --- DELETION OPERATIONS ---

    // Scenario: Remove the FIRST node.
    void deleteHead() {
        // Edge Case: Can't delete if list is empty
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        // Step 1: Save the current head in a temporary pointer
        // We do this so we can 'delete' its memory later.
        Node* toDelete = head;

        // Step 2: Move the head pointer to the second node
        head = head->next;

        // Step 3: Free the memory of the old head
        delete toDelete;
        
        cout << "Deleted head node." << endl;
    }

    // Scenario: Remove a node with a SPECIFIC VALUE (e.g., delete 15).
    void deleteValue(int val) {
        // Edge Case: Empty list
        if (head == nullptr) return;

        // Special Case: If the value we want to delete is at the HEAD
        if (head->data == val) {
            deleteHead(); // Re-use our logic from above
            return;
        }

        // Step 1: Create a temp pointer to traverse
        Node* temp = head;

        // Step 2: Traverse to find the node JUST BEFORE the one we want to delete.
        // We check 'temp->next->data' because we need to stop one step early.
        while (temp->next != nullptr && temp->next->data != val) {
            temp = temp->next;
        }

        // If we reached the end and didn't find the value
        if (temp->next == nullptr) {
            cout << "Value " << val << " not found." << endl;
            return;
        }

        // Step 3: Found it! 'temp' is the node BEFORE. 'toDelete' is the target.
        Node* toDelete = temp->next;

        // Step 4: Bypass the node we are deleting.
        // Link the node BEFORE (temp) to the node AFTER (temp->next->next).
        temp->next = temp->next->next;

        // Step 5: Free the memory
        delete toDelete;
        
        cout << "Deleted value " << val << "." << endl;
    }

    // --- REVERSE OPERATION (The Tricky One) ---

    void reverse() {
        // We need 3 pointers to perform a swap
        Node* prev = nullptr;   // Will track the node behind us
        Node* current = head;   // The node we are currently flipping
        Node* next = nullptr;   // Will store the next node so we don't lose the rest of the list

        while (current != nullptr) {
            // 1. Save the next node (because we are about to break the link)
            next = current->next;

            // 2. Reverse the pointer! Point 'current' backwards to 'prev'
            current->next = prev;

            // 3. Advance the pointers one step forward
            prev = current;     // 'prev' moves to where 'current' was
            current = next;     // 'current' moves to where 'next' was
        }

        // 4. Update head. 'prev' is now sitting at the new front of the list.
        head = prev;
        cout << "List reversed." << endl;
    }

    // --- DISPLAY ---
    void display() {
        Node* temp = head;
        cout << "List: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// ==========================================
// 3. MAIN EXECUTION
// ==========================================
int main() {
    // Create the list object
    LinkedList list;

    // 1. Add 10. List: 10 -> NULL
    list.insertAtHead(10);
    
    // 2. Add 5 at head. List: 5 -> 10 -> NULL
    list.insertAtHead(5);
    
    // 3. Add 20 at tail. List: 5 -> 10 -> 20 -> NULL
    list.insertAtTail(20);
    
    // Show current state
    list.display(); 

    // 4. Delete the 5 (Head). List: 10 -> 20 -> NULL
    list.deleteHead();
    list.display();

    // 5. Reverse list. List: 20 -> 10 -> NULL
    list.reverse();
    list.display();

    return 0;
}