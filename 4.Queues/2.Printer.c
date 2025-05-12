#include <stdio.h>
#include <stdlib.h>

#define JOBS 100
#define PRINTERS 3
#define MAX_QUEUE_SIZE 100

// Queue structure
typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Queue operations
void EnQ(Queue *q, int value) {
    if (q->rear == MAX_QUEUE_SIZE) {
        printf("Queue overflow!\n");
        exit(1);
    }
    q->data[q->rear++] = value;
}

int DeQ(Queue *q) {
    if (q->front == q->rear) {
        printf("Queue underflow!\n");
        exit(1);
    }
    return q->data[q->front++];
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

// Main function
int main() {
    int jobs[JOBS];
    int i, j, temp;
    Queue q;
    q.front = q.rear = 0;

    // Step 1: Generate random jobs
    printf("Jobs (pages):\n");
    for (i = 0; i < JOBS; i++) {
        jobs[i] = rand() % 50 + 1; // Pages between 1 and 50
        printf("%d ", jobs[i]);
    }
    printf("\n\n");

    // Step 2: Sort jobs in ascending order
    for (i = 0; i < JOBS - 1; i++) {
        for (j = 0; j < JOBS - 1 - i; j++) {
            if (jobs[j] > jobs[j + 1]) {
                temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }

    // Step 3: EnQ all jobs
    for (i = 0; i < JOBS; i++) {
        EnQ(&q, jobs[i]);
    }

    // Step 4: DeQ into printers until each has at least 10 pages
    int printer = 0;
    int printerPageCount[PRINTERS] = {0};
    int printerJobCount[PRINTERS] = {0};
    int jobStartTimes[JOBS];
    int jobEndTimes[JOBS];
    int jobIndex = 0;  // To track job number

    printf("Assigned Jobs:\n");
    printf("Job#  Pages  Printer#  Start Time  End Time\n");

    while (!isEmpty(&q)) {
        int sumPages = 0;
        int startTime = 0;

        while (!isEmpty(&q) && sumPages < 10) {
            int jobPages = DeQ(&q);
            sumPages += jobPages;

            // Start time of this job
            startTime = printerPageCount[printer];

            // Calculate end time (time taken to print job)
            int printTime = (jobPages + 9) / 10;  // Round up to nearest integer
            int endTime = startTime + printTime;

            // Record job start and end times
            jobStartTimes[jobIndex] = startTime;
            jobEndTimes[jobIndex] = endTime;

            printf("%4d  %5d     %d      %5d      %5d\n", jobIndex + 1, jobPages, printer + 1, startTime, endTime);

            printerPageCount[printer] += jobPages;
            printerJobCount[printer]++;
            jobIndex++;
        }

        printer = (printer + 1) % PRINTERS;
    }

    // Step 5: Summary
    printf("\nPrinter Summary:\n");
    for (i = 0; i < PRINTERS; i++) {
        printf("Printer %d: Total Pages = %d, Jobs = %d\n", i + 1, printerPageCount[i], printerJobCount[i]);
    }

    // Step 6: Calculate average time
    int totalTime = 0;
    for (i = 0; i < JOBS; i++) {
        totalTime += (jobEndTimes[i] - jobStartTimes[i]);
    }

    float averageTime = (float)totalTime / JOBS;
    printf("\nAverage time per job: %.2f minutes\n", averageTime);

    return 0;
}
