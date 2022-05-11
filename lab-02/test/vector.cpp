#include "CppUTest/TestHarness.h"

// Генератор
#include <cstdlib>

// Тестируемый модуль
#include "vector.hpp"

//! Генератор случайных векторов
Vector<int> arbitrary(size_t size) {
    Vector<int> vector(size);

    for (size_t i = 0; i < vector.size(); i++)
        vector[i] = std::rand() % 1000;

    return vector;
}

TEST_GROUP(Construct) {};

TEST(Construct, Empty) {
    Vector<int> u;

    CHECK_EQUAL(0, u.size());
}

TEST(Construct, Uninitialized) {
    Vector<int> u(42);

    CHECK_EQUAL(42, u.size());
}

TEST(Construct, Copy) {
    Vector<int> u = arbitrary(3), v(u);

    CHECK_EQUAL(u.size(), v.size());

    for (size_t i = 0; i < v.size(); i++)
        CHECK_EQUAL(u[i], v[i]);
}

TEST(Construct, Move) {
    Vector<int> u = Vector<int>::zero(2);

    CHECK_EQUAL(2, u.size());

    for (size_t i = 0; i < u.size(); i++)
        CHECK_EQUAL(0, u[i]);
}

TEST_GROUP(Assign) {};

TEST(Assign, Move) {
    Vector<int> u = arbitrary(42), v = Vector<int>(u);

    CHECK_EQUAL(42, v.size());

    for (size_t i = 0; i < v.size(); i++)
        CHECK_EQUAL(u[i], v[i]);
}

TEST_GROUP(Get) {};

TEST(Get, Odd) {
    Vector<int> vector = arbitrary(42);
    CHECK_THROWS(IndexException, vector[42]);
}

TEST_GROUP(Compare) {};

TEST(Compare, Same) {
    Vector<int> a = arbitrary(42), b(a);

    CHECK_EQUAL(1, a == b);
    CHECK_EQUAL(0, a != b);
}

TEST(Compare, Different) {
    Vector<int> a = arbitrary(42), b(a); b[0] += 1;

    CHECK_EQUAL(0, a == b);
    CHECK_EQUAL(1, a != b);
}

TEST(Compare, Empty) {
    Vector<int> u = arbitrary(1), v;

    CHECK_THROWS(EmptyException, u == v);
    CHECK_THROWS(EmptyException, u != v);

    CHECK_THROWS(EmptyException, v == u);
    CHECK_THROWS(EmptyException, v != u);

    CHECK_THROWS(EmptyException, v == v);
    CHECK_THROWS(EmptyException, v != v);
}

TEST(Compare, Match) {
    Vector<int> u = arbitrary(2), v = arbitrary(3);

    CHECK_THROWS(MatchException, u == v);
    CHECK_THROWS(MatchException, u != v);

    CHECK_THROWS(MatchException, v == u);
    CHECK_THROWS(MatchException, v != u);
}

TEST_GROUP(VectorAdd) {};

TEST(VectorAdd, VectorRandVectorZero) {
    Vector<int> a = arbitrary(42), b = Vector<int>::zero(42), c = a + b;

    CHECK_EQUAL(42, c.size());

    for (size_t i = 0; i < c.size(); i++)
        CHECK_EQUAL(a[i], c[i]);
}

TEST(VectorAdd, VectorZeroVectorRand) {
    Vector<int> a = Vector<int>::zero(42), b = arbitrary(42), c = a + b;

    CHECK_EQUAL(42, c.size());

    for (size_t i = 0; i < c.size(); i++)
        CHECK_EQUAL(b[i], c[i]);
}

TEST(VectorAdd, VectorRandVectorRand) {
    Vector<int> a = arbitrary(42), b = arbitrary(42), c = a + b;

    CHECK_EQUAL(42, c.size());

    for (size_t i = 0; i < c.size(); i++)
        CHECK_EQUAL(a[i] + b[i], c[i]);
}

TEST(VectorAdd, Empty) {
    Vector<int> u = arbitrary(1), v;

    CHECK_THROWS(EmptyException, u + v);
    CHECK_THROWS(EmptyException, v + u);
    CHECK_THROWS(EmptyException, v + v);
}

TEST(VectorAdd, Match) {
    Vector<int> u = arbitrary(2), v = arbitrary(3);

    CHECK_THROWS(MatchException, u + v);
    CHECK_THROWS(MatchException, v + u);
}

TEST_GROUP(VectorSubtract) {};

TEST(VectorSubtract, VectorRandVectorZero) {
    Vector<int> a = arbitrary(42), b = Vector<int>::zero(42), c = a - b;

    CHECK_EQUAL(42, c.size());

    for (size_t i = 0; i < c.size(); i++)
        CHECK_EQUAL(a[i], c[i]);
}

TEST(VectorSubtract, VectorZeroVectorRand) {
    Vector<int> a = Vector<int>::zero(42), b = arbitrary(42), c = a - b;

    CHECK_EQUAL(42, c.size());

    for (size_t i = 0; i < c.size(); i++)
        CHECK_EQUAL(-b[i], c[i]);
}

TEST(VectorSubtract, VectorRandVectorRand) {
    Vector<int> a = arbitrary(42), b = arbitrary(42), c = a - b;

    CHECK_EQUAL(42, c.size());

    for (size_t i = 0; i < c.size(); i++)
        CHECK_EQUAL(a[i] - b[i], c[i]);
}

TEST(VectorSubtract, Empty) {
    Vector<int> u = arbitrary(1), v;

    CHECK_THROWS(EmptyException, u - v);
    CHECK_THROWS(EmptyException, v - u);
    CHECK_THROWS(EmptyException, v - v);
}

TEST(VectorSubtract, Match) {
    Vector<int> u = arbitrary(2), v = arbitrary(3);

    CHECK_THROWS(MatchException, u - v);
    CHECK_THROWS(MatchException, v - u);
}

TEST_GROUP(VectorMultiply) {};

TEST(VectorMultiply, VectorRandScalarZero) {
    Vector<int> a = arbitrary(42), b = a * 0;

    CHECK_EQUAL(42, b.size());

    for (size_t i = 0; i < b.size(); i++)
        CHECK_EQUAL(0, b[i]);
}

TEST(VectorMultiply, VectorRandScalarUnit) {
    Vector<int> a = arbitrary(42), b = a * 1;

    CHECK_EQUAL(42, b.size());

    for (size_t i = 0; i < b.size(); i++)
        CHECK_EQUAL(a[i], b[i]);
}

TEST(VectorMultiply, VectorRandScalarRand) {
    Vector<int> a = arbitrary(42), b = a * 2;

    CHECK_EQUAL(42, b.size());

    for (size_t i = 0; i < b.size(); i++)
        CHECK_EQUAL(a[i] * 2, b[i]);
}

TEST(VectorMultiply, Empty) {
    Vector<int> u;
    CHECK_THROWS(EmptyException, u * 2);
}

TEST_GROUP(VectorDivide) {};

TEST(VectorDivide, VectorRandScalarUnit) {
    Vector<int> a = arbitrary(42), b = a / 1;

    CHECK_EQUAL(42, b.size());

    for (size_t i = 0; i < b.size(); i++)
        CHECK_EQUAL(a[i], b[i]);
}

TEST(VectorDivide, VectorRandScalarRand) {
    Vector<int> a = arbitrary(42), b = a / 4;

    CHECK_EQUAL(42, b.size());

    for (size_t i = 0; i < b.size(); i++)
        CHECK_EQUAL(a[i] / 4, b[i]);
}

TEST(VectorDivide, Empty) {
    Vector<int> u;

    CHECK_THROWS(EmptyException, u / 2);
}

TEST_GROUP(VectorIterate) {};

TEST(VectorIterate, End) {
    Vector<int> u = arbitrary(42);
    CHECK_THROWS(DerefException, *u.end());
}

TEST(VectorIterate, Mutable) {
    Vector<int> a = arbitrary(4);

    for (auto it = a.begin(); it != a.end(); it++)
        *it = 42;

    for (auto it = a.begin(); it != a.end(); it++)
        CHECK_EQUAL(42, *it);
}

TEST(VectorIterate, Immutable) {
    Vector<int> a = arbitrary(4);

    for (auto it = a.begin(); it != a.end(); it++)
        *it = 42;

    const Vector<int> &b = a;

    for (auto it = b.begin(); it != b.end(); it++)
        CHECK_EQUAL(42, *it);
}