#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

typedef struct Q {
    int data[SIZE];
    int F, R;
} Q;

int isFull(Q *q) {
    return ((q->R + 1) % SIZE == q->F);
}

int isEmpty(Q *q) {
    return (q->F == -1);
}

void Enqueue(Q *q, int x) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->F = q->R = 0;
    } else {
        q->R = (q->R + 1) % SIZE;
    }
    q->data[q->R] = x;
}

int Dequeue(Q *q) {
    if (isEmpty(q)) {
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
    if (isEmpty(q)) {
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
    Q q;
    q.F = q.R = -1;
    int choice, value;

    printf("\nCircular Queue Menu:\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Display Queue\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                Enqueue(&q, value);
                displayQueue(&q);
                break;
            case 2:
                value = Dequeue(&q);
                if (value != -1)
                    printf("Dequeued: %d\n", value);
                displayQueue(&q);
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}
