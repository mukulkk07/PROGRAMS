#include <iostream>
using namespace std;

// ==========================================
// 1. POINTER BASICS WITH ARRAYS
// ==========================================

// Function to print array using ONLY POINTER ARITHMETIC
// We pass 'int* ptr' because arrays decay into pointers when passed to functions.
void printUsingPointers(int* ptr, int size) {
    cout << "Array Content: [ ";
    for (int i = 0; i < size; i++) {
        // EXPLANATION:
        // 1. 'ptr' is the memory address of the first element.
        // 2. '(ptr + i)' calculates the address of the i-th element.
        //    (It automatically jumps 4 bytes per integer).
        // 3. '*' is the dereference operator. It gets the VALUE at that address.
        cout << *(ptr + i) << " "; 
    }
    cout << "]" << endl;
}

// Function to modify array values by moving the pointer
void modifyValues(int* ptr, int size) {
    // We can traverse by physically moving the pointer variable
    for (int i = 0; i < size; i++) {
        // Add 10 to the value at the current address
        *ptr = *ptr + 10; 
        
        // Move the pointer to the next memory slot
        ptr++; 
    }
    cout << "Values increased by 10 directly in memory." << endl;
}

// ==========================================
// 2. ADVANCED POINTER MANIPULATION
// ==========================================

// Helper to swap two values using pointers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Reverse an array using the "Two Pointer Technique"
// We pass pointers to the specific start and end memory addresses
void reverseArray(int* startPtr, int* endPtr) {
    // Loop until the pointers meet in the middle
    while (startPtr < endPtr) {
        // Swap the values at these two addresses
        swap(startPtr, endPtr);

        // Move start pointer forward
        startPtr++; 
        
        // Move end pointer backward
        endPtr--;   
    }
    cout << "Array reversed using pointer logic." << endl;
}

// ==========================================
// 3. MAIN EXECUTION
// ==========================================
int main() {
    // Define a standard array
    const int SIZE = 5;
    int arr[SIZE] = {10, 20, 30, 40, 50};

    // --- PART 1: UNDERSTANDING ADDRESSES ---
    cout << "--- Memory Inspection ---" << endl;
    // The name of the array IS the address of the first element
    cout << "Value of 'arr':          " << arr << endl;       
    cout << "Address of '&arr[0]':    " << &arr[0] << endl;   
    
    // Pointer Arithmetic proof
    // Note: Addresses will differ by 4 bytes (size of int)
    cout << "Address of index 0:      " << (arr) << endl;
    cout << "Address of index 1:      " << (arr + 1) << endl; 
    
    // --- PART 2: ACCESSING DATA ---
    cout << "\n--- Accessing Data ---" << endl;
    // Standard way
    cout << "Using arr[2]:            " << arr[2] << endl;
    
    // Pointer way (Dereferencing)
    cout << "Using *(arr + 2):        " << *(arr + 2) << endl;

    // CRAZY C++ FACT:
    // Since arr[i] == *(arr + i), and addition is commutative...
    // i[arr] == *(i + arr)
    cout << "Using 2[arr] (Weird!):   " << 2[arr] << endl;

    // --- PART 3: MANIPULATION ---
    cout << "\n--- Manipulation ---" << endl;
    printUsingPointers(arr, SIZE);
    
    modifyValues(arr, SIZE); // Adds 10 to everyone
    printUsingPointers(arr, SIZE); // [ 20 30 40 50 60 ]

    // --- PART 4: TWO POINTER REVERSAL ---
    cout << "\n--- Reversing ---" << endl;
    // We pass:
    // 1. The address of the start (arr)
    // 2. The address of the end (arr + 4)
    reverseArray(arr, arr + SIZE - 1);
    
    printUsingPointers(arr, SIZE); // [ 60 50 40 30 20 ]

    // --- PART 5: DYNAMIC ARRAYS (HEAP) ---
    cout << "\n--- Dynamic Memory (Heap) ---" << endl;
    // Creating an array manually on the heap
    int* heapArr = new int[3];
    
    // Setting values using pointer arithmetic
    *heapArr = 100;       // Index 0
    *(heapArr + 1) = 200; // Index 1
    *(heapArr + 2) = 300; // Index 2
    
    cout << "Heap Array: " << *heapArr << ", " << *(heapArr+1) << ", " << *(heapArr+2) << endl;

    // Always clean up heap memory!
    delete[] heapArr; 

    return 0;
}