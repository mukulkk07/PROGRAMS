#include <iostream>
#include <string>
#include <iomanip> // For formatting

using namespace std;

// ==========================================
// THE OVERLOADED FUNCTIONS
// ==========================================

// 1. Context: Simple Text Message
// Signature: logInfo(string)
void logInfo(string message) {
    cout << "[TEXT] " << message << endl;
}

// 2. Context: Error Codes (Integer processing)
// Signature: logInfo(int)
void logInfo(int errorCode) {
    cout << "[CODE] Error #" << errorCode;
    if (errorCode == 404) cout << " (Not Found)";
    else if (errorCode == 500) cout << " (Server Error)";
    cout << endl;
}

// 3. Context: Coordinates (Multiple parameters)
// Signature: logInfo(int, int)
void logInfo(int x, int y) {
    cout << "[POS ] Player moved to Grid (" << x << ", " << y << ")" << endl;
}

// 4. Context: Precision Data (Different type: double)
// Signature: logInfo(double)
void logInfo(double temperature) {
    cout << "[SENS] CPU Temp: " << fixed << setprecision(2) << temperature << " C" << endl;
}

// 5. Context: Mixed Types (Sequence matters!)
// Signature: logInfo(string, int)
void logInfo(string serverName, int port) {
    cout << "[NET ] Connected to " << serverName << " on port " << port << endl;
}

// ==========================================
// MAIN EXECUTION
// ==========================================
int main() {
    cout << "--- SYSTEM STARTUP ---" << endl;

    // The Compiler decides which function to call 
    // based on the ARGUMENTS passed.

    logInfo("System Booting...");       // Matches #1 (string)
    logInfo(404);                       // Matches #2 (int)
    logInfo(10, 25);                    // Matches #3 (int, int)
    logInfo(75.5678);                   // Matches #4 (double)
    logInfo("Alpha-Server", 8080);      // Matches #5 (string, int)

    // Implicit Type Conversion (A common scenario)
    // 'f' is a float, but we don't have a float version.
    // C++ promotes float -> double to match #4.
    float batteryLevel = 98.5f;
    logInfo(batteryLevel); 

    return 0;
}