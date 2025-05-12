#include <stdio.h>
#define SIZE 100

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;

// ---------------- Stack Operations ----------------

int isFull(int stackNum) {
    if (stackNum == 1)
        return top1 == SIZE - 1;
    else if (stackNum == 2)
        return top2 == SIZE - 1;
    else
        return 0;
}

int isEmpty(int stackNum) {
    if (stackNum == 1)
        return top1 == -1;
    else if (stackNum == 2)
        return top2 == -1;
    else
        return 1;
}

void push(int stackNum, int value) {
    if (isFull(stackNum)) {
        printf("Stack %d Overflow! Cannot push %d\n", stackNum, value);
        return;
    }

    if (stackNum == 1)
        stack1[++top1] = value;
    else if (stackNum == 2)
        stack2[++top2] = value;
    else
        printf("Invalid stack number\n");
}

int pop(int stackNum) {
    if (isEmpty(stackNum)) {
        printf("Stack %d Underflow!\n", stackNum);
        return -1;
    }

    if (stackNum == 1)
        return stack1[top1--];
    else if (stackNum == 2)
        return stack2[top2--];
    else {
        printf("Invalid stack number\n");
        return -1;
    }
}

void display(int stackNum) {
    if (isEmpty(stackNum)) {
        printf("Stack %d is empty\n", stackNum);
        return;
    }

    printf("Stack %d elements: ", stackNum);
    if (stackNum == 1) {
        for (int i = 0; i <= top1; i++)
            printf("%d ", stack1[i]);
    } else if (stackNum == 2) {
        for (int i = 0; i <= top2; i++)
            printf("%d ", stack2[i]);
    }
    printf("\n");
}

// ---------------- Menu-Driven Main ----------------

int main() {
    int choice, stackNum, value;

    do {
        printf("\n--- Two Stack Operations Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Check Stack Full\n");
        printf("4. Check Stack Empty\n");
        printf("5. Display Stack\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter stack number (1 or 2): ");
            scanf("%d", &stackNum);
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(stackNum, value);
            break;

        case 2:
            printf("Enter stack number (1 or 2): ");
            scanf("%d", &stackNum);
            value = pop(stackNum);
            if (value != -1)
                printf("Popped: %d\n", value);
            break;

        case 3:
            printf("Enter stack number (1 or 2): ");
            scanf("%d", &stackNum);
            if (isFull(stackNum))
                printf("Stack %d is Full\n", stackNum);
            else
                printf("Stack %d is Not Full\n", stackNum);
            break;

        case 4:
            printf("Enter stack number (1 or 2): ");
            scanf("%d", &stackNum);
            if (isEmpty(stackNum))
                printf("Stack %d is Empty\n", stackNum);
            else
                printf("Stack %d is Not Empty\n", stackNum);
            break;

        case 5:
            printf("Enter stack number (1 or 2): ");
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
