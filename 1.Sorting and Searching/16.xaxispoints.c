// Given a set of points Pi , 1 ? i ? N (? 2) on the x-axis, find Pi and P j
// such that |Pi ? P j | is minimum. e.g. P1 | P2 | P3 | P4 | P5 | P6 {P4 , P6}
// is the closest pair

#include <stdio.h>
#include <stdlib.h>

// Manual Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to find closest pair
void findClosestPair(int arr[], int n) {
    if (n < 2) {
        printf("Need at least two points.\n");
        return;
    }

    bubbleSort(arr, n);

    int minDiff = abs(arr[1] - arr[0]);
    int idx1 = 0, idx2 = 1;

    for (int i = 1; i < n - 1; i++) {
        int diff = abs(arr[i + 1] - arr[i]);
        if (diff < minDiff) {
            minDiff = diff;
            idx1 = i;
            idx2 = i + 1;
        }
    }

    printf("Closest points are: %d and %d\n", arr[idx1], arr[idx2]);
    printf("Minimum distance is: %d\n", minDiff);
}

int main() {
    int arr[100]; // Fixed-size array, can hold up to 100 elements
    int n;

    printf("How many elements? ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findClosestPair(arr, n);

    return 0;
}
