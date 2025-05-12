#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack structure to hold characters
struct stack {
    char data;
    struct stack *next;
};

// Global top pointer for stack
struct stack* Top = NULL;

// ---------------- Character Stack Functions ----------------

/* Function to push a character onto the stack */
void push(char data) {
    struct stack* p = (struct stack*)malloc(sizeof(struct stack));
    p->data = data;
    p->next = Top;
    Top = p;
}

/* Function to pop a character from the stack */
char pop() {
    if (Top == NULL) return '\0'; // Return null character if stack is empty
    struct stack* p = Top;
    char x = p->data;
    Top = Top->next;
    free(p);
    return x;
}

/* Function to check if the stack is empty */
int isEmptyStack() {
    return Top == NULL;
}

// ---------------- Utility Functions ----------------

/* Function to check if the string is a palindrome */
void isPalindrome(char* str) {
    int len = strlen(str);
    int i;

    // Push all characters into the stack
    for (i = 0; i < len; i++) {
        push(str[i]);
    }

    // Pop characters and compare with the original string
    for (i = 0; i < len; i++) {
        if (str[i] != pop()) {
            printf("String is not a palindrome\n");
            return;
        }
    }
    printf("String is a palindrome\n");
}

/* Function to reverse a string using the stack */
void reverseString(char* str) {
    int len = strlen(str);
    int i;

    // Push all characters of the string into the stack
    for (i = 0; i < len; i++) {
        push(str[i]);
    }

    // Pop characters and construct the reversed string
    printf("Reversed String: ");
    for (i = 0; i < len; i++) {
        printf("%c", pop());
    }
    printf("\n");
}

// Function to concatenate two strings by reversing both and pushing onto stack
void concatenateStrings(char* str1, char* str2) {
    // Reverse str2 and push onto stack
    for (int i = strlen(str2) - 1; i >= 0; i--) {
        push(str2[i]);
    }

    // Reverse str1 and push onto stack
    for (int i = strlen(str1) - 1; i >= 0; i--) {
        push(str1[i]);
    }

    // Pop characters from stack and print them in concatenated order
    printf("Concatenated String: ");
    while (!isEmptyStack()) {
        printf("%c", pop());
    }
    printf("\n");
}

/* Function to compare two strings */
void compareStrings(char* str1, char* str2) {
    int i = 0;
    
    // Compare each character of the two strings
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            printf("Strings are not equal\n");
            return;
        }
        i++;
    }

    // If one string ends and the other doesn't
    if (str1[i] != str2[i]) {
        printf("Strings are not equal\n");
        return;
    }

    printf("Strings are equal\n");
}

// ---------------- Parenthesis Validity Function ----------------

/* Function to check if parentheses are balanced */
int areParenthesesValid(char* expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        
        if (ch == '(') {
            push(ch);  // Push opening parentheses onto the stack
        } 
        else if (ch == ')') {
            // If there is no matching opening parentheses, return invalid
            if (pop() == '\0') {
                return 0;  // Invalid
            }
        }
    }
    
    // If the stack is empty, all parentheses are matched
    return isEmptyStack();
}

// ---------------- Menu-Driven Main Function ----------------

int main() {
    char str1[100], str2[100];
    int choice;

    do {
        printf("\nString Operations Menu:\n");
        printf("1. Palindrome Check\n");
        printf("2. Reverse String\n");
        printf("3. Concatenate Strings\n");
        printf("4. Compare Strings\n");
        printf("5. Parentheses Validity Check\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter a string: ");
            scanf("%s", str1);
            isPalindrome(str1); // Check if string is palindrome
            break;

        case 2:
            printf("Enter a string: ");
            scanf("%s", str1);
            reverseString(str1); // Reverse the string
            break;

        case 3:
            printf("Enter the first string: ");
            scanf("%s", str1);
            printf("Enter the second string: ");
            scanf("%s", str2);
            concatenateStrings(str1, str2); // Concatenate the strings
            break;

        case 4:
            printf("Enter the first string: ");
            scanf("%s", str1);
            printf("Enter the second string: ");
            scanf("%s", str2);
            compareStrings(str1, str2); // Compare the two strings
            break;

        case 5:
            printf("Enter a string of parentheses: ");
            scanf("%s", str1);
            if (areParenthesesValid(str1)) {
                printf("Parentheses are valid\n");
            } else {
                printf("Parentheses are not valid\n");
            }
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}
