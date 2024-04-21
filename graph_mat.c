#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct Graph
{
    struct List *array;
    int numV;
};

void addV(struct Graph *graph, int vertex)
{
    graph->numV++;
    graph->array = realloc(graph->array, graph->numV * sizeof(struct List));
    graph->array[graph->numV - 1].head = NULL;
}

void addE(struct Graph *graph, int source, int dest)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = dest;
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = source;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printAM(struct Graph *graph)
{
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < graph->numV; i++)
    {
        for (int j = 0; j < graph->numV; j++)
        {
            int found = 0;
            struct Node *temp = graph->array[i].head;
            while (temp)
            {
                if (temp->data == j)
                {
                    printf("1 ");
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
                printf("0 ");
        }
        printf("\n");
    }
}

void printVertices(struct Graph *graph)
{
    printf("\nVertices in the Graph:\n");
    for (int i = 0; i < graph->numV; i++)
    {
        printf("%d\n", i);
    }
}

void printAdjListUser(struct Graph *graph, int userVertex)
{
    if (userVertex < 0 || userVertex >= graph->numV)
    {
        printf("Invalid vertex index.\n");
        return;
    }
    printf("\nAdjacency List of Vertex %d:\n", userVertex);
    struct Node *temp = graph->array[userVertex].head;
    while (temp)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    struct Graph graph;
    int numEdges;
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    graph.numV = 0;
    graph.array = NULL;

    for (int i = 0; i < numEdges; i++)
    {
        int source, dest;
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &source, &dest);
        addV(&graph, source);
        addV(&graph, dest);
        addE(&graph, source, dest);
    }

    int option;
    do
    {
        printf("\n1. Print Adjacency Matrix\n");
        printf("2. Print Nodes\n");
        printf("3. Print Adjacency List for a Particular Vertex\n");
        printf("4. Print Adjacency List for All Vertices\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printAM(&graph);
            break;
        case 2:
            printVertices(&graph);
            break;
        case 3:
            printf("Enter the index of the vertex (0-%d): ", graph.numV - 1);
            int userVertex;
            scanf("%d", &userVertex);
            printAdjListUser(&graph, userVertex);
            break;
        case 4:
            for (int i = 0; i < graph.numV; i++)
            {
                printAdjListUser(&graph, i);
            }
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }

    } while (option != 0);

    for (int i = 0; i < graph.numV; i++)
    {
        struct Node *temp = graph.array[i].head;
        while (temp)
        {
            struct Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph.array);

    return 0;
}