#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

class BFSMaster {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency List

public:
    BFSMaster(int V) : V(V), adj(V) {}

    // Add undirected edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    // ==========================================
    // VARIATION 1: STANDARD BFS TRAVERSAL
    // Logic: Visit start, then all neighbors, then neighbors' neighbors.
    // ==========================================
    void standardBFS(int startNode) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            // Explore neighbors
            for (int neighbor : adj[u]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // ==========================================
    // VARIATION 2: SHORTEST PATH (Unweighted)
    // Logic: Track 'distance' and 'parent' to reconstruct the path.
    // BFS guarantees the shortest path in unweighted graphs.
    // ==========================================
    void shortestPath(int start, int end) {
        vector<int> dist(V, -1);
        vector<int> parent(V, -1);
        queue<int> q;

        dist[start] = 0;
        parent[start] = -1;
        q.push(start);

        bool found = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == end) {
                found = true;
                break;
            }

            for (int v : adj[u]) {
                if (dist[v] == -1) { // -1 implies unvisited
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if (!found) {
            cout << "No path from " << start << " to " << end << endl;
            return;
        }

        // Reconstruct path by backtracking from 'end' to 'start'
        vector<int> path;
        int curr = end;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());

        cout << "Shortest Path (" << dist[end] << " steps): ";
        for (int node : path) cout << node << " ";
        cout << endl;
    }

    // ==========================================
    // VARIATION 3: DISCONNECTED COMPONENTS
    // Logic: If the graph is broken into pieces, a single BFS from node 0 won't reach everything.
    // We must loop through all nodes and start BFS if unvisited.
    // ==========================================
    int countConnectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                count++;
                // Launch BFS to mark this entire component
                queue<int> q;
                q.push(i);
                visited[i] = true;
                while(!q.empty()){
                    int u = q.front(); q.pop();
                    for(int v : adj[u]){
                        if(!visited[v]){
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }
            }
        }
        return count;
    }
};

int main() {
    BFSMaster graph(6);
    // 0--1--2
    // |  |  |
    // 3--4--5
    graph.addEdge(0, 1); graph.addEdge(0, 3);
    graph.addEdge(1, 2); graph.addEdge(1, 4);
    graph.addEdge(2, 5); graph.addEdge(3, 4);
    graph.addEdge(4, 5);

    cout << "--- BFS MASTER ---" << endl;
    graph.standardBFS(0);
    graph.shortestPath(0, 5); // Should find path 0->1->2->5 or 0->3->4->5

    // Disconnected example
    BFSMaster discoGraph(5);
    discoGraph.addEdge(0, 1); // Component 1
    discoGraph.addEdge(2, 3); // Component 2
    // Node 4 is isolated (Component 3)
    cout << "Connected Components: " << discoGraph.countConnectedComponents() << endl;

    return 0;
}