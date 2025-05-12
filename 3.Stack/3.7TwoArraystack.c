#include <stdio.h>
#include <stdlib.h>

// Define stack node structure
struct stack {
    char data;
    struct stack *next;
};

// Three global stack tops
struct stack *top1 = NULL, *top2 = NULL, *top3 = NULL;

// Function to push onto a stack
void push(int stackNum, char value) {
    struct stack *newNode = (struct stack *)malloc(sizeof(struct stack));
    if (!newNode) {
        printf("Memory allocation failed. Stack Overflow!\n");
        return;
    }
    newNode->data = value;

    if (stackNum == 1) {
        newNode->next = top1;
        top1 = newNode;
    } else if (stackNum == 2) {
        newNode->next = top2;
        top2 = newNode;
    } else if (stackNum == 3) {
        newNode->next = top3;
        top3 = newNode;
    } else {
        printf("Invalid stack number!\n");
        free(newNode);
    }
}

// Function to pop from a stack
char pop(int stackNum) {
    struct stack *temp;
    char value;

    if (stackNum == 1) {
        if (top1 == NULL) {
            printf("Stack 1 Underflow!\n");
            return -1;
        }
        temp = top1;
        value = top1->data;
        top1 = top1->next;
    } else if (stackNum == 2) {
        if (top2 == NULL) {
            printf("Stack 2 Underflow!\n");
            return -1;
        }
        temp = top2;
        value = top2->data;
        top2 = top2->next;
    } else if (stackNum == 3) {
        if (top3 == NULL) {
            printf("Stack 3 Underflow!\n");
            return -1;
        }
        temp = top3;
        value = top3->data;
        top3 = top3->next;
    } else {
        printf("Invalid stack number!\n");
        return -1;
    }

    free(temp);
    return value;
}

// Check if a stack is empty
int isEmpty(int stackNum) {
    if (stackNum == 1)
        return top1 == NULL;
    else if (stackNum == 2)
        return top2 == NULL;
    else if (stackNum == 3)
        return top3 == NULL;
    else
        return 1;
}

// Display a stack
void display(int stackNum) {
    struct stack *current;

    if (stackNum == 1)
        current = top1;
    else if (stackNum == 2)
        current = top2;
    else if (stackNum == 3)
        current = top3;
    else {
        printf("Invalid stack number!\n");
        return;
    }

    if (current == NULL) {
        printf("Stack %d is empty\n", stackNum);
        return;
    }

    printf("Stack %d elements: ", stackNum);
    while (current) {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

// ---------------- Menu-Driven Main ----------------

int main() {
    int choice, stackNum;
    char value;

    do {
        printf("\n--- Three Stack Operations Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Check if Empty\n");
        printf("4. Display Stack\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character

        switch (choice) {
        case 1:
            printf("Enter stack number (1, 2, or 3): ");
            scanf("%d", &stackNum);
            getchar(); // clear newline
            printf("Enter character to push: ");
            scanf("%c", &value);
            push(stackNum, value);
            break;

        case 2:
            printf("Enter stack number (1, 2, or 3): ");
            scanf("%d", &stackNum);
            value = pop(stackNum);
            if (value != -1)
                printf("Popped: %c\n", value);
            break;

        case 3:
            printf("Enter stack number (1, 2, or 3): ");
            scanf("%d", &stackNum);
            if (isEmpty(stackNum))
                printf("Stack %d is Empty\n", stackNum);
            else
                printf("Stack %d is Not Empty\n", stackNum);
            break;

        case 4:
            printf("Enter stack number (1, 2, or 3): ");
            scanf("%d", &stackNum);
            display(stackNum);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}
