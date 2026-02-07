/**
 * COMPLEX VECTOR MASTERCLASS IN C++
 * ---------------------------------
 * This program demonstrates the full capabilities of the std::vector container.
 * * Topics Covered:
 * 1. Initialization methods
 * 2. Element Access (Safe vs Unsafe)
 * 3. Iterators and Traversal
 * 4. Capacity vs Size (Memory Management)
 * 5. Modifiers (Insert, Erase, Swap, Resize)
 * 6. Emplace vs Push_back (Optimization)
 * 7. 2D Vectors (Matrix)
 * 8. Storing Custom Objects
 * 9. Exception Handling
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for sort, find
#include <iomanip>   // for formatting output

// --- Helper Utility to Print Vectors ---
template <typename T>
void printVector(const std::vector<T>& v, const std::string& label) {
    std::cout << "[ " << std::left << std::setw(20) << label << " ] Content: { ";
    for (const auto& item : v) {
        std::cout << item << " ";
    }
    std::cout << "}\n";
}

// --- Helper to visualize capacity vs size ---
void printStats(const std::vector<int>& v) {
    std::cout << "   -> Size: " << v.size() 
              << " | Capacity: " << v.capacity() 
              << " | Address of Data: " << v.data() << "\n";
}

// ==========================================
// 1. INITIALIZATION TECHNIQUES
// ==========================================
void demonstrateInitialization() {
    std::cout << "\n=== 1. Initialization Techniques ===\n";

    // A. Default constructor (empty)
    std::vector<int> v1; 
    printVector(v1, "Default");

    // B. Fill constructor (size, value) -> 5 integers, all 10
    std::vector<int> v2(5, 10);
    printVector(v2, "Fill (5, 10)");

    // C. Initializer list (C++11)
    std::vector<int> v3 = {1, 2, 3, 4, 5};
    printVector(v3, "Initializer List");

    // D. Copy constructor
    std::vector<int> v4(v3);
    printVector(v4, "Copy of v3");

    // E. Range constructor (Iterator based)
    // Copies elements from v3.begin() up to (but not including) v3.begin() + 3
    std::vector<int> v5(v3.begin(), v3.begin() + 3);
    printVector(v5, "Range (Slice v3)");
}

// ==========================================
// 2. ELEMENT ACCESS
// ==========================================
void demonstrateAccess() {
    std::cout << "\n=== 2. Element Access ===\n";
    std::vector<int> v = {10, 20, 30, 40, 50};

    // A. Operator [] - No bounds checking (Fast but risky)
    std::cout << "v[1] (Unchecked): " << v[1] << "\n";

    // B. at() - Bounds checking (Safe, throws std::out_of_range)
    try {
        std::cout << "v.at(2) (Checked):  " << v.at(2) << "\n";
        // Intentional Error
        std::cout << v.at(100); 
    } catch (const std::out_of_range& e) {
        std::cout << "   [Exception Caught]: " << e.what() << "\n";
    }

    // C. Front and Back
    std::cout << "v.front(): " << v.front() << "\n";
    std::cout << "v.back():  " << v.back() << "\n";

    // D. Direct Data Access (Pointer to array)
    int* ptr = v.data();
    std::cout << "*(v.data() + 1): " << *(ptr + 1) << " (Pointer arithmetic)\n";
}

// ==========================================
// 3. CAPACITY AND MEMORY MANAGEMENT
// ==========================================
void demonstrateCapacity() {
    std::cout << "\n=== 3. Capacity vs Size ===\n";
    std::cout << "NOTE: Vectors double their capacity when full (implementation dependent).\n";

    std::vector<int> v;
    // reserve() allocates memory in advance to avoid reallocations
    v.reserve(10); 
    printStats(v);

    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    std::cout << "After pushing 5 elements:\n";
    printStats(v);

    // shrink_to_fit() releases unused memory (C++11)
    v.shrink_to_fit();
    std::cout << "After shrink_to_fit():\n";
    printStats(v);
    
    // Check if empty
    std::cout << "Is empty? " << (v.empty() ? "Yes" : "No") << "\n";
}

// ==========================================
// 4. MODIFIERS & ITERATORS
// ==========================================
void demonstrateModifiers() {
    std::cout << "\n=== 4. Modifiers & Iterators ===\n";
    std::vector<int> v = {1, 2, 3};

    // Push_back
    v.push_back(4);
    
    // Insert: requires an iterator. Insert 99 at the beginning.
    v.insert(v.begin(), 99);
    printVector(v, "Insert 99 at begin");

    // Erase: requires an iterator. Erase the second element.
    v.erase(v.begin() + 1);
    printVector(v, "Erase index 1");

    // Pop_back: removes last element
    v.pop_back();
    printVector(v, "Pop back");

    // Resize: Changes size. If larger, fills with default or specified value.
    v.resize(6, 0); // Size becomes 6, new spots filled with 0
    printVector(v, "Resize to 6");

    // Clear: Removes all elements, capacity remains
    v.clear();
    printStats(v);
}

// ==========================================
// 5. ADVANCED: CUSTOM OBJECTS & EMPLACE
// ==========================================

struct Robot {
    int id;
    std::string name;

    // Constructor
    Robot(int i, std::string n) : id(i), name(n) {
        std::cout << "  (Robot " << id << " Constructed)\n";
    }
    // Copy Constructor
    Robot(const Robot& other) : id(other.id), name(other.name) {
        std::cout << "  (Robot " << id << " Copied)\n";
    }
};

void demonstrateEmplace() {
    std::cout << "\n=== 5. Emplace_back vs Push_back ===\n";
    std::vector<Robot> bots;
    bots.reserve(3); // Reserve to avoid reallocation noise in output

    std::cout << "Using push_back (Constructs temporary -> Copies/Moves -> Destroys temp):\n";
    bots.push_back(Robot(1, "Alpha")); 

    std::cout << "Using emplace_back (Constructs directly in place):\n";
    // Arguments are forwarded directly to the Robot constructor
    bots.emplace_back(2, "Beta"); 
}

// ==========================================
// 6. 2D VECTORS (Matrix)
// ==========================================
void demonstrate2DVector() {
    std::cout << "\n=== 6. Vector of Vectors (2D) ===\n";
    
    // A 3x3 matrix initialized to 0
    // Syntax: vector<vector<type>> name(rows, vector<type>(cols, value))
    int rows = 3;
    int cols = 3;
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0));

    // Fill diagonal
    for(int i = 0; i < rows; ++i) {
        matrix[i][i] = 1;
    }

    std::cout << "Identity Matrix:\n";
    for(const auto& row : matrix) {
        std::cout << "  ";
        for(int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

// ==========================================
// 7. ALGORITHMS WITH VECTORS
// ==========================================
void demonstrateAlgorithms() {
    std::cout << "\n=== 7. STL Algorithms ===\n";
    std::vector<int> v = {50, 10, 40, 20, 30};
    printVector(v, "Original");

    // Sorting
    std::sort(v.begin(), v.end());
    printVector(v, "Sorted");

    // Binary Search (requires sorted vector)
    bool found = std::binary_search(v.begin(), v.end(), 20);
    std::cout << "Contains 20? " << (found ? "Yes" : "No") << "\n";

    // Reverse
    std::reverse(v.begin(), v.end());
    printVector(v, "Reversed");
}

// ==========================================
// MAIN DRIVER
// ==========================================
int main() {
    std::cout << "========================================\n";
    std::cout << "    THE C++ VECTOR DEEP DIVE\n";
    std::cout << "========================================\n";

    demonstrateInitialization();
    demonstrateAccess();
    demonstrateCapacity();
    demonstrateModifiers();
    demonstrateEmplace();
    demonstrate2DVector();
    demonstrateAlgorithms();

    std::cout << "\nProgram execution completed successfully.\n";
    return 0;
}