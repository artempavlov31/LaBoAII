#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct node {
    char name[256];
    struct node* next;
};

struct node* top = NULL;

void add()
{
    struct node* p;

    p = (struct node*)malloc(sizeof(struct node));

    if (p == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    printf("Введите название объекта (например object_1 или object-1): ");
    scanf("%255s", p->name);

    p->next = top;
    top = p;

    printf("Элемент добавлен в стек\n");
}

void del()
{
    struct node* temp;

    if (top == NULL) {
        printf("Стек пуст\n");
        return;
    }

    temp = top;
    top = top->next;

    printf("Удален элемент: %s\n", temp->name);
    free(temp);
}

void review()
{
    struct node* temp = top;

    if (top == NULL) {
        printf("Стек пуст\n");
        return;
    }

    printf("Содержимое стека (от вершины к основанию):\n");
    while (temp != NULL) {
        printf("Имя: %s\n", temp->name);
        temp = temp->next;
    }
}

void moveToTopByName()
{
    char name[256];
    int moved = 0;
    struct node* current;
    struct node* next;
    struct node* matchingHead = NULL;
    struct node* matchingTail = NULL;
    struct node* otherHead = NULL;
    struct node* otherTail = NULL;

    if (top == NULL) {
        printf("Стек пуст\n");
        return;
    }

    printf("Введите имя объекта: ");
    scanf("%255s", name);

    current = top;

    while (current != NULL) {
        next = current->next;
        current->next = NULL;

        if (strcmp(current->name, name) == 0) {
            if (matchingHead == NULL) {
                matchingHead = current;
            }
            else {
                matchingTail->next = current;
            }
            matchingTail = current;
            moved++;
        }
        else {
            if (otherHead == NULL) {
                otherHead = current;
            }
            else {
                otherTail->next = current;
            }
            otherTail = current;
        }

        current = next;
    }

    if (matchingHead == NULL) {
        top = otherHead;
        printf("Элементы с именем %s не найдены\n", name);
        return;
    }

    matchingTail->next = otherHead;
    top = matchingHead;

    printf("Элементы с именем %s перенесены на вершину: %d\n", name, moved);
}

void clear()
{
    struct node* temp;

    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        printf("\n1. Добавить элемент\n");
        printf("2. Удалить верхний элемент\n");
        printf("3. Просмотреть стек\n");
        printf("4. Перенести элементы по имени на вершину\n");
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
            moveToTopByName();
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
