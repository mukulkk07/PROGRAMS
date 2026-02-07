#include <iostream>
#include <vector>
#include <string>
#include <functional> // Required for std::function

using namespace std;

// ==========================================
// 1. VARIADIC TEMPLATE FUNCTION
// ==========================================
// This is a function that can take ANY number of arguments of ANY type.
// It uses recursion to peel off one argument at a time.

// Base case: When there are no arguments left, print a newline.
void systemLog() {
    cout << endl;
}

// Recursive case: Take the first arg (T), and keep the rest (Args...)
template <typename T, typename... Args>
void systemLog(T first, Args... rest) {
    cout << "[" << first << "] "; // Process the first argument
    systemLog(rest...);           // Recursively call with the rest
}

// ==========================================
// 2. THE GENERIC DATA CLASS
// ==========================================
template <typename T>
class SecurePacket {
private:
    int id;
    T payload;
    bool isLocked;
    
    // "SecurityAuditor" is a FRIEND. It can access 'id' and 'isLocked'.
    friend class SecurityAuditor; 

public:
    SecurePacket(int i, T data) : id(i), payload(data), isLocked(true) {}

    // Public getter (Normal users can only see this)
    T getData() const { return payload; }
    
    // Setter for the payload
    void setData(T newData) { payload = newData; }
};

// ==========================================
// 3. THE FRIEND CLASS (Privileged Access)
// ==========================================
class SecurityAuditor {
public:
    // This function can access private members of SecurePacket<T>
    template <typename T>
    void inspectPacket(const SecurePacket<T>& packet) {
        cout << "   [AUDIT] Packet ID: " << packet.id 
             << " | Locked status: " << (packet.isLocked ? "YES" : "NO") << endl;
    }
};

// ==========================================
// 4. THE PROCESSOR (Higher-Order Function)
// ==========================================
// This function takes a vector AND a function as a parameter.
// We use std::function<void(T&)> to define the "shape" of the allowed function.

template <typename T>
void runPipeline(vector<SecurePacket<T>>& batch, function<void(T&)> transformationAlgorithm) {
    systemLog("PIPELINE", "Start", "Batch Size:", batch.size()); // Variadic call

    for (auto& packet : batch) {
        // 1. Extract data
        T data = packet.getData();
        
        // 2. Apply the Lambda logic passed by the user
        transformationAlgorithm(data);
        
        // 3. Update the packet
        packet.setData(data);
    }
    
    systemLog("PIPELINE", "End", "Success"); // Variadic call
}

// ==========================================
// 5. MAIN EXECUTION
// ==========================================
int main() {
    // --- Setup ---
    SecurityAuditor admin;
    
    // Creating a batch of Integers
    vector<SecurePacket<int>> intBatch;
    intBatch.push_back(SecurePacket<int>(101, 5));
    intBatch.push_back(SecurePacket<int>(102, 10));

    // Creating a batch of Strings
    vector<SecurePacket<string>> strBatch;
    strBatch.push_back(SecurePacket<string>(201, "alpha"));
    strBatch.push_back(SecurePacket<string>(202, "beta"));

    // --- Scenario A: Processing Integers ---
    // We pass a LAMBDA that defines "Squaring" logic
    runPipeline<int>(intBatch, [](int& n) {
        cout << "   -> Processing int: " << n << " -> " << n * n << endl;
        n = n * n;
    });

    // Auditor checks private data
    cout << "--- Admin Audit (Ints) ---" << endl;
    for(const auto& p : intBatch) admin.inspectPacket(p);


    // --- Scenario B: Processing Strings ---
    // We pass a LAMBDA that defines "Uppercasing" logic
    // Notice: The function structure is identical to Scenario A, but logic differs.
    cout << "\n";
    runPipeline<string>(strBatch, [](string& s) {
        string old = s;
        for (auto &c : s) c = toupper(c);
        cout << "   -> Processing str: " << old << " -> " << s << endl;
    });

    // Auditor checks private data
    cout << "--- Admin Audit (Strings) ---" << endl;
    for(const auto& p : strBatch) admin.inspectPacket(p);

    // --- Scenario C: Variadic Logging Demo ---
    cout << "\n--- Variadic Template Demo ---" << endl;
    // Look at how the number of arguments changes!
    systemLog("INFO", "System check");
    systemLog("WARNING", "Memory Low", 85, "%");
    systemLog("ERROR", "Critical Failure", "Code", 404, "Module", "Network");

    return 0;
}