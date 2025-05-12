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

struct DLL* createList(int n) {
    struct DLL *head = NULL, *tail = NULL, *p;
    int val;
    for (int i = 0; i < n; i++) {
        p = malloc(sizeof *p);
        printf("Enter data for node %d: ", i+1);
        scanf("%d", &val);
        p->data = val;
        p->next = p->prev = NULL;
        if (!head) {
            head = tail = p;
        } else {
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
    }
    return head;
}

int main() {
    struct DLL *head1, *head2, *tail1;
    int n1, n2;

    printf("Create first sorted list\n");
    printf("Enter number of elements: ");
    scanf("%d", &n1);
    head1 = createList(n1);

    printf("\nCreate second sorted list\n");
    printf("Enter number of elements: ");
    scanf("%d", &n2);
    head2 = createList(n2);

    // append list2 onto end of list1
    tail1 = head1;
    while (tail1->next != NULL)
        tail1 = tail1->next;
    tail1->next = head2;
    if (head2)
        head2->prev = tail1;

    // now sort the merged list and display
    head1 = bubbleSort(head1);
    display(head1);

    return 0;
}
