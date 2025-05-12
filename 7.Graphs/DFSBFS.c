#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

// Stack
typedef struct Stack {
    int data;
    struct Stack *next;
} Stack;

Stack* top = NULL;

void push(int a) {
    Stack *p = (struct Stack*)malloc(sizeof(struct Stack));
    p->data = a;
    p->next = top;
    top = p;
}

int pop() {
    if (top != NULL) {
        Stack *p = top;
        int x = p->data;
        top = top->next;
        free(p);
        return x;
    } else {
        return -1;
    }
}

int emptyStack() {
    return top == NULL;
}

// Queue
typedef struct Q {
    int data[SIZE];
    int F, R;
} Q;

Q q;

int emptyQ(Q q) {
    return (q.F == -1 && q.R == -1);
}

void EnQ(int x) {
    if (emptyQ(q)) {
        q.F = 0;
        q.R = 0;
    } else {
        q.R++;
    }
    q.data[q.R] = x;
}

int DeQ() {
    int x = q.data[q.F];
    if (q.F == q.R)
        q.F = q.R = -1;
    else
        q.F++;
    return x;
}

// Adjacency Matrix
int M[10][10];

void creatematrix(int n) {
    int v1, v2, e;
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = 0;

    for (int i = 0; i < e; i++) {
        printf("Enter edge %d (e.g., 0 1): ", i + 1);
        scanf("%d%d", &v1, &v2);
        if (v1 >= 0 && v1 < n && v2 >= 0 && v2 < n) {
            M[v1][v2] = 1;
            M[v2][v1] = 1;
        } else {
            printf("Invalid vertices. Try again.\n");
            i--; // redo this iteration
        }
    }
}

// Adjacency List
struct node {
    int vertex;
    struct node* next;
};

struct node *A[10];

void init(struct node* A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = NULL;
}

void create(struct node* A[], int n) {
    int v1, v2, e;
    printf("Enter number of edges: ");
    scanf("%d", &e);

    for (int i = 0; i < e; i++) {
        printf("Enter edge %d (e.g., 0 1): ", i + 1);
        scanf("%d%d", &v1, &v2);

        // v1 -> v2
        struct node *newNode = (struct node*)malloc(sizeof(struct node));
        newNode->vertex = v2;
        newNode->next = NULL;
        if (A[v1] == NULL)
            A[v1] = newNode;
        else {
            struct node *p = A[v1];
            while (p->next != NULL)
                p = p->next;
            p->next = newNode;
        }

        // v2 -> v1
        newNode = (struct node*)malloc(sizeof(struct node));
        newNode->vertex = v1;
        newNode->next = NULL;
        if (A[v2] == NULL)
            A[v2] = newNode;
        else {
            struct node *p = A[v2];
            while (p->next != NULL)
                p = p->next;
            p->next = newNode;
        }
    }
}

void BFSmatrix(int M[10][10], int v) {
    int visited[10], i, st;
    for (i = 0; i < v; i++)
        visited[i] = 0;

    printf("Enter starting vertex for BFS (Adjacency Matrix): ");
    scanf("%d", &st);

    printf("BFS Traversal (Matrix): ");
    EnQ(st);
    visited[st] = 1;

    while (!emptyQ(q)) {
        int n = DeQ();
        printf("%d ", n);

        for (i = 0; i < v; i++) {
            if (M[n][i] == 1 && visited[i] == 0) {
                EnQ(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void DFSmatrix(int M[10][10], int v) {
    int visited[10], i, st;
    for (i = 0; i < v; i++)
        visited[i] = 0;

    printf("Enter starting vertex for DFS (Adjacency Matrix): ");
    scanf("%d", &st);

    printf("DFS Traversal (Matrix): ");
    push(st);
    visited[st] = 1;
    printf("%d ", st);

    do {
        int flag = 0;
        for (i = 0; i < v; i++) {
            if (M[st][i] == 1 && visited[i] == 0) {
                push(i);
                visited[i] = 1;
                printf("%d ", i);
                st = i;
                flag = 1;
                break;
            }
        }
        if (flag == 0 && !emptyStack())
            st = pop();
    } while (!emptyStack());

    printf("\n");
}

void BFSlist(struct node* A[], int v) {
    int visited[10], n, i, st;
    struct node *p;

    for (i = 0; i < v; i++)
        visited[i] = 0;

    printf("Enter starting vertex for BFS (Adjacency List): ");
    scanf("%d", &st);

    printf("BFS Traversal (List): ");
    EnQ(st);
    visited[st] = 1;

    while (!emptyQ(q)) {
        n = DeQ();
        printf("%d ", n);
        p = A[n];
        while (p != NULL) {
            if (visited[p->vertex] == 0) {
                EnQ(p->vertex);
                visited[p->vertex] = 1;
            }
            p = p->next;
        }
    }
    printf("\n");
}

void DFSlist(struct node* A[], int v) {
    int visited[10], n, i, st;
    struct node *p;

    for (i = 0; i < v; i++)
        visited[i] = 0;

    printf("Enter starting vertex for DFS (Adjacency List): ");
    scanf("%d", &st);

    printf("DFS Traversal (List): ");
    push(st);
    visited[st] = 1;
    printf("%d ", st);

    do {
        p = A[st];
        while (p != NULL) {
            if (visited[p->vertex] == 0) {
                push(p->vertex);
                visited[p->vertex] = 1;
                printf("%d ", p->vertex);
                st = p->vertex;
                break;
            } else {
                p = p->next;
            }
        }
        if (p == NULL && !emptyStack())
            st = pop();
    } while (!emptyStack());

    printf("\n");
}

int main() {
    int n;
    q.F = q.R = -1;
    printf("Enter number of vertices in the graph: ");
    scanf("%d", &n);

    creatematrix(n);
    BFSmatrix(M, n);
    DFSmatrix(M, n);

    q.F = q.R = -1; // Reset queue
    init(A, n);
    create(A, n);
    BFSlist(A, n);
    DFSlist(A, n);

    return 0;
}
