#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
};

struct Graph {
    struct List* array;
    int numV;
    bool* visited;
    int* disc;   
    int* low;  
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

struct Graph* createGraph(int numV) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numV = numV;
    graph->array = (struct List*)malloc(numV * sizeof(struct List));
    graph->visited = (bool*)malloc(numV * sizeof(bool));
    graph->disc = (int*)malloc(numV * sizeof(int));
    graph->low = (int*)malloc(numV * sizeof(int));

    for (int i = 0; i < numV; ++i) {
        graph->array[i].head = NULL;
        graph->visited[i] = false;
        graph->disc[i] = 0;
        graph->low[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNodeDest = newNode(dest);
    newNodeDest->next = graph->array[src].head;
    graph->array[src].head = newNodeDest;

    struct Node* newNodeSrc = newNode(src);
    newNodeSrc->next = graph->array[dest].head;
    graph->array[dest].head = newNodeSrc;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dfsCutEdges(struct Graph* graph, int u, int parent) {
    static int time = 0;
    graph->visited[u] = true;
    graph->disc[u] = graph->low[u] = ++time;

    struct Node* currentNode = graph->array[u].head;
    while (currentNode) {
        int v = currentNode->data;
        if (!graph->visited[v]) {
            dfsCutEdges(graph, v, u);
            graph->low[u] = min(graph->low[u], graph->low[v]);
            if (graph->low[v] > graph->disc[u])
                printf("Cut edge: %d - %d\n", u, v);
        } else if (v != parent) {
            graph->low[u] = min(graph->low[u], graph->disc[v]);
        }
        currentNode = currentNode->next;
    }
}

void findCutEdges(struct Graph* graph) {
    for (int i = 0; i < graph->numV; ++i)
        if (!graph->visited[i])
            dfsCutEdges(graph, i, -1);
}

int main() {
    int numV, numE;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &numV, &numE);

    struct Graph* graph = createGraph(numV);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < numE; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    findCutEdges(graph);

    return 0;
}