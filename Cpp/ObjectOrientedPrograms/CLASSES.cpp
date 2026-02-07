#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. CLASS DEFINITION (The Blueprint)
// ==========================================
class Student {
    
    // 'private': Data that CANNOT be touched from outside.
    // This is called "Encapsulation" (data protection).
    private:
        double gpa; 

    // 'public': Data and functions accessible by everyone.
    public:
        // Attributes (Variables)
        string name;
        int age;

        // ---------------------------------------------------
        // 2. CONSTRUCTOR
        // A special function with the SAME NAME as the class.
        // It runs AUTOMATICALLY when you create an object.
        // Used to initialize values.
        // ---------------------------------------------------
        Student(string n, int a, double g) {
            name = n;
            age = a;
            gpa = g;
            cout << "-> Constructor called for " << name << endl;
        }

        // ---------------------------------------------------
        // 3. MEMBER FUNCTIONS (Methods)
        // Functions that belong to the class.
        // ---------------------------------------------------
        void introduce() {
            cout << "Hi, I am " << name << " and I am " << age << " years old." << endl;
        }

        // A method to safely read private data (Getter)
        double getGpa() {
            return gpa;
        }

        // A method to safely change private data (Setter)
        void setGpa(double newGpa) {
            if (newGpa >= 0.0 && newGpa <= 4.0) {
                gpa = newGpa;
            } else {
                cout << "Error: Invalid GPA!" << endl;
            }
        }
}; // <--- IMPORTANT: Classes must end with a semicolon!

// ==========================================
// 4. MAIN FUNCTION (Using the Objects)
// ==========================================
int main() {
    cout << "--- Creating Objects ---" << endl;

    // Syntax: ClassName ObjectName(arguments);
    Student student1("Alice", 20, 3.8);
    Student student2("Bob", 22, 2.5);

    cout << "\n--- Using Methods ---" << endl;
    
    // Syntax: ObjectName.MethodName();
    student1.introduce();
    student2.introduce();

    cout << "\n--- Accessing Private Data ---" << endl;
    // cout << student1.gpa; // ERROR! This is private.
    
    // We must use the public 'Getter' method
    // FIX: Added the missing quote " at the start of the text below
    cout << "Alice's GPA is: " << student1.getGpa() << endl;

    cout << "\n--- Modifying Data ---" << endl;
    student1.setGpa(4.0); // Update using Setter
    cout << "Alice's new GPA is: " << student1.getGpa() << endl;

    return 0;
}