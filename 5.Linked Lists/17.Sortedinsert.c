#include <stdio.h>
#include <stdlib.h>

struct DLL {
    int data;
    struct DLL* next;
    struct DLL* prev;
};

void display(struct DLL* head) {
    struct DLL* q = head;
    printf("Elements of the linked list are:\n");
    while (q != NULL) {
        printf("Data %d at address %p\n", q->data, (void*)q);
        q = q->next;
    }
}

void SortedInsert(struct DLL* head, struct DLL* newNode) {
    if (head == NULL) {
        head = newNode;
        return;
    }

    // If the new node needs to be inserted at the beginning
    if (head->data >= newNode->data) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    struct DLL* current = head;

    // Traverse the list to find the correct insertion point
    while (current->next != NULL && current->data < newNode->data) {
        current = current->next;
    }

    // Insert at the correct position (between current and current->next)
    if (current->next != NULL) {
        newNode->next = current->next;
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

int main() {
    struct DLL* head = NULL;

    struct DLL* newNode = (struct DLL*)malloc(sizeof(struct DLL));
    newNode->data = 5;
    newNode->next = newNode->prev = NULL;
    SortedInsert(head, newNode);

    newNode = (struct DLL*)malloc(sizeof(struct DLL));
    newNode->data = 10;
    newNode->next = newNode->prev = NULL;
    SortedInsert(head, newNode);

    newNode = (struct DLL*)malloc(sizeof(struct DLL));
    newNode->data = 7;
    newNode->next = newNode->prev = NULL;
    SortedInsert(head, newNode);

    newNode = (struct DLL*)malloc(sizeof(struct DLL));
    newNode->data = 3;
    newNode->next = newNode->prev = NULL;
    SortedInsert(head, newNode);

    display(head);
    
    return 0;
}
