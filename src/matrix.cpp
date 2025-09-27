#include "matrix.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>  // Для std::min

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    // Выделяем память для массива указателей на строки
    mat.data = new double*[rows];
    
    // Выделяем память для каждой строки
    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        
        // Инициализируем нулями
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }
    
    return mat;
}

void free_matrix(Matrix m) {
    if (m.data == nullptr) return;

    // Освобождаем память каждой строки
    for (int i = 0; i < m.rows; i++) {
        delete[] m.data[i];
    }
    
    // Освобождаем массив указателей
    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Матрицы должны быть одного размера для сложения");
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Количество столбцов первой матрицы должно равняться количеству строк второй");
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0.0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}

void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    // Настройка формата вывода
    std::cout << std::fixed << std::setprecision(2);

    // Параметры для сокращенного вывода больших матриц
    const int MAX_ROWS_TO_SHOW = 10;
    const int MAX_COLS_TO_SHOW = 8;
    bool show_summary = (m.rows > MAX_ROWS_TO_SHOW || m.cols > MAX_COLS_TO_SHOW);
    int rows_to_show = show_summary ? MAX_ROWS_TO_SHOW : m.rows;
    int cols_to_show = show_summary ? MAX_COLS_TO_SHOW : m.cols;

    // Вывод строк матрицы
    for (int i = 0; i < rows_to_show; i++) {
        // Пропуск средних строк для больших матриц
        if (show_summary && i == MAX_ROWS_TO_SHOW / 2 && m.rows > MAX_ROWS_TO_SHOW) {
            std::cout << "[...";
            for (int j = 0; j < cols_to_show - 2; j++) {
                std::cout << "      "; // 6 пробелов для выравнивания
            }
            std::cout << "...]" << std::endl;
            continue;
        }

        std::cout << "["; // Начало строки

        // Вывод элементов строки
        for (int j = 0; j < cols_to_show; j++) {
            // Пропуск средних столбцов для больших матриц
            if (show_summary && j == MAX_COLS_TO_SHOW / 2 && m.cols > MAX_COLS_TO_SHOW) {
                std::cout << " ... ";
                continue;
            }

            std::cout << std::setw(6) << m.data[i][j];
            
            if (j < cols_to_show - 1) {
                std::cout << " ";
            }
        }

        std::cout << "]"; // Конец строки

        // Многоточие для пропущенных столбцов
        if (show_summary && m.cols > MAX_COLS_TO_SHOW) {
            std::cout << " ...";
        }

        std::cout << std::endl;
    }

    // Многоточие для пропущенных строк
    if (show_summary && m.rows > MAX_ROWS_TO_SHOW) {
        std::cout << "[...";
        for (int j = 0; j < std::min(cols_to_show, m.cols); j++) {
            std::cout << " ... ";
        }
        std::cout << "...]" << std::endl;
    }

    // Информация о реальном размере для больших матриц
    if (show_summary) {
        std::cout << "Matrix " << m.rows << "×" << m.cols 
                  << " (showing first " << rows_to_show << "×" << cols_to_show << ")"
                  << std::endl;
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }
    if (data == nullptr) {
        throw std::invalid_argument("Массив данных не может быть nullptr");
    }

    Matrix mat = create_matrix(rows, cols);
    
    // Копирование данных из массива в матрицу (построчно)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = data[i * cols + j];
        }
    }
    
    return mat;
}
Matrix matrix_transpose(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        throw std::invalid_argument("Матрица пустая или невалидная");

    }

    Matrix result = create_matrix(m.cols, m.rows);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];

        }
    }
    return result;
}
Matrix matrix_submatrix(Matrix m, int start_row, int start_col, int rows, int cols) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        throw std::invalid_argument("Исходная матрица пустая или невалидная");

    }

    if (start_row < 0 || start_col < 0 || rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Параметры должны быть неотрицательными, размеры - положительными");

    }

    if (start_row + rows > m.rows || start_col + cols > m.cols) {
        throw std::invalid_argument("Подматрица выходит за границы исходной матрицы");

    }

    Matrix submatrix =  create_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            submatrix.data[i][j] = m.data[start_row + i][start_col + j];

        }
    }

    return submatrix;
}