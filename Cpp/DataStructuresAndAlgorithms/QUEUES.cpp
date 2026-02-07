#include <iostream>
using namespace std;

// ==========================================
// 1. CONFIGURATION
// ==========================================
#define MAX_SIZE 5 // Small size to easily demonstrate "Full" state

// ==========================================
// 2. QUEUE CLASS DEFINITION
// ==========================================
class Queue {
private:
    int arr[MAX_SIZE];
    int front; // Points to the element at the front (to be removed next)
    int rear;  // Points to the last element added
    int count; // Keeps track of how many items are currently in the queue

public:
    // Constructor
    Queue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    // --- CORE OPERATIONS ---

    // 1. ENQUEUE: Add an item to the BACK of the line
    void enqueue(int val) {
        // Step 1: Check if the line is full
        if (isFull()) {
            cout << "Queue Overflow! Cannot enqueue " << val << endl;
            return;
        }

        // Step 2: Move 'rear' forward.
        // The Modulo operator (%) makes it "Circular".
        // If rear is at index 4 and size is 5: (4 + 1) % 5 = 0.
        // It wraps around to the beginning!
        rear = (rear + 1) % MAX_SIZE;

        // Step 3: Insert the value
        arr[rear] = val;
        
        // Step 4: Increase count
        count++;

        cout << "Enqueued: " << val << endl;
    }

    // 2. DEQUEUE: Remove the item from the FRONT of the line
    void dequeue() {
        // Step 1: Check if the line is empty
        if (isEmpty()) {
            cout << "Queue Underflow! Cannot dequeue." << endl;
            return;
        }

        // Step 2: Capture the value (just to show user)
        int removedVal = arr[front];

        // Step 3: Move 'front' forward.
        // Again, we use Modulo (%) to wrap around if needed.
        front = (front + 1) % MAX_SIZE;

        // Step 4: Decrease count
        count--;

        cout << "Dequeued: " << removedVal << endl;
    }

    // 3. PEEK: Look at who is at the front
    int peek() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        return arr[front];
    }

    // --- UTILITY OPERATIONS ---

    bool isEmpty() {
        return (count == 0);
    }

    bool isFull() {
        return (count == MAX_SIZE);
    }

    int size() {
        return count;
    }

    // 4. Display the queue (Visualizing the line)
    void display() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }

        cout << "Queue State: [ ";
        
        // We have to iterate 'count' times, starting from 'front'
        for (int i = 0; i < count; i++) {
            // Calculate actual index using modulo
            int index = (front + i) % MAX_SIZE; 
            cout << arr[index] << " ";
        }
        
        cout << "]" << endl;
    }
};

// ==========================================
// 3. MAIN EXECUTION
// ==========================================
int main() {
    Queue q;

    // 1. Fill the Queue
    cout << "--- Enqueuing ---" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50); // Queue is now FULL (size 5)
    q.display();   // [ 10 20 30 40 50 ]

    // 2. Try to add to a full queue
    q.enqueue(60); // Should fail (Overflow)

    // 3. Serve some people (Dequeue)
    cout << "\n--- Dequeuing ---" << endl;
    q.dequeue(); // Removes 10 (Front)
    q.dequeue(); // Removes 20
    q.display(); // [ 30 40 50 ]

    // 4. Circular Logic Test
    // Even though the array technically has space at index 0 and 1 now,
    // a normal queue would say "Full" because rear is at the end.
    // But our CIRCULAR logic will wrap around and use the freed space.
    cout << "\n--- Testing Circular Logic ---" << endl;
    q.enqueue(60); // Successfully wraps to index 0
    q.enqueue(70); // Successfully wraps to index 1
    q.display();   // [ 30 40 50 60 70 ]

    return 0;
}