#include <iostream>
#include <fstream> // <--- REQUIRED for file operations
#include <string>

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "      C++ FILE OPERATIONS DEMO" << endl;
    cout << "========================================" << endl;

    string filename = "my_notes.txt";

    // ---------------------------------------------------------
    // 1. WRITING TO A FILE (ofstream)
    // 'ofstream' stands for Output File Stream.
    // This creates a new file. If it exists, it DELETES the old content!
    // ---------------------------------------------------------
    cout << "\n1. [WRITING] Creating '" << filename << "'..." << endl;
    
    ofstream writer(filename); // Open file for writing

    if (writer.is_open()) {
        writer << "Hello! This is a file created by C++." << endl;
        writer << "File operations are useful for saving data." << endl;
        writer << "100" << endl; // You can write numbers too
        
        writer.close(); // ALWAYS close the file when done!
        cout << "   -> Success: Data written to file." << endl;
    } else {
        cout << "   -> Error: Could not create file." << endl;
    }


    // ---------------------------------------------------------
    // 2. APPENDING TO A FILE (ios::app)
    // By default, ofstream overwrites. Use 'ios::app' to ADD to the end.
    // ---------------------------------------------------------
    cout << "\n2. [APPENDING] Adding more text..." << endl;
    
    // syntax: ofstream variable(filename, mode);
    ofstream appender(filename, ios::app); 

    if (appender.is_open()) {
        appender << "This line was added later (Appended)." << endl;
        appender.close();
        cout << "   -> Success: Data appended." << endl;
    }


    // ---------------------------------------------------------
    // 3. READING FROM A FILE (ifstream)
    // 'ifstream' stands for Input File Stream.
    // ---------------------------------------------------------
    cout << "\n3. [READING] Reading contents back:" << endl;
    cout << "----------------------------------------" << endl;

    ifstream reader(filename); // Open file for reading
    string line;

    if (reader.is_open()) {
        // while(getline(file, string_variable)) reads line-by-line until the end
        while (getline(reader, line)) {
            cout << line << endl;
        }
        reader.close();
    } else {
        cout << "   -> Error: File not found!" << endl;
    }

    cout << "----------------------------------------" << endl;
    return 0;
}