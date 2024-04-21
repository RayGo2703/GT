#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Queue {
    int items[MAX_NODES];
    int front;
    int rear;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->rear == -1;
}

void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX_NODES - 1)
        printf("Queue is full");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

void bfs(int graph[MAX_NODES][MAX_NODES], int start, int n) {
    struct Queue* queue = createQueue();
    int visited[MAX_NODES] = {0};
    int i, currentNode;
    
    visited[start] = 1;
    enqueue(queue, start);
    
    while (!isEmpty(queue)) {
        currentNode = dequeue(queue);
        printf("%d ", currentNode);
        
        for (i = 0; i < n; ++i) {
            if (graph[currentNode][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
}

int main() {
    int n, i, j;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int graph[MAX_NODES][MAX_NODES];
    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &graph[i][j]);

    int startNode;
    printf("Enter the starting node: ");
    scanf("%d", &startNode);

    printf("BFS Traversal: ");
    bfs(graph, startNode, n);
    
    return 0;
}