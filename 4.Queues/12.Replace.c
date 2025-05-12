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
    return q->F == -1;
}

void EnQ(Q *q, int x) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->F = q->R = 0;
    } else {
        q->R++;
    }
    q->data[q->R] = x;
}

int DeQ(Q *q) {
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

void display(Q *q) {
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

void Replace(Q *q, int old, int newval) {
    Q temp;
    temp.F = temp.R = -1;

    while (!isEmpty(q)) {
        int x = DeQ(q);
        if (x == old) {
            EnQ(&temp, newval);
        } else {
            EnQ(&temp, x);
        }
    }

    // Copy back to original queue
    while (!isEmpty(&temp)) {
        EnQ(q, DeQ(&temp));
    }
}

int main() {
    Q q;
    q.F = q.R = -1;

    int choice, value, oldValue, newValue;

    while (1) {
        printf("\nQueue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Replace a value\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                EnQ(&q, value);
                break;
            case 2:
                printf("Enter value to replace: ");
                scanf("%d", &oldValue);
                printf("Enter new value: ");
                scanf("%d", &newValue);
                Replace(&q, oldValue, newValue);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
