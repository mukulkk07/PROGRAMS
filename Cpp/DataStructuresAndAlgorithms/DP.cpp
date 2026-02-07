#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

class DPMaster {
public:
    // =================================================================
    // LEVEL 1: THE EVOLUTION OF DP
    // Problem: Climbing Stairs (Fibonacci equivalent)
    // Goal: Count ways to reach step N if you can take 1 or 2 steps.
    // =================================================================

    // 1.1 Pure Recursion (O(2^n) - TLE / Slow)
    int climbRecursive(int n) {
        if (n == 0 || n == 1) return 1;
        return climbRecursive(n - 1) + climbRecursive(n - 2);
    }

    // 1.2 Top-Down: Recursion + Memoization (O(n) Time, O(n) Space)
    int climbMemoization(int n, vector<int>& memo) {
        if (n == 0 || n == 1) return 1;
        
        // CHECK: Have we solved this state before?
        if (memo[n] != -1) return memo[n];

        // STORE: Save result before returning
        return memo[n] = climbMemoization(n - 1, memo) + climbMemoization(n - 2, memo);
    }

    // 1.3 Bottom-Up: Tabulation (O(n) Time, O(n) Space)
    // No recursion overhead. We build the table from base case up.
    int climbTabulation(int n) {
        if (n <= 1) return 1;
        vector<int> dp(n + 1);
        
        // Base Cases
        dp[0] = 1;
        dp[1] = 1;

        // Fill table
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    // 1.4 Space Optimization (O(n) Time, O(1) Space)
    // We only need the last two values, not the whole array.
    int climbSpaceOpt(int n) {
        if (n <= 1) return 1;
        int prev2 = 1, prev1 = 1;
        
        for (int i = 2; i <= n; i++) {
            int current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }

    // =================================================================
    // LEVEL 2: THE KNAPSACK PATTERN (0/1 Knapsack)
    // Problem: Maximize value with weight limit W.
    // Logic: For every item, we have a CHOICE: Include it OR Exclude it.
    // =================================================================
    int knapsack(int W, const vector<int>& weights, const vector<int>& values) {
        int n = weights.size();
        // dp[i][w] = Max value using first 'i' items with weight limit 'w'
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                int weight = weights[i - 1];
                int value = values[i - 1];

                if (weight <= w) {
                    // Option A: Exclude item 'i' (Take value from row above)
                    // Option B: Include item 'i' (Add val + value from remaining weight)
                    dp[i][w] = max(dp[i - 1][w], 
                                   value + dp[i - 1][w - weight]);
                } else {
                    // Cannot include (too heavy), copy from previous row
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][W];
    }

    // =================================================================
    // LEVEL 3: STRING DP (Longest Common Subsequence)
    // Problem: Find length of longest subsequence common to Text1 and Text2.
    // Logic: If chars match, 1 + diagonal. If not, max(left, up).
    // =================================================================
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        
        // dp[i][j] represents LCS of text1[0..i] and text2[0..j]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // Char indices are 0-based, DP is 1-based
                if (text1[i - 1] == text2[j - 1]) {
                    // Match found: Extend the result from the diagonal (removing both chars)
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    // No match: Take best from excluding char from text1 OR text2
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][m];
    }

    // =================================================================
    // LEVEL 4: LINEAR DP (Longest Increasing Subsequence)
    // Problem: Find the length of the longest subsequence that is strictly increasing.
    // Logic: Compare current number with all previous numbers.
    // =================================================================
    int lengthOfLIS(const vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        
        // dp[i] = Length of LIS ending at index i
        // Initialize all to 1 (each element is an LIS of length 1)
        vector<int> dp(n, 1);
        int max_len = 1;

        for (int i = 1; i < n; i++) {
            // Check all previous elements (j < i)
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    // If current number > previous, we can extend that sequence
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_len = max(max_len, dp[i]);
        }
        return max_len;
    }
};

int main() {
    DPMaster solver;

    // --- TEST 1: The Evolution (Climbing Stairs) ---
    int steps = 10;
    vector<int> memo(steps + 1, -1);
    cout << "--- 1. DP Evolution (Climbing 10 stairs) ---" << endl;
    cout << "Recursive: " << solver.climbRecursive(steps) << endl;
    cout << "Memoized:  " << solver.climbMemoization(steps, memo) << endl;
    cout << "Tabulated: " << solver.climbTabulation(steps) << endl;
    cout << "Optimized: " << solver.climbSpaceOpt(steps) << endl;

    // --- TEST 2: 0/1 Knapsack ---
    // Items: {Weight, Value} -> {1, 4}, {3, 9}, {4, 10}
    vector<int> weights = {1, 3, 4, 5};
    vector<int> values = {1, 4, 5, 7};
    int capacity = 7;
    cout << "\n--- 2. Knapsack (Capacity 7) ---" << endl;
    cout << "Max Value: " << solver.knapsack(capacity, weights, values) << endl;

    // --- TEST 3: LCS ---
    string s1 = "abcde";
    string s2 = "ace"; 
    cout << "\n--- 3. Longest Common Subsequence ---" << endl;
    cout << "LCS of '" << s1 << "' & '" << s2 << "': " 
         << solver.longestCommonSubsequence(s1, s2) << endl; // Expect 3 ("ace")

    // --- TEST 4: LIS ---
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "\n--- 4. Longest Increasing Subsequence ---" << endl;
    cout << "LIS Length: " << solver.lengthOfLIS(arr) << endl; // Expect 4 (2, 3, 7, 18)

    return 0;
}