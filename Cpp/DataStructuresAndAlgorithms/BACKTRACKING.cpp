#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BacktrackingMaster {
public:
    // ==========================================
    // PATTERN 1: SUBSETS (Include vs Exclude)
    // Goal: Generate all possible subsets (Power Set)
    // Logic: For every number, we have two choices: take it or leave it.
    // ==========================================
    void solveSubsets(vector<int>& nums) {
        vector<vector<int>> results;
        vector<int> current;
        cout << "--- 1. Subsets ---" << endl;
        backtrackSubsets(nums, 0, current, results);
        
        // Print results
        for (const auto& subset : results) {
            cout << "[ ";
            for (int num : subset) cout << num << " ";
            cout << "]" << endl;
        }
    }

private:
    void backtrackSubsets(vector<int>& nums, int index, vector<int>& current, vector<vector<int>>& results) {
        // BASE CASE: We've considered all elements
        if (index == nums.size()) {
            results.push_back(current);
            return;
        }

        // OPTION A: Include the number at 'index'
        current.push_back(nums[index]);      // 1. MAKE MOVE
        backtrackSubsets(nums, index + 1, current, results); // 2. RECURSE
        current.pop_back();                  // 3. BACKTRACK (Undo move)

        // OPTION B: Exclude the number at 'index'
        // We do nothing to 'current', just move to next index
        backtrackSubsets(nums, index + 1, current, results);
    }

public:
    // ==========================================
    // PATTERN 2: PERMUTATIONS (Ordering)
    // Goal: Generate all distinctive orderings of an array
    // Logic: Swap current element with every subsequent element
    // ==========================================
    void solvePermutations(vector<int>& nums) {
        vector<vector<int>> results;
        cout << "\n--- 2. Permutations ---" << endl;
        backtrackPermutations(nums, 0, results);
        
        for (const auto& p : results) {
            cout << "[ ";
            for (int num : p) cout << num << " ";
            cout << "]" << endl;
        }
    }

private:
    void backtrackPermutations(vector<int>& nums, int start, vector<vector<int>>& results) {
        // BASE CASE: If we've reached the end of the array
        if (start == nums.size()) {
            results.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);          // 1. MAKE MOVE (Swap to put nums[i] in 'start' pos)
            backtrackPermutations(nums, start + 1, results); // 2. RECURSE
            swap(nums[start], nums[i]);          // 3. BACKTRACK (Swap back to restore state)
        }
    }

public:
    // ==========================================
    // PATTERN 3: N-QUEENS (Constraint Satisfaction)
    // Goal: Place N queens so no two attack each other
    // Logic: Try placing a queen in row 'r', check validity, move to row 'r+1'
    // ==========================================
    void solveNQueens(int n) {
        vector<vector<string>> results;
        // Initialize board with empty dots
        vector<string> board(n, string(n, '.')); 
        cout << "\n--- 3. N-Queens (First Solution Only) ---" << endl;
        
        backtrackNQueens(board, 0, n);
    }

private:
    // Helper to check if placing Queen at board[row][col] is safe
    bool isSafe(vector<string>& board, int row, int col, int n) {
        // Check column above
        for (int i = 0; i < row; i++)
            if (board[i][col] == 'Q') return false;

        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q') return false;

        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
            if (board[i][j] == 'Q') return false;

        return true;
    }

    bool backtrackNQueens(vector<string>& board, int row, int n) {
        // BASE CASE: All queens placed successfully
        if (row == n) {
            // Print the board
            for (const string& rowStr : board) cout << rowStr << endl;
            return true; // Return true to stop after finding ONE solution
        }

        // Try every column in the current row
        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q';           // 1. MAKE MOVE
                
                if (backtrackNQueens(board, row + 1, n)) return true; // 2. RECURSE
                
                board[row][col] = '.';           // 3. BACKTRACK (Remove Queen)
            }
        }
        return false;
    }

public:
    // ==========================================
    // PATTERN 4: GRID TRAVERSAL (Rat in a Maze)
    // Goal: Find a path from (0,0) to (N-1, N-1)
    // Logic: Try 4 directions (Down, Right, Up, Left). Mark visited to avoid cycles.
    // ==========================================
    void solveMaze(vector<vector<int>>& maze) {
        int n = maze.size();
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        string path = "";
        cout << "\n--- 4. Rat in a Maze ---" << endl;
        
        if (!backtrackMaze(maze, 0, 0, visited, path)) {
            cout << "No path found!" << endl;
        }
    }

private:
    bool backtrackMaze(vector<vector<int>>& maze, int r, int c, vector<vector<bool>>& visited, string& path) {
        int n = maze.size();
        
        // BASE CASE: Reached bottom-right
        if (r == n - 1 && c == n - 1) {
            cout << "Path: " << path << endl;
            return true;
        }

        // BOUNDARY & VALIDITY CHECKS
        // 1. Out of bounds? 2. Wall (0)? 3. Already visited?
        if (r < 0 || c < 0 || r >= n || c >= n || maze[r][c] == 0 || visited[r][c]) {
            return false;
        }

        visited[r][c] = true; // 1. MAKE MOVE (Mark visited)

        // Try all 4 directions: Down(D), Right(R), Up(U), Left(L)
        // Note: The order matters. Here we prioritize Down and Right.
        
        path += 'D';
        if (backtrackMaze(maze, r + 1, c, visited, path)) return true; // Recurse Down
        path.pop_back(); // Backtrack string

        path += 'R';
        if (backtrackMaze(maze, r, c + 1, visited, path)) return true; // Recurse Right
        path.pop_back();

        path += 'U';
        if (backtrackMaze(maze, r - 1, c, visited, path)) return true; // Recurse Up
        path.pop_back();

        path += 'L';
        if (backtrackMaze(maze, r, c - 1, visited, path)) return true; // Recurse Left
        path.pop_back();

        visited[r][c] = false; // 3. BACKTRACK (Unmark visited)
        return false;
    }
};

int main() {
    BacktrackingMaster solver;

    // 1. Subsets
    vector<int> nums = {1, 2, 3};
    solver.solveSubsets(nums);

    // 2. Permutations
    vector<int> pNums = {1, 2, 3};
    solver.solvePermutations(pNums);

    // 3. N-Queens (4x4 board)
    solver.solveNQueens(4);

    // 4. Rat in a Maze (1 is open, 0 is wall)
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    solver.solveMaze(maze);

    return 0;
}