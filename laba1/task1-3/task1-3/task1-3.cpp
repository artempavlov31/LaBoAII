#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>


int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int i,j;
	int n;
	int max = 40;
	int min=-15;
	int c = 0;
	int sum = 0;
	printf_s("Введите размер массива:");
	scanf_s("%d",&n);
	int **arr = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(n * sizeof(int));
	}
	printf("Массив:\n");
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++) {
			arr[i][j] = min + rand() % (max - min + 1);
			printf("%4d ", arr[i][j]);
		}
		printf("\n");
	}
	min = arr[0][0];
	max = arr[0][0];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {

			if (arr[i][j] > max) {
				max = arr[i][j];
			}
			if (arr[i][j] < min) {
				min = arr[i][j];
			}
			if (arr[i][j] < 0) {
				c++;
				sum += arr[i][j];
			}
		}
	}
	printf("Минимальное значение:%d\n", min);
	printf("Максимальное значение:%d\n", max);
	printf("Разница между максимальным и минимальным значениями:%d", max - min);
	printf("\nКоличество отрицательных элементов:%d\n", c);
	printf("Сумма отрицательных элементов:%d\n", sum);
	return 0;
}