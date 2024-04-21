#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Node
{
    int dest;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct Graph
{
    int numV;
    struct List *array;
};

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numV = numVertices;
    graph->array = (struct List*)malloc(numVertices * sizeof(struct List));
    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

int hasSelfLoop(struct Graph* graph) {
    for (int i = 0; i < graph->numV; i++) {
        struct Node* node = graph->array[i].head;
        while (node != NULL) {
            if (node->dest == i)
                return 1;
            node = node->next;
        }
    }
    return 0;
}

int hasParallelEdge(struct Graph* graph) {
    for (int i = 0; i < graph->numV; i++) {
        struct Node* node1 = graph->array[i].head;
        while (node1 != NULL) {
            int dest = node1->dest;
            struct Node* node2 = node1->next;
            while (node2 != NULL) {
                if (node2->dest == dest)
                    return 1;
                node2 = node2->next;
            }
            node1 = node1->next;
        }
    }
    return 0;
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numV; i++) {
        struct Node* node = graph->array[i].head;
        printf("Adjacency list of vertex %d: ", i);
        while (node != NULL) {
            printf("%d ", node->dest);
            node = node->next;
        }
        printf("\n");
    }
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    if (numVertices <= 0 || numVertices > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    struct Graph* graph = createGraph(numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);
    if (numEdges < 0 || numEdges > numVertices * (numVertices - 1)) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    printf("Enter edges (source then destination as integers):\n");
    for (int i = 0; i < numEdges; i++) {
        int source, dest;
        scanf("%d %d", &source, &dest);
        if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
            printf("Invalid edge.\n");
            return 1;
        }
        addEdge(graph, source, dest);
    }

    printf("Graph created successfully.\n");

    printf("Graph representation:\n");
    printGraph(graph);

    if (hasSelfLoop(graph))
        printf("The graph has a self-loop.\n");
    else
        printf("The graph does not have a self-loop.\n");

    if (hasParallelEdge(graph))
        printf("The graph has parallel edges.\n");
    else
        printf("The graph does not have parallel edges.\n");

    return 0;
}