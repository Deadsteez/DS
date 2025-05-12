#include <stdio.h>
#include <stdlib.h>

// Stack structure
struct Stack {
    int data;
    struct Stack* next;
};

struct Stack* Top = NULL;

// Push operation
void push(int val) {
    struct Stack* temp = (struct Stack*)malloc(sizeof(struct Stack));
    temp->data = val;
    temp->next = Top;
    Top = temp;
}

// Pop operation
int pop() {
    if (Top == NULL) return -1;
    struct Stack* temp = Top;
    int val = temp->data;
    Top = Top->next;
    free(temp);
    return val;
}

// Binary conversion using stack
void convertToBinary(int number) {
    while (number > 0) {
        push(number % 2);
        number /= 2;
    }
}

int main() {
    int room = 1;
    int decimal;

    // Forward journey through rooms 1 to 5
    while (room <= 5) {
        printf("Entered Room %d\n", room);
        if (room == 5) {
            printf("Found a box with a decimal number!\n");
            printf("Enter the decimal number: ");
            scanf("%d", &decimal);

            printf("Converting %d to binary...\n", decimal);
            convertToBinary(decimal);
        }
        room++;
    }

    // Reverse journey from 5 to 1 and printing binary
    room = 4; // Because we are already in Room 5
    printf("\nReturning back to Room 1...\n");
    printf("Binary code to unlock the treasure is: ");

    while (Top != NULL) {
        printf("%d", pop());
        room--;
    }

    printf("\nTreasure unlocked in Room 1!\n");

    return 0;
}

