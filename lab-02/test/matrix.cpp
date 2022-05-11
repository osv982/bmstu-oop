#include "CppUTest/TestHarness.h"

// Генератор
#include <cstdlib>

// Тестируемый модуль
#include "matrix.hpp"

//! Генератор случайных матриц
Matrix<int> arbitrary(size_t rows, size_t cols) {
    Matrix<int> a(rows, cols);

    for (size_t i = 0; i < a.rows(); i++)
        for (size_t j = 0; j < a.cols(); j++)
            a(i, j) = std::rand() % 1000;

    return a;
}

TEST_GROUP(MatrixAssign) {};

TEST(MatrixAssign, Copy) {
    Matrix<int> a = arbitrary(2, 3), b;

    b = a;

    CHECK_EQUAL(a.rows(), b.rows());
    CHECK_EQUAL(a.cols(), b.cols());

    for (size_t i = 0; i < a.rows(); i++)
        for (size_t j = 0; j < a.cols(); j++)
            CHECK_EQUAL(a(i, j), b(i, j));
}

TEST(MatrixAssign, Move) {
    Matrix<int> a = Matrix<int>::zero(2, 3);

    CHECK_EQUAL(2, a.rows());
    CHECK_EQUAL(3, a.cols());

    for (size_t i = 0; i < a.rows(); i++)
        for (size_t j = 0; j < a.cols(); j++)
            CHECK_EQUAL(0, a(i, j));
}

TEST_GROUP(MatrixAdd) {};

TEST(MatrixAdd, MatrixRandMatrixZero) {
    Matrix<int> a = arbitrary(2, 3), b = Matrix<int>::zero(2, 3), c = a + b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(a.cols(), c.cols());

    CHECK_EQUAL(b.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(a(i, j), c(i, j));
}

TEST(MatrixAdd, MatrixZeroMatrixRand) {
    Matrix<int> a = Matrix<int>::zero(2, 3), b = arbitrary(2, 3), c = a + b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(a.cols(), c.cols());

    CHECK_EQUAL(b.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(b(i, j), c(i, j));
}

TEST(MatrixAdd, MatrixRandMatrixRand) {
    Matrix<int> a = arbitrary(2, 3), b = arbitrary(2, 3), c = a + b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(a.cols(), c.cols());

    CHECK_EQUAL(b.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(a(i, j) + b(i, j), c(i, j));
}

TEST(MatrixAdd, Empty) {
    Matrix<int> a = arbitrary(2, 3), b;

    CHECK_THROWS(EmptyException, a + b);
    CHECK_THROWS(EmptyException, b + a);
    CHECK_THROWS(EmptyException, b + b);
}

TEST(MatrixAdd, Match) {
    Matrix<int> a = arbitrary(2, 3), b = arbitrary(3, 2);

    CHECK_THROWS(MatchException, a + b);
    CHECK_THROWS(MatchException, b + a);
}

TEST_GROUP(MatrixSubtract) {};

TEST(MatrixSubtract, MatrixRandMatrixZero) {
    Matrix<int> a = arbitrary(2, 3), b = Matrix<int>::zero(2, 3), c = a - b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(a.cols(), c.cols());

    CHECK_EQUAL(b.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(a(i, j), c(i, j));
}

TEST(MatrixSubtract, MatrixZeroMatrixRand) {
    Matrix<int> a = Matrix<int>::zero(2, 3), b = arbitrary(2, 3), c = a - b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(a.cols(), c.cols());

    CHECK_EQUAL(b.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(-b(i, j), c(i, j));
}

TEST(MatrixSubtract, MatrixRandMatrixRand) {
    Matrix<int> a = arbitrary(2, 3), b = arbitrary(2, 3), c = a - b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(a.cols(), c.cols());

    CHECK_EQUAL(b.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(a(i, j) - b(i, j), c(i, j));
}

TEST(MatrixSubtract, Empty) {
    Matrix<int> a = arbitrary(2, 3), b;

    CHECK_THROWS(EmptyException, a - b);
    CHECK_THROWS(EmptyException, b - a);
    CHECK_THROWS(EmptyException, b - b);
}

TEST(MatrixSubtract, Match) {
    Matrix<int> a = arbitrary(2, 3), b = arbitrary(3, 2);

    CHECK_THROWS(MatchException, a - b);
    CHECK_THROWS(MatchException, b - a);
}

TEST_GROUP(MatrixMultiply) {};

TEST(MatrixMultiply, MatrixRandScalarZero) {
    Matrix<int> a = arbitrary(5, 6), b = a * 0;

    CHECK_EQUAL(a.rows(), b.rows());
    CHECK_EQUAL(b.cols(), b.cols());

    for (size_t i = 0; i < b.rows(); i++)
        for (size_t j = 0; j < b.cols(); j++)
            CHECK_EQUAL(0, b(i, j));
}

TEST(MatrixMultiply, MatrixRandScalarUnit) {
    Matrix<int> a = arbitrary(5, 6), b = a * 1;

    CHECK_EQUAL(a.rows(), b.rows());
    CHECK_EQUAL(b.cols(), b.cols());

    for (size_t i = 0; i < b.rows(); i++)
        for (size_t j = 0; j < b.cols(); j++)
            CHECK_EQUAL(a(i, j), b(i, j));
}

TEST(MatrixMultiply, MatrixRandScalarRand) {
    Matrix<int> a = arbitrary(5, 6), b = a * 7;

    CHECK_EQUAL(a.rows(), b.rows());
    CHECK_EQUAL(b.cols(), b.cols());

    for (size_t i = 0; i < b.rows(); i++)
        for (size_t j = 0; j < b.cols(); j++)
            CHECK_EQUAL(a(i, j) * 7, b(i, j));
}

TEST(MatrixMultiply, MatrixRandMatrixZero) {
    Matrix<int> a = arbitrary(4, 4), b = Matrix<int>::zero(4, 4), c = a * b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(0, c(i, j));
}

TEST(MatrixMultiply, MatrixZeroMatrixRand) {
    Matrix<int> a = Matrix<int>::zero(4, 4), b = arbitrary(4, 4), c = a * b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(0, c(i, j));
}

TEST(MatrixMultiply, MatrixRandMatrixUnit) {
    Matrix<int> a = arbitrary(4, 4), b = Matrix<int>::unit(4), c = a * b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(a(i, j), c(i, j));
}

TEST(MatrixMultiply, MatrixUnitMatrixRand) {
    Matrix<int> a = Matrix<int>::unit(4), b = arbitrary(4, 4), c = a * b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < c.rows(); i++)
        for (size_t j = 0; j < c.cols(); j++)
            CHECK_EQUAL(b(i, j), c(i, j));
}

TEST(MatrixMultiply, MatrixRandMatrixRand) {
    Matrix<double> a = {
        { 0.0, 1.0, 2.0 },
        { 1.0, 2.0, 3.0 }
    };

    Matrix<double> b = {
        { 0.0, 1.0 },
        { 1.0, 2.0 },
        { 2.0, 3.0 }
    };

    Matrix<double> c = a * b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    CHECK_EQUAL( 5.0, c(0, 0));
    CHECK_EQUAL( 8.0, c(0, 1));

    CHECK_EQUAL( 8.0, c(1, 0));
    CHECK_EQUAL(14.0, c(1, 1));
}

TEST(MatrixMultiply, Empty) {
    Matrix<int> a = arbitrary(2, 3), b;

    CHECK_THROWS(EmptyException, b * 2);

    CHECK_THROWS(EmptyException, a * b);
    CHECK_THROWS(EmptyException, b * a);
    CHECK_THROWS(EmptyException, b * b);
}

TEST(MatrixMultiply, Match) {
    Matrix<int> a = arbitrary(2, 3), b = arbitrary(2, 3);

    CHECK_THROWS(MatchException, a * b);
    CHECK_THROWS(MatchException, b * a);
}

TEST_GROUP(MatrixDivide) {};

TEST(MatrixDivide, MatrixRandScalarUnit) {
    Matrix<int> a = arbitrary(2, 3), b = a / 1;

    CHECK_EQUAL(a.rows(), b.rows());
    CHECK_EQUAL(a.cols(), b.cols());

    for (size_t i = 0; i < b.rows(); i++)
        for (size_t j = 0; j < b.cols(); j++)
            CHECK_EQUAL(a(i, j), b(i, j));
}

TEST(MatrixDivide, MatrixRandScalarRand) {
    Matrix<int> a = arbitrary(2, 3), b = a / 4;

    CHECK_EQUAL(a.rows(), b.rows());
    CHECK_EQUAL(a.cols(), b.cols());

    for (size_t i = 0; i < b.rows(); i++)
        for (size_t j = 0; j < b.cols(); j++)
            CHECK_EQUAL(a(i, j) / 4, b(i, j));
}

TEST(MatrixDivide, MatrixRandMatrixUnit) {
    Matrix<int> a = arbitrary(3, 3), b = Matrix<int>::unit(3), c = a / b;

    CHECK_EQUAL(a.rows(), c.rows());
    CHECK_EQUAL(a.cols(), c.cols());

    CHECK_EQUAL(b.rows(), c.rows());
    CHECK_EQUAL(b.cols(), c.cols());

    for (size_t i = 0; i < b.rows(); i++)
        for (size_t j = 0; j < b.cols(); j++)
            CHECK_EQUAL(a(i, j), c(i, j));
}

TEST(MatrixDivide, Empty) {
    Matrix<int> a = arbitrary(2, 3), b;

    CHECK_THROWS(EmptyException, b / 2);

    CHECK_THROWS(EmptyException, a / b);
    CHECK_THROWS(EmptyException, b / a);
    CHECK_THROWS(EmptyException, b / b);
}

TEST(MatrixDivide, Match) {
    Matrix<int> a = arbitrary(2, 2), b = arbitrary(3, 3);

    CHECK_THROWS(MatchException, a / b);
    CHECK_THROWS(MatchException, b / a);
}

TEST(MatrixDivide, Shape) {
    Matrix<int> a = arbitrary(2, 3), b = arbitrary(2, 3);

    CHECK_THROWS(ShapeException, a / b);
    CHECK_THROWS(ShapeException, b / a);
}

TEST_GROUP(Invert) {};

TEST(Invert, Singleton) {
    Matrix<int> a = arbitrary(1, 1);
    CHECK_EQUAL(1 / a(0, 0), a.inverse()(0, 0));
}

TEST(Invert, Unit) {
    Matrix<int> a = Matrix<int>::unit(3), b = a.inverse();

    CHECK_EQUAL(a.rows(), b.rows());
    CHECK_EQUAL(a.cols(), b.cols());

    for (size_t i = 0; i < b.rows(); i++)
        for (size_t j = 0; j < b.cols(); j++)
            CHECK_EQUAL(a(i, j), b(i, j));
}

TEST_GROUP(Determinant) {};

TEST(Determinant, Singleton) {
    Matrix<int> a = arbitrary(1, 1);
    CHECK_EQUAL(a(0, 0), a.determinant());
}

TEST(Determinant, Zero) {
    Matrix<int> a = Matrix<int>::zero(2);
    CHECK_EQUAL(0, a.determinant());
}

TEST(Determinant, Unit) {
    Matrix<int> a = Matrix<int>::unit(3);
    CHECK_EQUAL(1, a.determinant());
}

TEST(Determinant, Rand) {
    Matrix<int> a = {
        { 0, 2 },
        { 3, 1 },
    };

    CHECK_EQUAL(-6, a.determinant());
}

TEST_GROUP(MatrixIterate) {};

TEST(MatrixIterate, End) {
    Matrix<int> a = arbitrary(2, 3);
    CHECK_THROWS(DerefException, *a.end());
}

TEST(MatrixIterate, Mutable) {
    Matrix<int> a = arbitrary(2, 3);

    for (auto it = a.begin(); it != a.end(); it++)
        *it = 42;

    for (auto it = a.begin(); it != a.end(); it++)
        CHECK_EQUAL(42, *it);
}

TEST(MatrixIterate, Immutable) {
        Matrix<int> a = arbitrary(2, 3);

    for (auto it = a.begin(); it != a.end(); it++)
        *it = 42;

    const Matrix<int> &b = a;

    for (auto it = b.begin(); it != b.end(); it++)
        CHECK_EQUAL(42, *it);
}