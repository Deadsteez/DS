#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX];
int *top, *base, *limit;

int n, m, size;

void initializeStacks(int totalSize, int numStacks) {
    n = totalSize;
    m = numStacks;
    size = n / m;

    top = (int*)malloc(m * sizeof(int));
    base = (int*)malloc(m * sizeof(int));
    limit = (int*)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        base[i] = i * size;
        top[i] = base[i] - 1; // top starts before base
        limit[i] = (i == m - 1) ? n - 1 : base[i + 1] - 1; // allow last stack to extend to end
    }
}

int isFull(int stackNum) {
    if (top[stackNum] < limit[stackNum]) return 0;

    // Try to borrow space from next stack
    if (stackNum < m - 1 && top[stackNum + 1] < limit[stackNum + 1]) {
        limit[stackNum]++;
        base[stackNum + 1]++;
        return 0;
    }

    return 1;
}

int isEmpty(int stackNum) {
    return top[stackNum] < base[stackNum];
}

void push(int stackNum, int val) {
    if (isFull(stackNum)) {
        printf("Stack %d is full and cannot borrow space.\n", stackNum);
        return;
    }

    top[stackNum]++;
    arr[top[stackNum]] = val;
}

int pop(int stackNum) {
    if (isEmpty(stackNum)) {
        printf("Stack %d is empty.\n", stackNum);
        return -1;
    }

    int val = arr[top[stackNum]];
    top[stackNum]--;
    return val;
}

void display(int stackNum) {
    if (isEmpty(stackNum)) {
        printf("Stack %d is empty.\n", stackNum);
        return;
    }

    printf("Stack %d: ", stackNum);
    for (int i = base[stackNum]; i <= top[stackNum]; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int totalSize, numStacks;
    printf("Enter total array size: ");
    scanf("%d", &totalSize);

    do {
        printf("Enter number of stacks (between 3 and %d): ", totalSize - 1);
        scanf("%d", &numStacks);
    } while (numStacks <= 2 || numStacks >= totalSize);

    initializeStacks(totalSize, numStacks);

    int choice, stackNum, val;
    do {
        printf("\n1. Push\n2. Pop\n3. Display Stack\n0. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter stack number (0 to %d): ", numStacks - 1);
            scanf("%d", &stackNum);
            printf("Enter value to push: ");
            scanf("%d", &val);
            push(stackNum, val);
            break;

        case 2:
            printf("Enter stack number (0 to %d): ", numStacks - 1);
            scanf("%d", &stackNum);
            val = pop(stackNum);
            if (val != -1) printf("Popped: %d\n", val);
            break;

        case 3:
            for (int i = 0; i < numStacks; i++) {
                display(i);
            }
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    free(top);
    free(base);
    free(limit);
    return 0;
}
