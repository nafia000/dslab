#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

// Adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node* adjList[MAX_VERTICES];
};

// Function to create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the graph
void initGraph(struct Graph* graph, int vertices) {
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
}

// Function to add an edge to the graph (Directed)
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// DFS (Depth First Search) - Recursive
void DFSUtil(struct Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    struct Node* adjList = graph->adjList[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        adjList = adjList->next;
    }
}

// DFS Traversal (Visit all vertices starting from a given vertex)
void DFS(struct Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = { false };

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);

    // After the DFS from start vertex, check for unvisited vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
    printf("\n");
}

// BFS (Breadth First Search)
void BFS(struct Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = { false };
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS starting from vertex %d: ", startVertex);
    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node* adjList = graph->adjList[currentVertex];
        while (adjList != NULL) {
            int adjVertex = adjList->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            adjList = adjList->next;
        }
    }
    printf("\n");
}

// Topological Sort - Using DFS with Cycle Detection
void topologicalSortUtil(struct Graph* graph, int vertex, bool visited[], bool recursionStack[], int stack[], int* stackIndex, bool* hasCycle) {
    if (*hasCycle) return; // Stop processing if a cycle is already detected

    // Mark the current vertex as visited and add it to the recursion stack
    visited[vertex] = true;
    recursionStack[vertex] = true;

    struct Node* adjList = graph->adjList[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;

        // If the adjacent vertex is in the recursion stack, a cycle is detected
        if (recursionStack[adjVertex]) {
            *hasCycle = true;
            return;
        }

        // If the adjacent vertex is not visited, recurse
        if (!visited[adjVertex]) {
            topologicalSortUtil(graph, adjVertex, visited, recursionStack, stack, stackIndex, hasCycle);
        }
        adjList = adjList->next;
    }

    // Remove the vertex from the recursion stack and add it to the result stack
    recursionStack[vertex] = false;
    stack[(*stackIndex)++] = vertex;
}

// Topological Sort
void topologicalSort(struct Graph* graph) {
    bool visited[MAX_VERTICES] = { false };
    bool recursionStack[MAX_VERTICES] = { false };
    int stack[MAX_VERTICES];
    int stackIndex = 0;
    bool hasCycle = false;

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, recursionStack, stack, &stackIndex, &hasCycle);
            if (hasCycle) {
                printf("The graph is not acyclic (contains a cycle).\n");
                return;
            }
        }
    }

    printf("Topological Sort: ");
    for (int i = stackIndex - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Function to display the graph (adjacency list)
void displayGraph(struct Graph* graph) {
    printf("\nGraph Representation (Adjacency List):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* adjList = graph->adjList[i];
        printf("Vertex %d: ", i);
        while (adjList != NULL) {
            printf("%d -> ", adjList->vertex);
            adjList = adjList->next;
        }
        printf("NULL\n");
}
}
int main() {
    struct Graph graph;
    int vertices, edges, src, dest, startVertex, choice;

    // Input number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initGraph(&graph, vertices);

    // Input edges
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);

        // Add directed edge to the graph
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            addEdge(&graph, src, dest);
        } else {
            printf("Invalid edge! Please enter vertices within the range of 0 to %d.\n", vertices - 1);
            i--;  // Decrement i to allow user to input the edge again
        }
    }

    // Main menu
    do {
        printf("\nMenu:\n");
        printf("1. Display Graph\n");
        printf("2. DFS Traversal\n");
        printf("3. BFS Traversal\n");
        printf("4. Topological Sort\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayGraph(&graph);
                break;
            case 2:
                printf("\nEnter the start vertex for DFS: ");
                scanf("%d", &startVertex);
                if (startVertex >= 0 && startVertex < vertices) {
                    DFS(&graph, startVertex);
                } else {
                    printf("Invalid start vertex!\n");
                }
                break;
            case 3:
                printf("\nEnter the start vertex for BFS: ");
                scanf("%d", &startVertex);
                if (startVertex >= 0 && startVertex < vertices) {
                    BFS(&graph, startVertex);
                } else {
                    printf("Invalid start vertex!\n");
                }
                break;
            case 4:
                topologicalSort(&graph);
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
