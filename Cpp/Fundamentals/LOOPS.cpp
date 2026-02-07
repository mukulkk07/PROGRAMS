#include <iostream>
#include <vector> // Required for the Range-based for loop example

using namespace std;

int main() {
    cout << "=========================================" << endl;
    cout << "      C++ LOOPS DEMONSTRATION" << endl;
    cout << "=========================================" << endl;

    // ---------------------------------------------------------
    // 1. THE FOR LOOP
    // Best used when you know exactly how many times you want to iterate.
    // Syntax: for (initialization; condition; increment/decrement)
    // ---------------------------------------------------------
    cout << "\n1. [FOR LOOP] Counting from 1 to 5:" << endl;
    
    for (int i = 1; i <= 5; i++) {
        cout << "   Iteration: " << i << endl;
    }


    // ---------------------------------------------------------
    // 2. THE WHILE LOOP
    // Best used when you don't know how many times the loop will run,
    // but you know the condition that stops it.
    // Checks the condition BEFORE executing the body.
    // ---------------------------------------------------------
    cout << "\n2. [WHILE LOOP] Countdown until energy runs out:" << endl;
    
    int energy = 3;
    while (energy > 0) {
        cout << "   Energy is: " << energy << " (Looping...)" << endl;
        energy--; // IMPORTANT: We must manually update the variable to avoid an infinite loop
    }
    cout << "   Loop stopped. Energy is 0." << endl;


    // ---------------------------------------------------------
    // 3. THE DO-WHILE LOOP
    // Similar to 'while', but guarantees the code runs AT LEAST ONCE.
    // Checks the condition AFTER executing the body.
    // ---------------------------------------------------------
    cout << "\n3. [DO-WHILE LOOP] Executing code once before checking:" << endl;
    
    int number = 10;
    do {
        cout << "   This prints even though number (" << number << ") is not < 5." << endl;
        number++;
    } while (number < 5); // Condition is false, but body already ran once.


    // ---------------------------------------------------------
    // 4. THE RANGE-BASED FOR LOOP (Modern C++)
    // Best used for iterating through collections (arrays, vectors, lists).
    // Syntax: for (declaration : range_expression)
    // ---------------------------------------------------------
    cout << "\n4. [RANGE-BASED FOR LOOP] Iterating over a list of prices:" << endl;
    
    vector<double> prices = {10.50, 20.99, 5.75, 99.00};
    
    // Read as: "For every 'price' inside 'prices'..."
    for (double price : prices) {
        cout << "   Price: $" << price << endl;
    }

    cout << "\n=========================================" << endl;
    cout << "      End of Demonstration" << endl;
    cout << "=========================================" << endl;

    return 0;
}