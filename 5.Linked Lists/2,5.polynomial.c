#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff, pow;
    struct Node *next;
} Node;

Node* createNode(int coeff, int pow) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;
    return newNode;
}

Node* insert(Node* head, int coeff, int pow) {
    Node* newNode = createNode(coeff, pow);
    if (!head) return newNode;
    Node* q = head;
    while (q->next != NULL)
        q = q->next;
    q->next = newNode;
    return head;
}

Node* addPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    while (p1 || p2) {
        if (p1 && (!p2 || p1->pow > p2->pow)) {
            result = insert(result, p1->coeff, p1->pow);
            p1 = p1->next;
        } else if (p2 && (!p1 || p2->pow > p1->pow)) {
            result = insert(result, p2->coeff, p2->pow);
            p2 = p2->next;
        } else {
            result = insert(result, p1->coeff + p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return result;
}

Node* multiplyPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    for (Node* i = p1; i; i = i->next)
        for (Node* j = p2; j; j = j->next)
            result = insert(result, i->coeff * j->coeff, i->pow + j->pow);
    return result;
}

void printPoly(Node* head) {
    while (head) {
        printf("%dx^%d", head->coeff, head->pow);
        if (head->next != NULL) printf(" + ");
        head = head->next;
    }
    printf("\n");
}

Node* inputPoly() {
    Node* head = NULL;
    int coeff, terms;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &terms);
    for (int i = terms - 1; i >= 0; i--) {
        printf("Enter coefficient for x^%d: ", i);
        scanf("%d", &coeff);
        head = insert(head, coeff, i);
    }
    return head;
}

int main() {
    printf("Enter first polynomial:\n");
    Node* p1 = inputPoly();
    printf("Enter second polynomial:\n");
    Node* p2 = inputPoly();

    Node* sum = addPoly(p1, p2);
    Node* product = multiplyPoly(p1, p2);

    printf("Sum: ");
    printPoly(sum);
    printf("Product: ");
    printPoly(product);

    return 0;
}
