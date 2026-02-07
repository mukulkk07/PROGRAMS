#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

// ==========================================================
// UTILITIES
// ==========================================================
// Function to generate a random number in range [min, max]
int randomRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// ==========================================================
// 1. RANDOMIZED QUICKSORT (Las Vegas Algorithm)
// ==========================================================
// TYPE: Las Vegas (Always correct, time varies).
// LOGIC: Instead of picking the last/first element as pivot, 
// we pick a random element. This destroys worst-case O(n^2) inputs.

int partition(vector<int>& arr, int low, int high) {
    // Randomized Pivot Selection
    int randomIndex = randomRange(low, high);
    swap(arr[randomIndex], arr[high]); // Move pivot to end

    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

// ==========================================================
// 2. RANDOMIZED SELECTION / QUICKSELECT (Las Vegas Algorithm)
// ==========================================================
// TYPE: Las Vegas.
// LOGIC: Finds the k-th smallest element in O(n) expected time.
// Uses the same random partition logic as Quicksort.

int randomizedSelect(vector<int>& arr, int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int pos = partition(arr, low, high);

        // If position is same as k
        if (pos - low == k - 1)
            return arr[pos];
        
        // If position is more, recur for left subarray
        if (pos - low > k - 1)
            return randomizedSelect(arr, low, pos - 1, k);

        // Else recur for right subarray
        return randomizedSelect(arr, pos + 1, high, k - pos + low - 1);
    }
    return INT_MAX;
}

// ==========================================================
// 3. FERMAT PRIMALITY TEST (Monte Carlo Algorithm)
// ==========================================================
// TYPE: Monte Carlo (Fixed time, small chance of error).
// LOGIC: Based on Fermat's Little Theorem: a^(n-1) == 1 (mod n).
// If this holds for many random 'a', 'n' is likely prime.

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return res;
}

bool fermatTest(long long n, int iterations = 5) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    for (int i = 0; i < iterations; i++) {
        // Pick a random number in [2..n-2]
        long long a = 2 + rand() % (n - 3);
        // Fermat's Little Theorem check
        if (power(a, n - 1, n) != 1)
            return false; // Composite
    }
    return true; // Probably Prime
}

// ==========================================================
// 4. MONTE CARLO ESTIMATION OF PI (Monte Carlo)
// ==========================================================
// TYPE: Monte Carlo (Approximation).
// LOGIC: Throw random darts at a square inscribing a circle.
// Ratio of points in circle to total points ~ Pi/4.

double estimatePi(int total_points) {
    int circle_points = 0;
    for (int i = 0; i < total_points; i++) {
        // Generate random x and y between 0 and 1
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // Check if point is inside unit circle
        if ((x * x + y * y) <= 1.0)
            circle_points++;
    }
    return 4.0 * circle_points / total_points;
}

// ==========================================================
// 5. KARGER'S MIN CUT ALGORITHM (Monte Carlo)
// ==========================================================
// TYPE: Monte Carlo.
// LOGIC: Randomly contract edges until only 2 vertices remain.
// The edges between the 2 vertices represent a "cut".

struct Edge {
    int src, dest;
};

struct Subset {
    int parent;
    int rank;
};

// Find set of an element i (uses path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int kargerMinCut(int V, int E, vector<Edge>& edges) {
    // Allocate memory for creating V subsets
    struct Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int vertices = V;
    
    // Iterate until only 2 vertices remain
    while (vertices > 2) {
        // Pick a random edge
        int i = rand() % E;

        // Find subsets (components) of the vertices of the edge
        int subset1 = find(subsets, edges[i].src);
        int subset2 = find(subsets, edges[i].dest);

        // If they belong to different sets, merge them (Contract edge)
        if (subset1 != subset2) {
            Union(subsets, subset1, subset2);
            vertices--;
        }
    }

    // Count edges crossing the cut
    int cutedges = 0;
    for (int i = 0; i < E; i++) {
        int subset1 = find(subsets, edges[i].src);
        int subset2 = find(subsets, edges[i].dest);
        if (subset1 != subset2)
            cutedges++;
    }
    
    delete[] subsets;
    return cutedges;
}

// ==========================================================
// 6. FISHER-YATES SHUFFLE
// ==========================================================
// TYPE: Random Permutation.
// LOGIC: Generates a random permutation of a finite sequence.
// O(n) time complexity.

void fisherYatesShuffle(vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i > 0; i--) {
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

// ==========================================================
// DRIVER MENU
// ==========================================================

int main() {
    // Seed random number generator
    srand(time(0));

    int choice;
    do {
        cout << "\n============================================\n";
        cout << "   MASTER RANDOMIZED ALGORITHMS PROGRAM   \n";
        cout << "============================================\n";
        cout << "1. Randomized Quicksort (Las Vegas)\n";
        cout << "2. Randomized Quickselect (Find K-th Smallest)\n";
        cout << "3. Fermat Primality Test (Monte Carlo)\n";
        cout << "4. Estimate Pi Value (Monte Carlo)\n";
        cout << "5. Karger's Min Cut (Monte Carlo Graph)\n";
        cout << "6. Fisher-Yates Shuffle (Random Permutation)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                cout << "Enter array size: "; cin >> n;
                vector<int> arr(n);
                cout << "Enter elements: ";
                for (int& x : arr) cin >> x;
                randomizedQuickSort(arr, 0, n - 1);
                cout << "Sorted Array: ";
                for (int x : arr) cout << x << " ";
                cout << endl;
                break;
            }
            case 2: {
                int n, k;
                cout << "Enter array size: "; cin >> n;
                vector<int> arr(n);
                cout << "Enter elements: ";
                for (int& x : arr) cin >> x;
                cout << "Enter k (1 to " << n << "): "; cin >> k;
                int val = randomizedSelect(arr, 0, n - 1, k);
                cout << "The " << k << "-th smallest element is: " << val << endl;
                break;
            }
            case 3: {
                long long num;
                cout << "Enter number to check primality: "; cin >> num;
                if (fermatTest(num))
                    cout << num << " is probably Prime." << endl;
                else
                    cout << num << " is Composite." << endl;
                break;
            }
            case 4: {
                int points;
                cout << "Enter number of points to simulate (e.g., 100000): "; cin >> points;
                double pi = estimatePi(points);
                cout << "Estimated Pi: " << pi << endl;
                cout << "Actual Pi:    " << 3.1415926535 << endl;
                break;
            }
            case 5: {
                int V, E;
                cout << "Enter vertices (0 to V-1) and edges: "; cin >> V >> E;
                vector<Edge> edges(E);
                cout << "Enter source and destination for " << E << " edges:\n";
                for (int i = 0; i < E; i++) {
                    cin >> edges[i].src >> edges[i].dest;
                }
                // Karger's sometimes fails, so we run it multiple times usually.
                // Here we run it once for demonstration.
                cout << "Running Karger's algorithm..." << endl;
                cout << "Minimum Cut found: " << kargerMinCut(V, E, edges) << endl;
                cout << "(Note: As a Monte Carlo algo, run multiple times for higher accuracy)" << endl;
                break;
            }
            case 6: {
                int n;
                cout << "Enter array size: "; cin >> n;
                vector<int> arr(n);
                // Initialize with 1 to n
                iota(arr.begin(), arr.end(), 1); 
                cout << "Original Array: ";
                for(int x : arr) cout << x << " "; cout << endl;
                
                fisherYatesShuffle(arr);
                
                cout << "Shuffled Array: ";
                for (int x : arr) cout << x << " ";
                cout << endl;
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