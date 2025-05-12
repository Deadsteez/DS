#include <stdio.h>
#include <string.h>

int swap_count = 0;

struct Student {
    char name[50];
    int prev_marks;
    int roll;
};

int Qpartition(struct Student a[], int left, int right) {
    struct Student pivot = a[left];
    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= right && a[i].prev_marks >= pivot.prev_marks)
            i++;
        while (j >= left && a[j].prev_marks < pivot.prev_marks)
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

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct Student students[n];

    // Input student data
    for (int i = 0; i < n; i++) {
        printf("Enter name of student %d: ", i + 1);
        scanf("%s", students[i].name);
        printf("Enter previous year marks: ");
        scanf("%d", &students[i].prev_marks);
    }

    // Sort students based on marks
    quickSort(students, 0, n - 1);

    // Assign roll numbers after sorting
    for (int i = 0; i < n; i++) {
        students[i].roll = i + 1;  // Topper gets roll 1
    }

    // Output final list
    printf("\nFinal Roll Numbers:\n");
    printf("Roll\tName\tMarks\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\n", students[i].roll, students[i].name, students[i].prev_marks);
    }

    printf("\nTotal swaps during sorting: %d\n", swap_count);
    return 0;
}
