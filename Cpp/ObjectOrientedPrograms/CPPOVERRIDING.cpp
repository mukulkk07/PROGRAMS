#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// 1. BASE CLASS (The Parent)
// ==========================================
class SmartDevice {
public:
    string deviceName;

    SmartDevice(string name) : deviceName(name) {}

    // The 'virtual' keyword tells C++: 
    // "Look at the specific object type at runtime, not just this pointer type."
    virtual void turnOn() {
        cout << "[" << deviceName << "] Generic device powering up..." << endl;
    }

    // Virtual destructor is crucial when using inheritance!
    virtual ~SmartDevice() {}
};

// ==========================================
// 2. DERIVED CLASSES (The Children)
// ==========================================

// Child 1: Smart Light
class SmartLight : public SmartDevice {
public:
    SmartLight(string name) : SmartDevice(name) {}

    // We OVERRIDE the parent's turnOn function
    void turnOn() override { 
        cout << "[" << deviceName << "] brightness set to 100%." << endl;
    }
};

// Child 2: Smart AC
class Thermostat : public SmartDevice {
public:
    Thermostat(string name) : SmartDevice(name) {}

    void turnOn() override {
        cout << "[" << deviceName << "] cooling system engaged. Target: 22C." << endl;
    }
};

// Child 3: Security Camera
class SecurityCamera : public SmartDevice {
public:
    SecurityCamera(string name) : SmartDevice(name) {}

    void turnOn() override {
        cout << "[" << deviceName << "] recording started. Motion sensors active." << endl;
    }
};

// ==========================================
// 3. MAIN FUNCTION
// ==========================================
int main() {
    // A. Create specific devices
    SmartLight livingRoomLight("Living Room Light");
    Thermostat mainAC("Hallway AC");
    SecurityCamera frontDoorCam("Front Door Cam");

    cout << "--- Direct Calls (Simple) ---" << endl;
    livingRoomLight.turnOn();
    mainAC.turnOn();

    cout << "\n--- Polymorphic Calls (The Power of Overriding) ---" << endl;
    
    // B. This is where the magic happens.
    // We create a list of pointers to the BASE class.
    // We can store ANY child object in this list.
    vector<SmartDevice*> homeSystem;

    homeSystem.push_back(&livingRoomLight);
    homeSystem.push_back(&mainAC);
    homeSystem.push_back(&frontDoorCam);

    // C. We loop through the list. 
    // Even though the pointer type is 'SmartDevice*', 
    // the program figures out which SPECIFIC 'turnOn' to call.
    for (SmartDevice* device : homeSystem) {
        device->turnOn(); 
    }

    return 0;
}