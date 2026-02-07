#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// 1. THE BASE CLASS (The Interface)
// ==========================================
class UIElement {
protected:
    string label;

public:
    UIElement(string l) : label(l) {}

    // ---------------------------------------------------
    // VIRTUAL FUNCTIONS
    // The 'virtual' keyword tells C++: 
    // "Wait until the program runs to decide which function to call."
    // ---------------------------------------------------
    
    // A virtual function we expect children to override
    virtual void draw() {
        cout << "[Generic Element] Drawing " << label << " (Basic style)" << endl;
    }

    // A PURE virtual function (= 0).
    // This forces every child to define their own click behavior.
    virtual void onClick() = 0;

    // IMPORTANT: Virtual Destructor
    // Ensures the correct destructor is called when deleting via a base pointer.
    virtual ~UIElement() {
        cout << "   (Destroying generic UI data for " << label << ")" << endl;
    }
};

// ==========================================
// 2. DERIVED CLASS: Button
// ==========================================
class Button : public UIElement {
public:
    Button(string l) : UIElement(l) {}

    // The 'override' keyword is good practice. 
    // It ensures we are actually replacing the base function.
    void draw() override {
        cout << "[BUTTON] |  " << label << "  | (Drawn with borders)" << endl;
    }

    void onClick() override {
        cout << "   -> Action: Submitted form '" << label << "'!" << endl;
    }
    
    ~Button() {
        cout << "   (Cleaning up Button specific resources)" << endl;
    }
};

// ==========================================
// 3. DERIVED CLASS: TextBox
// ==========================================
class TextBox : public UIElement {
public:
    TextBox(string l) : UIElement(l) {}

    void draw() override {
        cout << "[INPUT ] [ " << label << "....... ] (Drawn with cursor)" << endl;
    }

    void onClick() override {
        cout << "   -> Action: Cursor placed in '" << label << "'. Keyboard active." << endl;
    }
    
    ~TextBox() {
        cout << "   (Cleaning up TextBox specific resources)" << endl;
    }
};

// ==========================================
// 4. DERIVED CLASS: CheckBox
// ==========================================
class CheckBox : public UIElement {
    bool isChecked;
public:
    CheckBox(string l) : UIElement(l), isChecked(false) {}

    void draw() override {
        string state = isChecked ? "[X]" : "[ ]";
        cout << "[CHECK ] " << state << " " << label << endl;
    }

    void onClick() override {
        isChecked = !isChecked; // Toggle state
        cout << "   -> Action: Toggled '" << label << "' to " << (isChecked ? "ON" : "OFF") << endl;
    }
};

// ==========================================
// 5. MAIN SYSTEM
// ==========================================
int main() {
    cout << "=========================================" << endl;
    cout << "      POLYMORPHIC UI RENDERING" << endl;
    cout << "=========================================" << endl;

    // ---------------------------------------------------------
    // THE POWER OF POLYMORPHISM
    // We create a vector of POINTERS to the Base Class.
    // This vector can now hold Buttons, TextBoxes, or CheckBoxes mixed together!
    // ---------------------------------------------------------
    vector<UIElement*> myPage;

    // Adding different types to the same list
    myPage.push_back(new Button("Login"));
    myPage.push_back(new TextBox("Username"));
    myPage.push_back(new CheckBox("Remember Me"));
    myPage.push_back(new Button("Cancel"));

    // ---------------------------------------------------------
    // RENDER LOOP
    // We treat every item as just a "UIElement", 
    // but the Correct "draw()" function runs for each one.
    // ---------------------------------------------------------
    cout << "\n--- Rendering Page ---" << endl;
    for (UIElement* element : myPage) {
        element->draw(); 
    }

    // ---------------------------------------------------------
    // INPUT SIMULATION
    // ---------------------------------------------------------
    cout << "\n--- User Clicks 'Remember Me' ---" << endl;
    myPage[2]->onClick(); // Index 2 is the CheckBox
    
    cout << "\n--- Re-Rendering to show changes ---" << endl;
    myPage[2]->draw();    // The CheckBox should now have an [X]

    cout << "\n--- User Clicks 'Login' ---" << endl;
    myPage[0]->onClick(); // Index 0 is the Button


    // ---------------------------------------------------------
    // CLEANUP
    // Because the destructor is virtual, deleting the base pointer
    // successfully cleans up the derived part too.
    // ---------------------------------------------------------
    cout << "\n--- Closing Application (Cleanup) ---" << endl;
    for (UIElement* element : myPage) {
        delete element; // Calls ~Button, ~TextBox, etc. automatically
    }

    return 0;
}