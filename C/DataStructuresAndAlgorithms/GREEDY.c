#include <stdio.h>
#include <stdlib.h>

// ================= STRUCT DEFINITIONS =================

// Structure for Fractional Knapsack
struct Item {
    int id;
    int weight;
    int value;
};

// Structure for Job Sequencing
struct Job {
    char id;     // Job Id
    int deadline;
    int profit;
};

// Structure for Kruskal's (Edge List)
struct Edge {
    int src, dest, weight;
};

// Structure for Union-Find (Used in Kruskal's)
struct Subset {
    int parent;
    int rank;
};

// ================= HELPER FUNCTIONS & COMPARATORS =================

// Comparator for Fractional Knapsack (Descending Order of Value/Weight)
int compareKnapsack(const void* a, const void* b) {
    struct Item* item1 = (struct Item*)a;
    struct Item* item2 = (struct Item*)b;
    double r1 = (double)item1->value / (double)item1->weight;
    double r2 = (double)item2->value / (double)item2->weight;
    if (r1 < r2) return 1;
    else if (r1 > r2) return -1;
    return 0;
}

// Comparator for Job Sequencing (Descending Order of Profit)
int compareJobs(const void* a, const void* b) {
    struct Job* j1 = (struct Job*)a;
    struct Job* j2 = (struct Job*)b;
    return j2->profit - j1->profit; 
}

// Comparator for Kruskal's (Ascending Order of Weight)
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

// Union-Find: Find function
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union-Find: Union function
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

// ================= ALGORITHM IMPLEMENTATIONS =================

// 1. FRACTIONAL KNAPSACK ALGORITHM
void solveFractionalKnapsack() {
    int n, capacity;
    printf("\n--- Fractional Knapsack ---\n");
    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));

    printf("Enter Value and Weight for each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        printf("Item %d (Value Weight): ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
    }

    printf("Enter Knapsack Capacity: ");
    scanf("%d", &capacity);

    // Sort items by value/weight ratio
    qsort(items, n, sizeof(struct Item), compareKnapsack);

    double totalValue = 0.0;
    int currentWeight = 0;

    printf("\nSelected Items:\n");
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
            printf("Added Item %d (100%%) - Val: %d\n", items[i].id, items[i].value);
        } else {
            int remain = capacity - currentWeight;
            double fraction = (double)remain / (double)items[i].weight;
            totalValue += items[i].value * fraction;
            printf("Added Item %d (%.2f%%) - Val: %.2f\n", items[i].id, fraction * 100, items[i].value * fraction);
            break; // Knapsack full
        }
    }
    printf("Maximum Value in Knapsack: %.2f\n", totalValue);
    free(items);
}

// 2. JOB SEQUENCING WITH DEADLINES
void solveJobSequencing() {
    int n;
    printf("\n--- Job Sequencing with Deadlines ---\n");
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    struct Job* jobs = (struct Job*)malloc(n * sizeof(struct Job));
    int maxDeadline = 0;

    printf("Enter JobID (char), Deadline, Profit:\n");
    for(int i=0; i<n; i++) {
        printf("Job %d: ", i+1);
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
        if(jobs[i].deadline > maxDeadline) maxDeadline = jobs[i].deadline;
    }

    // Sort by profit descending
    qsort(jobs, n, sizeof(struct Job), compareJobs);

    char* result = (char*)malloc((maxDeadline + 1) * sizeof(char));
    int* slot = (int*)malloc((maxDeadline + 1) * sizeof(int));

    // Initialize slots as free
    for(int i=0; i<=maxDeadline; i++) slot[i] = 0;

    int totalProfit = 0;
    int jobsCount = 0;

    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (start from its deadline and move back)
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                result[j] = jobs[i].id;
                slot[j] = 1;
                totalProfit += jobs[i].profit;
                jobsCount++;
                break;
            }
        }
    }

    printf("\nJob Sequence: ");
    for(int i=1; i<=maxDeadline; i++) {
        if(slot[i]) printf("%c -> ", result[i]);
    }
    printf("END\nTotal Profit: %d\n", totalProfit);

    free(jobs); free(result); free(slot);
}

// 3. KRUSKAL'S ALGORITHM (MINIMUM SPANNING TREE)
void solveKruskal() {
    int V, E;
    printf("\n--- Kruskal's Algorithm (MST) ---\n");
    printf("Enter number of Vertices and Edges: ");
    scanf("%d %d", &V, &E);

    struct Edge* edges = (struct Edge*)malloc(E * sizeof(struct Edge));

    printf("Enter Source, Destination, Weight for each edge:\n");
    for(int i=0; i<E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    // Sort edges by weight ascending
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    struct Edge* result = (struct Edge*)malloc((V - 1) * sizeof(struct Edge));
    int e = 0; // Index for result[]
    int i = 0; // Index for sorted edges[]

    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause cycle
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("\nEdges in the MST:\n");
    int minCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Total Cost of MST: %d\n", minCost);

    free(edges); free(subsets); free(result);
}

// 4. COIN CHANGE PROBLEM (Standard Greedy)
void solveCoinChange() {
    printf("\n--- Coin Change Problem (Greedy) ---\n");
    // Standard denominations (e.g., Indian Currency or US)
    // Greedy works for standard canonical coin systems, but not all arbitrary sets.
    int coins[] = { 1, 2, 5, 10, 20, 50, 100, 200, 500, 2000 };
    int n = sizeof(coins) / sizeof(coins[0]);
    
    int amount;
    printf("Available Coins: {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000}\n");
    printf("Enter Amount: ");
    scanf("%d", &amount);

    printf("Coins Selected: ");
    int count = 0;
    
    // Iterate from largest coin to smallest
    for (int i = n - 1; i >= 0; i--) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
            count++;
        }
    }
    printf("\nTotal coins used: %d\n", count);
}

// ================= MAIN DRIVER =================
int main() {
    int choice;
    while(1) {
        printf("\n==========================================");
        printf("\n    MASTER GREEDY ALGORITHM PROGRAM");
        printf("\n==========================================");
        printf("\n1. Fractional Knapsack");
        printf("\n2. Job Sequencing with Deadlines");
        printf("\n3. Kruskal's Algorithm (MST)");
        printf("\n4. Coin Change Problem");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: solveFractionalKnapsack(); break;
            case 2: solveJobSequencing(); break;
            case 3: solveKruskal(); break;
            case 4: solveCoinChange(); break;
            case 5: 
                printf("Exiting...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}