#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack structure to hold strings (name parts)
struct stack {
    char data[100];
    struct stack* next;
};

// Global top pointer for stack
struct stack* Top = NULL;

// ---------------- Stack Functions ----------------

/* Push a string onto the stack */
void push(char* data) {
    struct stack* p = (struct stack*)malloc(sizeof(struct stack));
    strcpy(p->data, data);
    p->next = Top;
    Top = p;
}

/* Pop a string from the stack */
char* pop() {
    if (Top == NULL) return NULL;
    struct stack* p = Top;
    char* x = (char*)malloc(100 * sizeof(char));
    strcpy(x, p->data);
    Top = Top->next;
    free(p);
    return x;
}

/* Check if the stack is empty */
int isEmptyStack() {
    return Top == NULL;
}

// ---------------- Function to Rearrange Name ----------------

void rearrangeName(char* firstName, char* middleName, char* surname) {
    // Push each part of the name onto the stack in reverse of the desired output order
    push(middleName); // Push middle name first (will be popped last)
    push(firstName);  // Push first name second (will be popped second)
    push(surname);    // Push surname last (will be popped first)

    // Pop and print the words in the desired order (Surname, First Name, Middle Name)
    printf("Rearranged Name (Surname, First Name, Middle Name): ");
    while (!isEmptyStack()) {
        char* namePart = pop();
        printf("%s ", namePart);
        free(namePart); // Free the memory allocated in pop()
    }
    printf("\n");
}

// ---------------- Main Function ----------------

int main() {
    char firstName[100], middleName[100], surname[100];
    
    // Accept the name parts as input
    printf("Enter your First Name: ");
    scanf("%s", firstName);
    
    printf("Enter your Middle Name: ");
    scanf("%s", middleName);
    
    printf("Enter your Surname: ");
    scanf("%s", surname);

    // Call the function to rearrange the name
    rearrangeName(firstName, middleName, surname);
    
    return 0;
}