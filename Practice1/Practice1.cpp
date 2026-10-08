#include <iostream>
#include <limits>       

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    setlocale(LC_ALL, "Russn");
    int n, m;
    int** matrix = nullptr;
    int** transposed = nullptr;

    try {
        // 1. ввод размеров
        std::cout << "Введите количество строк и столбцов: ";
        if (!(std::cin >> n >> m)) {
            throw std::invalid_argument("Ошибка ввода размеров");
        }

        // проверка на invalid_argument
        if (n <= 0 || m <= 0) {
            throw std::invalid_argument("Размеры матрицы должны быть положительными");
        }


        //превышает максимально возможное значение
        size_t max_size = std::numeric_limits<size_t>::max();
        if (static_cast<size_t>(n) > max_size / static_cast<size_t>(m)) {
            throw std::overflow_error("Размер матрицы слишком велик (переполнение)");
        }

        // 2. выделение памяти под исходную матрицу
        matrix = new int* [n];
        for (int i = 0; i < n; ++i) {
            matrix[i] = new int[m];
        }

        // 3. ввод элементов
        std::cout << "Введите элементы матрицы:" << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!(std::cin >> matrix[i][j])) {
                    throw std::invalid_argument("Ошибка ввода элементов матрицы");
                }
            }
        }

        // 4. выделение памяти под транспонированную матрицу
        transposed = new int* [m];
        for (int i = 0; i < m; ++i) {
            transposed[i] = new int[n];
        }

        // 5. транспонирование
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                transposed[j][i] = matrix[i][j];
            }
        }

        // 6. вывод
        std::cout << "Транспонированная матрица:" << '\n';
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << transposed[i][j] << " ";
            }
            std::cout << '\n';
        }

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        if (matrix != nullptr) {
            for (int i = 0; i < n; ++i) delete[] matrix[i];
            delete[] matrix;
        }
        if (transposed != nullptr) {
            for (int i = 0; i < m; ++i) delete[] transposed[i];
            delete[] transposed;
        }
        return 1;
    }
    catch (const std::overflow_error& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }

    // 7. освобождение памяти при успешном завершении
    freeMatrix(matrix, n);
    freeMatrix(transposed, m);

    return 0;
}