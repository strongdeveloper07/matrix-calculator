#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    double** data; // двумерный массив с числами
    int rows; // количество строк
    int cols; // количество столбцов

} Matrix;

/**
 * @brief Создает матрицу заданного размера
 * @param rows Количество строк (должно быть > 0)
 * @param cols Количество столбцов (должно быть > 0)
 * @return Matrix Созданная матрица с нулевыми элементами
 * @throw std::invalid_argument Если rows или cols <= 0
 */
Matrix create_matrix(int rows, int cols);
/**
 * @brief Освобождает память, занятую матрицей
 * @param m Матрица для освобождения
 * @warning Всегда вызывайте эту функцию для созданных матриц!
 */
void free_matrix(Matrix m);
/**
 * @brief Сложение двух матриц
 * @param a Первая матрица
 * @param b Вторая матрица
 * @return Matrix Результат сложения матриц a и b
 * @throw std::invalid_argument Если размеры матриц не совпадают
 */
Matrix matrix_add(Matrix a, Matrix b);
/**
 * @brief Умножение двух матриц
 * @param a Первая матрица (должна иметь размер M x N)
 * @param b Вторая матрица (должна иметь размер N x K)
 * @return Matrix Результат умножения матриц a и b (размер M x K)
 * @throw std::invalid_argument Если количество столбцов матрицы a не равно количеству строк матрицы b
 */
Matrix matrix_multiply(Matrix a, Matrix b);
/**
 * @brief Вывод матрицы в стандартный поток вывода
 * @param m Матрица для вывода
 * @warning Если матрица пустая, выводится "[Empty matrix]"
 */
void print_matrix(Matrix m);
/**
 * @brief Создание матрицы из одномерного массива
 * @param data Указатель на массив данных
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Matrix Матрица, заполненная данными из массива
 * @note Данные копируются из массива в матрицу построчно
 * @throw std::invalid_argument Если rows или cols <= 0
 */
Matrix matrix_from_array(double* data, int rows, int cols);
/**
 * @brief Транспонирование матрицы
 * @param m Исходная матрица
 * @return Matrix Транспонированная матрица
 * @throw std::invalid_argument Если матрица пустая или невалидная
 */
Matrix matrix_transpose(Matrix m);
#endif
