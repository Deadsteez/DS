#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int front;
    int rear;
} Queue;

int arr[MAX];
int n, m, size;
int queueNo = 0; // current queue number (0-based)
Queue q;

// Enqueue operation with value as parameter
void EnQ(int val) {
    // Move to next queue if current one filled
    if ((q.rear + 1) % size == 0 && q.rear != -1) {
        queueNo++;
        printf("Queue %d full. Moving to Queue %d\n", queueNo, queueNo + 1);
    }

    q.rear++;
    arr[q.rear] = val;
    printf("Inserted %d in Queue %d\n", val, queueNo + 1);
}

// Dequeue operation
void DeQ() {
    if (q.front == q.rear) {
        printf("All queues are empty!\n");
        return;
    }

    q.front++;
    printf("Deleted %d from Queue %d\n", arr[q.front], (q.front / size) + 1);
}

// Display all queues
void display() {
    if (q.front == q.rear) {
        printf("All queues are empty!\n");
        return;
    }

    printf("Displaying all queues:\n");

    for (int i = q.front + 1; i <= q.rear; i++) {
        int queueNum = (i / size) + 1;
        if (i == q.front + 1 || (i % size) == 0)
            printf("Queue %d: ", queueNum);
        printf("%d ", arr[i]);

        // Print newline when end of a queue or last element
        if ((i + 1) % size == 0 || i == q.rear)
            printf("\n");
    }
}

int main() {
    int choice, val;

    printf("Enter total size of array (n): ");
    scanf("%d", &n);
    printf("Enter number of queues (m): ");
    scanf("%d", &m);

    q.front = -1;
    q.rear = -1;
    size = n / m;

    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                EnQ(val);
                break;
            case 2: DeQ(); break;
            case 3: display(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
