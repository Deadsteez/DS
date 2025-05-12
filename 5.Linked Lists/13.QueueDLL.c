#include <stdio.h>
#include <stdlib.h>

// Node structure for DLL
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// DLL-based Queue
struct Queue {
    struct Node* F;
    struct Node* R;
};

struct Queue* q = NULL;

int isEmptyQ() {
    return q->F == NULL;
}


void EnQ(int val) {
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));
    p->data = val;
    p->next = NULL;
    p->prev = NULL;

    if (isEmptyQ()) {
        q->F = q->R = p;
    } else {
        q->R->next = p;
        p->prev = q->R;
        q->R = p;
    }
}

int DeQ() {
    if (isEmptyQ()) {
        printf("Queue is empty\n");
        return -1;
    }

    int val = q->F->data;
    struct Node* temp = q->F;

    if (q->F == q->R) {
        q->F = q->R = NULL;
    } else {
        q->F = q->F->next;
        q->F->prev = NULL;
    }

    free(temp);
    return val;
}

void display() {
    struct Node* p = q->F;
    printf("Queue elements (Front to Rear): ");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    q = (struct Queue*)malloc(sizeof(struct Queue));
    q->F = q->R = NULL;

    EnQ(10);
    EnQ(20);
    EnQ(30);
    display();

    printf("Dequeued: %d\n", DeQ());
    display();

    return 0;
}
