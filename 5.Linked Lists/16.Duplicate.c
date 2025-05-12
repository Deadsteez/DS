#include <stdio.h>
#include <stdlib.h>

struct DLL {
    int data;
    struct DLL* next;
    struct DLL* prev;
};

// Function to display the list
void display(struct DLL* head) {
    struct DLL* q = head;
    printf("Elements of the linked list are:\n");
    while (q != NULL) {
        printf("Data %d at address %p\n", q->data, (void*)q);
        q = q->next;
    }
}

// Function to remove duplicates from a sorted doubly linked list
void removeDuplicates(struct DLL* head) {
    if (head == NULL) return;

    struct DLL* current = head;

    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            struct DLL* temp = current->next;
            current->next = temp->next;
            if (temp->next != NULL)
                temp->next->prev = current;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// Bubble sort for sorting the list before removing duplicates
void bubbleSort(struct DLL* head) {
    if (!head) return;

    int swapped;
    struct DLL* ptr;
    do {
        swapped = 0;
        ptr = head;
        while (ptr->next != NULL) {
            if (ptr->data > ptr->next->data) {
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
    } while (swapped);
}

// Function to insert a new node at the end of the list
void insertEnd(struct DLL** head, int data) {
    struct DLL* newNode = (struct DLL*)malloc(sizeof(struct DLL));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct DLL* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

int main() {
    struct DLL* head = NULL;
    int n, val;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter data %d: ", i + 1);
        scanf("%d", &val);
        insertEnd(&head, val);
    }

    printf("\nBefore removing duplicates:\n");
    display(head);

    // Sort the list before removing duplicates
    bubbleSort(head);

    // Remove duplicates
    removeDuplicates(head);

    printf("\nAfter removing duplicates:\n");
    display(head);

    return 0;
}
