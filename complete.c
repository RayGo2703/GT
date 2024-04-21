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
