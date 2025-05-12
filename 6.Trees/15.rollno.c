// Write a program, using trees, to assign the roll nos. to the students of
// your class as per their previous years result. i.e topper will be roll no. 1.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold student data
struct Student {
    char name[50];
    int marks;
    int roll;
};

// BST node
struct Node {
    struct Student data;
    struct Node *left, *right;
};

// Create a new BST node
struct Node* newNode(const char* name, int marks) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node->data.name, name);
    node->data.marks = marks;
    node->data.roll = 0;
    node->left = node->right = NULL;
    return node;
}

// Insert student into BST (key = marks)
struct Node* insertNode(struct Node* root, const char* name, int marks) {
    if (root == NULL) {
        return newNode(name, marks);
    }
    if (marks < root->data.marks) {
        root->left = insertNode(root->left, name, marks);
    } else {
        root->right = insertNode(root->right, name, marks);
    }
    return root;
}

// Assign roll numbers by reverse inorder (highest marks first)
void assignRollNumbers(struct Node* root, int* currentRoll) {
    if (root == NULL)
        return;
    // Visit right subtree first (higher marks)
    assignRollNumbers(root->right, currentRoll);
    // Assign roll number
    root->data.roll = (*currentRoll)++;
    // Then left subtree
    assignRollNumbers(root->left, currentRoll);
}

// Print assigned roll numbers in descending marks order
void printRollAssignments(struct Node* root) {
    if (root == NULL)
        return;
    printRollAssignments(root->right);
    printf("Roll No. %d: %s (Marks: %d)\n", root->data.roll, root->data.name, root->data.marks);
    printRollAssignments(root->left);
}

// Free BST
void freeTree(struct Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct Node* root = NULL;
    char name[50];
    int marks;

    for (int i = 0; i < n; i++) {
        printf("\nStudent %d Name: ", i + 1);
        scanf("%49s", name);
        printf("%s's Marks: ", name);
        scanf("%d", &marks);
        root = insertNode(root, name, marks);
    }

    int currentRoll = 1;
    assignRollNumbers(root, &currentRoll);

    printf("\nAssigned Roll Numbers:\n");
    printRollAssignments(root);

    freeTree(root);
    return 0;
}