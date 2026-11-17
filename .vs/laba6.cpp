#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


void generateMatrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
                matrix[i][j] = rand() % 2;
                matrix[j][i] = matrix[i][j];
        }
    }
}
void generatesecondMatrix(int** matrix, int N2) {
    for (int i = 0; i < N2; i++) {
        for (int j = i+1; j < N2; j++) {
                matrix[i][j] = rand() % 2;
                matrix[j][i] = matrix[i][j];
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));
    setlocale(LC_ALL, ".UTF8");

    int N;
    int N2;
    printf("Введите количество вершин графа: ");
    scanf("%d", &N);
    printf("Введите количество вершин 2 графа: ");
    scanf("%d", &N2);
    if (N <= 0 || N2 <= 0) {
        printf("Ошибка: количество вершин должно быть положительным.\n");
        return 1;
    }

    int** matrix = (int**)malloc(N * sizeof(int*));
    int** matrix2 = (int**)malloc(N2 * sizeof(int*));
    if (matrix == NULL || matrix2 == NULL) {
        printf("Ошибка: не удалось выделить память для матрицы.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));

        if (matrix[i] == NULL) {
            printf("Ошибка: не удалось выделить память для строки матрицы.\n");

            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }

            free(matrix);
            return 1;
        }
    }
    for (int i = 0; i < N2; i++) {
        matrix2[i] = (int*)malloc(N2 * sizeof(int));

        if (matrix2[i] == NULL) {
            printf("Ошибка: не удалось выделить память для строки матрицы.\n");

            for (int j = 0; j < i; j++) {
                free(matrix2[j]);
            }

            free(matrix2);
            return 1;
        }
    }
    generateMatrix(matrix, N);
    generatesecondMatrix(matrix2, N2);
    printf("Матрица смежности графа:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Матрица смежности 2 графа:\n");

    for (int i = 0; i < N2; i++) {
        for (int j = 0; j < N2; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }

    free(matrix);

    return 0;
}