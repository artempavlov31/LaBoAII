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

    printf("Введите название объекта (например object_1 или object-1): ");
    scanf("%255s", p->name);

    printf("Введите приоритет (пример 1, 2, -5): ");
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

    printf("Элемент добавлен\n");
}


void review()
{
    struct node* temp = head;

    if (head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    while (temp != NULL) {
        printf("Имя: %s, приоритет: %d\n",
            temp->name, temp->priority);
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
}

int main()
{
	setlocale(LC_ALL, "Russian");
    int choice;

    do {
        printf("\n1. Добавить элемент\n");
        printf("2. Просмотреть очередь\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add();
            break;
        case 2:
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
