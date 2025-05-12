#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define SERVICE_TIME 15

struct Queue {
    int data[MAX]; // store only timestamps
    int front, rear;
};

void initQueue(struct Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue *q) {
    return q->front == -1;
}

void enqueue(struct Queue *q, int timestamp) {
    if (q->rear == MAX - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->data[q->rear] = timestamp;
}

int dequeue(struct Queue *q) {
    int temp = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return temp;
}

int main() {
    struct Queue landingQueue, takeoffQueue;
    initQueue(&landingQueue);
    initQueue(&takeoffQueue);

    int runway1 = 0, runway2 = 0;
    int landingsDone = 0, takeoffsDone = 0;
    int totalLandingWait = 0, totalTakeoffWait = 0;

    for (int time = 0; time <= 120; time++) {
        if (time % 5 == 0) {
            if (rand() % 2 == 0) {
                enqueue(&landingQueue, time);
                printf("New landing request at time %d\n", time);
            } else {
                enqueue(&takeoffQueue, time);
                printf("New takeoff request at time %d\n", time);
            }
        }

        if (runway1 > 0) runway1--;
        if (runway2 > 0) runway2--;

        if (runway1 == 0) {
            if (!isEmpty(&landingQueue)) {
                int reqTime = dequeue(&landingQueue);
                runway1 = SERVICE_TIME - 1;
                landingsDone++;
                totalLandingWait += (time - reqTime);
                printf("Runway 1: Landing processed (request at %d, now at %d)\n", reqTime, time);
            } else if (!isEmpty(&takeoffQueue)) {
                int reqTime = dequeue(&takeoffQueue);
                runway1 = SERVICE_TIME - 1;
                takeoffsDone++;
                totalTakeoffWait += (time - reqTime);
                printf("Runway 1: Takeoff processed (request at %d, now at %d)\n", reqTime, time);
            }
        }

        if (runway2 == 0) {
            if (!isEmpty(&landingQueue)) {
                int reqTime = dequeue(&landingQueue);
                runway2 = SERVICE_TIME - 1;
                landingsDone++;
                totalLandingWait += (time - reqTime);
                printf("Runway 2: Landing processed (request at %d, now at %d)\n", reqTime, time);
            } else if (!isEmpty(&takeoffQueue)) {
                int reqTime = dequeue(&takeoffQueue);
                runway2 = SERVICE_TIME - 1;
                takeoffsDone++;
                totalTakeoffWait += (time - reqTime);
                printf("Runway 2: Takeoff processed (request at %d, now at %d)\n", reqTime, time);
            }
        }
    }

    printf("\nSimulation ended.\n");
    printf("Total landings completed: %d\n", landingsDone);
    printf("Total takeoffs completed: %d\n", takeoffsDone);

    int remainingLanding = isEmpty(&landingQueue) ? 0 : (landingQueue.rear - landingQueue.front + 1);
    int remainingTakeoff = isEmpty(&takeoffQueue) ? 0 : (takeoffQueue.rear - takeoffQueue.front + 1);
    printf("Remaining planes waiting to land: %d\n", remainingLanding);
    printf("Remaining planes waiting to takeoff: %d\n", remainingTakeoff);

    printf("Average waiting time for landing: %.2f minutes\n", landingsDone ? (float)totalLandingWait / landingsDone : 0);
    printf("Average waiting time for takeoff: %.2f minutes\n", takeoffsDone ? (float)totalTakeoffWait / takeoffsDone : 0);

    return 0;
}
