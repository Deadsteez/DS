#include <stdio.h>
#include <stdlib.h>

struct DLL {
    int data;
    struct DLL* next;
    struct DLL* prev;
};

void display(struct DLL* head) {
    struct DLL* temp = head;
    printf("Elements of the linked list are:\n");
    while (temp != NULL) {
        printf("Data %d at address %p\n", temp->data, temp);
        temp = temp->next;
    }
}

struct DLL* insertionSort(struct DLL* head) {
    if (head == NULL)
        return NULL;

    struct DLL* sorted = NULL; // New sorted (repositioned) list
    struct DLL* current = head;

    while (current != NULL) {
        struct DLL* next = current->next;
        current->prev = current->next = NULL;

        if (sorted == NULL) {
            sorted = current;
        } else if (current->data < sorted->data) {
            // Insert at beginning
            current->next = sorted;
            sorted->prev = current;
            sorted = current;
        } else {
            struct DLL* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }

            current->next = temp->next;
            if (temp->next != NULL)
                temp->next->prev = current;

            temp->next = current;
            current->prev = temp;
        }

        current = next;
    }

    return sorted;
}


int main() {
    struct DLL* head = NULL;
    struct DLL* p, * q;
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Creating the doubly linked list
    for (int i = 0; i < n; i++) {
        p = (struct DLL*)malloc(sizeof(struct DLL));
        printf("Enter data: ");
        scanf("%d", &p->data);
        p->next = NULL;
        p->prev = NULL;

        if (head == NULL) {
            head = p;
        } else {
            q = head;
            while (q->next != NULL) {
                q = q->next;
            }
            q->next = p;
            p->prev = q;
        }
    }

    // Perform insertion sort
    head = insertionSort(head);

    // Display the sorted list
    display(head);

    return 0;
}

