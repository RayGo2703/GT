#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Stack {
    int items[MAX_NODES];
    int top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int value) {
    stack->items[++stack->top] = value;
}

int pop(struct Stack* stack) {
    return stack->items[stack->top--];
}

void dfs(int graph[MAX_NODES][MAX_NODES], int start, int n) {
    struct Stack* stack = createStack();
    int visited[MAX_NODES] = {0};
    int i, currentNode;

    push(stack, start);

    while (!isEmpty(stack)) {
        currentNode = pop(stack);
        if (!visited[currentNode]) {
            printf("%d ", currentNode);
            visited[currentNode] = 1;
        }

        for (i = n - 1; i >= 0; --i) {
            if (graph[currentNode][i] && !visited[i]) {
                push(stack, i);
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

    printf("DFS Traversal: ");
    dfs(graph, startNode, n);

    return 0;
}