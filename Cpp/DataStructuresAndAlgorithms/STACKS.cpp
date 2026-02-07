#include <iostream>
using namespace std;

// ==========================================
// 1. CONFIGURATION
// ==========================================
// We define a maximum size for our stack (Array limitation)
#define MAX_SIZE 100 

// ==========================================
// 2. STACK CLASS DEFINITION
// ==========================================
class Stack {
private:
    int arr[MAX_SIZE]; // The container holding our data
    int top;           // The index of the top-most element

public:
    // Constructor: Runs when we create "Stack s;"
    Stack() {
        // We initialize top to -1.
        // Why? Because array indices start at 0.
        // -1 means "The stack is empty, pointing to nothing."
        top = -1; 
    }

    // --- CORE OPERATIONS ---

    // 1. PUSH: Add an element to the top
    void push(int val) {
        // Step 1: Check for Overflow (Is the stack full?)
        if (top >= MAX_SIZE - 1) {
            cout << "Stack Overflow! Cannot push " << val << endl;
            return;
        }

        // Step 2: Increment 'top' to the next empty slot
        top++;

        // Step 3: Insert the value
        arr[top] = val;
        
        cout << "Pushed: " << val << endl;
    }

    // 2. POP: Remove the top element
    void pop() {
        // Step 1: Check for Underflow (Is the stack empty?)
        if (top < 0) {
            cout << "Stack Underflow! Cannot pop." << endl;
            return;
        }

        // Step 2: Capture the value (optional, just for display)
        int poppedValue = arr[top];

        // Step 3: Decrement 'top'. 
        // We don't actually delete the data from memory; we just "forget" it exists
        // by moving the pointer down. The next push will overwrite it.
        top--;
        
        cout << "Popped: " << poppedValue << endl;
    }

    // 3. PEEK (or TOP): Look at the top element without removing it
    int peek() {
        if (top < 0) {
            cout << "Stack is Empty." << endl;
            return -1; // Return error code
        }
        return arr[top];
    }

    // --- UTILITY OPERATIONS ---

    // 4. Check if empty
    bool isEmpty() {
        // If top is -1, we have no elements
        return (top == -1);
    }

    // 5. Check if full
    bool isFull() {
        // If top is at the last index
        return (top == MAX_SIZE - 1);
    }

    // 6. Size of stack
    int size() {
        // Since indices are 0-based, count is top + 1
        return top + 1;
    }

    // 7. Display all elements (Just for visualization)
    void display() {
        if (top < 0) {
            cout << "Stack is Empty" << endl;
            return;
        }
        cout << "Stack State: [ ";
        // We print from 0 up to Top
        for(int i = 0; i <= top; i++) {
            cout << arr[i] << " ";
        }
        cout << "] <-- TOP" << endl;
    }
};

// ==========================================
// 3. MAIN EXECUTION
// ==========================================
int main() {
    Stack s;

    cout << "--- Pushing Elements ---" << endl;
    s.push(10); // Bottom of stack
    s.push(20);
    s.push(30); // Top of stack
    
    s.display(); // [ 10 20 30 ] <-- TOP

    cout << "\n--- Peeking ---" << endl;
    cout << "Top element is: " << s.peek() << endl; // Should be 30

    cout << "\n--- Popping Elements ---" << endl;
    s.pop();     // Removes 30
    s.display(); // [ 10 20 ] <-- TOP

    s.pop();     // Removes 20
    s.display(); // [ 10 ] <-- TOP

    cout << "\n--- Checking Empty ---" << endl;
    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    s.pop();     // Removes 10. Stack is now empty.
    s.pop();     // Tries to remove from empty stack (Underflow)

    return 0;
}