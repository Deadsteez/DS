#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;   // To store a single digit
    struct Node* next;
};

// Function to create a number (linked list of digits)
struct Node* createNumber() {
    struct Node *head = NULL, *p, *q;
    int n, digit;
    printf("Enter the number of digits: ");
    scanf("%d", &n);

    if (n > 10) {
        printf("Maximum number of digits is 10.\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        p = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter digit %d: ", i + 1);
        scanf("%d", &digit);
        
        p->data = digit;
        p->next = NULL;

        if (head == NULL) {
            head = p;
        } else {
            q = head;
            while (q->next != NULL) {
                q = q->next;
            }
            q->next = p;
        }
    }
    return head;
}

// Function to display the number represented by the linked list
void display(struct Node* head) {
    struct Node* q = head;
    while (q != NULL) {
        printf("%d", q->data);
        q = q->next;
    }
    printf("\n");
}

// Function to add two numbers represented by linked lists
struct Node* add(struct Node* num1, struct Node* num2) {
    struct Node *result = NULL, *temp, *prev = NULL;
    int carry = 0, sum;
    
    while (num1 != NULL || num2 != NULL || carry) {
        sum = carry;
        
        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }
        
        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = sum;
        temp->next = NULL;

        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;
    }
    return result;
}

// Function to subtract two numbers represented by linked lists (assuming num1 >= num2)
struct Node* subtract(struct Node* num1, struct Node* num2) {
    struct Node *result = NULL, *temp, *prev = NULL;
    int borrow = 0, diff;

    while (num1 != NULL) {
        diff = num1->data - (num2 != NULL ? num2->data : 0) - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = diff;
        temp->next = NULL;

        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;

        num1 = num1->next;
        if (num2 != NULL) {
            num2 = num2->next;
        }
    }
    return result;
}

int main() {
    struct Node *num1, *num2, *result;
    
    // Input two numbers
    printf("Create Number 1:\n");
    num1 = createNumber();

    printf("Create Number 2:\n");
    num2 = createNumber();

    // Display the numbers
    printf("\nNumber 1: ");
    display(num1);

    printf("Number 2: ");
    display(num2);

    // Perform addition
    result = add(num1, num2);
    printf("\nSum: ");
    display(result);

    // Perform subtraction (num1 >= num2 assumed)
    result = subtract(num1, num2);
    printf("\nDifference: ");
    display(result);

    return 0;
}
