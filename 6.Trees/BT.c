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
    struct node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

int countNodes(struct node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeafNodes(struct node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int height(struct node* root) {
    if (root == NULL) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main() {
    struct node* root = newNode(30);
    root->left = newNode(15);
    root->right = newNode(50);
    root->left->left = newNode(5);
    root->left->right = newNode(20);
    root->right->left = newNode(40);
    root->right->right = newNode(60);

    int choice;
    while (1) {
        printf("\nBinary Tree Operations:\n");
        printf("1. Inorder Traversal\n");
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Levelwise Display\n");
        printf("5. Count Total Nodes\n");
        printf("6. Count Leaf Nodes\n");
        printf("7. Display Height\n");
        printf("8. Mirror Image\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inorder Traversal: ");
                inorder(root);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(root);
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorder(root);
                break;
            case 4:
                printf("Levelwise Display: ");
                levelOrder(root);
                break;
            case 5:
                printf("Total number of nodes = %d\n", countNodes(root));
                break;
            case 6:
                printf("Number of leaf nodes = %d\n", countLeafNodes(root));
                break;
            case 7:
                printf("Height of the tree = %d\n", height(root));
                break;
            case 8:
                mirror(root);
                printf("Tree mirrored successfully!\n");
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
