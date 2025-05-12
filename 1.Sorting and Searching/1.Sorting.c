#include <stdio.h>
#include <string.h>

struct Student {
    char name[20];
    int roll;
    int marks;
};

int swap_count = 0;
//bubble
void bubbleSort(struct Student a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].roll > a[j + 1].roll) {
                struct Student temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swap_count++;
            }
        }
    }
}

//Quick
int Qpartition(struct Student a[], int left, int right) {
    struct Student pivot = a[left];
    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= right && a[i].roll <= pivot.roll)
            i++;
        while (j >= left && a[j].roll > pivot.roll)
            j--;
        if (i < j) {
            struct Student temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            swap_count++;
        }
    }
    struct Student temp = a[left];
    a[left] = a[j];
    a[j] = temp;
    swap_count++;
    return j;
}

void quickSort(struct Student a[], int left, int right) {
    if (left < right) {
        int j = Qpartition(a, left, right);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

//Merge
void merge(struct Student a[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    struct Student temp[right - left + 1];

    while (i <= mid && j <= right) {
        if (a[i].roll < a[j].roll)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
        swap_count++;
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= right)
        temp[k++] = a[j++];

    for (i = 0; i < k; i++)
        a[left + i] = temp[i];
}

void mergeSort(struct Student a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

//Heap
void heapify(struct Student a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left].roll > a[largest].roll)
        largest = left;
    if (right < n && a[right].roll > a[largest].roll)
        largest = right;
    if (largest != i) {
        struct Student temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        swap_count++;
        heapify(a, n, largest);
    }
}

void heapSort(struct Student a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        struct Student temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        swap_count++;
        heapify(a, i, 0);
    }
}


//-----------------------------------------------------------------------------//
void insertionSort(struct Student a[], int n) {
    for (int i = 1; i < n; i++) {
        struct Student key = a[i];
        int j;
        for (j = i - 1; j >= 0 && a[j].roll > key.roll; j--) {
            a[j + 1] = a[j];
            swap_count++;
        }
        a[j + 1] = key;
    }
}


void selectionSort(struct Student a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j].roll < a[minIdx].roll)
                minIdx = j;
        }
        if (minIdx != i) {
            struct Student temp = a[i];
            a[i] = a[minIdx];
            a[minIdx] = temp;
            swap_count++;
        }
    }
}



int main() {
    int n, choice;
    printf("Enter number of students: ");
    scanf("%d", &n);
    struct Student student[n];

    for (int i = 0; i < n; i++) {
        printf("Enter name, roll number and marks for student %d: ", i + 1);
        scanf("%s %d %d", student[i].name, &student[i].roll, &student[i].marks);
    }

    printf("\nEnter sorting method:\n");
    printf("1. Bubble Sort\n2. Quick Sort\n3. Insertion Sort\n4. Merge Sort\n");
    printf("5. Selection Sort\n6. Bucket Sort\n7. Shell Sort\n8. Heap Sort\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            bubbleSort(student, n);
            break;
        case 2:
            quickSort(student, 0, n - 1);
            break;
        case 3:
            insertionSort(student, n);
            break;
        case 4:
            mergeSort(student, 0, n - 1);
            break;
        case 5:
            selectionSort(student, n);
            break;        
        case 6:
            heapSort(student, n);
            break;
        default:
            printf("Invalid choice!\n");
            return 0;
    }

    printf("\nSorted Students by Roll Number:\n");
    for (int i = 0; i < n; i++)
        printf("Name: %s, Roll: %d, Marks: %d\n", student[i].name, student[i].roll, student[i].marks);

    printf("\nTotal Swaps: %d\n", swap_count);
    return 0;
}
