#include <stdio.h>
#include <stdlib.h>

// Node structure for a doubly linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to copy a doubly linked list
struct Node* CopyList(struct Node* head) {
    struct Node* newHead = NULL;
    struct Node* tail = NULL;
    struct Node* p = head;

    while (p != NULL) {
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->data = p->data;
        node->next = NULL;
        node->prev = NULL;

        if (newHead == NULL) {
            newHead = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }

        p = p->next;
    }

    return newHead;
}

// Utility to create a new node
struct Node* CreateNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Utility to print the list forward
void PrintList(struct Node* head) {
    struct Node* p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    // Create a sample list: 10 <-> 20 <-> 30
    struct Node* head = CreateNode(10);
    head->next = CreateNode(20);
    head->next->prev = head;
    head->next->next = CreateNode(30);
    head->next->next->prev = head->next;

    printf("Original list: ");
    PrintList(head);

    struct Node* copied = CopyList(head);

    printf("Copied list:   ");
    PrintList(copied);

    return 0;
}
