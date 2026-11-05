#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdlib.h>

int countEdges(int** matrix, int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matrix[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int N;
    printf("Введите количество вершин графа: ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Ошибка: количество вершин должно быть положительным.\n");
        return 1;
    }

    int** matrix = (int**)malloc(N * sizeof(int*));

    if (matrix == NULL) {
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
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = rand() % 2;
            }
        }
    }
    printf("Матрица смежности графа:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    int edgeCount = countEdges(matrix, N);
    printf("Количество рёбер в графе: %d\n", edgeCount);
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;

}
