#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits> // For INT_MIN, INT_MAX
#include <algorithm> // For max, min

using namespace std;

class SlidingWindowMaster {
public:
    // ==========================================
    // STRATEGY 1: FIXED SIZE WINDOW
    // Use Case: "Find the max/min/sum of every subarray of size K"
    // ==========================================
    int maxSumFixedWindow(const vector<int>& nums, int k) {
        if (nums.size() < k) return -1; // Edge case

        int max_sum = INT_MIN;
        int current_sum = 0;

        // Step 1: Initialize the first window [0 to k-1]
        for (int i = 0; i < k; i++) {
            current_sum += nums[i];
        }
        max_sum = current_sum;

        // Step 2: Slide the window
        // 'right' is the new element entering the window
        // 'right - k' is the old element leaving the window
        for (int right = k; right < nums.size(); right++) {
            current_sum += nums[right];       // Add new element
            current_sum -= nums[right - k];   // Remove old element
            
            max_sum = max(max_sum, current_sum); // Update result
        }
        return max_sum;
    }

    // ==========================================
    // STRATEGY 2: VARIABLE WINDOW (SHRINKING)
    // Use Case: "Find smallest subarray with sum >= Target"
    // Logic: Expand right until valid, then shrink left to optimize
    // ==========================================
    int minSubArrayLen(int target, const vector<int>& nums) {
        int min_len = INT_MAX;
        int current_sum = 0;
        int left = 0; 

        // Step 1: Expand window (move 'right')
        for (int right = 0; right < nums.size(); right++) {
            current_sum += nums[right];

            // Step 2: Contract window (move 'left') ONLY while condition is met
            while (current_sum >= target) {
                // We found a valid window, check if it's the smallest so far
                int current_window_size = right - left + 1;
                min_len = min(min_len, current_window_size);

                // Shrink: Remove left element and move pointer
                current_sum -= nums[left];
                left++;
            }
        }

        return (min_len == INT_MAX) ? 0 : min_len;
    }

    // ==========================================
    // STRATEGY 3: VARIABLE WINDOW (WITH HASH MAP)
    // Use Case: "Longest substring with at most K distinct characters"
    // Logic: Use a Map to track frequency within the window
    // ==========================================
    int longestSubstringKDistinct(string s, int k) {
        if (s.empty() || k == 0) return 0;

        unordered_map<char, int> char_counts;
        int max_len = 0;
        int left = 0;

        // Step 1: Expand right
        for (int right = 0; right < s.length(); right++) {
            char incoming = s[right];
            char_counts[incoming]++;

            // Step 2: If window is invalid (distinct chars > k), shrink from left
            while (char_counts.size() > k) {
                char outgoing = s[left];
                char_counts[outgoing]--;
                
                // Crucial: If count hits 0, remove key completely so .size() is accurate
                if (char_counts[outgoing] == 0) {
                    char_counts.erase(outgoing);
                }
                left++;
            }

            // Step 3: Update result (Window is guaranteed valid here)
            max_len = max(max_len, right - left + 1);
        }

        return max_len;
    }
};

int main() {
    SlidingWindowMaster solver;

    // --- Test 1: Fixed Window ---
    vector<int> nums1 = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k = 4;
    cout << "1. Fixed Window (Max sum of size 4): " 
         << solver.maxSumFixedWindow(nums1, k) << endl; 
    // Expect: 39 (4+2+10+23)

    // --- Test 2: Variable Window (Min Subarray) ---
    vector<int> nums2 = {2, 3, 1, 2, 4, 3};
    int target = 7;
    cout << "2. Variable Window (Min len for sum >= 7): " 
         << solver.minSubArrayLen(target, nums2) << endl;
    // Expect: 2 (Subarray [4,3])

    // --- Test 3: Variable Window (With Map) ---
    string s = "eceba";
    int distinct_k = 2;
    cout << "3. Variable Window (Longest substring with 2 distinct chars): " 
         << solver.longestSubstringKDistinct(s, distinct_k) << endl;
    // Expect: 3 ("ece")

    return 0;
}