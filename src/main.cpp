#include <iostream>
#include "matrix.h"

int main() {
    try {
        // Тест 1: Создание и вывод матрицы
        std::cout << "=== Тест 1: Создание матрицы ===" << std::endl;
        Matrix A = create_matrix(2, 3);
        A.data[0][0] = 1.5; A.data[0][1] = 2.3; A.data[0][2] = 3.1;
        A.data[1][0] = 4.7; A.data[1][1] = 5.9; A.data[1][2] = 6.2;
        print_matrix(A);

        // Тест 2: Сложение матриц
        std::cout << "\n=== Тест 2: Сложение матриц ===" << std::endl;
        Matrix B = create_matrix(2, 3);
        B.data[0][0] = 0.5; B.data[0][1] = 0.7; B.data[0][2] = 0.9;
        B.data[1][0] = 1.3; B.data[1][1] = 1.1; B.data[1][2] = 0.8;
        
        Matrix C = matrix_add(A, B);
        print_matrix(C);

        // Тест 3: Умножение матриц
        std::cout << "\n=== Тест 3: Умножение матриц ===" << std::endl;
        Matrix D = create_matrix(3, 2);
        D.data[0][0] = 1; D.data[0][1] = 2;
        D.data[1][0] = 3; D.data[1][1] = 4;
        D.data[2][0] = 5; D.data[2][1] = 6;
        
        Matrix E = matrix_multiply(A, D);
        print_matrix(E);

        // Тест 4: Создание из массива
        std::cout << "\n=== Тест 4: Матрица из массива ===" << std::endl;
        double arr[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
        Matrix F = matrix_from_array(arr, 2, 3);
        print_matrix(F);

        // Индивидуальное задание (№13)
        std::cout << "\n=== Тест 5: Выделение подматрицы ===" << std::endl;


        double big_data[] = {
             1.1, 2.2, 3.3, 4.4,
            5.5, 6.6, 7.7, 8.8,
            9.9, 10.1, 11.11, 12.12,
            13.13, 14.14, 15.15, 16.16
        };
        Matrix big_matrix = matrix_from_array(big_data, 4, 4);

        std::cout << "Исходная матрица 4x4:" << std::endl;
        print_matrix(big_matrix);

        Matrix sub = matrix_submatrix(big_matrix, 1, 1, 2, 3);
        std::cout << "Подматрица 2x3 (начиная с [1, 1]:)" << std::endl;
        print_matrix(sub);

        Matrix single_element = matrix_submatrix(big_matrix, 2, 2, 1, 1);
        std::cout << "Подматрица 1x1 (элемент [2, 2]):" << std::endl;
        print_matrix(single_element);


        std::cout << "Исходный элемент [2, 2]:" << big_matrix.data[2][2] << std::endl;
        std::cout << "Элемент подматрицы [0, 0]:" << single_element.data[0][0] << std::endl;


        single_element.data[0][0] = 999.9;
        std::cout << "После изменения подматрицы:" << std::endl;
        std::cout << "Исходный элемент [2, 2]:" << big_matrix.data[2][2] << "(не изменился)" << std::endl;
        std::cout << "элемент подматрицы [0, 0]:" << single_element.data[0][0] << "(изменился)" << std::endl;


        // Освобождение памяти
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
        free_matrix(D);
        free_matrix(E);
        free_matrix(F);
        free_matrix(big_matrix);
        free_matrix(sub);
        free_matrix(single_element);

        std::cout << "\n✅ Все тесты пройдены успешно!" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "❌ Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}