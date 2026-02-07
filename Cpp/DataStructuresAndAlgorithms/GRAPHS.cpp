#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <vector>

using namespace std;

// ==========================================
// GRAPH CLASS DEFINITION
// ==========================================
class Graph {
private:
    // Adjacency List:
    // Map Key (int) = The Vertex
    // Map Value (list<int>) = A list of all vertices connected to it
    map<int, list<int>> adj;

    // Helper function for DFS (Recursive)
    void dfsHelper(int node, map<int, bool> &visited) {
        // Step 1: Mark the current node as visited and print it
        visited[node] = true;
        cout << node << " ";

        // Step 2: Recur for all the vertices adjacent to this vertex
        for (int neighbor : adj[node]) {
            // If the neighbor hasn't been visited yet, go deeper!
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited);
            }
        }
    }

public:
    // --- CORE OPERATIONS ---

    // 1. ADD EDGE: Connects vertex 'u' and vertex 'v'
    // 'bidirectional' = true means if A is connected to B, B is also connected to A.
    void addEdge(int u, int v, bool bidirectional = true) {
        adj[u].push_back(v); // Connect u -> v
        
        if (bidirectional) {
            adj[v].push_back(u); // Connect v -> u
        }
    }

    // 2. BFS (Breadth-First Search) - The "Layer by Layer" Approach
    void bfs(int startNode) {
        cout << "BFS Traversal: ";
        
        // Use a map to keep track of who we have already visited
        map<int, bool> visited;
        
        // Use a QUEUE for BFS (First In, First Out)
        queue<int> q;

        // Step 1: Start with the initial node
        q.push(startNode);
        visited[startNode] = true;

        while (!q.empty()) {
            // Step 2: Get the node at the front
            int currentNode = q.front();
            q.pop();
            cout << currentNode << " ";

            // Step 3: Look at all neighbors of the current node
            for (int neighbor : adj[currentNode]) {
                // If we haven't visited this neighbor yet...
                if (!visited[neighbor]) {
                    q.push(neighbor); // Add to queue to visit later
                    visited[neighbor] = true; // Mark as visited so we don't add it twice
                }
            }
        }
        cout << endl;
    }

    // 3. DFS (Depth-First Search) - The "Deep Dive" Approach
    void dfs(int startNode) {
        cout << "DFS Traversal: ";
        
        // We need a visited map to stop infinite loops in cycles
        map<int, bool> visited;
        
        // Call the recursive helper
        dfsHelper(startNode, visited);
        
        cout << endl;
    }

    // 4. DISPLAY THE GRAPH
    void printGraph() {
        cout << "\n--- Adjacency List Structure ---" << endl;
        // Iterate over every key-value pair in the map
        for (auto row : adj) {
            cout << row.first << " -> "; // The Node
            for (int neighbor : row.second) { // Its Neighbors
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << "--------------------------------\n" << endl;
    }
};

// ==========================================
// MAIN EXECUTION
// ==========================================
int main() {
    Graph g;

    // --- Building the Graph ---
    // Let's build a social network logic:
    // 0 is friends with 1 and 2
    // 1 is friends with 2
    // 2 is friends with 0 and 3
    /*
        0 --- 1
        |     |
        2 --- 3
         \   /
           4
    */

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2); // 1 and 2 are connected
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(2, 4);

    // Show the internal structure
    g.printGraph();

    // BFS: Should look wide first. 
    // From 0, it sees 1 and 2. Then it visits neighbors of 1, then neighbors of 2.
    // Expected: 0 1 2 3 4 (Order may vary slightly based on insertion)
    g.bfs(0);

    // DFS: Should go deep first.
    // From 0, go to 1. From 1, go to 2. From 2, go to 3...
    // Expected: 0 1 2 3 4 (But the path taken is different)
    g.dfs(0);

    return 0;
}