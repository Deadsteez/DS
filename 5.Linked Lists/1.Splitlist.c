#include <stdio.h>
#include <stdlib.h>

struct SLL {
    int data;
    struct SLL* next;
};

// Display function
void display(struct SLL* head) {
    struct SLL* q = head;
    while (q != NULL) {
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}

int main() {
    struct SLL *head1 = NULL, *p, *q, *head2 = NULL;
    int count = 0, n, val;

    // 1) Build the list
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p = malloc(sizeof *p);
        printf("Enter data: ");
        scanf("%d", &p->data);
        p->next = NULL;
        if (!head1) {
            head1 = p;
        } else {
            q = head1;
            while (q->next)
                q = q->next;
            q->next = p;
        }
    }

    // 2) Count nodes
    q = head1;
    while (q) {
        count++;
        q = q->next;
    }

    // 3) Compute split point (front gets extra if odd)
    int mid = (count + 1) / 2;

    // 4) Traverse to the node just before the split
    q = head1;
    for (int i = 1; i < mid; i++) {
        q = q->next;
    }

    // 5) Split the list
    head2 = q->next;
    q->next = NULL;

    // 6) Display both sublists
    printf("Front half: ");
    display(head1);
    printf("Back half: ");
    display(head2);

    return 0;
}
