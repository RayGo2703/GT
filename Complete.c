#include<stdio.h>
#define MAX_VERTICES 100

void createCompleteGraph(int vertices,int graph[][MAX_VERTICES])
{
    for(int i=0;i < vertices; i++)
    {
        for(int j=0; j < vertices; j++ )
        {
            if(i != j)
            {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
            else
            {
                graph[i][j] = 0;
            }
        }
    }
}

void printGraph(int vertices,int graph[][MAX_VERTICES])
{
    printf("Adjacency Matric:\n");
    for(int i=0;i < vertices; i++)
    {
        for(int j=0;j < vertices; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int vertices;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d",&vertices);

    if(vertices <= 0 || vertices > MAX_VERTICES)
    {
        printf("Invaild no. of vertices. Please enter a value between 1 and %d.\n",MAX_VERTICES);
    }

    int graph[MAX_VERTICES][MAX_VERTICES];

    createCompleteGraph(vertices,graph);

    printGraph(vertices,graph);

    return 0;
}