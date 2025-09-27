#include <iostream>
#include <cassert>
#include "matrix.h"

void test_create_and_free() {
    Matrix m = create_matrix(2, 2);
    assert(m.rows == 2);
    assert(m.cols == 2);
    assert(m.data != nullptr);
    free_matrix(m);
    std::cout << "test_create_and_free: PASSED" << std::endl;

}

void test_matrix_addition() {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_add(A, B);

    assert(C.data[0][0] == 6);
    assert(C.data[0][1] == 8);
    assert(C.data[1][0] == 10);
    assert(C.data[1][1] == 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    std::cout << "test_matrix_addition: PASSED" << std::endl;

}

void test_matrix_multiply() {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_multiply(A, B);

    assert(C.data[0][0] == 19); // 1*5 + 2*7 
    assert(C.data[0][1] == 22); // 1*6 + 2*8
    assert(C.data[1][0] == 43);
    assert(C.data[1][1] == 50);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    std::cout << "test_matrix_multiply: PASSED" << std::endl;

}

void test_error_handling() {
    try {
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(3, 3);
        Matrix result = matrix_add(A, B);

        free_matrix(A);
        free_matrix(B);
        free_matrix(result);
        assert(false);

    } catch (const std::exception& e) {
        std::cout << "test_error_handling addition: PASSED" << std::endl;


    }

    try {
        Matrix A = create_matrix(2, 3);
        Matrix B = create_matrix(2, 3);
        Matrix result = matrix_multiply(A, B);

        free_matrix(A);
        free_matrix(B);
        free_matrix(result);
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "test_error_handling multiplication: PASSED" << std::endl;
    }
}

void test_matrix_transpose() {
    double arr[] = {1, 2, 3, 4, 5, 6};
    Matrix A = matrix_from_array(arr, 2, 3);

    Matrix T = matrix_transpose(A);
    assert(T.rows == 3);
    assert(T.cols == 2);
    assert(T.data[0][0] == 1); assert(T.data[0][1] == 4);
    assert(T.data[1][0] == 2); assert(T.data[1][1] == 5);
    assert(T.data[2][0] == 3); assert(T.data[2][1] == 6);

    free_matrix(A);
    free_matrix(T);
    std::cout << "test_matrix_transpose: PASSED" << std::endl;
}

int main () {
    test_create_and_free();
    test_matrix_addition();
    test_matrix_multiply();
    test_error_handling();
    test_matrix_transpose();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}