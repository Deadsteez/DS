// Write a program to efficiently search a perticular employee record by
// using Tree data structure. Also sort the data on emp-id in ascending
// order.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int emp_id;
    char name[50];
    float salary;
    struct Employee* left;
    struct Employee* right;
};

// Create a new employee node
struct Employee* createEmployee(int id, const char* name, float salary) {
    struct Employee* newEmp = (struct Employee*)malloc(sizeof(struct Employee));
    newEmp->emp_id = id;
    strcpy(newEmp->name, name);
    newEmp->salary = salary;
    newEmp->left = newEmp->right = NULL;
    return newEmp;
}

// Insert an employee into the BST
struct Employee* insertEmployee(struct Employee* root, int id, const char* name, float salary) {
    if (root == NULL)
        return createEmployee(id, name, salary);
    
    if (id < root->emp_id)
        root->left = insertEmployee(root->left, id, name, salary);
    else if (id > root->emp_id)
        root->right = insertEmployee(root->right, id, name, salary);
    else
        printf("Employee ID %d already exists! Duplicate not allowed.\n", id);

    return root;
}

// Search an employee by emp_id
struct Employee* searchEmployee(struct Employee* root, int id) {
    if (root == NULL || root->emp_id == id)
        return root;
    
    if (id < root->emp_id)
        return searchEmployee(root->left, id);
    else
        return searchEmployee(root->right, id);
}

// Inorder traversal to display employees sorted by emp_id
void inorderTraversal(struct Employee* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("ID: %d, Name: %s, Salary: %.2f\n", root->emp_id, root->name, root->salary);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Employee* root = NULL;
    int choice, id;
    char name[50];
    float salary;
    struct Employee* result;

    while (1) {
        printf("\nEmployee Management:\n");
        printf("1. Insert Employee\n");
        printf("2. Search Employee\n");
        printf("3. Display Employees (Sorted by ID)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Salary: ");
                scanf("%f", &salary);
                root = insertEmployee(root, id, name, salary);
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                result = searchEmployee(root, id);
                if (result != NULL)
                    printf("Found -> ID: %d, Name: %s, Salary: %.2f\n", result->emp_id, result->name, result->salary);
                else
                    printf("Employee with ID %d not found!\n", id);
                break;
            case 3:
                printf("Employees in ascending order of ID:\n");
                inorderTraversal(root);
                break;
            case 4:
                printf("Exiting Program...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
