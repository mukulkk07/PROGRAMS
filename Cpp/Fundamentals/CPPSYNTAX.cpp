#include <iostream> // Include library for I/O

// Entry point of the program
int main() {
    // Variable declaration
    int age; 
    
    // Output statement
    std::cout << "Enter your age: "; 
    
    // Input statement
    std::cin >> age; 
    
    // Conditional logic block
    if (age >= 18) {
        std::cout << "Access granted.\n"; // \n represents a newline
    } else {
        std::cout << "Access denied.\n";
    }

    return 0; // Return success to the system
}