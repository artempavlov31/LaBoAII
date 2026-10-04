#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct node {
    char name[256];
    struct node* next;
};

struct node* head = NULL;
struct node* last = NULL;

void add()
{
    struct node* p;

    p = (struct node*)malloc(sizeof(struct node));

    if (p == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    printf("Введите название объекта:Пример (object-1 или object_1) ");
    scanf("%255s", p->name);

    p->next = NULL;

    if (head == NULL) {
        head = p;
        last = p;
    }
    else {
        last->next = p;
        last = p;
    }

    printf("Элемент добавлен\n");
}

void del()
{
    struct node* temp;

    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    temp = head;
    head = head->next;

    printf("Удален элемент: %s\n", temp->name);

    free(temp);

    if (head == NULL) {
        last = NULL;
    }
}

void review()
{
    struct node* temp = head;

    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    while (temp != NULL) {
        printf("Имя: %s\n", temp->name);
        temp = temp->next;
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

    last = NULL;
}

int main()
{
	setlocale(LC_ALL, "Russian");
    int choice;

    do {
        printf("\n1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Просмотреть очередь\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add();
            break;
        case 2:
            del();
            break;
        case 3:
            review();
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
