#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

// Task Types
#define DOWNLOAD 1
#define MUSIC 2
#define GAME 3

typedef struct Task {
    int taskType; 
    char description[50]; 
} Task;

typedef struct Queue {
    Task tasks[SIZE];
    int front, rear;
} Queue;

// Function to check if the queue is full
int isFull(Queue* q) {
    return q->rear == SIZE - 1;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Enqueue task to the queue
void enqueue(Queue* q, Task task) {
    if (isFull(q)) {
        printf("Queue is full, cannot enqueue task: %s\n", task.description);
        return;
    }
    if (q->front == -1) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->tasks[q->rear] = task;
}

// Dequeue task from the queue
Task dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty, no task to dequeue.\n");
        Task emptyTask = {0, ""};
        return emptyTask;
    }
    Task task = q->tasks[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return task;
}

// Function to display the queue contents
void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Current Queue: \n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Task Type: %d, Description: %s\n", q->tasks[i].taskType, q->tasks[i].description);
    }
}

// Function to simulate the multitasking system
void multitask(Queue* downloadQueue, Queue* otherQueue) {
    // Process all download tasks first (highest priority)
    while (!isEmpty(downloadQueue)) {
        Task task = dequeue(downloadQueue);
        printf("Processing Download Task: %s\n", task.description);
    }

    // Then process all other tasks (lower priority)
    while (!isEmpty(otherQueue)) {
        Task task = dequeue(otherQueue);
        if (task.taskType == MUSIC) {
            printf("Processing Music Task: %s\n", task.description);
        } else if (task.taskType == GAME) {
            printf("Processing Game Task: %s\n", task.description);
        }
    }
}

int main() {
    Queue downloadQueue, otherQueue;
    downloadQueue.front = downloadQueue.rear = -1;
    otherQueue.front = otherQueue.rear = -1;

    Task task;
    int choice;

    while (1) {
        printf("\nMultitasking System Menu:\n");
        printf("1. Add Download Task\n");
        printf("2. Add Music Task\n");
        printf("3. Add Game Task\n");
        printf("4. Process Tasks\n");
        printf("5. Display Queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter description for download task: ");
                getchar(); // To clear the buffer
                fgets(task.description, 50, stdin);
                task.description[strcspn(task.description, "\n")] = '\0'; // Remove newline character
                task.taskType = DOWNLOAD;
                enqueue(&downloadQueue, task);
                break;
            case 2:
                printf("Enter description for music task: ");
                getchar(); // To clear the buffer
                fgets(task.description, 50, stdin);
                task.description[strcspn(task.description, "\n")] = '\0'; // Remove newline character
                task.taskType = MUSIC;
                enqueue(&otherQueue, task);
                break;
            case 3:
                printf("Enter description for game task: ");
                getchar(); // To clear the buffer
                fgets(task.description, 50, stdin);
                task.description[strcspn(task.description, "\n")] = '\0'; // Remove newline character
                task.taskType = GAME;
                enqueue(&otherQueue, task);
                break;
            case 4:
                multitask(&downloadQueue, &otherQueue);
                break;
            case 5:
                printf("\nDownload Queue:\n");
                displayQueue(&downloadQueue);
                printf("\nOther Task Queue:\n");
                displayQueue(&otherQueue);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
