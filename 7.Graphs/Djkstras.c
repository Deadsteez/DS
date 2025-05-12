#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10

int v, G[MAX][MAX];

int findMinVertex(int dist[], int visited[]) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < v; i++)
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    return index;
}

void createMatrix() {
    int e, v1, v2, w;
    printf("Enter number of edges: ");
    scanf("%d", &e);
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            G[i][j] = 0;
    for (int i = 0; i < e; i++) {
        printf("Enter edge (v1 v2 weight): ");
        scanf("%d%d%d", &v1, &v2, &w);
        G[v1][v2] = w;
    }
}

void DjkstrasMatrix() {
    int dist[MAX], visited[MAX];
    for (int i = 0; i < v; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    int start;
    printf("Enter start vertex for Matrix: ");
    scanf("%d", &start);
    dist[start] = 0;

    for (int count = 0; count < v - 1; count++) {
        int u = findMinVertex(dist, visited);
        visited[u] = 1;
        for (int i = 0; i < v; i++) {
            if (G[u][i] && !visited[i] && dist[u] + G[u][i] < dist[i]) {
                dist[i] = dist[u] + G[u][i];
            }
        }
    }

    for (int i = 0; i < v; i++)
        printf("Distance of %d from source vertex is %d\n", i, dist[i]);
}

struct node {
    int vertex, weight;
    struct node* next;
};

struct node* A[MAX];

void initList() {
    for (int i = 0; i < v; i++)
        A[i] = NULL;
}

void insertEdge(int v1, int v2, int w) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v2;
    newNode->weight = w;
    newNode->next = NULL;

    if (A[v1] == NULL)
        A[v1] = newNode;
    else {
        struct node* p = A[v1];
        while (p->next != NULL)
            p = p->next;
        p->next = newNode;
    }
}

void createList() {
    int e, v1, v2, w;
    printf("Enter number of edges: ");
    scanf("%d", &e);
    for (int i = 0; i < e; i++) {
        printf("Enter edge (v1 v2 weight): ");
        scanf("%d%d%d", &v1, &v2, &w);
        insertEdge(v1, v2, w);
    }
}

void DjkstrasList() {
    int dist[MAX], visited[MAX] = {0};
    for (int i = 0; i < v; i++)
        dist[i] = INT_MAX;

    int start;
    printf("Enter start vertex for List: ");
    scanf("%d", &start);
    dist[start] = 0;

    for (int count = 0; count < v - 1; count++) {
        int u = findMinVertex(dist, visited);
        visited[u] = 1;
        struct node* temp = A[u];
        while (temp) {
            int j = temp->vertex;
            int w = temp->weight;
            if (!visited[j] && dist[u] + w < dist[j]) {
                dist[j] = dist[u] + w;
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < v; i++)
        printf("Distance of %d from source vertex is %d\n", i, dist[i]);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &v);

    printf("\nMatrix\n");
    createMatrix();
    DjkstrasMatrix();

    printf("\nList\n");
    initList();
    createList();
    DjkstrasList();

    return 0;
}
