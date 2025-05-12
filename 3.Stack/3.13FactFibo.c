#include <stdio.h>
#include <stdlib.h>

// Stack structure to hold integers
struct stack {
    int data;
    struct stack *next;
};

// Global top pointer for stack
struct stack* Top = NULL;

// ---------------- Integer Stack Functions ----------------

/* Push an integer onto the stack */
void push(int data) {
    struct stack* p = (struct stack*)malloc(sizeof(struct stack));
    p->data = data;
    p->next = Top;
    Top = p;
}

/* Pop an integer from the stack */
int pop() {
    if (Top == NULL) return 0;
    struct stack* p = Top;
    int x = p->data;
    Top = Top->next;
    free(p);
    return x;
}

/* Check if the stack is empty */
int isEmptyStack() {
    return Top == NULL;
}

// ---------------- Factorial Using Stack ----------------

void factorialUsingStack(int num) {
    if (num < 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return;
    }

    int result = 1;

    // Push numbers from num down to 1
    for (int i = num; i >= 1; i--) {
        push(i);
    }

    // Multiply them one by one
    while (!isEmptyStack()) {
        result *= pop();
    }

    printf("Factorial of %d is: %d\n", num, result);
}

// ---------------- Fibonacci Using Stack ----------------

void fibonacciUsingStack(int n) {
    if (n <= 0) {
        printf("Invalid input.\n");
        return;
    }

    // First term
    printf("Fibonacci Series: ");
    push(0);
    printf("0 ");

    if (n > 1) {
        push(1);
        printf("1 ");
    }

    for (int i = 2; i < n; i++) {
        int a = Top->data;
        int b = Top->next->data;
        int next = a + b;
        push(next);
        printf("%d ", next);
    }

    printf("\n");
}

// ---------------- Main Function ----------------

int main() {
    int choice, num;

    do {
        printf("\nStack-Based Operations Menu:\n");
        printf("1. Factorial of a number\n");
        printf("2. Fibonacci series\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter number to find factorial: ");
            scanf("%d", &num);
            factorialUsingStack(num);
            break;

        case 2:
            printf("Enter number of terms for Fibonacci series: ");
            scanf("%d", &num);
            fibonacciUsingStack(num);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
