#include <iostream>
#include <vector>
#include <string>

using namespace std;

class RecursionMaster {
public:
    // ==========================================
    // LEVEL 1: THE BASICS (Stack Frames & Flow)
    // Concept: Head vs Tail Recursion
    // ==========================================

    // 1.1 Head Recursion (Process on the way UP)
    // Logic: Recurse first, Print later. This reverses the order (1 to N).
    void printHead(int n) {
        if (n == 0) return; // Base Case
        
        printHead(n - 1);   // Recursive Call (Dive deeper)
        cout << n << " ";   // Action (Executes as stack unwinds)
    }

    // 1.2 Tail Recursion (Process on the way DOWN)
    // Logic: Print first, Recurse later. This keeps order (N to 1).
    // Compiler Optimization: Tail recursion can often be optimized into a loop by the compiler.
    void printTail(int n) {
        if (n == 0) return; // Base Case
        
        cout << n << " ";   // Action
        printTail(n - 1);   // Recursive Call
    }

    // 1.3 The Accumulator Pattern (Factorial)
    // Passing the result down the chain.
    int factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1); // Trust the function to solve n-1
    }

    // ==========================================
    // LEVEL 2: MULTIPLE BRANCHING (Tree Recursion)
    // Concept: Calling function multiple times inside itself.
    // Complexity: O(Branch^Depth) -> Exponential
    // ==========================================
    
    // 2.1 Fibonacci (Classic Tree Recursion)
    // F(N) = F(N-1) + F(N-2)
    int fibonacci(int n) {
        if (n <= 1) return n;
        // This splits into two branches at every step
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    // 2.2 Tower of Hanoi
    // Move N disks from Source(A) to Dest(C) using Aux(B)
    void towerOfHanoi(int n, char from, char to, char aux) {
        if (n == 0) return;

        // Step 1: Move top n-1 disks from Source -> Aux
        towerOfHanoi(n - 1, from, aux, to);
        
        // Step 2: Move the biggest disk (nth) from Source -> Dest
        cout << "Move disk " << n << " from " << from << " to " << to << endl;
        
        // Step 3: Move the n-1 disks from Aux -> Dest
        towerOfHanoi(n - 1, aux, to, from);
    }

    // ==========================================
    // LEVEL 3: STRING RECURSION (Subsets)
    // Use Case: Generate Power Set (All Subsequences)
    // Pattern: Pick vs Don't Pick
    // ==========================================
    void generateSubsequences(string input, string output) {
        // Base Case: No more characters left to process
        if (input.empty()) {
            cout << "'" << output << "' ";
            return;
        }

        // Logic: We process the first char of 'input'
        char current = input[0];
        string remaining = input.substr(1);

        // Branch 1: Exclude the current char
        generateSubsequences(remaining, output);

        // Branch 2: Include the current char
        generateSubsequences(remaining, output + current);
    }

    // 3.1 Check Palindrome
    // Logic: Compare outer chars, recurse on inner string
    bool isPalindrome(const string& s, int left, int right) {
        if (left >= right) return true; // Base case: Middle reached
        if (s[left] != s[right]) return false; // Mismatch found
        
        return isPalindrome(s, left + 1, right - 1); // Recurse
    }
    
    // ==========================================
    // LEVEL 4: MATRIX RECURSION (Flood Fill)
    // Use Case: Paint Bucket Tool
    // ==========================================
    void floodFill(vector<vector<int>>& image, int r, int c, int newColor, int oldColor) {
        // Boundary Checks & Base Cases
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size()) return;
        if (image[r][c] != oldColor) return; // Not the target color
        if (image[r][c] == newColor) return; // Already painted

        // Process
        image[r][c] = newColor;

        // Recurse 4 Directions
        floodFill(image, r + 1, c, newColor, oldColor); // Down
        floodFill(image, r - 1, c, newColor, oldColor); // Up
        floodFill(image, r, c + 1, newColor, oldColor); // Right
        floodFill(image, r, c - 1, newColor, oldColor); // Left
    }
};

int main() {
    RecursionMaster solver;

    cout << "--- 1. Basic Recursion ---" << endl;
    cout << "Print 1 to 5 (Head): "; solver.printHead(5); cout << endl;
    cout << "Print 5 to 1 (Tail): "; solver.printTail(5); cout << endl;
    cout << "Factorial(5): " << solver.factorial(5) << endl;

    cout << "\n--- 2. Tree Recursion (Fibonacci 6) ---" << endl;
    cout << "Fib(6): " << solver.fibonacci(6) << endl;

    cout << "\n--- 3. Tower of Hanoi (3 Disks) ---" << endl;
    solver.towerOfHanoi(3, 'A', 'C', 'B');

    cout << "\n--- 4. Subsequences of 'abc' ---" << endl;
    // Expect: "" "c" "b" "bc" "a" "ac" "ab" "abc"
    solver.generateSubsequences("abc", "");
    cout << endl;

    cout << "\n--- 5. Palindrome Check ---" << endl;
    string s = "racecar";
    cout << "Is 'racecar' palindrome? " << (solver.isPalindrome(s, 0, s.length()-1) ? "Yes" : "No") << endl;

    return 0;
}