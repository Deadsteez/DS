#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack for characters
struct stack {
    char data;
    struct stack *next;
};

struct stack* top = NULL;

// ---------------- Stack Functions ----------------

void push(char a) {
    struct stack *p = (struct stack*) malloc(sizeof(struct stack));
    p->data = a;
    p->next = top;
    top = p;
}

char pop() {
    if (top) {
        struct stack* temp = top;
        char ch = temp->data;
        top = top->next;
        free(temp);
        return ch;
    }
    return '\0';
}

char Top() {
    return top ? top->data : '\0';
}

int isEmptyStack() {
    return top == NULL;
}

// ---------------- Utility Functions ----------------

int isOperand(char ch) {
    return isalnum(ch); // Check if alphabet or number
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^':
        case '%': return 3;
        default: return 0;
    }
}

// ---------------- Infix to Postfix ----------------

void InftoPost(char infix[], char postfix[]) {
    int i, j = 0;
    char ch;

    for (i = 0; (ch = infix[i]) != '\0'; i++) {
        if (isOperand(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (!isEmptyStack() && Top() != '(')
                postfix[j++] = pop();
            pop(); // Remove '('
        } else {
            while (!isEmptyStack() && precedence(Top()) >= precedence(ch))
                postfix[j++] = pop();
            push(ch);
        }
    }
    while (!isEmptyStack())
        postfix[j++] = pop();

    postfix[j] = '\0'; // Null-terminate string
}

// ---------------- Infix to Prefix ----------------

void InftoPre(char infix[], char prefix[]) {
    char reversed[100];
    strcpy(reversed, infix);
    strrev(reversed); // Reverse the infix expression

    // Swap brackets
    for (int i = 0; reversed[i] != '\0'; i++) {
        if (reversed[i] == '(') reversed[i] = ')';
        else if (reversed[i] == ')') reversed[i] = '(';
    }

    while (!isEmptyStack()) pop(); // Clear stack

    // Get postfix of modified infix
    InftoPost(reversed, prefix);

    // Reverse postfix to get prefix
    strrev(prefix);
}

// ---------------- Main Function ----------------

int main() {
    char expr[100], postfix[100], prefix[100];

    printf("Enter Infix Expression: ");
    scanf("%s", expr);

    InftoPost(expr, postfix);
    printf("Postfix Expression: %s\n", postfix);

    InftoPre(expr, prefix);
    printf("Prefix Expression: %s\n", prefix);

    return 0;
}
