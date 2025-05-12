#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct Q {
    int data[SIZE];
    int F, R;
} Q;

void EnQ(Q *q, int x) {
    if ((q->R + 1) % SIZE == q->F) {
        printf("Queue is full\n");
        return;
    }
    if (q->R == -1) {
        q->F = q->R = 0;
    } else {
        q->R = (q->R + 1) % SIZE;
    }
    q->data[q->R] = x;
}

int DeQ(Q *q) {
    if (q->F == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    int x = q->data[q->F];
    if (q->F == q->R) {
        q->F = q->R = -1;
    } else {
        q->F = (q->F + 1) % SIZE;
    }
    return x;
}

void displayQueue(Q *q) {
    if (q->F == -1) {
        printf("Queue is empty\n");
        return;
    }
    int i = q->F;
    while (i != q->R) {
        printf("%d ", q->data[i]);
        i = (i + 1) % SIZE;
    }
    printf("%d\n", q->data[q->R]);
}

int main() {
    int n, m, x;
    Q q;
    q.F = q.R = -1; // Initialize the queue as empty

    printf("Enter total number of soldiers (n): ");
    scanf("%d", &n);
    printf("Enter count number (m): ");
    scanf("%d", &m);
    printf("Enter starting soldier number (x): ");
    scanf("%d", &x);

    // Enqueue 1..n soldiers
    for (int i = 1; i <= n; i++) {
        EnQ(&q, i);
    }

    // Rotate until soldier x is at the front
    while (q.data[q.F] != x) {
        EnQ(&q, DeQ(&q)); // Move front soldier to rear
    }

    // Eliminate soldiers until one remains
    while (q.F != q.R) {
        for (int i = 1; i < m; i++) {
            EnQ(&q, DeQ(&q)); // Move front soldier to rear
        }
        int eliminated = DeQ(&q); // Remove the m-th soldier
        printf("Soldier %d is removed from the game\n", eliminated);
    }

    printf("Soldier %d wins and will go for help\n", DeQ(&q));
    return 0;
}


