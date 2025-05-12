#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing product data
struct Product {
    int code;
    char name[50];
    float price;
    int stock;
    char date_received[11]; // Format: YYYY-MM-DD
    char expiration_date[11]; // Format: YYYY-MM-DD
    struct Product* left;
    struct Product* right;
};

// Function to create a new product node
struct Product* newProduct(int code, const char* name, float price, int stock, const char* date_received, const char* expiration_date) {
    struct Product* new_node = (struct Product*)malloc(sizeof(struct Product));
    new_node->code = code;
    strcpy(new_node->name, name);
    new_node->price = price;
    new_node->stock = stock;
    strcpy(new_node->date_received, date_received);
    strcpy(new_node->expiration_date, expiration_date);
    new_node->left = new_node->right = NULL;
    return new_node;
}

// Insert a new product into the BST
struct Product* insertProduct(struct Product* root, int code, const char* name, float price, int stock, const char* date_received, const char* expiration_date) {
    if (root == NULL) {
        return newProduct(code, name, price, stock, date_received, expiration_date);
    }

    if (code < root->code) {
        root->left = insertProduct(root->left, code, name, price, stock, date_received, expiration_date);
    } else if (code > root->code) {
        root->right = insertProduct(root->right, code, name, price, stock, date_received, expiration_date);
    }

    return root;
}

// Find a product by its code
struct Product* findProduct(struct Product* root, int code) {
    if (root == NULL || root->code == code) {
        return root;
    }

    if (code < root->code) {
        return findProduct(root->left, code);
    } else {
        return findProduct(root->right, code);
    }
}

// Update a product's details
void updateProduct(struct Product* product, const char* name, float price, int stock, const char* date_received, const char* expiration_date) {
    if (product != NULL) {
        strcpy(product->name, name);
        product->price = price;
        product->stock = stock;
        strcpy(product->date_received, date_received);
        strcpy(product->expiration_date, expiration_date);
    }
}

// Inorder traversal (lexicographic order of names)
void inorder(struct Product* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Code: %d, Name: %s, Price: %.2f, Stock: %d, Date Received: %s, Expiration Date: %s\n", 
                root->code, root->name, root->price, root->stock, root->date_received, root->expiration_date);
        inorder(root->right);
    }
}

// Preorder traversal (for expired items)
void preorderExpired(struct Product* root) {
    if (root != NULL) {
        // Check expiration date (simple comparison for this example)
        int exp_year, exp_month, exp_day;
        sscanf(root->expiration_date, "%d-%d-%d", &exp_year, &exp_month, &exp_day);
        if (exp_year < 2025 || (exp_year == 2025 && exp_month < 5)) {
            printf("Expired - Code: %d, Name: %s, Expiration Date: %s\n", root->code, root->name, root->expiration_date);
        }
        preorderExpired(root->left);
        preorderExpired(root->right);
    }
}

// Delete a product by code
struct Product* deleteProduct(struct Product* root, int code) {
    if (root == NULL) {
        return root;
    }

    if (code < root->code) {
        root->left = deleteProduct(root->left, code);
    } else if (code > root->code) {
        root->right = deleteProduct(root->right, code);
    } else {
        if (root->left == NULL) {
            struct Product* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Product* temp = root->left;
            free(root);
            return temp;
        }

        struct Product* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        root->code = temp->code;
        root->right = deleteProduct(root->right, temp->code);
    }

    return root;
}

// Delete all expired products
struct Product* deleteExpiredProducts(struct Product* root) {
    if (root == NULL) return NULL;

    root->left = deleteExpiredProducts(root->left);
    root->right = deleteExpiredProducts(root->right);

    int exp_year, exp_month, exp_day;
    sscanf(root->expiration_date, "%d-%d-%d", &exp_year, &exp_month, &exp_day);

    if (exp_year < 2025 || (exp_year == 2025 && exp_month < 5)) {
        root = deleteProduct(root, root->code);
    }

    return root;
}

// Main function to demonstrate the operations
int main() {
    struct Product* root = NULL;
    int choice, code, stock;
    char name[50], date_received[11], expiration_date[11];
    float price;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Product\n");
        printf("2. Find and Update Product\n");
        printf("3. List Valid Products (Lexicographic Order)\n");
        printf("4. List Expired Products (Prefix Order)\n");
        printf("5. Delete Product by Code\n");
        printf("6. Delete All Expired Products\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Product Code: ");
                scanf("%d", &code);
                printf("Enter Product Name: ");
                scanf("%s", name);
                printf("Enter Price: ");
                scanf("%f", &price);
                printf("Enter Stock: ");
                scanf("%d", &stock);
                printf("Enter Date Received (YYYY-MM-DD): ");
                scanf("%s", date_received);
                printf("Enter Expiration Date (YYYY-MM-DD): ");
                scanf("%s", expiration_date);

                root = insertProduct(root, code, name, price, stock, date_received, expiration_date);
                break;

            case 2:
                printf("Enter Product Code to Find: ");
                scanf("%d", &code);
                struct Product* product = findProduct(root, code);
                if (product != NULL) {
                    printf("Product Found: Code: %d, Name: %s\n", product->code, product->name);
                    printf("Enter New Name: ");
                    scanf("%s", name);
                    printf("Enter New Price: ");
                    scanf("%f", &price);
                    printf("Enter New Stock: ");
                    scanf("%d", &stock);
                    printf("Enter New Date Received (YYYY-MM-DD): ");
                    scanf("%s", date_received);
                    printf("Enter New Expiration Date (YYYY-MM-DD): ");
                    scanf("%s", expiration_date);
                    updateProduct(product, name, price, stock, date_received, expiration_date);
                    printf("Product Updated Successfully.\n");
                } else {
                    printf("Product not found.\n");
                }
                break;

            case 3:
                printf("Listing Valid Products (Lexicographic Order):\n");
                inorder(root);
                break;

            case 4:
                printf("Listing Expired Products (Prefix Order):\n");
                preorderExpired(root);
                break;

            case 5:
                printf("Enter Product Code to Delete: ");
                scanf("%d", &code);
                root = deleteProduct(root, code);
                printf("Product Deleted.\n");
                break;

            case 6:
                root = deleteExpiredProducts(root);
                printf("All Expired Products Deleted.\n");
                break;

            case 7:
                exit(0);

            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
