#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct Q {
    int data[SIZE];
    int F, R;
} Q;

int isFull(Q *q) {
    return q->R == SIZE - 1;
}

int isEmpty(Q *q) {
    return (q->F == -1);
}

void EnQFront(Q *q, int x) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->F == -1) {
        q->F = q->R = 0;
    } else {
        q->F--;
    }
    q->data[q->F] = x;
}

void EnQRear(Q *q, int x) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->F == -1) {
        q->F = q->R = 0;
    } else {
        q->R++;
    }
    q->data[q->R] = x;
}

int DeQFront(Q *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int x = q->data[q->F];
    if (q->F == q->R) {
        q->F = q->R = -1;
    } else {
        q->F++;
    }
    return x;
}

int DeQRear(Q *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int x = q->data[q->R];
    if (q->F == q->R) {
        q->F = q->R = -1;
    } else {
        q->R--;
    }
    return x;
}

void displayQueue(Q *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue contents: ");
    for (int i = q->F; i <= q->R; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() {
    Q q;
    q.F = q.R = -1;
    int choice, value;

    printf("\nDouble-Ended Queue Menu:\n");
    printf("1. Enqueue at Front\n");
    printf("2. Enqueue at Rear\n");
    printf("3. Dequeue from Front\n");
    printf("4. Dequeue from Rear\n");
    printf("5. Display Queue\n");
    printf("6. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to enqueue at front: ");
                scanf("%d", &value);
                EnQFront(&q, value);
                
                break;
            case 2:
                printf("Enter value to enqueue at rear: ");
                scanf("%d", &value);
                EnQRear(&q, value);
                
                break;
            case 3:
                value = DeQFront(&q);
                if (value != -1)
                    printf("Dequeued from front: %d\n", value);
                
                break;
            case 4:
                value = DeQRear(&q);
                if (value != -1)
                    printf("Dequeued from rear: %d\n", value);
                
                break;
            case 5:
                displayQueue(&q);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}
