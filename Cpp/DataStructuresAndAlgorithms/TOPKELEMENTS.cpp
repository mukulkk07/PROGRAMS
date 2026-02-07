#include <iostream>
#include <vector>
#include <algorithm> // For sort
#include <queue>     // For priority_queue (Heap)

using namespace std;

// ==========================================
// 1. NAIVE APPROACH: SORTING
// ==========================================
// Logic: Sort the entire array and take the last K elements.
// Time Complexity: O(N log N) - Slow for huge datasets
void topKSorting(vector<int> arr, int k) {
    cout << "--- Approach 1: Sorting (Naive) ---" << endl;
    
    // Step 1: Sort the entire vector (Descending order)
    sort(arr.begin(), arr.end(), greater<int>());

    // Step 2: Print the first K elements
    cout << "Top " << k << " elements: ";
    for (int i = 0; i < k; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ==========================================
// 2. OPTIMIZED APPROACH: MIN-HEAP
// ==========================================
// Logic: Maintain a "VIP Lounge" (Heap) of size K. 
// Only let new elements in if they are bigger than the "poorest" VIP member.
// Time Complexity: O(N log K) - Much faster when K is small compared to N.
void topKHeap(const vector<int>& arr, int k) {
    cout << "\n--- Approach 2: Min-Heap (Optimized) ---" << endl;

    // A standard priority_queue is a Max-Heap.
    // We need a MIN-HEAP to easily access the smallest of the top K elements.
    // Syntax: priority_queue<Type, Container, Comparator>
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Step 1: Iterate through the data
    for (int val : arr) {
        
        // Case A: Heap is not full yet? Just add it.
        if (minHeap.size() < k) {
            minHeap.push(val);
        }
        // Case B: Heap is full. Challenge the gatekeeper (Root).
        else {
            // If the new value is larger than the smallest element in the heap...
            if (val > minHeap.top()) {
                minHeap.pop();  // Remove the smallest (kick it out)
                minHeap.push(val); // Add the new giant
            }
            // Else: The new value is too small, ignore it.
        }
    }

    // Step 2: Display results
    // Note: The heap is not sorted, it just guarantees access to the smallest.
    // We empty the heap to print them.
    cout << "Top " << k << " elements (in increasing order): ";
    
    // Helper vector to store them for display
    vector<int> result;
    while(!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    // Print
    for(int x : result) cout << x << " ";
    cout << endl;
}

// ==========================================
// MAIN EXECUTION
// ==========================================
int main() {
    // Dataset: 10 elements
    vector<int> data = {10, 50, 20, 80, 60, 30, 90, 40, 100, 70};
    int K = 3; // We want the Top 3 Largest

    cout << "Data Set: { ";
    for(int x : data) cout << x << " ";
    cout << "}\n" << endl;

    // Run Naive
    topKSorting(data, K);

    // Run Efficient
    topKHeap(data, K);

    return 0;
}