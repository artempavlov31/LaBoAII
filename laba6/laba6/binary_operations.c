#include <stdio.h>
#include <stdlib.h>

static int hasEdge(int **matrix, int size, int u, int v) {
    return u < size && v < size && matrix[u][v] != 0;
}

static void printCombinedMatrix(int **first, int firstSize, int **second,
                                int secondSize, int size, int minimumCount) {
    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            int count = hasEdge(first, firstSize, u, v)
                      + hasEdge(second, secondSize, u, v);
            printf("%d ", count >= minimumCount);
        }
        putchar('\n');
    }
}

static int ringEdge(int **first, int firstSize, int **second,
                    int secondSize, int u, int v) {
    return hasEdge(first, firstSize, u, v) != hasEdge(second, secondSize, u, v);
}

static void printRingSum(int **first, int firstSize, int **second,
                         int secondSize, int size) {
    int *vertices = malloc((size_t)size * sizeof *vertices);
    if (vertices == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для кольцевой суммы.\n");
        return;
    }

    int count = 0;
    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            if (ringEdge(first, firstSize, second, secondSize, u, v)) {
                vertices[count++] = u;
                break;
            }
        }
    }

    if (count == 0) {
        puts("Граф пуст.");
    } else {
        printf("Номера вершин по порядку строк и столбцов:");
        for (int i = 0; i < count; i++) {
            printf(" %d", vertices[i] + 1);
        }
        putchar('\n');

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                int edge = ringEdge(first, firstSize, second, secondSize,
                                    vertices[i], vertices[j]);
                printf("%d ", edge);
            }
            putchar('\n');
        }
    }
    free(vertices);
}

void showBinaryOperations(int **first, int firstSize, int **second, int secondSize) {
    int smallerSize = firstSize < secondSize ? firstSize : secondSize;
    int largerSize = firstSize > secondSize ? firstSize : secondSize;

    puts("\nОбъединение G1 и G2:");
    printCombinedMatrix(first, firstSize, second, secondSize, largerSize, 1);

    puts("Пересечение G1 и G2:");
    printCombinedMatrix(first, firstSize, second, secondSize, smallerSize, 2);

    puts("Кольцевая сумма G1 и G2:");
    printRingSum(first, firstSize, second, secondSize, largerSize);
}
