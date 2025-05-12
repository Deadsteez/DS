#include<stdio.h>
#include<stdlib.h>
#define MAX 10
#define INF 9999

int v,G[MAX][MAX];

int findMinVertex(int dist[], int visited[]) {
    int min = INF, index = -1;
    for (int i = 0; i < v; i++)
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    return index;
}

void displayMST(int parent[], int weight[], int vertices) {
    int totalWeight = 0;
    printf("\nMST:\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d -> %d\n", parent[i], i, weight[i]);
        totalWeight += weight[i];
    }
    printf("Total weight of MST = %d\n", totalWeight);
}



//ADJ MATRIX
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
        G[v2][v1] = w;
    }
}

void primMatrix() {
    int parent[MAX], dist[MAX], visited[MAX];
    for (int i = 0; i < v; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i]=0;
    }
    int start;
    printf("Enter start vertex for Prim (Matrix): ");
    scanf("%d", &start);
    dist[start] = 0;
    for (int i = 0; i < v - 1; i++) {
        int u = findMinVertex(dist, visited);
        visited[u] = 1;
        for (int j = 0; j < v; j++) {
            if (G[u][j] && !visited[j] && G[u][j] < dist[j]) {
                dist[j] = G[u][j];
                parent[j] = u;
            }
        }
    }
    displayMST(parent, dist, v);

}




//ADJ LIST
struct node {
    int vertex, weight;
    struct node* next;
} *A[MAX];

void initList() {
    for (int i = 0; i < v; i++) A[i] = NULL;
}

void createList() {
    int e, v1, v2, w;
    printf("Enter number of edges: ");
    scanf("%d", &e);
    for (int i = 0; i < e; i++) {
        printf("Enter edge (v1 v2 weight): ");
        scanf("%d%d%d", &v1, &v2, &w);

        struct node *newNode, *p;

        // Add edge v1 to v2
        newNode = (struct node*)malloc(sizeof(struct node));
        newNode->vertex = v2;
        newNode->weight = w;
        newNode->next = NULL;
        p = A[v1];
        if (p == NULL)
            A[v1] = newNode;
        else {
            while (p->next != NULL)
                p = p->next;
            p->next = newNode;
        }

        // Add edge v2 to v1 (undirected)
        newNode = (struct node*)malloc(sizeof(struct node));
        newNode->vertex = v1;
        newNode->weight = w;
        newNode->next = NULL;
        p = A[v2];
        if (p == NULL)
            A[v2] = newNode;
        else {
            while (p->next != NULL)
                p = p->next;
            p->next = newNode;
        }
    }
}

void primList() {
    int parent[MAX], dist[MAX], visited[MAX] = {0};
    for (int i = 0; i < v; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    int start;
    printf("Enter start vertex for Prim (List): ");
    scanf("%d", &start);
    dist[start] = 0;
    for (int i = 0; i < v - 1; i++) {
        int u = findMinVertex(dist, visited);
        visited[u] = 1;
        struct node* temp = A[u];
        while (temp) {
            int j = temp->vertex, w = temp->weight;
            if (!visited[j] && w < dist[j]) {
                dist[j] = w;
                parent[j] = u;
            }
            temp = temp->next;
        }
    }
    displayMST(parent, dist, v);

}



// MAIN
int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &v);

    printf("\nMatrix\n");
    createMatrix();
    primMatrix();

    printf("\nList\n");
    initList();
    createList();
    primList();

    return 0;
}
