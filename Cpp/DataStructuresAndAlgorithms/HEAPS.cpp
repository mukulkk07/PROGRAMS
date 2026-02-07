#include <iostream>
#include <vector>
#include <algorithm> // For std::swap

using namespace std;

// ==========================================
// HEAP CLASS DEFINITION
// ==========================================
class MinHeap {
private:
    // We use a vector (dynamic array) to store the heap elements.
    // Index 0 is the root.
    // For any node at index 'i':
    // - Left Child:  2*i + 1
    // - Right Child: 2*i + 2
    // - Parent:      (i - 1) / 2
    vector<int> heap;

    // --- HELPER FUNCTIONS (Internal logic) ---

    // 1. Get Parent Index
    int parent(int i) { return (i - 1) / 2; }

    // 2. Get Left Child Index
    int left(int i) { return (2 * i + 1); }

    // 3. Get Right Child Index
    int right(int i) { return (2 * i + 2); }

    // 4. Heapify Up (Used during Insertion)
    // Moves a node UP the tree until the Heap Property is restored.
    void heapifyUp(int i) {
        // While we are not at the root AND the current node is smaller than its parent
        while (i > 0 && heap[i] < heap[parent(i)]) {
            
            // Logic: A child cannot be smaller than its parent in a Min-Heap.
            // Action: Swap them!
            swap(heap[i], heap[parent(i)]);
            
            // Move our tracker 'i' up to the parent's position to check again
            i = parent(i);
        }
    }

    // 5. Heapify Down (Used during Deletion)
    // Moves a node DOWN the tree until the Heap Property is restored.
    void heapifyDown(int i) {
        int smallest = i;       // Assume current node is the smallest
        int l = left(i);        // Index of left child
        int r = right(i);       // Index of right child
        int n = heap.size();    // Total elements

        // Check if Left Child exists AND is smaller than current 'smallest'
        if (l < n && heap[l] < heap[smallest]) {
            smallest = l;
        }

        // Check if Right Child exists AND is smaller than current 'smallest'
        if (r < n && heap[r] < heap[smallest]) {
            smallest = r;
        }

        // If the current node 'i' is NOT the smallest anymore
        // (meaning one of its children was smaller)
        if (smallest != i) {
            // Swap current node with the smaller child
            swap(heap[i], heap[smallest]);

            // Recursively call heapifyDown on the child's new position
            // to ensure the subtree is also correct.
            heapifyDown(smallest);
        }
    }

public:
    // --- CORE OPERATIONS ---

    // 1. Insert: Adds a new element to the heap
    void insert(int key) {
        // Step 1: Add the new element to the very end of the array (Leaf node)
        heap.push_back(key);

        // Step 2: The new element might break the heap property (it might be too small).
        // So we bubble it UP to its correct spot.
        int index = heap.size() - 1;
        heapifyUp(index);

        cout << "Inserted: " << key << endl;
    }

    // 2. Extract Min: Removes and returns the root (smallest element)
    int extractMin() {
        if (heap.size() == 0) {
            cout << "Heap is empty!" << endl;
            return -1;
        }

        // Step 1: Capture the root (the minimum value)
        int root = heap[0];

        // Step 2: Replace the root with the very last element in the array.
        // We do this to maintain the "Complete Binary Tree" structure (no gaps).
        heap[0] = heap.back();
        heap.pop_back(); // Remove the duplicate last element

        // Step 3: The new root is likely too big. Bubble it DOWN to fix the order.
        if (!heap.empty()) {
            heapifyDown(0);
        }

        return root;
    }

    // 3. Get Min: Just looks at the root without removing it
    int getMin() {
        if (heap.size() == 0) return -1;
        return heap[0];
    }

    // 4. Display: Prints the array representation
    void printHeap() {
        cout << "Heap Array: [ ";
        for (int i : heap) {
            cout << i << " ";
        }
        cout << "]" << endl;
    }
};

// ==========================================
// MAIN EXECUTION
// ==========================================
int main() {
    MinHeap h;

    cout << "--- Building the Heap ---" << endl;
    // We insert numbers in random order. 
    // The heap will automatically arrange them so the smallest is always at the top.
    h.insert(10);
    h.insert(5);  // 5 is smaller, so it will bubble up to become root
    h.insert(3);  // 3 is smaller than 5, so it bubbles up to become new root
    h.insert(2);  // 2 becomes the new root
    h.insert(8);
    h.insert(15);

    /* Visualizing the Tree structure internally:
              2
            /   \
           3     5
          / \   /
         10  8 15
    */

    h.printHeap();
    cout << "Current Minimum (Root): " << h.getMin() << endl;

    cout << "\n--- extracting Elements ---" << endl;
    
    // Extracting the root (2)
    cout << "Extracted: " << h.extractMin() << endl;
    h.printHeap(); // Root should now be 3 (the next smallest)

    // Extracting the root (3)
    cout << "Extracted: " << h.extractMin() << endl;
    h.printHeap(); // Root should now be 5

    return 0;
}