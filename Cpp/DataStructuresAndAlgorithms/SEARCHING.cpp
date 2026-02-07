#include <iostream>
#include <algorithm> // For std::sort
using namespace std;

// ==========================================
// 1. LINEAR SEARCH
// ==========================================
// Logic: Iterate through the array one by one.
// Time Complexity: O(n) - Slow for large datasets
int linearSearch(int arr[], int size, int target) {
    cout << "  [Linear Search] Scanning: ";
    
    for (int i = 0; i < size; i++) {
        // Visualize the scan
        cout << arr[i] << "... "; 
        
        if (arr[i] == target) {
            cout << "Found!" << endl;
            return i; // Return the index where found
        }
    }
    
    cout << "Not Found." << endl;
    return -1; // Standard error code for "not found"
}

// ==========================================
// 2. BINARY SEARCH (Iterative)
// ==========================================
// Logic: Keep splitting the search space in half.
// PRE-REQUISITE: Array MUST be sorted.
// Time Complexity: O(log n) - Extremely fast
int binarySearchIterative(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    cout << "  [Binary Search] Range: ";

    while (left <= right) {
        // Calculate middle index
        // We use l + (r-l)/2 to prevent Integer Overflow for huge arrays
        int mid = left + (right - left) / 2;

        cout << "[" << left << " to " << right << "] ";

        // Case 1: Match!
        if (arr[mid] == target) {
            return mid;
        }

        // Case 2: Target is greater, ignore left half
        if (arr[mid] < target) {
            left = mid + 1;
        }
        // Case 3: Target is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// ==========================================
// 3. BINARY SEARCH (Recursive)
// ==========================================
// Logic: Same as iterative, but using function calls
int binarySearchRecursive(int arr[], int left, int right, int target) {
    // Base Case: Range is invalid (Not found)
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    // Case 1: Match
    if (arr[mid] == target) {
        return mid;
    }

    // Case 2: Target is smaller -> Search left subarray
    if (arr[mid] > target) {
        return binarySearchRecursive(arr, left, mid - 1, target);
    }

    // Case 3: Target is larger -> Search right subarray
    return binarySearchRecursive(arr, mid + 1, right, target);
}

// ==========================================
// 4. MAIN EXECUTION
// ==========================================
int main() {
    // Dataset
    const int SIZE = 10;
    int data[SIZE] = {50, 10, 30, 80, 20, 90, 40, 70, 60, 100};
    int target = 70;

    cout << "--- 1. Linear Search (Unsorted Data) ---" << endl;
    // Linear search works on messy data
    int index = linearSearch(data, SIZE, target);
    cout << "Result: Found " << target << " at index " << index << "\n" << endl;


    cout << "--- 2. Binary Search (Requires Sorting) ---" << endl;
    // Step 1: Sort the array (Binary Search crashes on unsorted data)
    sort(data, data + SIZE);
    
    cout << "Sorted Data: [ ";
    for(int x : data) cout << x << " ";
    cout << "]" << endl;

    // Run Iterative
    cout << "Running Iterative Search for " << target << "..." << endl;
    index = binarySearchIterative(data, SIZE, target);
    cout << "\nResult: Found at index " << index << "\n" << endl;

    // Run Recursive
    cout << "Running Recursive Search for " << 25 << " (Not in list)..." << endl;
    index = binarySearchRecursive(data, 0, SIZE - 1, 25);
    if (index == -1) cout << "Result: Element not found." << endl;

    return 0;
}