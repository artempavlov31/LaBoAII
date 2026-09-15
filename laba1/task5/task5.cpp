#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#pragma execution_character_set("utf-8")

struct Student
{
    char surname[50];
    char name[50];
    char faculty[50];
    int recordBookNumber;
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");

    const int MAX_STUDENTS = 10;
    Student students[MAX_STUDENTS];
    int count;

    printf("Введите количество студентов: ");
    scanf_s("%d", &count);

    if (count < 1 || count > MAX_STUDENTS)
    {
        printf("Количество должно быть от 1 до 10.\n");
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\nСтудент №%d\n", i + 1);

        printf("Фамилия: ");
        scanf_s("%49s", students[i].surname,
            (unsigned)sizeof(students[i].surname));

        printf("Имя: ");
        scanf_s("%49s", students[i].name,
            (unsigned)sizeof(students[i].name));

        printf("Факультет: ");
        scanf_s("%49s", students[i].faculty,
            (unsigned)sizeof(students[i].faculty));

        printf("Номер зачётной книжки: ");
        scanf_s("%d", &students[i].recordBookNumber);
    }

    char searchSurname[50];
    char searchName[50];

    printf("\nВведите фамилию искомого студента: ");
    scanf_s("%49s", searchSurname, (unsigned)sizeof(searchSurname));

    printf("Введите имя искомого студента: ");
    scanf_s("%49s", searchName, (unsigned)sizeof(searchName));

    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].surname, searchSurname) == 0 &&
            strcmp(students[i].name, searchName) == 0)
        {
            printf("\nСтудент найден:\n");
            printf("Фамилия: %s\n", students[i].surname);
            printf("Имя: %s\n", students[i].name);
            printf("Факультет: %s\n", students[i].faculty);
            printf("Номер зачётной книжки: %d\n",
                students[i].recordBookNumber);

            found = 1;
        }
    }

    if (!found)
    {
        printf("\nСтудент не найден.\n");
    }

    return 0;
}