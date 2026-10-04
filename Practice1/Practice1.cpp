#include <iostream>

int main() {

	unsigned int rows, cols;
	std::cout << "¬ведите количество строк и столбцов: ";
	std::cin >> rows >> cols;

	int** matrix = new int* [rows];

	for (int i{}; i < rows; ++i) {
		matrix[i] = new int[cols];
	}

	std::cout << "¬ведите элементы матрицы:" << std::endl;        //вводим элементы матрицы
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cin >> matrix[i][j];
		}
	}








	for (int i = 0; i < rows; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	return 0;
}