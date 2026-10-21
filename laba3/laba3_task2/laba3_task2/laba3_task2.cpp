#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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

void reverseQueue()
{
    struct node* previous = NULL;
    struct node* current = head;
    struct node* next = NULL;

    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    last = head;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    head = previous;
    printf("Очередь развернута\n");
}

void moveToHeadByName()
{
    char name[256];
    struct node* previous;
    struct node* current;

    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Введите название объекта: ");
    scanf("%255s", name);

    if (strcmp(head->name, name) == 0) {
        printf("Элемент уже находится в голове очереди\n");
        return;
    }

    previous = head;
    current = head->next;

    while (current != NULL && strcmp(current->name, name) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Элемент с названием %s не найден\n", name);
        return;
    }

    previous->next = current->next;

    if (current == last) {
        last = previous;
    }

    current->next = head;
    head = current;

    printf("Элемент %s перенесен в голову очереди\n", name);
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
        printf("4. Развернуть очередь\n");
        printf("5. Перенести элемент по названию в голову\n");
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
        case 4:
            reverseQueue();
            break;
        case 5:
            moveToHeadByName();
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
