
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct node {
    char name[256];
    int priority;
    struct node* next;
};

struct node* head = NULL;

void add()
{
    struct node* p;
    struct node* temp;

    p = (struct node*)malloc(sizeof(struct node));

    if (p == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    printf("Введите название объекта: ");
    scanf("%255s", p->name);

    printf("Введите приоритет: ");
    scanf("%d", &p->priority);

    p->next = NULL;

    if (head == NULL || p->priority > head->priority) {
        p->next = head;
        head = p;
    }
    else {
        temp = head;

        while (temp->next != NULL &&
            temp->next->priority >= p->priority) {
            temp = temp->next;
        }

        p->next = temp->next;
        temp->next = p;
    }

    temp = head;
    int number = 1;

    while (temp != p) {
        temp = temp->next;
        number++;
    }

    printf("Элемент добавлен под номером %d\n", number);
}

void review()
{
    struct node* temp = head;
    int number = 1;

    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    printf("\n№\tИмя\t\tПриоритет\n");
    printf("--------------------------------\n");

    while (temp != NULL) {
        printf("%d\t%s\t\t%d\n",
            number, temp->name, temp->priority);

        number++;
        temp = temp->next;
    }
}

void search()
{
    struct node* temp = head;
    int priority;
    int number = 1;
    int found = 0;

    printf("Введите приоритет для поиска: ");
    scanf("%d", &priority);

    while (temp != NULL) {
        if (temp->priority == priority) {
            if (found == 0) {
                printf("\nНайденные элементы:\n");
                printf("№\tИмя\t\tПриоритет\n");
                printf("--------------------------------\n");
            }

            printf("%d\t%s\t\t%d\n",
                number, temp->name, temp->priority);

            found = 1;
        }

        number++;
        temp = temp->next;
    }

    if (found == 0) {
        printf("Элементы с таким приоритетом не найдены\n");
    }
}

void clear()
{
    struct node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int choice;

    do {
        printf("\n1. Добавить элемент\n");
        printf("2. Просмотреть очередь\n");
        printf("3. Найти элемент по приоритету\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода\n");
            clear();
            return 1;
        }

        switch (choice) {
        case 1:
            add();
            break;

        case 2:
            review();
            break;

        case 3:
            search();
            break;

        case 0:
            clear();
            printf("Выход\n");
            break;

        default:
            printf("Неверный выбор\n");
        }

    } while (choice != 0);

    return 0;
}
