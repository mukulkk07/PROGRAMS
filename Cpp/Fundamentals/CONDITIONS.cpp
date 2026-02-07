#include <iostream>
#include <string>

using namespace std;

int main() {
    cout << "=========================================" << endl;
    cout << "   C++ CONDITIONAL STATEMENTS DEMO" << endl;
    cout << "=========================================" << endl;

    // ---------------------------------------------------------
    // 1. IF and ELSE
    // Use this for simple "Yes/No" or "True/False" decisions.
    // ---------------------------------------------------------
    cout << "\n1. [IF / ELSE] Password Check:" << endl;
    
    int secretCode = 1234;
    int inputCode;
    
    cout << "   Enter the secret code (hint: 1234): ";
    cin >> inputCode;

    if (inputCode == secretCode) {
        cout << "   -> Access Granted! Welcome." << endl;
    } else {
        cout << "   -> Access Denied! Wrong code." << endl;
    }


    // ---------------------------------------------------------
    // 2. ELSE IF LADDER
    // Use this when checking multiple conditions in a specific order.
    // As soon as one is true, the rest are skipped.
    // ---------------------------------------------------------
    cout << "\n2. [ELSE IF] Grading System:" << endl;
    
    int score;
    cout << "   Enter a score (0-100): ";
    cin >> score;

    if (score >= 90) {
        cout << "   -> Grade: A (Excellent)" << endl;
    } else if (score >= 75) {
        cout << "   -> Grade: B (Good)" << endl;
    } else if (score >= 50) {
        cout << "   -> Grade: C (Average)" << endl;
    } else {
        cout << "   -> Grade: F (Fail)" << endl;
    }


    // ---------------------------------------------------------
    // 3. SWITCH STATEMENT
    // Use this when checking a SINGLE variable against exact values.
    // It is cleaner than many 'else if' statements for menus.
    // ---------------------------------------------------------
    cout << "\n3. [SWITCH] Vending Machine:" << endl;
    cout << "   1: Coke\n   2: Pepsi\n   3: Water" << endl;
    cout << "   Choose an option (1-3): ";
    
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "   -> Dispensing Coke..." << endl;
            break; // 'break' stops the code from falling into the next case
        case 2:
            cout << "   -> Dispensing Pepsi..." << endl;
            break;
        case 3:
            cout << "   -> Dispensing Water..." << endl;
            break;
        default:
            cout << "   -> Error: Invalid selection." << endl;
    }


    // ---------------------------------------------------------
    // 4. TERNARY OPERATOR (Shorthand If-Else)
    // Syntax: (condition) ? value_if_true : value_if_false;
    // Best used for quick assignments.
    // ---------------------------------------------------------
    cout << "\n4. [TERNARY OPERATOR] Even or Odd?" << endl;
    
    int number = 7;
    // Read as: "Is number % 2 equal to 0? If yes, result is 'Even', else 'Odd'"
    string result = (number % 2 == 0) ? "Even" : "Odd";
    
    cout << "   The number " << number << " is " << result << "." << endl;


    cout << "\n=========================================" << endl;
    cout << "      End of Demonstration" << endl;
    cout << "=========================================" << endl;

    return 0;
}