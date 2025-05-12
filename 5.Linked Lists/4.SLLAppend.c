#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Display function
void display(struct Node* head) {
    struct Node* q = head;
    printf("List: ");
    while (q != NULL) {
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}

// Create list function
struct Node* createList() {
    int n;
    struct Node* head = NULL, * p, * q;
    printf("Enter the number of elements to create: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter data: ");
        scanf("%d", &p->data);
        p->next = NULL;

        if (head == NULL) {
            head = p;
        } else {
            q = head;
            while (q->next != NULL) {
                q = q->next;
            }
            q->next = p;
        }
    }
    return head;
}

int main() {
    struct Node *head1, *head2, *q;

    printf("Create List 1:\n");
    head1 = createList();

    printf("Create List 2:\n");
    head2 = createList();

    // a) Append head1 to the START of head2 (by modifying head2)
    q = head1;
    while (q->next != NULL) {
        q = q->next;
    }
    q->next = head2;

    printf("\nList after appending List1 at START of List2:\n");
    display(head1);  // The result will show head1 followed by head2.

    // Recreate both lists
    printf("\nCreate List 1 again:\n");
    head1 = createList();

    printf("Create List 2 again:\n");
    head2 = createList();

    // b) Append head1 to the END of head2
    q = head2;
    while (q->next != NULL) {
        q = q->next;
    }
    q->next = head1;

    printf("\nList after appending List1 at END of List2:\n");
    display(head2);

    return 0;
}
