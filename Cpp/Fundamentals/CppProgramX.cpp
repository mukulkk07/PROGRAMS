/*
 * SmartInventory.cpp
 * Demonstrates: std::optional, Event Listeners (Observers), and Custom Exceptions.
 *
 * TO COMPILE: g++ -std=c++17 SmartInventory.cpp -o inventory
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>   // For std::function (callbacks)
#include <optional>     // C++17: Safer than returning pointers or -1
#include <stdexcept>    // For std::runtime_error
#include <iomanip>      // For std::setprecision

// ==========================================
// 1. DATA TYPES & CUSTOM EXCEPTIONS
// ==========================================

struct Product {
    int id;
    std::string name;
    double price;
    int stock;

    void print() const {
        std::cout << "   [ID: " << id << "] " << name 
                  << " - $" << std::fixed << std::setprecision(2) << price 
                  << " (" << stock << " in stock)\n";
    }
};

// Custom Exception Class
class InventoryError : public std::runtime_error {
public:
    // Pass message to the standard runtime_error
    InventoryError(const std::string& msg) : std::runtime_error("Inventory Error: " + msg) {}
};

// ==========================================
// 2. THE SMART INVENTORY SYSTEM
// ==========================================

class Inventory {
private:
    std::vector<Product> products;
    
    // Event Listeners: A list of functions to call when a new item is added.
    // This allows external code to "subscribe" to updates.
    std::vector<std::function<void(const Product&)>> observers;

public:
    // -- A. Observer Registration --
    void onProductAdded(std::function<void(const Product&)> listener) {
        observers.push_back(listener);
    }

    // -- B. Core Logic with Notification --
    void addProduct(int id, std::string name, double price, int stock) {
        if (price < 0) {
            throw InventoryError("Price cannot be negative for " + name);
        }

        Product newP = {id, name, price, stock};
        products.push_back(newP);

        // Notify all listeners (The Observer Pattern)
        for (const auto& listener : observers) {
            listener(newP);
        }
    }

    // -- C. Modern Return Type: std::optional --
    // Instead of returning nullptr or throwing an error if not found,
    // we return "Empty" or "Value". This forces the user to check validity.
    std::optional<Product> findById(int id) {
        auto it = std::find_if(products.begin(), products.end(), 
            [id](const Product& p) { return p.id == id; });

        if (it != products.end()) {
            return *it; // Return the found product
        }
        return std::nullopt; // Return "Nothing"
    }

    // -- D. Bulk Updates (Lambda Application) --
    // Apply a strategy to modify all items (e.g., Inflation, Sale)
    void applyMarketShift(std::function<void(Product&)> strategy) {
        for (auto& p : products) {
            strategy(p);
        }
    }

    void listAll() const {
        std::cout << "--- Current Inventory ---\n";
        for (const auto& p : products) p.print();
        std::cout << "-------------------------\n";
    }
};

// ==========================================
// 3. MAIN EXECUTION
// ==========================================

int main() {
    Inventory store;

    // 1. SETUP EVENT LISTENERS (Lambdas)
    // Listener 1: The Logger
    store.onProductAdded([](const Product& p) {
        std::cout << "[LOG] System received new item: " << p.name << "\n";
    });

    // Listener 2: The Alert System (Logic inside lambda)
    store.onProductAdded([](const Product& p) {
        if (p.stock < 5) {
            std::cout << "[ALERT] Low stock warning for " << p.name << "!\n";
        }
    });

    std::cout << "=== Inventory System Online ===\n\n";

    // 2. ERROR HANDLING (Try-Catch Block)
    try {
        store.addProduct(101, "Gaming Mouse", 49.99, 20);
        store.addProduct(102, "Mechanical Keyboard", 120.00, 3); // Triggers Low Stock Alert
        
        // This will throw an exception
        std::cout << "Attempting to add invalid item...\n";
        store.addProduct(103, "Broken Item", -50.00, 10); 

    } catch (const InventoryError& e) {
        std::cerr << ">> CAUGHT EXCEPTION: " << e.what() << "\n\n";
    }

    // 3. USING std::optional
    std::cout << "Searching for ID 101...\n";
    auto result = store.findById(101);
    
    // We check if result "has_value" before accessing it
    if (result.has_value()) {
        std::cout << "Found: " << result->name << "\n";
    }

    std::cout << "Searching for ID 999 (Non-existent)...\n";
    auto missing = store.findById(999);
    
    // value_or() returns the value if present, or a default object if nullopt
    Product fallback = missing.value_or(Product{0, "Unknown", 0.0, 0});
    std::cout << "Result: " << fallback.name << "\n\n";

    // 4. MODIFYING STATE (Lambdas)
    store.listAll();
    
    std::cout << "Applying 10% Inflation...\n";
    store.applyMarketShift([](Product& p) {
        p.price *= 1.10; // Increase price by 10%
    });
    
    store.listAll();

    return 0;
}