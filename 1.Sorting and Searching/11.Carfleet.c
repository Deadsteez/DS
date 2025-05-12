// You hav e a fleet of N cars waiting for repair, with the estimated repair
// times rk for the car Ci , 1 ? k ? N. What is the best repairschedule (order
// of repairs) to minimize the total lost time for being out-of-service. How
// much computation is needed to find the lost service-times all schedules?


#include <stdio.h>
#include <stdlib.h>

// Structure to hold car info
struct Car {
    int id;
    int repairTime;
};

// Function to sort cars by repairTime
void sortByRepairTime(struct Car cars[], int n) {
    struct Car temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (cars[j].repairTime > cars[j+1].repairTime) {
                temp = cars[j];
                cars[j] = cars[j+1];
                cars[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of cars: ");
    scanf("%d", &n);

    struct Car cars[n];

    // Input repair times
    for (int i = 0; i < n; i++) {
        printf("Enter repair time for Car %d: ", i+1);
        scanf("%d", &cars[i].repairTime);
        cars[i].id = i+1; // Assign Car ID
    }

    // Sort cars by repair times
    sortByRepairTime(cars, n);

    int totalLostTime = 0, currentTime = 0;

    printf("\nRepair Schedule:\n");
    for (int i = 0; i < n; i++) {
        currentTime += cars[i].repairTime;
        printf("Car %d repaired (Repair time: %d, Finished at: %d)\n", cars[i].id, cars[i].repairTime, currentTime);
        totalLostTime += currentTime;
    }

    printf("\nTotal Lost Service Time: %d\n", totalLostTime);

    return 0;
}