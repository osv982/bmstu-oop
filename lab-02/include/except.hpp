#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

// Класс `exception`
#include <exception>

// Класс `string`
#include <string>

using namespace std;

//! Базовый класс локализуемых исключений
struct WhereException : public exception {

    //! Генерация сообщения об ошибке
    const char *what() const noexcept;

protected:

    //! Создание локализуемого исключения
    explicit WhereException(const char *);

    //! Снабжение описанием
    void describe(const char *);

private:

    //! Сообщение
    string message;
};

//! Ошибка выделения памяти
struct AllocException : public WhereException {
    AllocException(const char *);
};

//! Ошибка разыменования итератора
struct DerefException : public WhereException {
    DerefException(const char *);
};

//! Обработка пустой матрицы
struct EmptyException : public WhereException {
    EmptyException(const char *);
};

//! Выход за область допустимых индексов
struct IndexException : public WhereException {
    IndexException(const char *);
};

//! Несогласованность размерностей
struct MatchException : public WhereException {
    MatchException(const char *);
};

//! Несоответствие формы
struct ShapeException : public WhereException {
    ShapeException(const char *);
};

#endif // EXCEPTION_HPP