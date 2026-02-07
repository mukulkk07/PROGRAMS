package JavaDSA;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/**
 * A Master Class demonstrating Graph Data Structures and Algorithms.
 * File Name: MasterGraph.java
 * * * * CONCEPTS:
 * 1. Adjacency Matrix: A 2D array where cell [i][j] = 1 means an edge exists.
 * - Space: O(V^2) -> Expensive!
 * - Lookup: O(1) -> Fast.
 * * 2. Adjacency List: An Array of Lists where index 'i' contains a list of neighbors.
 * - Space: O(V + E) -> Efficient.
 * - Lookup: O(degree) -> Slower than matrix.
 */
public class Graphs {

    public static void main(String[] args) {
        System.out.println("=== 1. ADJACENCY MATRIX (2D Array) ===");
        matrixDemo();

        System.out.println("\n=== 2. ADJACENCY LIST (ArrayList) ===");
        // We will use this graph for BFS and DFS
        // Graph Structure:
        // 0 -- 1 -- 2
        // |    |
        // 3 -- 4
        int V = 5; // Vertices 0 to 4
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        
        // Initialize empty lists for each vertex
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // Add Edges (Undirected)
        addEdgeList(adj, 0, 1);
        addEdgeList(adj, 0, 3);
        addEdgeList(adj, 1, 2);
        addEdgeList(adj, 1, 4);
        addEdgeList(adj, 3, 4);

        printAdjList(adj);

        System.out.println("\n=== 3. BFS TRAVERSAL (Level Order) ===");
        bfs(adj, V, 0); // Start from node 0

        System.out.println("\n=== 4. DFS TRAVERSAL (Depth First) ===");
        dfs(adj, V, 0); // Start from node 0
    }

    // ==========================================================
    // SECTION 1: ADJACENCY MATRIX REPRESENTATION
    // ==========================================================
    public static void matrixDemo() {
        int v = 3;
        int[][] matrix = new int[v][v];

        // Edge 0-1
        matrix[0][1] = 1;
        matrix[1][0] = 1; // Undirected

        // Edge 1-2
        matrix[1][2] = 1;
        matrix[2][1] = 1;

        System.out.println("Matrix Representation:");
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    // ==========================================================
    // SECTION 2: ADJACENCY LIST HELPERS
    // ==========================================================
    public static void addEdgeList(ArrayList<ArrayList<Integer>> adj, int u, int v) {
        adj.get(u).add(v); // Add v to u's list
        adj.get(v).add(u); // Add u to v's list (Undirected)
    }

    public static void printAdjList(ArrayList<ArrayList<Integer>> adj) {
        for (int i = 0; i < adj.size(); i++) {
            System.out.print("Vertex " + i + ": ");
            for (int neighbor : adj.get(i)) {
                System.out.print(neighbor + " ");
            }
            System.out.println();
        }
    }

    // ==========================================================
    // SECTION 3: BFS (Breadth-First Search)
    // ==========================================================
    // Uses a QUEUE to explore neighbors level by level.
    public static void bfs(ArrayList<ArrayList<Integer>> adj, int V, int startNode) {
        boolean[] visited = new boolean[V];
        Queue<Integer> q = new LinkedList<>();

        visited[startNode] = true;
        q.add(startNode);

        System.out.print("BFS Path: ");
        while (!q.isEmpty()) {
            int curr = q.poll();
            System.out.print(curr + " ");

            // Get all neighbors of curr
            for (int neighbor : adj.get(curr)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.add(neighbor);
                }
            }
        }
        System.out.println();
    }

    // ==========================================================
    // SECTION 4: DFS (Depth-First Search)
    // ==========================================================
    // Uses RECURSION (System Stack) to go deep into one path.
    public static void dfs(ArrayList<ArrayList<Integer>> adj, int V, int startNode) {
        boolean[] visited = new boolean[V];
        System.out.print("DFS Path: ");
        dfsRecursive(adj, startNode, visited);
        System.out.println();
    }

    private static void dfsRecursive(ArrayList<ArrayList<Integer>> adj, int curr, boolean[] visited) {
        // Mark current node as visited and print it
        visited[curr] = true;
        System.out.print(curr + " ");

        // Recur for all connected neighbors
        for (int neighbor : adj.get(curr)) {
            if (!visited[neighbor]) {
                dfsRecursive(adj, neighbor, visited);
            }
        }
    }
}