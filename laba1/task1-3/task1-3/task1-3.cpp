#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>


int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int i;
	int n;
	int max, min;
	printf_s("Введите размер массива:");
	scanf_s("%d",&n);
	printf_s("Введите миниммальное значение:");
	scanf_s("%d", &min);
	printf_s("Введите максимальное значение:");
	scanf_s("%d", &max);
	int *arr = (int*)malloc(n * sizeof(int));
	printf("Массив:");
	for (i = 0; i < n; i++) {
		arr[i]= min + rand() % (max - min + 1);
		printf("%d ", arr[i]);
	}
	printf("\n");
	min = arr[0];
	max = arr[0];
	for (i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	printf("Минимальное значение:%d\n", min);
	printf("Максимальное значение:%d\n", max);
	printf("Разница между максимальным и минимальным значениями:%d", max - min);
	return 0;
}