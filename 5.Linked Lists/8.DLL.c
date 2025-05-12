#include <stdio.h>
#include <stdlib.h>

struct DLL {
    int data;
    struct DLL* next;
    struct DLL* prev;
};

void display(struct DLL *head) {
    struct DLL* q = head;
    printf("Elements of the linked list are: \n");
    while (q != NULL) {
        printf("Data %d is at address %p \n", q->data, q);
        q = q->next;
    }
}

struct DLL* Insert(struct DLL* head, int val, int loc) {
    struct DLL *p, *q;
    p = (struct DLL*)malloc(sizeof(struct DLL));
    p->data = val;
    p->next = NULL;
    p->prev = NULL;
    if (loc == 1) {
        p->next = head;
        if (head != NULL) head->prev = p;
        head = p;
        return head;
    }
    q = head;
    for (int i = 0; i < loc - 2; i++) {
        if (q != NULL)
            q = q->next;
        else {
            printf("Out of the list's bounds\n");
            return head;
        }
    }
    p->next = q->next;
    p->prev = q;
    if (q->next != NULL) q->next->prev = p;
    q->next = p;
    return head;
}

struct DLL* Delete(struct DLL* head, int loc) {
    struct DLL *p, *q;
    if (head == NULL) {
        printf("The list is empty.\n");
        return head;
    }
    if (loc == 1) {
        q = head;
        head = head->next;
        if (head != NULL) head->prev = NULL;
        free(q);
        return head;
    }
    q = head;
    for (int i = 1; i < loc; i++) {
        p = q;
        q = q->next;
        if (q == NULL) {
            printf("Invalid position!\n");
            return head;
        }
    }
    p->next = q->next;
    if (q->next != NULL) q->next->prev = p;
    free(q);
    return head;
}

struct DLL* Reverse(struct DLL* head) {
    struct DLL *temp = NULL, *curr = head;
    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    head = temp->prev;
    return head;
}

int main() {
    struct DLL* head = NULL;
    struct DLL* p;
    int choice, n, val, loc;
    while (1) {
        printf("\nEnter operation to be done :\n");
        printf("1)Create a linked list\n");
        printf("2)Insert a node in linked list\n");
        printf("3)Delete a node in linked list\n");
        printf("4)Reverse the linked list\n");
        printf("5)Display the linked list\n");
        printf("6)Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the number of elements to create: ");
                scanf("%d", &n);
                head = NULL;
                for (int i = 0; i < n; i++) {
                    p = (struct DLL*)malloc(sizeof(struct DLL));
                    printf("Enter data: ");
                    scanf("%d", &p->data);
                    p->next = NULL;
                    p->prev = NULL;
                    if (head == NULL)
                        head = p;
                    else {
                        struct DLL* q = head;
                        while (q->next != NULL) {
                            q = q->next;
                        }
                        q->next = p;
                        p->prev = q;
                    }
                }
                break;
            case 2:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                printf("Enter position to insert: ");
                scanf("%d", &loc);
                head = Insert(head, val, loc);
                break;
            case 3:
                printf("Enter position to delete: ");
                scanf("%d", &loc);
                head = Delete(head, loc);
                break;
            case 4:
                head = Reverse(head);
                break;
            case 5:
                display(head);
                break;
            case 6:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
