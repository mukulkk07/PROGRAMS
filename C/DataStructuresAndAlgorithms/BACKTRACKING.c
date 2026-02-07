#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20
#define SUDOKU_N 9

// ================= 1. N-QUEENS PROBLEM =================

void printNQueens(int board[MAX][MAX], int N) {
    printf("\n--- N-Queens Solution ---\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %s ", board[i][j] ? "Q" : ".");
        }
        printf("\n");
    }
}

// Function to check if a queen can be placed on board[row][col]
bool isSafeNQ(int board[MAX][MAX], int row, int col, int N) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i]) return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j]) return false;

    return true;
}

bool solveNQUtil(int board[MAX][MAX], int col, int N) {
    // Base case: If all queens are placed
    if (col >= N) return true;

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < N; i++) {
        if (isSafeNQ(board, i, col, N)) {
            board[i][col] = 1; // Place queen

            // Recur to place rest of the queens
            if (solveNQUtil(board, col + 1, N)) return true;

            // If placing queen in board[i][col] doesn't lead to a solution
            // then remove queen from board[i][col] (BACKTRACK)
            board[i][col] = 0;
        }
    }
    return false;
}

void solveNQueens() {
    int N;
    int board[MAX][MAX];
    
    printf("\n--- N-Queens Problem ---\n");
    printf("Enter the size of the board (N): ");
    scanf("%d", &N);

    // Initialize board
    for(int i=0; i<N; i++) 
        for(int j=0; j<N; j++) 
            board[i][j] = 0;

    if (!solveNQUtil(board, 0, N)) {
        printf("Solution does not exist.\n");
    } else {
        printNQueens(board, N);
    }
}

// ================= 2. SUDOKU SOLVER =================

void printSudoku(int grid[SUDOKU_N][SUDOKU_N]) {
    printf("\n--- Sudoku Solution ---\n");
    for (int row = 0; row < SUDOKU_N; row++) {
        if(row % 3 == 0 && row != 0) printf("---------------------\n");
        for (int col = 0; col < SUDOKU_N; col++) {
            if(col % 3 == 0 && col != 0) printf("| ");
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

bool isSafeSudoku(int grid[SUDOKU_N][SUDOKU_N], int row, int col, int num) {
    // Check Row
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num) return false;

    // Check Column
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num) return false;

    // Check 3x3 Box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num) return false;

    return true;
}

bool solveSudokuUtil(int grid[SUDOKU_N][SUDOKU_N], int row, int col) {
    // If we have reached the 8th row and 9th col (0 indexed), we are done
    if (row == SUDOKU_N - 1 && col == SUDOKU_N) return true;

    // Move to next row if we reached end of column
    if (col == SUDOKU_N) {
        row++;
        col = 0;
    }

    // Skip filled cells
    if (grid[row][col] > 0) return solveSudokuUtil(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafeSudoku(grid, row, col, num)) {
            grid[row][col] = num; // Assume

            if (solveSudokuUtil(grid, row, col + 1)) return true;

            grid[row][col] = 0; // BACKTRACK
        }
    }
    return false;
}

void solveSudoku() {
    printf("\n--- Sudoku Solver ---\n");
    printf("Using a default hard puzzle for demonstration...\n");
    
    // A sample hard puzzle (0 represents empty cells)
    int grid[SUDOKU_N][SUDOKU_N] = { 
        { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
        { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
        { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
        { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
        { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
        { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
        { 0, 0, 5, 2, 0, 6, 3, 0, 0 } 
    };

    printSudoku(grid); // Print initial state
    
    if (solveSudokuUtil(grid, 0, 0))
        printSudoku(grid); // Print solved state
    else
        printf("No solution exists\n");
}

// ================= 3. HAMILTONIAN CYCLE =================

bool isSafeHam(int v, int graph[MAX][MAX], int path[], int pos) {
    // Check if this vertex is an adjacent vertex of the previously added vertex
    if (graph[path[pos - 1]][v] == 0) return false;

    // Check if the vertex has already been included
    for (int i = 0; i < pos; i++)
        if (path[i] == v) return false;

    return true;
}

bool hamCycleUtil(int graph[MAX][MAX], int path[], int pos, int V) {
    // Base Case: If all vertices are included in Hamiltonian Path
    if (pos == V) {
        // And if there is an edge from the last included vertex to the first vertex
        if (graph[path[pos - 1]][path[0]] == 1) return true;
        else return false;
    }

    // Try different vertices as a next candidate in Hamiltonian Cycle
    for (int v = 1; v < V; v++) {
        if (isSafeHam(v, graph, path, pos)) {
            path[pos] = v;

            if (hamCycleUtil(graph, path, pos + 1, V)) return true;

            path[pos] = -1; // BACKTRACK
        }
    }
    return false;
}

void solveHamiltonian() {
    int V;
    int graph[MAX][MAX];
    int path[MAX];

    printf("\n--- Hamiltonian Cycle ---\n");
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter Adjacency Matrix (0 or 1):\n");
    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    for (int i = 0; i < V; i++) path[i] = -1;
    path[0] = 0; // Start at vertex 0

    if (!hamCycleUtil(graph, path, 1, V)) {
        printf("\nSolution does not exist\n");
    } else {
        printf("\nHamiltonian Cycle Found: \n");
        for (int i = 0; i < V; i++) printf(" %d ->", path[i]);
        printf(" %d\n", path[0]); // Complete the loop
    }
}

// ================= 4. SUBSET SUM PROBLEM =================

bool subsetSumUtil(int set[], int subset[], int n, int subSize, int total, int nodeCount, int target) {
    if (total == target) {
        printf("Subset Found: { ");
        for (int i = 0; i < subSize; i++) printf("%d ", subset[i]);
        printf("}\n");
        return true; // Return true if you only want ONE solution, remove to find ALL
    }

    for (int i = nodeCount; i < n; i++) {
        if (total + set[i] <= target) {
            subset[subSize] = set[i]; // Include element
            
            // Recur
            if(subsetSumUtil(set, subset, n, subSize + 1, total + set[i], i + 1, target)) return true;
            
            // BACKTRACK is implicit here as we overwrite subset[subSize] in next iteration
        }
    }
    return false;
}

void solveSubsetSum() {
    int n, target;
    int set[MAX], subset[MAX];

    printf("\n--- Subset Sum Problem ---\n");
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    printf("Enter elements: ");
    for(int i=0; i<n; i++) scanf("%d", &set[i]);

    printf("Enter target sum: ");
    scanf("%d", &target);

    // Sort is often helpful for pruning, but standard backtracking works without it for small N
    printf("\nSearching for subset...\n");
    if (!subsetSumUtil(set, subset, n, 0, 0, 0, target)) {
        printf("No subset with given sum found.\n");
    }
}

// ================= MAIN DRIVER =================

int main() {
    int choice;
    while(1) {
        printf("\n==========================================");
        printf("\n    MASTER BACKTRACKING PROGRAM");
        printf("\n==========================================");
        printf("\n1. N-Queens Problem");
        printf("\n2. Sudoku Solver");
        printf("\n3. Hamiltonian Cycle");
        printf("\n4. Subset Sum Problem");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: solveNQueens(); break;
            case 2: solveSudoku(); break;
            case 3: solveHamiltonian(); break;
            case 4: solveSubsetSum(); break;
            case 5: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
    return 0;
}