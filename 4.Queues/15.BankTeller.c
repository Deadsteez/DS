#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

typedef struct Q {
    int data[SIZE]; // Each value represents service time needed by a customer
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

void simulateTeller(Q *q, int numTellers) {
    int tellerTime[2] = {0}; // Max 2 tellers for simplicity
    int totalWait = 0, count = 0;

    while (!isEmpty(q)) {
        int serviceTime = Delq(q);
        int minIndex = 0;

        if (numTellers == 2 && tellerTime[1] < tellerTime[0])
            minIndex = 1;

        totalWait += tellerTime[minIndex];
        tellerTime[minIndex] += serviceTime;
        count++;
    }

    printf("\nSimulation with %d teller(s):\n", numTellers);
    printf("Average waiting time: %.2f units\n", count > 0 ? (float)totalWait / count : 0);
}

int main() {
    Q bankQueue;
    init(&bankQueue);

    int n, time;
    printf("Enter number of customers: ");
    scanf("%d", &n);

    printf("Enter service time for each customer:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &time);
        Addq(&bankQueue, time);
    }

    // Copy the queue to simulate with both teller setups
    Q tempQueue = bankQueue;

    simulateTeller(&bankQueue, 1);  // Single teller simulation
    simulateTeller(&tempQueue, 2);  // Two teller simulation

    return 0;
}
