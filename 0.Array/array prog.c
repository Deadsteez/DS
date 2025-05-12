// 1)Difference 

// #include <stdio.h>

// int Difference(int arr[], int n) {
//     int sum = 0, expectedSum = n * (n + 1) / 2;
//     for (int i = 0; i < n - 1; i++) {
//         sum += arr[i];
//     }
//     return expectedSum - sum;
// }

// int main() {
//     int n;
//     printf("Enter the number of elements: ");
//     scanf("%d", &n);

//     int arr[n - 1];
//     printf("Enter %d numbers\n", n - 1);
//     for (int i = 0; i < n - 1; i++) {
//         scanf("%d", &arr[i]);
//     }

//     printf("Difference= %d\n", Difference(arr, n));
//     return 0;
// }

//--------------------------------------------------------------------------------------------------------------------------------------------

// 2)Saddle point
// #include <stdio.h>

// void findSaddlePoint(int a[10][10], int rows, int cols) {
//     for (int i = 0; i < rows; i++) {
//         int rowMin = a[i][0], colIndex = 0;
//         for (int j = 1; j < cols; j++) {
//             if (a[i][j] < rowMin) {
//                 rowMin = a[i][j];
//                 colIndex = j;
//             }
//         }

//         int isSaddle = 1;
//         for (int k = 0; k < rows; k++) {
//             if (a[k][colIndex] > rowMin) {
//                 isSaddle = 0;
//                 break;
//             }
//         }

//         if (isSaddle) {
//             printf("Saddle Point is %d at (%d, %d)\n", rowMin, i, colIndex);
//             return;
//         }
//     }
//     printf("No Saddle Point Found\n");
// }

// int main() {
//     int rows, cols;
//     int a[10][10];

//     printf("Enter the number of rows and columns: ");
//     scanf("%d %d", &rows, &cols);

//     printf("Enter the elements of the matrix:\n");
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             scanf("%d", &a[i][j]);
//         }
//     }

//     findSaddlePoint(a, rows, cols);
//     return 0;
// }



//--------------------------------------------------------------------------------------------------------------------------------------------


// 3)Magic Square
// #include <stdio.h>

// int isMagicSquare(int a[10][10], int n) {
//     int sum = 0, diag1 = 0, diag2 = 0;

//     // Sum of the first row
//     for (int j = 0; j < n; j++) {
//         sum += a[0][j];
//     }

//     // Check rows and columns
//     for (int i = 0; i < n; i++) {
//         int rowSum = 0, colSum = 0;
//         for (int j = 0; j < n; j++) {
//             rowSum += a[i][j];
//             colSum += a[j][i];
//         }
//         if (rowSum != sum || colSum != sum) {
//             return 0;
//         }
//     }

//     // Check diagonals
//     for (int i = 0; i < n; i++) {
//         diag1 += a[i][i];
//         diag2 += a[i][n - i - 1];
//     }

//     return (diag1 == sum && diag2 == sum);
// }

// int main() {
//     int n;
//     int a[10][10];

//     printf("Enter the size of the matrix (n x n): ");
//     scanf("%d", &n);

//     printf("Enter the elements of the matrix:\n");
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             scanf("%d", &a[i][j]);
//         }
//     }

//     if (isMagicSquare(a, n)) {
//         printf("The matrix is a magic square.\n");
//     } else {
//         printf("The matrix is not a magic square.\n");
//     }

//     return 0;
// }

//--------------------------------------------------------------------------------------------------------------------------------------------

// 4)Sparse matrix

// #include <stdio.h>

// void sparse(int A[][100], int m, int n) {
//     int sp[100][3], k = 1;

//     sp[0][0] = m;
//     sp[0][1] = n;

//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             if (A[i][j] != 0) {
//                 sp[k][0] = i;
//                 sp[k][1] = j;
//                 sp[k][2] = A[i][j];
//                 k++;
//             }
//         }
//     }

//     sp[0][2] = k - 1;

//     printf("\nSparse Matrix Representation:\n");
//     printf("Row\tColumn\tValue\n");
//     for (int i = 0; i < k; i++) {
//         printf("%d\t%d\t%d\n", sp[i][0], sp[i][1], sp[i][2]);
//     }
// }

// int main() {
//     int m, n;
//     int a[100][100];

//     printf("Enter the number of rows and columns: ");
//     scanf("%d %d", &m, &n);

//     printf("Enter the elements of the matrix:\n");
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             scanf("%d", &a[i][j]);
//         }
//     }

//     sparse(a, m, n);
//     return 0;
// }
