#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>   // For printing binary representation

using namespace std;

// ==========================================================
// UTILITY: Print Binary
// ==========================================================
void printBinary(int n) {
    // Prints the 32-bit binary representation of n
    cout << "Binary (" << n << "): " << bitset<8>(n) << " (showing last 8 bits for clarity)" << endl;
}

// ==========================================================
// 1. BASIC BIT OPERATIONS
// ==========================================================

bool getBit(int n, int pos) {
    // Shift 1 to pos, then AND. If result is non-zero, bit is 1.
    return ((n & (1 << pos)) != 0);
}

int setBit(int n, int pos) {
    // OR with a mask having 1 at pos.
    return (n | (1 << pos));
}

int clearBit(int n, int pos) {
    // AND with a mask having 0 at pos and 1 everywhere else.
    int mask = ~(1 << pos);
    return (n & mask);
}

int toggleBit(int n, int pos) {
    // XOR with a mask having 1 at pos. 
    // (1^1 = 0, 0^1 = 1)
    return (n ^ (1 << pos));
}

int updateBit(int n, int pos, int value) {
    // First clear the bit, then set it to value (0 or 1).
    int mask = ~(1 << pos);
    int cleared_n = n & mask;
    return (cleared_n | (value << pos));
}

// ==========================================================
// 2. PROPERTY CHECKS
// ==========================================================

bool isEven(int n) {
    // Even numbers have the LSB (0th bit) as 0.
    return (n & 1) == 0;
}

bool isPowerOfTwo(int n) {
    // Powers of 2 have only one bit set. 
    // n & (n-1) flips the rightmost set bit. If result is 0, it was power of 2.
    // Must check n > 0 because 0 is not a power of 2.
    return (n > 0 && (n & (n - 1)) == 0);
}

// ==========================================================
// 3. COUNTING AND MANIPULATION
// ==========================================================

int countSetBits(int n) {
    // Brian Kernighan’s Algorithm
    // Repeats only as many times as there are set bits (faster than looping all 32 bits).
    int count = 0;
    while (n > 0) {
        n = (n & (n - 1)); // Removes the rightmost set bit
        count++;
    }
    return count;
}

unsigned int reverseBits(unsigned int n) {
    unsigned int reversed_n = 0;
    for (int i = 0; i < 32; i++) {
        // If the i-th bit of n is set, set the (31-i)-th bit of reversed_n
        if ((n & (1 << i)))
            reversed_n |= (1 << (31 - i));
    }
    return reversed_n;
}

// ==========================================================
// 4. TRICKS AND OPTIMIZATIONS
// ==========================================================

void swapNumbers(int &a, int &b) {
    // XOR Swap Algorithm (No temp variable needed)
    if (a == b) return; // Guard against swapping same memory address
    a = a ^ b;
    b = a ^ b; // b becomes original a
    a = a ^ b; // a becomes original b
}

int clearLastIBits(int n, int i) {
    // Clears bits from index 0 to i-1
    // Example: clear 2 bits of 1111 -> 1100
    // Create mask: ~0 is 111...111. Shift left by i: 111...100
    int mask = (~0 << i);
    return (n & mask);
}

int clearRangeBits(int n, int i, int j) {
    // Clears bits from range i to j (inclusive)
    // Create mask like: 111000111
    int a = (~0) << (j + 1); // 11100000
    int b = (1 << i) - 1;    // 00000111
    int mask = a | b;
    return (n & mask);
}

// ==========================================================
// 5. ARRAY APPLICATIONS (XOR PROBLEMS)
// ==========================================================

int findUnique(const vector<int>& arr) {
    // Finds the one element that appears once while others appear twice.
    // Logic: x ^ x = 0 and x ^ 0 = x
    int xor_sum = 0;
    for (int val : arr) {
        xor_sum ^= val;
    }
    return xor_sum;
}

void findTwoUnique(const vector<int>& arr) {
    // Finds two elements that appear once while others appear twice.
    int xor_sum = 0;
    for (int val : arr) xor_sum ^= val;

    // xor_sum is now (a ^ b). We need to separate a and b.
    // Find the rightmost set bit in xor_sum. 
    // This bit is set in one unique number and unset in the other.
    int set_bit = xor_sum & ~(xor_sum - 1); // Extract rightmost set bit

    int x = 0, y = 0;
    for (int val : arr) {
        if (val & set_bit) {
            x ^= val; // Group 1 (bit is set)
        } else {
            y ^= val; // Group 2 (bit is unset)
        }
    }
    cout << "The two unique numbers are: " << x << " and " << y << endl;
}

// ==========================================================
// DRIVER MENU
// ==========================================================

int main() {
    int choice;
    do {
        cout << "\n============================================\n";
        cout << "   MASTER BINARY MANIPULATION PROGRAM   \n";
        cout << "============================================\n";
        cout << "1.  Get, Set, Clear, Toggle Bit\n";
        cout << "2.  Check Odd/Even & Power of 2\n";
        cout << "3.  Count Set Bits (Population Count)\n";
        cout << "4.  Reverse Bits (32-bit integer)\n";
        cout << "5.  Swap Numbers (XOR Trick)\n";
        cout << "6.  Clear Range of Bits\n";
        cout << "7.  Find Unique Number (in array of duplicates)\n";
        cout << "8.  Find Two Unique Numbers\n";
        cout << "0.  Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n, pos, val;
                cout << "Enter number: "; cin >> n;
                printBinary(n);
                cout << "Enter position (0-indexed): "; cin >> pos;
                
                cout << "Bit at pos " << pos << ": " << getBit(n, pos) << endl;
                cout << "After Set:    " << setBit(n, pos) << endl;
                cout << "After Clear:  " << clearBit(n, pos) << endl;
                cout << "After Toggle: " << toggleBit(n, pos) << endl;
                break;
            }
            case 2: {
                int n;
                cout << "Enter number: "; cin >> n;
                cout << n << " is " << (isEven(n) ? "Even" : "Odd") << endl;
                cout << n << " is " << (isPowerOfTwo(n) ? "a Power of 2" : "NOT a Power of 2") << endl;
                break;
            }
            case 3: {
                int n;
                cout << "Enter number: "; cin >> n;
                printBinary(n);
                cout << "Number of set bits (1s): " << countSetBits(n) << endl;
                break;
            }
            case 4: {
                unsigned int n;
                cout << "Enter number: "; cin >> n;
                printBinary(n);
                unsigned int rev = reverseBits(n);
                cout << "Reversed: " << rev << endl;
                // Note: bitset<32> is better here to see full reversal
                cout << "Binary Rev: " << bitset<32>(rev) << endl; 
                break;
            }
            case 5: {
                int a, b;
                cout << "Enter a and b: "; cin >> a >> b;
                cout << "Before Swap: a=" << a << ", b=" << b << endl;
                swapNumbers(a, b);
                cout << "After Swap:  a=" << a << ", b=" << b << endl;
                break;
            }
            case 6: {
                int n, i, j;
                cout << "Enter number: "; cin >> n;
                printBinary(n);
                cout << "Enter range [i, j] to clear (inclusive): "; cin >> i >> j;
                int res = clearRangeBits(n, i, j);
                cout << "Result: " << res << endl;
                printBinary(res);
                break;
            }
            case 7: {
                int s;
                cout << "Enter size of array: "; cin >> s;
                vector<int> arr(s);
                cout << "Enter elements (all appear twice except one): ";
                for (int &x : arr) cin >> x;
                cout << "Unique element is: " << findUnique(arr) << endl;
                break;
            }
            case 8: {
                int s;
                cout << "Enter size of array: "; cin >> s;
                vector<int> arr(s);
                cout << "Enter elements (all appear twice except two): ";
                for (int &x : arr) cin >> x;
                findTwoUnique(arr);
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
