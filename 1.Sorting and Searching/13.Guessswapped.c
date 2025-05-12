// Assume that an array A with n elements was sorted in an ascending
// order, but two of its elements swapped their positions by a mistake while
// maintaining the array. Write a code to identify the swapped pair of
// elements and their positions in the asymptotically best possible time.
// [Assume that all given elements are distinct integers.]

#include <stdio.h>

// Function to find and print the swapped elements
void findSwappedElements(int arr[], int n) {
    int x = -1, y = -1; // To store the two swapped elements
    int i;

    for (i = 0; i < n-1; i++) {
        if (arr[i] > arr[i+1]) {
            if (x == -1) {
                x = i;
            } else {
                y = i+1;
            }
        }
    }

    if (y == -1) {
        y = x + 1;
    }

    printf("Swapped elements are: %d and %d\n", arr[x], arr[y]);
    printf("Their positions are: %d and %d\n", x, y);
}

int main() {
    int arr[] = {1, 2, 6, 4, 5, 3, 7, 8};  // Example
    int n = sizeof(arr)/sizeof(arr[0]);

    findSwappedElements(arr, n);

    return 0;
}
