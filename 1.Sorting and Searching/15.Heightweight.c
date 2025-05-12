#include <stdio.h>
#include <string.h>

#define MAX 100

struct Employee {
    char name[50];
    float height; // in cm
    float weight; // in kg
};

// Function to compute average of height and weight
float average(struct Employee emp) {
    return (emp.height + emp.weight) / 2.0;
}

// Bubble Sort based on average of height and weight
void bubbleSort(struct Employee emp[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (average(emp[j]) > average(emp[j + 1])) {
                // Swap
                struct Employee temp = emp[j];
                emp[j] = emp[j + 1];
                emp[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee emp[n];

    // Input employee data
    for (int i = 0; i < n; i++) {
        printf("\nEnter name of employee %d: ", i + 1);
        scanf("%s", emp[i].name);
        printf("Enter height (in cm): ");
        scanf("%f", &emp[i].height);
        printf("Enter weight (in kg): ");
        scanf("%f", &emp[i].weight);
    }

    // Sort employees
    bubbleSort(emp, n);

    // Display sorted list
    printf("\nEmployees sorted by average of height and weight:\n");
    printf("Name\t\tHeight\tWeight\tAverage\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t\t%.2f\t%.2f\t%.2f\n", emp[i].name, emp[i].height, emp[i].weight, average(emp[i]));
    }

    return 0;
}
