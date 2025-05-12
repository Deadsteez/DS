#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue Structure
typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void init(Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) return;
    if (isEmpty(q))
        q->front = q->rear = 0;
    else
        q->rear++;
    q->arr[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    int val = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

int main() {
    Queue regular, frequent;
    init(&regular);
    init(&frequent);

    int n, time = 0;
    int reg_wait = 0, freq_wait = 0;

    // Sample input: number of customers in each queue
    printf("Enter number of regular customers: ");
    int r;
    scanf("%d", &r);
    printf("Enter number of frequent flyers: ");
    int f;
    scanf("%d", &f);

    // Arrival times (just assume one after another)
    for (int i = 0; i < r; i++) enqueue(&regular, i);
    for (int i = 0; i < f; i++) enqueue(&frequent, i);

    // Serve 2 frequent, then 1 regular
    int freq_count = 0;

    while (!isEmpty(&regular) || !isEmpty(&frequent)) {
        if (!isEmpty(&frequent) && freq_count < 2) {
            int arrival = dequeue(&frequent);
            freq_wait += time - arrival;
            time++;
            freq_count++;
        } else if (!isEmpty(&regular)) {
            int arrival = dequeue(&regular);
            reg_wait += time - arrival;
            time++;
            freq_count = 0;  // Reset after regular
        } else if (!isEmpty(&frequent)) {
            // Regulars finished, continue with frequent
            int arrival = dequeue(&frequent);
            freq_wait += time - arrival;
            time++;
        }
    }

    printf("\nAverage waiting time for regular customers: %.2f\n",(float)reg_wait / r );
    printf("Average waiting time for frequent flyers: %.2f\n",(float)freq_wait / f);

    return 0;
}
