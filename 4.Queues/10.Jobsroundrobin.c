#include <stdio.h>

#define SIZE 10

typedef struct {
    int data[SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int index) {
    if (q->rear == SIZE - 1) return;
    if (isEmpty(q)) q->front = 0;
    q->data[++q->rear] = index;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->data[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

int main() {
    int burst[3], remaining[3];
    int quantum;

    printf("Enter burst times for 3 jobs:\n");
    for (int i = 0; i < 3; i++) {
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    Queue q;
    initQueue(&q);

    for (int i = 0; i < 3; i++) {
        enqueue(&q, i);  // enqueue job index
    }

    int time = 0;
    while (!isEmpty(&q)) {
        int idx = dequeue(&q);

        if (remaining[idx] > quantum) {
            printf("Job %d processed for %d units\n", idx + 1, quantum);
            remaining[idx] -= quantum;
            time += quantum;
            enqueue(&q, idx);
        } else {
            printf("Job %d completed in %d units (Total Time: %d)\n",idx + 1, remaining[idx], time + remaining[idx]);
            time += remaining[idx];
            remaining[idx] = 0;
        }
    }

    return 0;
}
