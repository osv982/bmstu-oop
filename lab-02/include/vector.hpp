#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "except.hpp"

template<class T> struct Vector {


    //: Создание

    Vector();

    //! Вектор данной размерности
    explicit Vector(size_t);

    //! Конструктор копирования
    explicit Vector(const Vector<T> &);

    //! Конструктор перемещения
    Vector(Vector<T> &&);

    //! Копирование массива
    Vector(T *, size_t);

    //! Конструктор с инициализацией
    Vector(initializer_list<T>);

    //! Нулевой вектор
    static Vector<T> zero(size_t);


    //: Удаление

    virtual ~Vector();


    //: Присваивание

    //! Присваивание с копированием
    Vector<T> &operator =(const Vector<T> &);

    //! Присваивание с перемещением
    Vector<T> &operator =(Vector<T> &&);


    //: Свойства

    //! Количество элементов
    size_t size() const;


    //: Проекции

    //! Элемент по индексу
    T &operator [](size_t);

    //! Значение элемента по индексу
    const T &operator [](size_t) const;

    //! Значение элемента по индексу
    const T &get(size_t) const;

    //! Присваивание по индексу
    void set(size_t, const T &);


    //: Сложение

    //! Сложение со скаляром
    template<class S> Vector<T> &add(const S &);

    //! Сложение со скаляром
    template<class S> Vector<T> &operator +=(const S &);

    //! Сумма вектора и скаляра
    template<class S> decltype(auto) sum(const S &) const;

    //! Сумма вектора и скаляра
    template<class S> decltype(auto) operator +(const S &) const;

    //! Сложение с вектором
    template<class S> Vector<T> &add(const Vector<S> &);

    //! Сложение с вектором
    template<class S> Vector<T> &operator +=(const Vector<S> &);

    //! Сумма векторов
    template<class S> decltype(auto) sum(const Vector<S> &) const;

    //! Сумма векторов
    template<class S> decltype(auto) operator +(const Vector<S> &) const;


    //: Вычитание

    //! Вычитание скаляра
    template<class S> Vector<T> &subtract(const S &);

    //! Вычитание скаляра
    template<class S> Vector<T> &operator -=(const S &);

    //! Разность вектора и скаляра
    template<class S> decltype(auto) difference(const S &) const;

    //! Разность вектора и скаляра
    template<class S> decltype(auto) operator -(const S &) const;

    //! Вычитание вектора
    template<class S> Vector<T> &subtract(const Vector<S> &);

    //! Вычитание вектора
    template<class S> Vector<T> &operator -=(const Vector<S> &);

    //! Разность векторов
    template<class S> decltype(auto) difference(const Vector<S> &) const;

    //! Разность векторов
    template<class S> decltype(auto) operator -(const Vector<S> &) const;


    //: Умножение

    //! Умножение на скаляр
    template<class S> Vector<T> &multiply(const S &);

    //! Умножение на скаляр
    template<class S> Vector<T> &operator *=(const S &);

    //! Произведение вектора и скаляра
    template<class S> decltype(auto) product(const S &) const;

    //! Произведение вектора и скаляра
    template<class S> decltype(auto) operator *(const S &) const;


    //: Деление

    //! Деление на скаляр
    template<class S> Vector<T> &divide(const S &);

    //! Деление на скаляр
    template<class S> Vector<T> &operator /=(const S &);

    //! Частное вектора и скаляра
    template<class S> decltype(auto) quotient(const S &) const;

    //! Частное вектора и скаляра
    template<class S> decltype(auto) operator /(const S &) const;


    //: Сравнение

    //! Проверка на равенство
    template<class S> bool operator ==(const Vector<S> &) const;

    //! Проверка на неравенство
    template<class S> bool operator !=(const Vector<S> &) const;


    //! Итератор
    struct Iterator {

        //! Конструктор
        Iterator(const Vector<T> &, size_t);

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

        //! Массив элементов
        weak_ptr<T[]> m_data;

        //! Количество элементов
        size_t m_size;

        //! Индекс текущего элемента
        size_t m_elem;
    };

    //! Итератор на начало
    Iterator begin();

    //! Итератор на конец
    Iterator end();


    //! Константный итератор
    struct ConstIterator {

        //! Конструктор
        ConstIterator(const Vector<T> &, size_t);

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

        //! Значение текущего элемента
        const T &operator *() const;

        //! Указатель на значение текущего элемента
        const T *operator ->() const;

    private:

        //! Массив элементов
        weak_ptr<T[]> m_data;

        //! Количество элементов
        size_t m_size;

        //! Индекс текущего элемента
        size_t m_elem;
    };

    //! Константный итератор на начало
    ConstIterator begin() const;

    //! Константный итератор на конец
    ConstIterator end() const;


    //: Ввод-вывод

    //! Вывод вектора
    template<class S> friend ostream &operator <<(ostream &, const Vector<S> &);

private:

    //! Массив элементов
    shared_ptr<T[]> m_data;

    //! Количество элементов
    size_t m_size;
};

#include "implementation/vector.hpp"

#endif // VECTOR_HPP