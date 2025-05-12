#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* top = NULL;

void push(int value) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = top;

    if (top != NULL) {
        top->prev = newNode;
    }

    top = newNode;
}

int pop() {
    if (top == NULL) {
        printf("Stack Underflow\n");
        return -1;
    }

    struct Node* temp = top;
    int val = temp->data;

    top = top->next;
    if (top != NULL) {
        top->prev = NULL;
    }

    free(temp);
    return val;
}

int main() {
    push(10);
    push(20);
    push(30);

    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop()); // Underflow case

    return 0;
}
