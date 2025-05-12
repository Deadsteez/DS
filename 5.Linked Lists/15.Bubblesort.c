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
        printf("Data %d at address %p\n", q->data, q);
        q = q->next;
    }
}

struct DLL* bubbleSort(struct DLL* head) {
    if (!head || !head->next) return head;

    int swap_count = 0;
    struct DLL *p, *q;
    for (p = head; p->next != NULL; p = p->next) {
        for (q = head; q->next != NULL; q = q->next) {
            if (q->data > q->next->data) {
                int temp = q->data;
                q->data = q->next->data;
                q->next->data = temp;
                swap_count++;
            }
        }
    }
    printf("Swap count: %d\n", swap_count);
    return head;
}

int main() {
    struct DLL *head = NULL, *p, *tail;
    int n, val;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p = malloc(sizeof *p);
        printf("Enter data: ");
        scanf("%d", &p->data);
        p->next = p->prev = NULL;
        if (!head) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
    }

    head = bubbleSort(head);
    display(head);
    return 0;
}
