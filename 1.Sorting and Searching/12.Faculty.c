// Write a program to arrange the data of the faculties recruited in the
// institute. There are three categories of faculties in the every deartment
// namely professor, Associate professor, and assistant professor.
// Recruitment is done as mentioned below. 1. Every professor has two
// associate professors. 2. Every Associate has two assistant professors.
// Data is given randomly. Suggest suitable sorting method and implement.

#include <stdio.h>
#include <string.h>

struct Faculty {
    char name[50];
    char designation[50];
    int priority; // Lower value = higher rank
};

// Function to assign priority
int getPriority(char designation[]) {
    if (strcmp(designation, "Professor") == 0)
        return 1;
    else if (strcmp(designation, "Associate Professor") == 0)
        return 2;
    else if (strcmp(designation, "Assistant Professor") == 0)
        return 3;
    else
        return 100; // Unknown designation
}

// Simple bubble sort based on priority
void sortFaculty(struct Faculty f[], int n) {
    struct Faculty temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (f[j].priority > f[j+1].priority) {
                temp = f[j];
                f[j] = f[j+1];
                f[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of faculties: ");
    scanf("%d", &n);

    struct Faculty f[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter name of faculty %d: ", i+1);
        scanf(" %[^\n]s", f[i].name);
        printf("Enter designation (Professor/Associate Professor/Assistant Professor): ");
        scanf(" %[^\n]s", f[i].designation);
        f[i].priority = getPriority(f[i].designation);
    }

    // Sort the faculty list
    sortFaculty(f, n);

    // Display
    printf("\nSorted Faculty List:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Designation: %s\n", f[i].name, f[i].designation);
    }

    return 0;
}