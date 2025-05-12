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
    struct stack* s = NULL;
    push(root);
    while (!isEmpty()) {
        root = pop();
        struct node* temp = root->left;
        root->left = root->right;
        root->right = temp;
        if (root->left)
            push(root->left);
        if (root->right)
            push(root->right);
    }
}

int countNodes(struct node* root) {
    if (root == NULL) return 0;
    int count = 0;
    struct stack* s = NULL;
    push(root);
    while (!isEmpty()) {
        root = pop();
        count++;
        if (root->right) push(root->right);
        if (root->left) push(root->left);
    }
    return count;
}

int countLeafNodes(struct node* root) {
    if (root == NULL) return 0;
    int count = 0;
    struct stack* s = NULL;
    push(root);
    while (!isEmpty()) {
        root = pop();
        if (root->left == NULL && root->right == NULL)
            count++;
        if (root->right) push(root->right);
        if (root->left) push(root->left);
    }
    return count;
}

int height(struct node* root) {
    if (root == NULL) return 0;
    int maxHeight = 0;
    struct node* queue[100];
    int levelCount, front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        levelCount = rear - front;
        maxHeight++;
        while (levelCount--) {
            root = queue[front++];
            if (root->left)
                queue[rear++] = root->left;
            if (root->right)
                queue[rear++] = root->right;
        }
    }
    return maxHeight;
}

int findMaximum(struct node* root) {
    if (root == NULL) return -1;
    int max = root->data;
    struct stack* s = NULL;
    push(root);
    while (!isEmpty()) {
        root = pop();
        if (root->data > max)
            max = root->data;
        if (root->right) push(root->right);
        if (root->left) push(root->left);
    }
    return max;
}


struct node* insert(struct node* root, int key) {
    if (root == NULL)
        return newNode(key);
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    return root;
}

struct node* findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return NULL;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node found
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        } else {
            struct node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}


int main() {
    struct node* root = newNode(30);
    root->left = newNode(15);
    root->right = newNode(50);
    root->left->left = newNode(5);
    root->left->right = newNode(20);
    root->right->left = newNode(40);
    root->right->right = newNode(60);

    int choice, value;
    while (1) {
        printf("\nBinary Tree Operations:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Levelwise Display\n");
        printf("7. Count Total Nodes\n");
        printf("8. Count Leaf Nodes\n");
        printf("9. Display Height\n");
        printf("10. Mirror Image\n");
        printf("11. Find Maximum Value\n");
        printf("12. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Node inserted.\n");
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Node deleted (if it existed).\n");
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
                printf("Maximum value in the tree = %d\n", findMaximum(root));
                break;
            case 12:
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
