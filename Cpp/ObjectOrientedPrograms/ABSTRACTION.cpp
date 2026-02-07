#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. ABSTRACT BASE CLASS (The "Contract")
// ==========================================
class PaymentProcessor {
public:
    // Pure Virtual Function
    // The "= 0" means: "I don't know how to do this yet, 
    // but any specific payment method MUST define it."
    virtual void processPayment(double amount) = 0;

    // Virtual destructor is important for cleanup
    virtual ~PaymentProcessor() {}
};

// ==========================================
// 2. CONCRETE CLASS: Credit Card
// Hides the complexity of bank numbers and encryption
// ==========================================
class CreditCardPayment : public PaymentProcessor {
private:
    string cardNumber;
    string cvv;

    // Internal "Helper" function - The user never sees this!
    bool connectToBank() {
        cout << "   [System] Connecting to Bank Gateway..." << endl;
        return true; 
    }

public:
    CreditCardPayment(string num, string code) {
        cardNumber = num;
        cvv = code;
    }

    // Implementing the abstract function
    void processPayment(double amount) override {
        cout << "\n--- Processing Credit Card ---" << endl;
        if (connectToBank()) {
            cout << "   [System] Verifying Card Ending in " << cardNumber.substr(12) << "..." << endl;
            cout << "   -> Success: Paid $" << amount << " via VISA." << endl;
        }
    }
};

// ==========================================
// 3. CONCRETE CLASS: PayPal
// Hides the complexity of email login and tokens
// ==========================================
class PayPalPayment : public PaymentProcessor {
private:
    string email;

public:
    PayPalPayment(string mail) {
        email = mail;
    }

    // Implementing the abstract function differently
    void processPayment(double amount) override {
        cout << "\n--- Processing PayPal ---" << endl;
        cout << "   [System] Redirecting to PayPal.com..." << endl;
        cout << "   [System] Logging in user: " << email << endl;
        cout << "   -> Success: Paid $" << amount << " via PayPal balance." << endl;
    }
};

// ==========================================
// 4. THE CLIENT (The "Store")
// This function demonstrates Abstraction perfectly.
// It accepts ANY PaymentProcessor. It doesn't care how it works.
// ==========================================
void checkout(PaymentProcessor* paymentMethod, double totalAmount) {
    cout << "Store: Starting checkout for $" << totalAmount << "..." << endl;
    
    // THE MAGIC LINE:
    // We just call processPayment(). We don't know if it uses a bank, 
    // an email, or crypto. The complexity is abstracted away.
    paymentMethod->processPayment(totalAmount);
    
    cout << "Store: Transaction complete.\n" << endl;
}

int main() {
    cout << "=========================================" << endl;
    cout << "      ABSTRACTION IN PAYMENT SYSTEMS" << endl;
    cout << "=========================================" << endl;

    double cartTotal = 99.50;

    // Scenario 1: User pays with Card
    // We create the complex object, but handle it via the base pointer
    CreditCardPayment* myCard = new CreditCardPayment("1234567812349999", "123");
    checkout(myCard, cartTotal);

    // Scenario 2: User pays with PayPal
    PayPalPayment* myPaypal = new PayPalPayment("user@example.com");
    checkout(myPaypal, cartTotal);

    // Cleanup
    delete myCard;
    delete myPaypal;

    return 0;
}