#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INF 99999

// --- Function Prototypes ---
void runFibonacci();
void runKnapsack();
void runLCS();
void runMatrixChain();
void runCoinChange();
void runFloydWarshall();

int main() {
    int choice;

    while (1) {
        printf("\n==========================================\n");
        printf("   MASTER DYNAMIC PROGRAMMING PROGRAM     \n");
        printf("==========================================\n");
        printf("1. Fibonacci Series (Space Optimized)\n");
        printf("2. 0/1 Knapsack Problem\n");
        printf("3. Longest Common Subsequence (LCS)\n");
        printf("4. Matrix Chain Multiplication\n");
        printf("5. Coin Change Problem (Min Coins)\n");
        printf("6. Floyd-Warshall (Graph Shortest Path)\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: runFibonacci(); break;
            case 2: runKnapsack(); break;
            case 3: runLCS(); break;
            case 4: runMatrixChain(); break;
            case 5: runCoinChange(); break;
            case 6: runFloydWarshall(); break;
            case 7: exit(0);
            default: printf("Invalid Choice\n");
        }
    }
    return 0;
}

// ====================================================
// 1. FIBONACCI (Space Optimized)
// ====================================================
// Standard Recursive is O(2^n). DP reduces this to O(n).
// This specific version uses O(1) space.
void runFibonacci() {
    int n;
    printf("\n--- Fibonacci Series ---\n");
    printf("Enter N (position): ");
    scanf("%d", &n);

    if (n < 0) { printf("Invalid input.\n"); return; }
    
    long long a = 0, b = 1, c;
    if (n == 0) printf("Fib(0) = 0\n");
    else {
        printf("Sequence: 0 1 ");
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
            printf("%lld ", c);
        }
        printf("\nFib(%d) = %lld\n", n, b);
    }
}

// ====================================================
// 2. 0/1 KNAPSACK PROBLEM
// ====================================================
// Maximize value in a knapsack of capacity W
void runKnapsack() {
    int n, W;
    printf("\n--- 0/1 Knapsack Problem ---\n");
    printf("Enter number of items: ");
    scanf("%d", &n);

    int *val = (int*)malloc(n * sizeof(int));
    int *wt = (int*)malloc(n * sizeof(int));

    printf("Enter Values of %d items: ", n);
    for(int i=0; i<n; i++) scanf("%d", &val[i]);
    
    printf("Enter Weights of %d items: ", n);
    for(int i=0; i<n; i++) scanf("%d", &wt[i]);

    printf("Enter Knapsack Capacity: ");
    scanf("%d", &W);

    // DP Table allocation
    int **K = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++)
        K[i] = (int*)malloc((W + 1) * sizeof(int));

    // Build table K[][] in bottom up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = MAX(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    printf(">> Maximum Value achievable: %d\n", K[n][W]);

    // Cleanup
    for(int i=0; i<=n; i++) free(K[i]);
    free(K); free(val); free(wt);
}

// ====================================================
// 3. LONGEST COMMON SUBSEQUENCE (LCS)
// ====================================================
// Finds the longest subsequence common to two strings
void runLCS() {
    char s1[100], s2[100];
    printf("\n--- Longest Common Subsequence ---\n");
    printf("Enter first string: ");
    scanf("%s", s1);
    printf("Enter second string: ");
    scanf("%s", s2);

    int m = strlen(s1);
    int n = strlen(s2);

    int **L = (int**)malloc((m + 1) * sizeof(int*));
    for(int i = 0; i <= m; i++) 
        L[i] = (int*)malloc((n + 1) * sizeof(int));

    // Building the Matrix
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = MAX(L[i - 1][j], L[i][j - 1]);
        }
    }

    int index = L[m][n];
    printf(">> Length of LCS is: %d\n", index);

    // Reconstructing the LCS string
    char *lcsAlgo = (char*)malloc((index + 1) * sizeof(char));
    lcsAlgo[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcsAlgo[index - 1] = s1[i - 1];
            i--; j--; index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }
    printf(">> LCS String is: %s\n", lcsAlgo);

    for(int k=0; k<=m; k++) free(L[k]);
    free(L); free(lcsAlgo);
}

// ====================================================
// 4. MATRIX CHAIN MULTIPLICATION
// ====================================================
// Finds most efficient way to multiply a sequence of matrices
void runMatrixChain() {
    int n;
    printf("\n--- Matrix Chain Multiplication ---\n");
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    
    // Dimensions array size is n+1 because matrix i is p[i-1] x p[i]
    int *p = (int*)malloc((n + 1) * sizeof(int));
    printf("Enter dimensions (array of size %d): ", n + 1);
    for(int i=0; i<=n; i++) scanf("%d", &p[i]);

    // m[i][j] stores minimum number of scalar multiplications
    int **m = (int**)malloc((n + 1) * sizeof(int*));
    for(int i=0; i<=n; i++) m[i] = (int*)malloc((n + 1) * sizeof(int));

    // Cost is zero when multiplying one matrix
    for (int i = 1; i <= n; i++) m[i][i] = 0;

    // L is chain length
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    printf(">> Minimum number of multiplications: %d\n", m[1][n]);

    for(int i=0; i<=n; i++) free(m[i]);
    free(m); free(p);
}

// ====================================================
// 5. COIN CHANGE PROBLEM (Min Coins)
// ====================================================
// Finds minimum coins required to make a specific value V
void runCoinChange() {
    int n, V;
    printf("\n--- Coin Change Problem ---\n");
    printf("Enter number of distinct coin types: ");
    scanf("%d", &n);

    int *coins = (int*)malloc(n * sizeof(int));
    printf("Enter coin values: ");
    for(int i=0; i<n; i++) scanf("%d", &coins[i]);

    printf("Enter Value to make (V): ");
    scanf("%d", &V);

    // table[i] stores min coins for value i
    int *table = (int*)malloc((V + 1) * sizeof(int));

    // Initialize with infinity
    table[0] = 0;
    for (int i = 1; i <= V; i++) table[i] = INT_MAX;

    // Compute minimum coins
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int sub_res = table[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < table[i])
                    table[i] = sub_res + 1;
            }
        }
    }

    if (table[V] == INT_MAX)
        printf(">> Not possible to make value %d with given coins.\n", V);
    else
        printf(">> Minimum coins required: %d\n", table[V]);

    free(coins); free(table);
}

// ====================================================
// 6. FLOYD-WARSHALL ALGORITHM
// ====================================================
// All-Pairs Shortest Path
void runFloydWarshall() {
    int V;
    printf("\n--- Floyd-Warshall Algorithm ---\n");
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int **dist = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) dist[i] = (int*)malloc(V * sizeof(int));

    printf("Enter Adjacency Matrix (use 99999 for Infinity):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    // The Algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    printf("\n>> Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] >= INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<V; i++) free(dist[i]);
    free(dist);
}