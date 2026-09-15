#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    const int MAX_SIZE = 10;
    int a[MAX_SIZE][MAX_SIZE];
    int rows, columns;

    printf("Введите количество строк от 1 до 10: ");
    scanf_s("%d", &rows);

    printf("Введите количество столбцов от 1 до 10: ");
    scanf_s("%d", &columns);

    if (rows < 1 || rows > MAX_SIZE ||
        columns < 1 || columns > MAX_SIZE)
    {
        printf("Некорректный размер массива.\n");
        return 1;
    }

    printf("\nДвумерный массив:\n");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            a[i][j] = rand() % 10;
            printf("%3d", a[i][j]);
        }

        printf("\n");
    }

    printf("\nСуммы элементов каждого столбца:\n");

    for (int j = 0; j < columns; j++)
    {
        int sum = 0;

        for (int i = 0; i < rows; i++)
        {
            sum += a[i][j];
        }

        printf("Столбец %d: %d\n", j + 1, sum);
    }

    return 0;
}
