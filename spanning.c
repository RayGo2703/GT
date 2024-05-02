#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent a graph
struct Graph {
    int V;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since it's an undirected graph, add an edge from dest to src as well
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the minimal spanning tree represented by the graph
void printMST(struct Graph* graph) {
    printf("Minimal Spanning Tree:\n");
    for (int i = 0; i < graph->V; ++i) {
        printf("Vertex %d:", i);
        struct AdjListNode* temp = graph->array[i].head;
        while (temp) {
            printf(" -> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int V = 4; // Number of vertices in the graph
    struct Graph* graph = createGraph(V);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 2, 3);

    printMST(graph);

    return 0;
}