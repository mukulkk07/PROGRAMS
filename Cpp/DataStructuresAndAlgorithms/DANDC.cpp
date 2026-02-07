#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cfloat>
#include<string.h>

using namespace std;

// ==========================================================
// 1. BINARY SEARCH (Divide and Conquer for Searching)
// ==========================================================
// DIVIDE: Find the middle element.
// CONQUER: Recursively search the left or right subarray.
// COMBINE: The index is returned directly.

int binarySearch(const vector<int>& arr, int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] > target)
            return binarySearch(arr, left, mid - 1, target);

        return binarySearch(arr, mid + 1, right, target);
    }
    return -1;
}

// ==========================================================
// 2. MERGE SORT (Divide and Conquer for Sorting)
// ==========================================================
// DIVIDE: Split array into two halves.
// CONQUER: Sort the two halves recursively.
// COMBINE: Merge the sorted halves.

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ==========================================================
// 3. QUICK SORT (Divide and Conquer for Sorting)
// ==========================================================
// DIVIDE: Partition array around a pivot.
// CONQUER: Sort subarrays before and after pivot recursively.
// COMBINE: No explicit combine step needed (in-place).

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ==========================================================
// 4. MAXIMUM SUBARRAY SUM (Optimization)
// ==========================================================
// DIVIDE: Split array into two halves.
// CONQUER: Find max sum in left, right, and crossing middle.
// COMBINE: Return the maximum of the three.

int maxCrossingSum(const vector<int>& arr, int l, int m, int h) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--) {
        sum = sum + arr[i];
        if (sum > left_sum) left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m + 1; i <= h; i++) {
        sum = sum + arr[i];
        if (sum > right_sum) right_sum = sum;
    }
    return max(left_sum + right_sum, max(left_sum, right_sum)); // Handle single element cases logic carefully
}

int maxSubArraySum(const vector<int>& arr, int l, int h) {
    if (l == h) return arr[l];
    int m = (l + h) / 2;
    return max({maxSubArraySum(arr, l, m),
                maxSubArraySum(arr, m + 1, h),
                maxCrossingSum(arr, l, m, h)});
}

// ==========================================================
// 5. KARATSUBA ALGORITHM (Fast Multiplication)
// ==========================================================
// DIVIDE: Split numbers into high and low bits.
// CONQUER: Recursively multiply parts.
// COMBINE: Apply formula: x*y = ac*10^n + (ad+bc)*10^(n/2) + bd

int getLength(long long value) {
    string str = to_string(abs(value));
    return str.length();
}

long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) return x * y;

    int n = max(getLength(x), getLength(y));
    int half = n / 2;
    long long multiplier = pow(10, half);

    long long a = x / multiplier;
    long long b = x % multiplier;
    long long c = y / multiplier;
    long long d = y % multiplier;

    long long ac = karatsuba(a, c);
    long long bd = karatsuba(b, d);
    long long ad_plus_bc = karatsuba(a + b, c + d) - ac - bd;

    return ac * (long long)pow(10, 2 * half) + ad_plus_bc * multiplier + bd;
}

// ==========================================================
// 6. TOWER OF HANOI (Puzzle/Recursion)
// ==========================================================
// DIVIDE: Move n-1 disks from Source to Aux.
// CONQUER: Move nth disk from Source to Destination.
// COMBINE: Move n-1 disks from Aux to Destination.

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 0) return;
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << endl;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

// ==========================================================
// 7. CLOSEST PAIR OF POINTS (Geometric)
// ==========================================================
// DIVIDE: Split points into left and right subsets.
// CONQUER: Find closest pair in left and right.
// COMBINE: Check the "strip" in the middle for closer points.

struct Point {
    int x, y;
};

bool compareX(const Point& a, const Point& b) { return a.x < b.x; }
bool compareY(const Point& a, const Point& b) { return a.y < b.y; }

float dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForceClosest(vector<Point>& P, int n) {
    float min_dist = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min_dist)
                min_dist = dist(P[i], P[j]);
    return min_dist;
}

float stripClosest(vector<Point>& strip, float d) {
    float min_val = d;
    sort(strip.begin(), strip.end(), compareY);

    for (int i = 0; i < strip.size(); ++i)
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_val; ++j)
            if (dist(strip[i], strip[j]) < min_val)
                min_val = dist(strip[i], strip[j]);
    return min_val;
}

float closestUtil(vector<Point>& P, int n) {
    if (n <= 3) return bruteForceClosest(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    vector<Point> Pl(P.begin(), P.begin() + mid);
    vector<Point> Pr(P.begin() + mid, P.end());

    float dl = closestUtil(Pl, mid);
    float dr = closestUtil(Pr, n - mid);
    float d = min(dl, dr);

    vector<Point> strip;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip.push_back(P[i]);

    return min(d, stripClosest(strip, d));
}

float closestPair(vector<Point>& P) {
    sort(P.begin(), P.end(), compareX);
    return closestUtil(P, P.size());
}

// ==========================================================
// DRIVER MENU
// ==========================================================

int main() {
    int choice;
    do {
        cout << "\n============================================\n";
        cout << "   MASTER DIVIDE & CONQUER PROGRAM   \n";
        cout << "============================================\n";
        cout << "1. Binary Search\n";
        cout << "2. Merge Sort\n";
        cout << "3. Quick Sort\n";
        cout << "4. Maximum Subarray Sum\n";
        cout << "5. Karatsuba Multiplication\n";
        cout << "6. Tower of Hanoi\n";
        cout << "7. Closest Pair of Points\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n, target;
                cout << "Enter number of elements: "; cin >> n;
                vector<int> arr(n);
                cout << "Enter sorted elements: ";
                for (int& x : arr) cin >> x;
                cout << "Enter target: "; cin >> target;
                int res = binarySearch(arr, 0, n - 1, target);
                if (res != -1) cout << "Element found at index " << res << endl;
                else cout << "Element not found" << endl;
                break;
            }
            case 2: {
                int n;
                cout << "Enter number of elements: "; cin >> n;
                vector<int> arr(n);
                cout << "Enter elements: ";
                for (int& x : arr) cin >> x;
                mergeSort(arr, 0, n - 1);
                cout << "Sorted Array (Merge Sort): ";
                for (int x : arr) cout << x << " ";
                cout << endl;
                break;
            }
            case 3: {
                int n;
                cout << "Enter number of elements: "; cin >> n;
                vector<int> arr(n);
                cout << "Enter elements: ";
                for (int& x : arr) cin >> x;
                quickSort(arr, 0, n - 1);
                cout << "Sorted Array (Quick Sort): ";
                for (int x : arr) cout << x << " ";
                cout << endl;
                break;
            }
            case 4: {
                int n;
                cout << "Enter number of elements: "; cin >> n;
                vector<int> arr(n);
                cout << "Enter elements (include negatives): ";
                for (int& x : arr) cin >> x;
                cout << "Maximum Contiguous Sum is: " << maxSubArraySum(arr, 0, n - 1) << endl;
                break;
            }
            case 5: {
                long long x, y;
                cout << "Enter two numbers to multiply: ";
                cin >> x >> y;
                cout << "Product (Karatsuba): " << karatsuba(x, y) << endl;
                break;
            }
            case 6: {
                int n;
                cout << "Enter number of disks: "; cin >> n;
                towerOfHanoi(n, 'A', 'C', 'B');
                break;
            }
            case 7: {
                int n;
                cout << "Enter number of points: "; cin >> n;
                vector<Point> P(n);
                cout << "Enter points (x y):\n";
                for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;
                cout << "Smallest distance is: " << closestPair(P) << endl;
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}