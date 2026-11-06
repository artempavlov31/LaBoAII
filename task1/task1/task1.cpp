#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <clocale>

void generateSymmetricMatrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            matrix[j][i] = matrix[i][j];
        }
    }
}
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
void findVerticles(int** matrix, int N) {
    int degree;
    bool isIsolated;
    bool terminal;
    bool dominant;
    for (int i = 0; i < N; i++) {
        degree = 0;
        isIsolated = true;
        terminal = false;
        dominant = true;
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                degree++;
                isIsolated = false;
            }
            if (matrix[i][j] == 1 && degree == 1) {
                terminal = true;
            }
            if (matrix[i][j] == 0 && i != j) {
                dominant = false;
            }
        }
        printf("Вершина %d: степень %d, ", i + 1, degree);
        if (isIsolated) {
            printf("изолированная, ");
        }
        else {
            printf("не изолированная, ");
        }
        if (terminal) {
            printf("терминальная, ");
        }
        else {
            printf("не терминальная, ");
        }
        if (dominant) {
            printf("доминирующая\n");
        }
        else {
            printf("не доминирующая\n");
        }
    }
}

int main() {
    srand(time(0));
	setlocale(LC_ALL, ".UTF8");
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
	generateSymmetricMatrix(matrix, N);
    printf("Матрица смежности графа:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Характеристики вершин:\n");
    findVerticles(matrix, N);
    int edgeCount = countEdges(matrix, N);
    printf("Количество рёбер в графе: %d\n", edgeCount);
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;

}
