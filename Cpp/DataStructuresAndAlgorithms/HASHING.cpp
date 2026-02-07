#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>

using namespace std;

class HashingMaster {
public:
    // ==========================================
    // PATTERN 1: FREQUENCY MAP & LOOKUP
    // Use Case: "Find the first non-repeating character", "Two Sum", "Anagrams"
    // Logic: Store counts or indices for O(1) retrieval later.
    // ==========================================
    
    // Problem A: First Unique Character
    char firstUniqChar(string s) {
        unordered_map<char, int> countMap;

        // Pass 1: Build frequency map
        for (char c : s) countMap[c]++;

        // Pass 2: Check order
        for (char c : s) {
            if (countMap[c] == 1) return c;
        }
        return '_'; 
    }

    // Problem B: Two Sum (Find indices that add up to target)
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen; // Maps: Number -> Index

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];

            // Have we seen the needed number before?
            if (seen.find(complement) != seen.end()) {
                return {seen[complement], i};
            }

            // Store current number and index
            seen[nums[i]] = i;
        }
        return {}; 
    }

    // ==========================================
    // PATTERN 2: PREFIX SUM HASHING
    // Use Case: "Subarray Sum equals K", "Longest Subarray with sum K"
    // Logic: If (CumulativeSum[i] - CumulativeSum[j]) == K, 
    //        then the subarray between j and i sums to K.
    // ==========================================
    int subarraySumEqualsK(vector<int>& nums, int k) {
        // Map stores: {PrefixSum -> Frequency of that sum}
        unordered_map<int, int> prefixSumCounts;
        
        int count = 0;
        int currentSum = 0;

        // BASE CASE: A sum of 0 exists once (conceptually before the array starts)
        // This handles cases where a subarray starting at index 0 equals K.
        prefixSumCounts[0] = 1;

        for (int num : nums) {
            currentSum += num;

            // Mathematical Magic:
            // We need: currentSum - "some old sum" = k
            // So: "some old sum" = currentSum - k
            if (prefixSumCounts.find(currentSum - k) != prefixSumCounts.end()) {
                count += prefixSumCounts[currentSum - k];
            }

            // Add current sum to history
            prefixSumCounts[currentSum]++;
        }
        return count;
    }

    // ==========================================
    // PATTERN 3: ROLLING HASH (Rabin-Karp)
    // Use Case: "Find pattern in text", "Longest Duplicate Substring"
    // Logic: Treat string as a base-26 number. Slide window and update hash in O(1).
    // Hash(new) = (Hash(old) - LeadingVal) * Base + TrailingVal
    // ==========================================
    int searchPatternRollingHash(string text, string pattern) {
        int n = text.length();
        int m = pattern.length();
        if (m > n) return -1;

        long long pHash = 0; // Pattern hash
        long long tHash = 0; // Text window hash
        long long h = 1;     // The value of the most significant digit position
        int base = 256;      // Alphabet size
        int prime = 101;     // Prime number to reduce collisions

        // 1. Precompute 'h' = pow(base, m-1) % prime
        for (int i = 0; i < m - 1; i++)
            h = (h * base) % prime;

        // 2. Calculate initial hashes
        for (int i = 0; i < m; i++) {
            pHash = (base * pHash + pattern[i]) % prime;
            tHash = (base * tHash + text[i]) % prime;
        }

        // 3. Slide the window
        for (int i = 0; i <= n - m; i++) {
            // Check if hash matches
            if (pHash == tHash) {
                // Verify characters to rule out collisions
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) return i; 
            }

            // Calculate hash for NEXT window
            if (i < n - m) {
                // Remove leading char, shift left, add new trailing char
                tHash = (base * (tHash - text[i] * h) + text[i + m]) % prime;

                // Handle negative results from modulo arithmetic
                if (tHash < 0) tHash = (tHash + prime);
            }
        }
        return -1;
    }
};

int main() {
    HashingMaster solver;

    // --- TEST 1: Basic Map ---
    string s = "leetcode";
    cout << "1. First Unique Char in '" << s << "': " << solver.firstUniqChar(s) << endl; 

    // --- TEST 2: Two Sum ---
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> res = solver.twoSum(nums, target);
    cout << "2. Two Sum Indices: [" << res[0] << ", " << res[1] << "]" << endl;

    // --- TEST 3: Prefix Hash ---
    vector<int> arr = {1, -1, 1, 1, 1, 1}; 
    int k = 3; 
    // Subarrays: [1,1,1] (indices 2-4) and [1,1,1] (indices 3-5)
    cout << "3. Subarrays with sum " << k << ": " << solver.subarraySumEqualsK(arr, k) << endl; 

    // --- TEST 4: Rolling Hash ---
    string text = "GEEKS FOR GEEKS";
    string pat = "FOR";
    cout << "4. Pattern '" << pat << "' found at index: " << solver.searchPatternRollingHash(text, pat) << endl;

    return 0;
}