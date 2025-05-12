#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct Q {
    int data[SIZE];
    int F, R;
} Q;

int isFull(Q *q) {
    return q->R == SIZE - 1;
}

int isEmpty(Q *q) {
    return q->F == -1;
}

void EnQ(Q *q, int x) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->F == -1) {
        q->F = q->R = 0;
    } else {
        q->R++;
    }
    q->data[q->R] = x;
}

void resetQueue(Q *q) {
    q->F = q->R = -1;
}

void display(Q *q) {
    if (isEmpty(q)) {
        printf("None\n");
        return;
    }
    for (int i = q->F; i <= q->R; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() {
    Q student, staff, director;
    student.F = student.R = -1;
    staff.F = staff.R = -1;
    director.F = director.R = -1;

    int choice, id;

    while (1) {
        printf("\nLift Menu:\n");
        printf("1. Student enters\n");
        printf("2. Staff enters\n");
        printf("3. Director enters\n");
        printf("4. Show who is in the lift\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (!isEmpty(&staff) || !isEmpty(&director)) {
                    printf("Lift occupied by higher priority person. Student can't enter.\n");
                } else {
                    printf("Enter Student ID: ");
                    scanf("%d", &id);
                    EnQ(&student, id);
                    printf("Student entered the lift.\n");
                }
                break;
            case 2:
                if (!isEmpty(&director)) {
                    printf("Director in lift. Staff can't enter.\n");
                } else {
                    resetQueue(&student);
                    printf("Enter Staff ID: ");
                    scanf("%d", &id);
                    EnQ(&staff, id);
                    printf("Staff entered the lift. Students removed.\n");
                }
                break;
            case 3:
                resetQueue(&staff);
                resetQueue(&student);
                printf("Enter Director ID: ");
                scanf("%d", &id);
                EnQ(&director, id);
                printf("Director entered the lift. Everyone else removed.\n");
                break;
            case 4:
                printf("Directors: ");
                display(&director);
                printf("Staff: ");
                display(&staff);
                printf("Students: ");
                display(&student);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
