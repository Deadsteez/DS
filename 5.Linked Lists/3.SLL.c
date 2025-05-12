#include <stdio.h>
#include <stdlib.h>

struct SLL {
    int data;
    struct SLL* next;
};

void display(struct SLL *head) {
    struct SLL* q = head;
    printf("Elements of the linked list are: \n");
    while (q != NULL) {
        printf("Data %d is at address %p \n", q->data, q);
        q = q->next;
    }
}

struct SLL* Insert(struct SLL* head, int val, int loc) {
    struct SLL *p, *q;
    p = (struct SLL*)malloc(sizeof(struct SLL));
    p->data = val;
    p->next = NULL;
    if (loc == 1) {
        p->next = head;
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
    q->next = p;
    return head;
}

struct SLL* Delete(struct SLL* head, int loc) {
    struct SLL *p, *q;
    if (head == NULL) {
        printf("The list is empty.\n");
        return head;
    }
    if (loc == 1) {
        q = head;
        head = head->next;
        free(q);
        return head;
    }
    q = head;
    p = NULL;
    for (int i = 1; i < loc; i++) {
        p = q;
        q = q->next;
        if (q == NULL) {
            printf("Invalid position!\n");
            return head;
        }
    }
    p->next = q->next;
    free(q);
    return head;
}

struct SLL* Reverse(struct SLL* head) {
    struct SLL* prev = NULL, * curr = head, * next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

int main() {
    struct SLL* head = NULL;
    struct SLL* p;
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
                    p = (struct SLL*)malloc(sizeof(struct SLL));
                    printf("Enter data: ");
                    scanf("%d", &p->data);
                    p->next = NULL;
                    if (head == NULL)
                        head = p;
                    else {
                        struct SLL* q = head;
                        while (q->next != NULL) {
                            q = q->next;
                        }
                        q->next = p;
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
