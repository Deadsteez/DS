#include <stdio.h>
#include <stdlib.h>

#define SIZE 30

typedef struct Queue {
    int data[SIZE]; 
    int front, rear; 
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = -1;  
}

int isEmpty(Queue* q) {
    return q->front == -1;  
}

int isFull(Queue* q) {
    return q->rear == SIZE - 1;  
}


void Enqueue(Queue* q, int patientID) {
    if (isFull(q)) {
        printf("Sorry, the clinic is full. Please wait for a slot.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;  
    }
    q->rear++;
    q->data[q->rear] = patientID;
    printf("Patient %d has checked in.\n", patientID);
}

int Dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("No patients are waiting for consultation.\n");
        return -1;  
    }
    int patientID = q->data[q->front];
   
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return patientID;
}

void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No patients are waiting.\n");
        return;
    }
    printf("Patients waiting for consultation: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);  // Initialize the queue

    int choice, patientID;

    while (1) {
        printf("\nClinic Menu:\n");
        printf("1. Check-in a Patient\n");
        printf("2. Assign Doctor to Patient\n");
        printf("3. Display Waiting List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the patient ID: ");
                scanf("%d", &patientID);
                Enqueue(&q, patientID);  // Check-in the patient
                break;

            case 2:
                patientID = Dequeue(&q);  // Assign doctor to the first patient
                if (patientID != -1) {
                    printf("Doctor is now seeing patient %d.\n", patientID);
                }
                break;

            case 3:
                displayQueue(&q);  // Show the list of patients waiting for consultation
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);  // Exit the program

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
