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
    int* parent;
    int* disc; 
    int* low;
    bool* isCutVertex;
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
    graph->parent = (int*)malloc(numV * sizeof(int));
    graph->disc = (int*)malloc(numV * sizeof(int));
    graph->low = (int*)malloc(numV * sizeof(int));
    graph->isCutVertex = (bool*)malloc(numV * sizeof(bool));

    for (int i = 0; i < numV; ++i) {
        graph->array[i].head = NULL;
        graph->visited[i] = false;
        graph->parent[i] = -1;
        graph->disc[i] = 0;
        graph->low[i] = 0;
        graph->isCutVertex[i] = false;
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

void dfsCutVertices(struct Graph* graph, int u, bool isRoot) {
    static int time = 0;
    int children = 0;
    graph->visited[u] = true;
    graph->disc[u] = graph->low[u] = ++time;

    struct Node* currentNode = graph->array[u].head;
    while (currentNode) {
        int v = currentNode->data;
        if (!graph->visited[v]) {
            children++;
            graph->parent[v] = u;
            dfsCutVertices(graph, v, false);
            graph->low[u] = min(graph->low[u], graph->low[v]);

            if (!isRoot && graph->low[v] >= graph->disc[u])
                graph->isCutVertex[u] = true;
        } else if (v != graph->parent[u])
            graph->low[u] = min(graph->low[u], graph->disc[v]);
        currentNode = currentNode->next;
    }

    if (isRoot && children > 1)
        graph->isCutVertex[u] = true;
}

void findCutVertices(struct Graph* graph) {
    for (int i = 0; i < graph->numV; ++i)
        if (!graph->visited[i])
            dfsCutVertices(graph, i, true);

    printf("Cut vertices in the graph:\n");
    for (int i = 0; i < graph->numV; ++i)
        if (graph->isCutVertex[i])
            printf("%d ", i);
    printf("\n");
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

    findCutVertices(graph);

    return 0;
}