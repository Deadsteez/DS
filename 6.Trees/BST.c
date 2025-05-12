#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct stack {
    struct node* data;
    struct stack* next;
};

struct stack* top = NULL;

void push(struct node* a) {
    struct stack* p = (struct stack*)malloc(sizeof(struct stack));
    p->data = a;
    p->next = top;
    top = p;
}

struct node* pop() {
    if (top == NULL) {
        return NULL;
    }
    struct stack* temp = top;
    struct node* n = temp->data;
    top = top->next;
    free(temp);
    return n;
}

int isEmpty() {
    return top == NULL;
}

struct node* newNode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* bstinsert(struct node* root, int data) {
    struct node* temp = newNode(data);
    struct node* parent;
    struct node* p = root;

    if (root == NULL) {
        return temp;
    }

    while (p != NULL) {
        parent = p;
        if (data < p->data)
            p = p->left;
        else
            p = p->right;
    }

    if (data < parent->data)
        parent->left = temp;
    else
        parent->right = temp;

    return root;
}

void inorder(struct node* root) { // iterative
    while (root != NULL) {
        push(root);
        root = root->left;
    }
    while (!isEmpty()) {
        root = pop();
        printf("%d ", root->data);
        root = root->right;
        while (root != NULL) {
            push(root);
            root = root->left;
        }
    }
    printf("\n");
}

void preorder(struct node* root) {
    while (root != NULL) {
        push(root);
        printf("%d ", root->data);
        root = root->left;
    }
    while (!isEmpty()) {
        root = pop();
        root = root->right;
        while (root != NULL) {
            push(root);
            printf("%d ", root->data);
            root = root->left;
        }
    }
    printf("\n");
}

void postorder(struct node* root) { // Left Right Parent
    struct node* prev = NULL;

    while (root != NULL) {
        push(root);
        root = root->left;
    }

    while (!isEmpty()) {
        root = top->data;
        if (root->right == NULL || root->right == prev) {
            root = pop();
            printf("%d ", root->data);
            prev = root;
            root = NULL;
        } else {
            root = root->right;
            while (root != NULL) {
                push(root);
                root = root->left;
            }
        }
    }
    printf("\n");
}

void levelOrder(struct node* root) {
    if (root == NULL) return;
    struct node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct node* temp = queue[front++];
        printf("%d ", temp->data);
        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }
    printf("\n");
}

void mirror(struct node* root) {
    if (root == NULL) return;

    struct stack* s = NULL;
    push(root);

    while (!isEmpty()) {
        struct node* current = pop();

        struct node* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left) push(current->left);
        if (current->right) push(current->right);
    }
}


int countNodes(struct node* root) {
    int count = 0;
    if (root == NULL) return 0;

    push(root);
    while (!isEmpty()) {
        struct node* curr = pop();
        count++;
        if (curr->right) push(curr->right);
        if (curr->left) push(curr->left);
    }
    return count;
}


int countLeafNodes(struct node* root) {
    int count = 0;
    if (root == NULL) return 0;

    push(root);
    while (!isEmpty()) {
        struct node* curr = pop();
        if (curr->left == NULL && curr->right == NULL)
            count++;
        if (curr->right) push(curr->right);
        if (curr->left) push(curr->left);
    }
    return count;
}


int height(struct node* root) {
    if (root == NULL) return 0;

    struct node* queue[100];
    int front = 0, rear = 0;
    int height = 0;
    queue[rear++] = root;

    while (front < rear) {
        int nodeCount = rear - front;
        height++;

        while (nodeCount > 0) {
            struct node* temp = queue[front++];
            if (temp->left)
                queue[rear++] = temp->left;
            if (temp->right)
                queue[rear++] = temp->right;
            nodeCount--;
        }
    }
    return height;
}

struct node* findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// New function to find a value in the BST
struct node* find(struct node* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root != NULL) {
        if (value == root->data) {
            return root;  // Found the value
        } else if (value < root->data) {
            root = root->left;  // Search in left subtree
        } else {
            root = root->right;  // Search in right subtree
        }
    }
    
    return NULL;  // Value not found
}

// Helper function for show() to print the tree structure
void printLevel(struct node* root, int level, int space) {
    if (root == NULL) {
        return;
    }
    
    // Increase distance between levels
    space += 10;
    
    // Process right child first
    printLevel(root->right, level + 1, space);
    
    // Print current node
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    // Process left child
    printLevel(root->left, level + 1, space);
}

// New function to display the tree structure
void show(struct node* root) {
    if (root == NULL) {
        printf("Empty tree\n");
        return;
    }
    
    // Start with initial space 0
    printLevel(root, 0, 0);
    printf("\n");
}

int main() {
    struct node* root = NULL;
    int choice, val;
    struct node* result; // Declare variables at the top

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Levelwise Display\n");
        printf("7. Count Total Nodes\n");
        printf("8. Count Leaf Nodes\n");
        printf("9. Display Height\n");
        printf("10. Mirror Image\n");
        printf("11. Find Value\n");
        printf("12. Show Tree Structure\n");
        printf("13. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = bstinsert(root, val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                break;
            case 4:
                printf("Preorder Traversal: ");
                preorder(root);
                break;
            case 5:
                printf("Postorder Traversal: ");
                postorder(root);
                break;
            case 6:
                printf("Levelwise Display: ");
                levelOrder(root);
                break;
            case 7:
                printf("Total number of nodes = %d\n", countNodes(root));
                break;
            case 8:
                printf("Number of leaf nodes = %d\n", countLeafNodes(root));
                break;
            case 9:
                printf("Height of the tree = %d\n", height(root));
                break;
            case 10:
                mirror(root);
                printf("Tree mirrored successfully!\n");
                break;
            case 11:
                printf("Enter value to find: ");
                scanf("%d", &val);
                result = find(root, val);
                if (result != NULL) {
                    printf("Value %d found in the tree!\n", val);
                } else {
                    printf("Value %d not found in the tree.\n", val);
                }
                break;
            case 12:
                printf("Tree Structure:\n");
                show(root);
                break;
            case 13:
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}