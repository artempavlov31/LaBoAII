#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


int main(){
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int N;

    printf("Введите количество вершин графа: ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Количество вершин должно быть положительным числом.\n");
        return 1;
    }

    int ** matrix = (int **)malloc(N * sizeof(int *));

    if (matrix == NULL) {
        printf("Ошибка выделения памяти для матрицы смежности.\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(N * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка выделения памяти для строки матрицы смежности.\n");
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
            } else {
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

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}