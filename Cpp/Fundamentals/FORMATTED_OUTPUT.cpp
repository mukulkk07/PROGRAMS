#include <iostream>
#include <iomanip> // <--- REQUIRED for setw, setprecision, etc.
#include <string>

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "      C++ FORMATTED OUTPUT DEMO" << endl;
    cout << "========================================" << endl;

    // ---------------------------------------------------------
    // 1. WIDTH AND ALIGNMENT (setw, left, right)
    // setw(n) reserves 'n' spaces for the NEXT item only.
    // ---------------------------------------------------------
    cout << "\n1. [TABLE ALIGNMENT]" << endl;
    
    // By default, text is aligned to the RIGHT.
    // We use 'left' to align text to the left side of the reserved space.
    
    cout << left << setw(15) << "PRODUCT" 
         << right << setw(10) << "QTY" 
         << right << setw(10) << "PRICE" << endl;

    cout << string(35, '-') << endl; // Print a divider line

    cout << left << setw(15) << "Apple" 
         << right << setw(10) << 5 
         << right << setw(10) << "$1.00" << endl;

    cout << left << setw(15) << "Banana" 
         << right << setw(10) << 12 
         << right << setw(10) << "$0.50" << endl;

    cout << left << setw(15) << "Watermelon" 
         << right << setw(10) << 1 
         << right << setw(10) << "$5.00" << endl;


    // ---------------------------------------------------------
    // 2. FILL CHARACTERS (setfill)
    // Replaces empty spaces with a specific character.
    // ---------------------------------------------------------
    cout << "\n2. [FILL CHARACTERS]" << endl;
    
    cout << "Loading: ";
    cout << setfill('#') << setw(20) << "" << endl; // Prints 20 '#' characters
    
    // Reset fill back to empty space for normal printing
    cout << setfill(' '); 


    // ---------------------------------------------------------
    // 3. FLOATING POINT NUMBERS (fixed, setprecision)
    // Essential for printing money (2 decimal places).
    // ---------------------------------------------------------
    cout << "\n3. [DECIMAL PRECISION]" << endl;
    
    double pi = 3.14159265359;
    double money = 1500.5; // Should look like 1500.50

    cout << "Original PI:    " << pi << endl;
    
    // 'fixed' prevents scientific notation (e.g., 1.5e3)
    // 'setprecision(n)' sets the number of digits after the decimal point
    cout << fixed << setprecision(2);
    
    cout << "Money format:   $" << money << endl;
    cout << "PI (2 decimals): " << pi << endl;

    cout << setprecision(5);
    cout << "PI (5 decimals): " << pi << endl;


    // ---------------------------------------------------------
    // 4. BOOLEANS (boolalpha)
    // Prints "true"/"false" instead of 1/0.
    // ---------------------------------------------------------
    cout << "\n4. [BOOLEAN FORMAT]" << endl;
    
    bool isCodingFun = true;
    bool isTired = false;

    cout << "Default output: " << isCodingFun << ", " << isTired << endl;
    
    cout << boolalpha; // Switch to text mode
    cout << "Alpha output:   " << isCodingFun << ", " << isTired << endl;


    cout << "\n========================================" << endl;
    return 0;
}