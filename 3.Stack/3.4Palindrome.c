#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack Node
struct stack {
    char data;
    struct stack *next;
};

struct stack* top = NULL;

// ------------ Stack Functions ------------

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

void clearStack() {
    while (top != NULL) {
        struct stack* temp = top;
        top = top->next;
        free(temp);
    }
}

int isEmptyStack() {
    return top == NULL;
}

// ------------ A. Palindrome ------------

void checkPalindrome(char str[]) {
    // Clear stack before use
    clearStack();
    
    int length = strlen(str);
    int i;
    
    // Push half characters onto stack
    for (i = 0; i < length / 2; i++) {
        push(str[i]);
    }
    
    // Skip middle character for odd-length strings
    if (length % 2 != 0) {
        i++;
    }
    
    // Compare second half with popped characters
    int flag = 1;
    while (i < length) {
        if (pop() != str[i]) {
            flag = 0;
            break;
        }
        i++;
    }
    
    if (flag)
        printf("String is a Palindrome.\n");
    else
        printf("String is NOT a Palindrome.\n");
}

// ------------ B. String Reverse ------------

void reverseString(char str[]) {
    // Clear stack before use
    clearStack();
    
    for (int i = 0; str[i] != '\0'; i++) {
        push(str[i]);
    }

    printf("Reversed String: ");
    while (!isEmptyStack()) {
        printf("%c", pop());
    }
    printf("\n");
}

// ------------ C. String Concatenation ------------

void concatenateAndReverse(char str1[], char str2[]) {
    // Clear stack before use
    clearStack();
    
    // Push second string first (to reverse order)
    for (int i = 0; str2[i] != '\0'; i++) {
        push(str2[i]);
    }
    
    // Then push first string
    for (int i = 0; str1[i] != '\0'; i++) {
        push(str1[i]);
    }
    
    printf("Concatenated and Reversed String : ");
    while (!isEmptyStack()) {
        printf("%c", pop());
    }
    printf("\n");
}

// ------------ D. String Compare ------------

void compareStrings(char str1[], char str2[]) {
    int i;
    for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) {
            printf("Strings are NOT equal.\n");
            return;
        }
    }

    if (str1[i] == '\0' && str2[i] == '\0')
        printf("Strings are EQUAL.\n");
    else
        printf("Strings are NOT equal.\n");
}

// ------------ Main Function ------------

int main() {
    char str1[100], str2[100];
    int choice;

    // Using fgets to get input safely
    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';  // Remove newline character

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';  // Remove newline character

    do {
        printf("Menu:\n");
        printf("1. Palindrome Check (First String)\n");
        printf("2. Reverse First String\n");
        printf("3. Concatenate First and Second String\n");
        printf("4. Compare Strings\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline left by scanf

        switch (choice) {
            case 1:
                checkPalindrome(str1);
                break;
            case 2:
                reverseString(str1);
                break;
            case 3:
                concatenateAndReverse(str1, str2);
                break;
            case 4:
                compareStrings(str1, str2);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 5);

    // Clean up any remaining stack nodes before exiting
    clearStack();
    return 0;
}