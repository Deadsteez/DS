#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int hashTable[SIZE];

// Initialize table with -1 (empty)
void initialize() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
}

// Hash function: basic mod
int hashFunction(int key) {
    return key % SIZE;
}

// Second hash for double hashing
int secondHash(int key) {
    return 7 - (key % 7);
}

// Insert using Linear Probing
void linearProbing(int key) {
    int idx = hashFunction(key);
    int startIdx = idx;
    while (hashTable[idx] != -1) {
        idx = (idx + 1) % SIZE;
        if (idx == startIdx) {
            printf("Hash Table is full (Linear Probing)\n");
            return;
        }
    }
    hashTable[idx] = key;
}

// Insert using Quadratic Probing
void quadraticProbing(int key) {
    int idx = hashFunction(key);
    int i = 1;
    while (hashTable[idx] != -1) {
        idx = (idx + i * i) % SIZE;
        i++;
        if (i == SIZE) {
            printf("Hash Table is full (Quadratic Probing)\n");
            return;
        }
    }
    hashTable[idx] = key;
}

// Insert using Double Hashing
void doubleHashing(int key) {
    int idx = hashFunction(key);
    int step = secondHash(key);
    int startIdx = idx;
    while (hashTable[idx] != -1) {
        idx = (idx + step) % SIZE;
        if (idx == startIdx) {
            printf("Hash Table is full (Double Hashing)\n");
            return;
        }
    }
    hashTable[idx] = key;
}

// Display hash table
void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("[%d] -> %d\n", i, hashTable[i]);
    }
}

int main() {
    int choice, key;

    while (1) {
        printf("\n1. Linear Probing\n2. Quadratic Probing\n3. Double Hashing\n4. Display Table\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initialize();
                printf("Enter 5 keys to insert (Linear Probing):\n");
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &key);
                    linearProbing(key);
                }
                break;

            case 2:
                initialize();
                printf("Enter 5 keys to insert (Quadratic Probing):\n");
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &key);
                    quadraticProbing(key);
                }
                break;

            case 3:
                initialize();
                printf("Enter 5 keys to insert (Double Hashing):\n");
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &key);
                    doubleHashing(key);
                }
                break;

            case 4:
                display();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
