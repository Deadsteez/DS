#include <stdio.h>

#define MAX_STACK_SIZE 5  // Define the maximum size for a stack

// Global variables for multiple stacks
int stacks[10][MAX_STACK_SIZE]; // A 2D array to represent 10 stacks (change 10 as needed)
int stack_tops[10]; // Array to track the top index for each stack

// Function to initialize the stacks
void initStacks(int m) {
    for (int i = 0; i < m; i++) {
        stack_tops[i] = -1; // Initialize each stack to be empty
    }
}

void push(int value, int stack_num) {
    if (stack_tops[stack_num] < MAX_STACK_SIZE - 1) {
        stacks[stack_num][++stack_tops[stack_num]] = value;
        printf("Pushed %d into Stack %d\n", value, stack_num + 1);  // Print after each push
    } else {
        printf("Stack %d is full! Moving to the next stack...\n", stack_num + 1);
        // Move to the next stack if current one is full
        if (stack_num + 1 < 10) {
            push(value, stack_num + 1);  // Call push recursively for next stack
        } else {
            printf("Out of space! No more stacks available.\n");
        }
    }
}

int pop(int stack_num) {
    if (stack_tops[stack_num] == -1) {
        printf("Stack %d is empty!\n", stack_num + 1);
        return -1; 
    } else {
        int value = stacks[stack_num][stack_tops[stack_num]--];
        printf("Popped %d from Stack %d\n", value, stack_num + 1);
        return value;
    }
}

// Display all stacks
void displayStacks(int m) {
    printf("\nCurrent Stack Contents:\n");
    for (int i = 0; i < m; i++) {
        printf("Stack %d: ", i + 1);
        if (stack_tops[i] == -1) {
            printf("Empty\n");
        } else {
            for (int j = 0; j <= stack_tops[i]; j++) {
                printf("%d ", stacks[i][j]);
            }
            printf("\n");
        }
    }
}

int main() {
    int n, m;

    printf("Enter the number of elements (n): ");
    scanf("%d", &n);

    printf("Enter the number of subarrays (m): ");
    scanf("%d", &m);

    initStacks(m);

    int value;
    int current_stack = 0;
    int choice;

    for (int i = 0; i < n; i++) {
        printf("\nChoose an operation:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display Stacks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value to push: ");
            scanf("%d", &value);

            push(value, current_stack);

            if (stack_tops[current_stack] == MAX_STACK_SIZE - 1) {
                current_stack++;
                if (current_stack >= m) {
                    printf("Out of space! No more stacks available.\n");
                    break;
                }
            }
        } else if (choice == 2) {

            printf("Enter stack number to pop from (1 to %d): ", m);
            int stack_num;
            scanf("%d", &stack_num);

            if (stack_num < 1 || stack_num > m) {
                printf("Invalid stack number. Try again.\n");
            } else {
                pop(stack_num - 1);
            }
        } else if (choice == 3) {
            displayStacks(m);
        } else if (choice == 4) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
