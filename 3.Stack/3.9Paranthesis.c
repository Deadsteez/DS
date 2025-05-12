#include <stdio.h>
#include <stdlib.h>

// Stack Node
struct stack {
    char data;
    struct stack *next;
};

struct stack* top = NULL;

// ------------- Stack Functions -------------

void push(char a) {
    struct stack* p = (struct stack*) malloc(sizeof(struct stack));
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

// ------------- Parenthesis Validity Check -------------

int isValidParenthesis(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmptyStack()) {
                return 0;
            }

            char topChar = Top();
            if ((ch == ')' && topChar == '(') ||
                (ch == '}' && topChar == '{') ||
                (ch == ']' && topChar == '[')) {
                pop();
            }
            else {
                return 0;
            }
        }
    }

    return isEmptyStack(); // Stack should be empty at the end
}

// ------------- Main Function -------------

int main() {
    char str[100];

    printf("Enter a string of parentheses: ");
    gets(str);

    if (isValidParenthesis(str)) {
        printf("The string is VALID.\n");
    }
    else {
        printf("The string is INVALID.\n");
    }

    return 0;
}
