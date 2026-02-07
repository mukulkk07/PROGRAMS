#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 50

// --- 1. DATA STRUCTURE DEFINITIONS ---

// Adjacency List Node (Represents an edge)
struct AdjNode {
    int dest;
    int weight;
    struct AdjNode* next;
};

// Graph Structure
struct Graph {
    struct AdjNode* head[MAX_VERTICES];
    int numVertices;
};

// --- 2. QUEUE HELPER (For BFS) ---
// A simple circular queue implementation

struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->rear == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) return; // Overflow check
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) { // Reset queue
        q->front = q->rear = -1;
    }
    return item;
}

// --- 3. CORE GRAPH OPERATIONS ---

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
        graph->head[i] = NULL;
    return graph;
}

struct AdjNode* createNode(int dest, int weight) {
    struct AdjNode* newNode = (struct AdjNode*)malloc(sizeof(struct AdjNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Add Edge (Directed = 0 for undirected, 1 for directed)
void addEdge(struct Graph* graph, int src, int dest, int weight, int isDirected) {
    // Add edge from src -> dest
    struct AdjNode* newNode = createNode(dest, weight);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    // If undirected, add edge from dest -> src
    if (!isDirected) {
        newNode = createNode(src, weight);
        newNode->next = graph->head[dest];
        graph->head[dest] = newNode;
    }
}

// Display Graph (Adjacency List view)
void displayGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct AdjNode* temp = graph->head[i];
        printf("Vertex %d: ", i);
        while (temp) {
            printf("-> (Node: %d, W: %d) ", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

// --- 4. SEARCH ALGORITHMS ---

// BFS: Breadth First Search (Uses Queue)
void BFS(struct Graph* graph, int startVertex) {
    struct Queue* q = createQueue();
    int visited[MAX_VERTICES] = {0};

    visited[startVertex] = 1;
    enqueue(q, startVertex);

    printf("BFS Traversal: ");

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        struct AdjNode* temp = graph->head[currentVertex];
        while (temp) {
            int adjVertex = temp->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(q);
}

// DFS Helper (Recursive)
void DFSUtil(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct AdjNode* temp = graph->head[vertex];
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// DFS: Depth First Search (Uses Recursion)
void DFS(struct Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    printf("DFS Traversal: ");
    DFSUtil(graph, startVertex, visited);
    printf("\n");
}

// --- 5. SHORTEST PATH ALGORITHM (DIJKSTRA) ---

// Find vertex with min distance that hasn't been visited yet
int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Dijkstra's Algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->numVertices;
    int dist[MAX_VERTICES]; // Output array. dist[i] holds shortest distance from src to i
    int sptSet[MAX_VERTICES]; // Shortest Path Tree Set (True if vertex is finalized)

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        struct AdjNode* temp = graph->head[u];
        while (temp != NULL) {
            int v = temp->dest;
            int weight = temp->weight;
            
            // Update dist[v] only if is not in sptSet, there is an edge from u to v,
            // and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
            temp = temp->next;
        }
    }

    // Print the constructed distance array
    printf("\n--- Dijkstra's Shortest Paths from Vertex %d ---\n", src);
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if(dist[i] == INT_MAX)
             printf("%d \t\t INFINITY\n", i);
        else
             printf("%d \t\t %d\n", i, dist[i]);
    }
}

// --- 6. MAIN DRIVER ---

int main() {
    int V, choice, src, dest, weight, directed;
    
    printf("=== MASTER GRAPH PROGRAM ===\n");
    printf("Enter number of vertices (0 to %d): ", MAX_VERTICES - 1);
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

    while (1) {
        printf("\n1. Add Edge\n2. Display Graph\n");
        printf("3. BFS Traversal\n4. DFS Traversal\n");
        printf("5. Dijkstra Shortest Path\n6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Source, Dest, Weight: ");
                scanf("%d %d %d", &src, &dest, &weight);
                printf("Directed (1) or Undirected (0)? ");
                scanf("%d", &directed);
                addEdge(graph, src, dest, weight, directed);
                break;
            case 2:
                displayGraph(graph);
                break;
            case 3:
                printf("Enter Start Vertex: ");
                scanf("%d", &src);
                BFS(graph, src);
                break;
            case 4:
                printf("Enter Start Vertex: ");
                scanf("%d", &src);
                DFS(graph, src);
                break;
            case 5:
                printf("Enter Source for Dijkstra: ");
                scanf("%d", &src);
                dijkstra(graph, src);
                break;
            case 6:
                printf("Exiting...\n");
                // Note: In a full production app, we would write a function to free all mallocs here.
                exit(0);
            default:
                printf("Invalid Choice\n");
        }
    }
    return 0;
}