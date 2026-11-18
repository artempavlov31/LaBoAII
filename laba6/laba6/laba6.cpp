#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
using Vertices = std::vector<std::size_t>;

Matrix emptyMatrix(std::size_t size) {
    return Matrix(size, std::vector<int>(size));
}

Matrix generateMatrix(std::size_t size) {
    Matrix matrix = emptyMatrix(size);
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = i + 1; j < size; ++j) {
            matrix[i][j] = matrix[j][i] = std::rand() % 2;
        }
    }
    return matrix;
}

void printMatrix(const Matrix& matrix) {
    if (matrix.empty()) {
        std::cout << "Граф пуст.\n";
        return;
    }

    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}

Matrix identifyVertices(const Matrix& matrix, std::size_t u, std::size_t v) {
    Vertices remaining;
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        if (i != u && i != v) {
            remaining.push_back(i);
        }
    }

    const std::size_t merged = remaining.size();
    Matrix result = emptyMatrix(merged + 1);
    for (std::size_t i = 0; i < merged; ++i) {
        const auto original = remaining[i];
        for (std::size_t j = 0; j < merged; ++j) {
            result[i][j] = matrix[original][remaining[j]];
        }
        result[i][merged] = result[merged][i] = matrix[original][u] || matrix[original][v];
    }
    return result;
}

Matrix contractEdge(const Matrix& matrix, std::size_t u, std::size_t v) {
    if (!matrix[u][v]) {
        throw std::invalid_argument("Выбранные вершины не смежны.");
    }
    return identifyVertices(matrix, u, v);
}

Matrix splitVertex(const Matrix& matrix, std::size_t u) {
    const std::size_t extra = matrix.size();
    Matrix result = emptyMatrix(extra + 1);
    std::size_t target = u;
    for (std::size_t i = 0; i < extra; ++i) {
        if (i == u) {
            continue;
        }
        for (std::size_t j = 0; j < extra; ++j) {
            if (j != u) {
                result[i][j] = matrix[i][j];
            }
        }
        if (matrix[u][i]) {
            result[target][i] = result[i][target] = 1;
            target = target == u ? extra : u;
        }
    }
    result[u][extra] = result[extra][u] = 1;
    return result;
}

bool hasEdge(const Matrix& matrix, std::size_t u, std::size_t v) {
    return u < matrix.size() && v < matrix.size() && matrix[u][v] != 0;
}

enum class GraphOperation { Union, Intersection, RingSum };

Matrix combineGraphs(const Matrix& first, const Matrix& second, GraphOperation operation) {
    const auto size = operation == GraphOperation::Intersection
        ? std::min(first.size(), second.size())
        : std::max(first.size(), second.size());
    Matrix result = emptyMatrix(size);
    for (std::size_t u = 0; u < size; ++u) {
        for (std::size_t v = u + 1; v < size; ++v) {
            const bool inFirst = hasEdge(first, u, v);
            const bool inSecond = hasEdge(second, u, v);
            bool edge = false;
            switch (operation) {
                case GraphOperation::Union: edge = inFirst || inSecond; break;
                case GraphOperation::Intersection: edge = inFirst && inSecond; break;
                case GraphOperation::RingSum: edge = inFirst != inSecond; break;
            }
            result[u][v] = result[v][u] = edge;
        }
    }
    return result;
}

Vertices nonIsolatedVertices(const Matrix& matrix) {
    Vertices labels;
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        if (std::find(matrix[i].begin(), matrix[i].end(), 1) != matrix[i].end()) {
            labels.push_back(i);
        }
    }
    return labels;
}

Matrix keepVertices(const Matrix& matrix, const Vertices& labels) {
    Matrix result = emptyMatrix(labels.size());
    for (std::size_t i = 0; i < labels.size(); ++i) {
        for (std::size_t j = 0; j < labels.size(); ++j) {
            result[i][j] = matrix[labels[i]][labels[j]];
        }
    }
    return result;
}

bool readNumbers(const char* prompt, std::initializer_list<int*> numbers) {
    while (std::cout << prompt) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            return false;
        }
        std::istringstream input(line);
        for (int* number : numbers) {
            input >> *number;
        }
        if (input && (input >> std::ws).eof()) {
            return true;
        }
        std::cout << "Введите целые числа в указанном формате.\n";
    }
    return false;
}

bool readGraphSize(const char* prompt, int& size) {
    while (readNumbers(prompt, {&size})) {
        if (size >= 2) {
            return true;
        }
        std::cout << "В графе должно быть минимум две вершины.\n";
    }
    return false;
}

bool readVertices(const Matrix& matrix, bool edgeRequired, std::size_t& u, std::size_t& v) {
    int first = 0;
    int second = 0;
    while (readNumbers("Введите два разных номера вершин через пробел: ", {&first, &second})) {
        if (first < 1 || second < 1 || static_cast<std::size_t>(first) > matrix.size()
            || static_cast<std::size_t>(second) > matrix.size() || first == second) {
            std::cout << "Проверьте номера вершин.\n";
            continue;
        }
        u = first - 1;
        v = second - 1;
        if (!edgeRequired || matrix[u][v]) {
            return true;
        }
        std::cout << "Между этими вершинами нет ребра. Выберите другую пару.\n";
    }
    return false;
}

bool showUnaryOperations(const Matrix& matrix, int graphNumber) {
    std::cout << "\nУнарные операции для графа G" << graphNumber << "\n";
    std::cout << "Каждая операция выполняется для исходной матрицы.\n";

    std::size_t u = 0;
    std::size_t v = 0;
    std::cout << "Отождествление вершин\n";
    if (!readVertices(matrix, false, u, v)) {
        return false;
    }
    std::cout << "После отождествления:\n";
    printMatrix(identifyVertices(matrix, u, v));

    std::cout << "Стягивание ребра\n";
    if (nonIsolatedVertices(matrix).empty()) {
        std::cout << "Стягивание невозможно: в исходном графе нет рёбер.\n";
    } else {
        if (!readVertices(matrix, true, u, v)) {
            return false;
        }
        std::cout << "После стягивания:\n";
        printMatrix(contractEdge(matrix, u, v));
    }

    std::cout << "Расщепление вершины\n";
    int vertex = 0;
    while (readNumbers("Введите номер вершины: ", {&vertex})) {
        if (vertex >= 1 && static_cast<std::size_t>(vertex) <= matrix.size()) {
            std::cout << "После расщепления:\n";
            printMatrix(splitVertex(matrix, vertex - 1));
            return true;
        }
        std::cout << "Проверьте номер вершины.\n";
    }
    return false;
}

void showBinaryOperations(const Matrix& first, const Matrix& second) {
    std::cout << "\nОбъединение G1 и G2:\n";
    printMatrix(combineGraphs(first, second, GraphOperation::Union));
    std::cout << "Пересечение G1 и G2:\n";
    printMatrix(combineGraphs(first, second, GraphOperation::Intersection));

    const Matrix difference = combineGraphs(first, second, GraphOperation::RingSum);
    const Vertices labels = nonIsolatedVertices(difference);
    std::cout << "Кольцевая сумма G1 и G2:\n";
    if (!labels.empty()) {
        std::cout << "Номера вершин по порядку строк и столбцов: ";
        for (std::size_t label : labels) {
            std::cout << label + 1 << ' ';
        }
        std::cout << '\n';
    }
    printMatrix(keepVertices(difference, labels));
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int firstSize = 0;
    int secondSize = 0;
    if (!readGraphSize("Введите число вершин графа G1: ", firstSize)
        || !readGraphSize("Введите число вершин графа G2: ", secondSize)) {
        return 1;
    }

    try {
        const Matrix first = generateMatrix(firstSize);
        const Matrix second = generateMatrix(secondSize);
        std::cout << "\nМатрица смежности G1:\n";
        printMatrix(first);
        std::cout << "\nМатрица смежности G2:\n";
        printMatrix(second);
        if (!showUnaryOperations(first, 1) || !showUnaryOperations(second, 2)) {
            return 1;
        }
        showBinaryOperations(first, second);
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
