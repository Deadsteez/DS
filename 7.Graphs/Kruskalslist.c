#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct node {
    int vertex;
    int weight;
    struct node* next;
};

struct node* A[MAX];

struct edge {
    int src, dest, weight;
};

struct edge edgeList[MAX * MAX];
int edgeCount = 0;
int par[MAX], n;

int find_par(int i) {
    while (i != par[i])
        i = par[i];
    return i;
}

int union_sets(int i, int j) {
    if (i != j) {
        par[j] = i;
        return 1;
    }
    return 0;
}

void sortEdges() {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edgeList[j].weight > edgeList[j + 1].weight) {
                struct edge temp = edgeList[j];
                edgeList[j] = edgeList[j + 1];
                edgeList[j + 1] = temp;
            }
        }
    }
}

void createList() {
    int e, v1, v2, w;
    printf("Enter number of edges: ");
    scanf("%d", &e);
    for (int i = 0; i < e; i++) {
        printf("Enter edge (v1 v2 weight): ");
        scanf("%d%d%d", &v1, &v2, &w);

        struct node* newNode, *p;

        // v1 -> v2
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

        // v2 -> v1 (undirected)
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

        // Save edge
        edgeList[edgeCount].src = v1;
        edgeList[edgeCount].dest = v2;
        edgeList[edgeCount].weight = w;
        edgeCount++;
    }
}

void kruskal_list() {
    for (int i = 0; i < n; i++) par[i] = i;

    sortEdges();
    int mst_weight = 0, count = 0;

    printf("\nMST using Adjacency List:\n");
    for (int i = 0; i < edgeCount && count < n - 1; i++) {
        int u = edgeList[i].src;
        int v = edgeList[i].dest;
        int w = edgeList[i].weight;

        int a = find_par(u);
        int b = find_par(v);

        if (union_sets(a, b)) {
            printf("Edge %d: %d - %d = %d\n", count + 1, u, v, w);
            mst_weight += w;
            count++;
        }
    }

    printf("Total weight = %d\n", mst_weight);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    createList();
    kruskal_list();

    return 0;
}
