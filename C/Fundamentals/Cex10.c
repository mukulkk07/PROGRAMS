#include <stdio.h>

int main() {
    int n, m, i, j;

    /* 1. Get Dimensions */
    printf("--- College Examination System ---\n");
    printf("Enter number of Students (n): ");
    scanf("%d", &n);
    printf("Enter number of Subjects (m): ");
    scanf("%d", &m);

    /* 2. Declare Matrices */
    // matrixA = Exam 1, matrixB = Exam 2, total = Sum
    int matrixA[n][m];
    int matrixB[n][m];
    int totalMatrix[n][m];

    /* 3. Input for Exam 1 (Matrix A) */
    printf("\n--- Enter Marks for Exam 1 ---\n");
    for (i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        for (j = 0; j < m; j++) {
            printf("  Subject %d Marks: ", j + 1);
            scanf("%d", &matrixA[i][j]);
        }
    }

    /* 4. Input for Exam 2 (Matrix B) */
    printf("\n--- Enter Marks for Exam 2 ---\n");
    for (i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        for (j = 0; j < m; j++) {
            printf("  Subject %d Marks: ", j + 1);
            scanf("%d", &matrixB[i][j]);
        }
    }

    /* 5. Calculate Total (Matrix Addition) */
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            totalMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    /* 6. Display Reports */
    // Helper macro to print a separating line
    printf("\n\n================ REPORT GENERATION ================\n");

    // --- Display Exam 1 ---
    printf("\n[Matrix A] Exam 1 Marks:\n");
    printf("St_ID\t"); 
    for(j=0; j<m; j++) printf("Sub%d\t", j+1); // Header
    printf("\n");
    
    for (i = 0; i < n; i++) {
        printf("St_%d\t", i + 1); // Row Header
        for (j = 0; j < m; j++) {
            printf("%d\t", matrixA[i][j]);
        }
        printf("\n");
    }

    // --- Display Exam 2 ---
    printf("\n[Matrix B] Exam 2 Marks:\n");
    printf("St_ID\t"); 
    for(j=0; j<m; j++) printf("Sub%d\t", j+1);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("St_%d\t", i + 1);
        for (j = 0; j < m; j++) {
            printf("%d\t", matrixB[i][j]);
        }
        printf("\n");
    }

    // --- Display Consolidated Total ---
    printf("\n[Final] Total Marks (Exam 1 + Exam 2):\n");
    printf("St_ID\t"); 
    for(j=0; j<m; j++) printf("Sub%d\t", j+1);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("St_%d\t", i + 1);
        for (j = 0; j < m; j++) {
            printf("%d\t", totalMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}