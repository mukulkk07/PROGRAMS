#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class DFSMaster {
    int V;
    vector<vector<int>> adj;

public:
    DFSMaster(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        // adj[v].push_back(u); // Uncomment for undirected. Keeping Directed for Cycle detection demo.
    }

    // ==========================================
    // VARIATION 1: STANDARD RECURSIVE DFS
    // The cleanest and most common way to write DFS.
    // ==========================================
    void standardDFS(int startNode) {
        vector<bool> visited(V, false);
        cout << "DFS Recursive: ";
        dfsRecursiveHelper(startNode, visited);
        cout << endl;
    }

private:
    void dfsRecursiveHelper(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsRecursiveHelper(v, visited);
            }
        }
    }

public:
    // ==========================================
    // VARIATION 2: ITERATIVE DFS
    // Logic: Mimics recursion using an explicit std::stack.
    // Useful to avoid StackOverflow errors on massive graphs.
    // ==========================================
    void iterativeDFS(int startNode) {
        vector<bool> visited(V, false);
        stack<int> s;

        s.push(startNode);
        
        cout << "DFS Iterative: ";
        while (!s.empty()) {
            int u = s.top();
            s.pop();

            // Stack might contain duplicate nodes pushed from different parents,
            // so we check visited AFTER popping.
            if (!visited[u]) {
                cout << u << " ";
                visited[u] = true;
            }

            // Push neighbors to stack.
            // Note: We traverse in reverse order of adjacency list to mimic recursive order exactly
            // (optional, but good for consistency).
            for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
        cout << endl;
    }

    // ==========================================
    // VARIATION 3: CYCLE DETECTION (Directed Graph)
    // Logic: A cycle exists if we see a node that is currently in the active recursion stack.
    // We need 3 states: 0 (Unvisited), 1 (Visiting/In Stack), 2 (Visited/Done)
    // ==========================================
    bool hasCycle() {
        vector<int> state(V, 0); // 0=Unvisited, 1=Visiting, 2=Visited
        
        for (int i = 0; i < V; i++) {
            if (state[i] == 0) {
                if (checkCycle(i, state)) return true;
            }
        }
        return false;
    }

private:
    bool checkCycle(int u, vector<int>& state) {
        state[u] = 1; // Mark as currently visiting (in recursion stack)

        for (int v : adj[u]) {
            if (state[v] == 1) return true; // Found a back-edge! Cycle detected.
            if (state[v] == 0) {
                if (checkCycle(v, state)) return true;
            }
        }

        state[u] = 2; // Mark as completely processed
        return false;
    }
};

int main() {
    // Creating a graph designed for DFS
    // 0 -> 1 -> 2
    // |    |
    // v    v
    // 3 -> 4
    DFSMaster graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 4);
    graph.addEdge(3, 4);

    cout << "--- DFS MASTER ---" << endl;
    graph.standardDFS(0);
    graph.iterativeDFS(0);

    // Cycle Detection Test
    DFSMaster cycleGraph(3);
    cycleGraph.addEdge(0, 1);
    cycleGraph.addEdge(1, 2);
    cycleGraph.addEdge(2, 0); // Back to 0
    cout << "Cycle Detected: " << (cycleGraph.hasCycle() ? "Yes" : "No") << endl;

    return 0;
}