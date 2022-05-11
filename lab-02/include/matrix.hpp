#ifndef MATRIX_HPP
#define MATRIX_HPP

// Ввод-вывод
#include <iostream>

// Умные указатели
#include <memory>

#include "except.hpp"
#include "vector.hpp"
#include "scales.hpp"

template<class T> struct Matrix : public Scales {


    //: Создание

    Matrix();

    //! Прямоугольная матрица
    Matrix(size_t, size_t);

    //! Квадратная матрица
    explicit Matrix(size_t);

    //! Конструктор копирования
    explicit Matrix(const Matrix<T> &);

    //! Конструктор перемещения
    Matrix(Matrix<T> &&) noexcept;

    //! Копирование массива
    Matrix(T **, size_t, size_t);

    //! Конструктор с инициализацией
    Matrix(initializer_list<initializer_list<T>>);

    //! Прямоугольная нулевая матрица
    static Matrix<T> zero(size_t, size_t);

    //! Квадратная нулевая матрица
    static Matrix<T> zero(size_t);

    //! Единичная матрица
    static Matrix<T> unit(size_t);


    //: Удаление

    virtual ~Matrix();


    //: Присваивание

    //! Присваивание с копированием
    Matrix<T> &operator =(const Matrix<T> &);

    //! Присваивание с перемещением 
    Matrix<T> &operator =(Matrix<T> &&);


    //: Проекции

    //! Строка по индексу
    Vector<T> &operator [](size_t);

    //! Значение строки по индексу
    const Vector<T> &operator [](size_t) const;

    //! Значение строки по индексу
    const Vector<T> &get(size_t) const;

    //! Присваивание строки по индексу
    void set(size_t, const Vector<T> &);

    //! Элемент по индексу
    T &operator ()(size_t, size_t);

    //! Значение элемента по индексу
    const T &operator ()(size_t, size_t) const;

    //! Значение элемента по индексу
    const T &get(size_t, size_t) const;

    //! Присваивание элемента по индексу
    void set(size_t, size_t, const T &);


    //: Унарные операции

    //! Транспонированная матрица
    Matrix<T> transpose() const;

    //! Определитель
    T determinant() const;

    //! Обратная матрица
    Matrix<T> inverse() const;


    //: Сложение

    //! Сложение со скаляром
    template<class S> Matrix<T> &add(const S &);

    //! Сложение со скаляром
    template<class S> Matrix<T> &operator +=(const S &);

    //! Сумма матрицы и скаляра
    template<class S> decltype(auto) sum(const S &) const;

    //! Сумма матрицы и скаляра
    template<class S> decltype(auto) operator +(const S &) const;

    //! Сложение с матрицей
    template<class S> Matrix<T> &add(const Matrix<S> &);

    //! Сложение с матрицей
    template<class S> Matrix<T> &operator +=(const Matrix<S> &);

    //! Сумма матриц
    template<class S> decltype(auto) sum(const Matrix<S> &) const;

    //! Сумма матриц
    template<class S> decltype(auto) operator +(const Matrix<S> &) const;


    //: Вычитание

    //! Вычитание скаляра
    template<class S> Matrix<T> &subtract(const S &);

    //! Вычитание скаляра
    template<class S> Matrix<T> &operator -=(const S &);

    //! Разность матрицы и скаляра
    template<class S> decltype(auto) difference(const S &) const;

    //! Разность матрицы и скаляра
    template<class S> decltype(auto) operator -(const S &) const;

    //! Вычитание матрицы
    template<class S> Matrix<T> &subtract(const Matrix<S> &);

    //! Вычитание матрицы
    template<class S> Matrix<T> &operator -=(const Matrix<S> &);

    //! Разность матриц
    template<class S> decltype(auto) difference(const Matrix<S> &) const;

    //! Разность матриц
    template<class S> decltype(auto) operator -(const Matrix<S> &) const;


    //: Умножение

    //! Умножение на скаляр
    template<class S> Matrix<T> &multiply(const S &);

    //! Умножение на скаляр
    template<class S> Matrix<T> &operator *=(const S &);

    //! Произведение матрицы и скаляра
    template<class S> decltype(auto) product(const S &) const;

    //! Произведение матрицы и скаляра
    template<class S> decltype(auto) operator *(const S &) const;

    //! Умножение на матрицу
    template<class S> Matrix<T> &multiply(const Matrix<S> &);

    //! Умножение на матрицу
    template<class S> Matrix<T> &operator *=(const Matrix<S> &);

    //! Произведение матриц
    template<class S> decltype(auto) product(const Matrix<S> &) const;

    //! Произведение матриц
    template<class S> decltype(auto) operator *(const Matrix<S> &) const;


    //: Деление

    //! Деление на скаляр
    template<class S> Matrix<T> &divide(const S &);

    //! Деление на скаляр
    template<class S> Matrix<T> &operator /=(const S &);

    //! Частное матрицы и скаляра
    template<class S> decltype(auto) quotient(const S &) const;

    //! Частное матрицы и скаляра
    template<class S> decltype(auto) operator /(const S &) const;

    //! Деление на матрицу
    template<class S> Matrix<T>& divide(const Matrix<S> &);

    //! Деление на матрицу
    template<class S> Matrix<T>& operator /=(const Matrix<S> &);

    //! Частное матриц
    template<class S> decltype(auto) quotient(const Matrix<S> &) const;

    //! Частное матриц
    template<class S> decltype(auto) operator /(const Matrix<S> &) const;


    //: Сравнение

    //! Проверка на равенство
    template<class S> bool operator ==(const Matrix<S> &) const;

    //! Проверка на неравенство
    template<class S> bool operator !=(const Matrix<S> &) const;


    //! Итератор
    struct Iterator {

        //! Конструктор
        Iterator(const Matrix<T> &, size_t);

        //! Конструктор копирования
        explicit Iterator(const Iterator &);

        //! Конструктор перемещения
        Iterator(Iterator &&);

        //! Проверка истечения
        operator bool() const;

        //! Проверка на равенство
        bool operator ==(const Iterator &) const;

        //! Проверка на неравенство
        bool operator !=(const Iterator &) const;

        //! Префиксный инкремент
        Iterator &operator ++();

        //! Постфиксный инкремент
        Iterator operator ++(int);

        //! Префиксный декремент
        Iterator &operator --();

        //! Постфиксный декремент
        Iterator operator --(int);

        //! Текущий элемент
        T &operator *();

        //! Значение текущего элемента
        const T &operator *() const;

        //! Указатель на текущий элемент
        T *operator ->();

        //! Указатель на значение текущего элемента
        const T *operator ->() const;

    private:

        //! Массив строк
        weak_ptr<Vector<T>[]> m_data;

        //! Количество строк
        size_t m_rows;

        //! Количество столбцов
        size_t m_cols;

        //! Текущий элемент
        size_t m_elem;
    };

    //! Итератор на начало
    Iterator begin();

    //! Итератор на конец
    Iterator end();


    //! Константный итератор
    struct ConstIterator {

        //! Конструктор
        ConstIterator(const Matrix<T> &, size_t);

        //! Конструктор копирования
        explicit ConstIterator(const ConstIterator &);

        //! Конструктор перемещения
        ConstIterator(ConstIterator &&);

        //! Проверка истечения
        operator bool() const;

        //! Проверка на равенство
        bool operator ==(const ConstIterator &) const;

        //! Проверка на неравенство
        bool operator !=(const ConstIterator &) const;

        //! Префиксный инкремент
        ConstIterator &operator ++();

        //! Постфиксный инкремент
        ConstIterator operator ++(int);

        //! Префиксный декремент
        ConstIterator &operator --();

        //! Постфиксный декремент
        ConstIterator operator --(int);

        //! Значение текущей строки
        const T &operator *() const;

        //! Указатель на значение текущей строки
        const T *operator ->() const;

    private:

        //! Массив строк
        weak_ptr<Vector<T>[]> m_data;

        //! Количество строк
        size_t m_rows;

        //! Количество столбцов
        size_t m_cols;

        //! Текущий элемент
        size_t m_elem;
    };

    //! Константный итератор на начало
    ConstIterator begin() const;

    //! Константный итератор на конец
    ConstIterator end() const;

    //! Константный итератор на начало
    ConstIterator cbegin() const;

    //! Константный итератор на конец
    ConstIterator cend() const;


    //: Ввод-вывод

    //! Вывод матрицы
    template<class S> friend ostream &operator <<(ostream &, const Matrix<S> &);

private:

    //! Массив строк
    shared_ptr<Vector<T>[]> m_data;

    //! Минор по индексу
    Matrix<T> minor(size_t, size_t) const;
};

#include "implementation/matrix.hpp"

#endif // MATRIX_HPP