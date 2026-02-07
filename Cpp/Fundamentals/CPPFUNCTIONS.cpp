#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==========================================
// 1. FUNCTION PROTOTYPES (Declarations)
// ==========================================
// We declare these at the top so 'main' knows they exist.
// The actual logic (Definition) comes after main.

void printWelcomeMessage();
int addNumbers(int a, int b);
void swapValues(int &a, int &b);                    // Pass by Reference
double calculateArea(double radius);                // Overloading (Circle)
double calculateArea(double length, double width);  // Overloading (Rectangle)
void logAction(string message, int priority = 1);   // Default Argument

// ==========================================
// 2. MAIN FUNCTION (Entry Point)
// ==========================================
int main() {
    // A. Basic Void Function
    printWelcomeMessage();

    // B. Basic Return Value
    int sum = addNumbers(10, 5);
    cout << "1. Sum of 10 and 5 is: " << sum << endl;

    // C. Pass by Reference vs Pass by Value
    int x = 100, y = 200;
    cout << "2. Before Swap: x=" << x << ", y=" << y << endl;
    swapValues(x, y); // Takes the ACTUAL variables, not copies
    cout << "   After Swap:  x=" << x << ", y=" << y << endl;

    // D. Function Overloading (Polymorphism)
    cout << "3. Area of Circle (r=5.5): " << calculateArea(5.5) << endl;
    cout << "   Area of Rect (l=5, w=4): " << calculateArea(5.0, 4.0) << endl;

    // E. Default Arguments
    cout << "4. Logging tests:" << endl;
    logAction("System started");          // Uses default priority (1)
    logAction("System error!", 5);        // Overrides default priority

    return 0;
}

// ==========================================
// 3. FUNCTION DEFINITIONS (Logic)
// ==========================================

// Simple void function
void printWelcomeMessage() {
    cout << "===================================" << endl;
    cout << "   C++ FUNCTION TOOLKIT DEMO       " << endl;
    cout << "===================================" << endl;
}

// Pass by Value: 'a' and 'b' are copies of the originals
int addNumbers(int a, int b) {
    return a + b;
}

// Pass by Reference: 'a' and 'b' refer to the ORIGINAL memory addresses
// The '&' symbol creates a reference (alias).
void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Overload #1: Logic for Circle
double calculateArea(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}

// Overload #2: Logic for Rectangle
// The compiler tells them apart by the number of parameters.
double calculateArea(double length, double width) {
    return length * width;
}

// Default Arguments: If 'priority' isn't passed, it assumes 1.
void logAction(string message, int priority) {
    cout << "   [Log] Priority " << priority << ": " << message << endl;
}