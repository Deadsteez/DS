#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct Q {
    int data[SIZE];
    int F, R;
} Q;

void init(Q *q) {
    q->F = q->R = -1;
}

int isFull(Q *q) {
    return q->R == SIZE - 1;
}

int isEmpty(Q *q) {
    return q->F == -1;
}

void Addq(Q *q, int x) {
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

int Delq(Q *q) {
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

void Display(Q *q, int num) {
    if (isEmpty(q)) {
        printf("Queue %d is empty\n", num);
        return;
    }
    printf("Queue %d contents: ", num);
    for (int i = q->F; i <= q->R; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() {
    Q q1, q2;
    init(&q1);
    init(&q2);

    int ch, val, qno;
    while (1) {
        printf("\nMenu:\n1. Addq\n2. Delq\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &qno);
                printf("Enter value to add: ");
                scanf("%d", &val);
                if (qno == 1)
                    Addq(&q1, val);
                else if (qno == 2)
                    Addq(&q2, val);
                else
                    printf("Invalid queue number\n");
                break;

            case 2:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &qno);
                if (qno == 1)
                    val = Delq(&q1);
                else if (qno == 2)
                    val = Delq(&q2);
                else {
                    printf("Invalid queue number\n");
                    break;
                }
                if (val != -1)
                    printf("Deleted value: %d\n", val);
                break;

            case 3:
                Display(&q1, 1);
                Display(&q2, 2);
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
