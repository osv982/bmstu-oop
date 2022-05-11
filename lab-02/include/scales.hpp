#ifndef SCALES_HPP
#define SCALES_HPP

struct Scales {

    //: Удаление

    virtual ~Scales();


    //: Свойства

    //! Количество строк
    size_t rows() const;

    //! Количество столбцов
    size_t cols() const;

    //! Количество элементов
    size_t size() const;

protected:


    //: Создание

    Scales();

    //! Размеры прямоугольника
    Scales(size_t, size_t);

    //! Размеры квадрата
    explicit Scales(size_t);


    //: Данные

    //! Количество строк
    size_t m_rows;

    //! Количество столбцов
    size_t m_cols;
};


//: Создание

Scales::Scales()
    : Scales(0) {}

Scales::Scales(size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols) {}

Scales::Scales(size_t size)
    : Scales(size, size) {}


//: Удаление

Scales::~Scales()
    = default;


//: Свойства

size_t Scales::rows() const {
    return m_rows;
}

size_t Scales::cols() const {
    return m_cols;
}

size_t Scales::size() const {
    return rows() * cols();
}

#endif // SCALES_HPP