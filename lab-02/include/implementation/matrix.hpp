//: Создание

template<class T> Matrix<T>::Matrix()
    : Scales(), m_data(nullptr) {}

template<class T> Matrix<T>::Matrix(size_t rows, size_t cols) : Scales(rows, cols) {
    try { m_data = shared_ptr<Vector<T>[]>(new Vector<T>[rows]); }

    catch (bad_alloc) {
        throw AllocException(__func__);
    }

    for (size_t i = 0; i < rows; i++)
        m_data[i] = Vector<T>(cols);
}

template<class T> Matrix<T>::Matrix(size_t size)
    : Matrix(size, size) {}

template<class T> Matrix<T>::Matrix(const Matrix<T> &matrix) : Matrix(matrix.rows(), matrix.cols()) {
    for (size_t i = 0; i < rows(); i++)
        for (size_t j = 0; j < cols(); j++)
            set(i, j, matrix(i, j));
}

template<class T> Matrix<T>::Matrix(Matrix<T> &&matrix) noexcept
    : Scales(matrix.rows(), matrix.cols()), m_data(matrix.m_data) {}

template<class T> Matrix<T>::Matrix(T **data, size_t rows, size_t cols) : Matrix(rows, cols) {
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            set(i, j, data[i][j]);
}

template<class T> Matrix<T>::Matrix(initializer_list<initializer_list<T>> list) {
    m_rows = list.size();
    m_cols = list.begin()->size();

    try { m_data = shared_ptr<Vector<T>[]>(new Vector<T>[m_rows]); }

    catch(bad_alloc) {
        throw AllocException(__func__);
    }

    for (size_t i = 0; i < m_rows; i++)
        m_data[i] = Vector<T>(m_cols);

    size_t i = 0;

    for (auto row = list.begin(); row != list.end(); ++row, i++) {
        if (row->size() != cols())
            throw MatchException(__func__);

        size_t j = 0;

        for (auto col = row->begin(); col != row->end(); ++col, j++)
            set(i, j, *col);
    } 
}

template<class T> Matrix<T> Matrix<T>::zero(size_t rows, size_t cols) {
    Matrix<T> matrix(rows, cols);

    for (size_t i = 0; i < matrix.rows(); i++)
        for (size_t j = 0; j < matrix.cols(); j++)
            matrix(i, j) = 0;

    return matrix;
}

template<class T> Matrix<T> Matrix<T>::zero(size_t size) {
    return Matrix<T>::zero(size, size);
}

template<class T> Matrix<T> Matrix<T>::unit(size_t size) {
    Matrix<T> matrix = Matrix<T>::zero(size);

    for (size_t k = 0; k < size; k++)
        matrix(k, k) = 1;

    return matrix;
}


//: Удаление

template<class T> Matrix<T>::~Matrix()
    = default;


//: Присваивание

template<class T> Matrix<T> &Matrix<T>::operator =(const Matrix<T> &matrix) {
    return *this = Matrix(matrix);
}

template<class T> Matrix<T> &Matrix<T>::operator =(Matrix<T> &&matrix) {
    m_data = matrix.m_data;

    m_rows = matrix.m_rows;
    m_cols = matrix.m_cols;

    return *this;
}


//: Проекции

template<class T> Vector<T> &Matrix<T>::operator [](size_t i) {
    if (size() == 0)
        throw EmptyException(__func__);

    if (i >= rows())
        throw IndexException(__func__);

    return m_data.get()[i];
}

template<class T> const Vector<T> &Matrix<T>::operator [](size_t i) const {
    if (size() == 0)
        throw EmptyException(__func__);

    if (i >= rows())
        throw IndexException(__func__);

    return m_data.get()[i];
}

template<class T> const Vector<T> &Matrix<T>::get(size_t i) const {
    return (*this)[i];
}

template<class T> void Matrix<T>::set(size_t i, const Vector<T> &vector) {
    (*this)[i] = vector;
}

template<class T> T &Matrix<T>::operator ()(size_t i, size_t j) {
    return (*this)[i][j];
}

template<class T> const T &Matrix<T>::operator ()(size_t i, size_t j) const {
    return (*this)[i][j];
}

template<class T> const T &Matrix<T>::get(size_t i, size_t j) const {
    return (*this)(i, j);
}

template<class T> void Matrix<T>::set(size_t i, size_t j, const T &scalar) {
    (*this)(i, j) = scalar;
}


//: Унарные операции

template<class T> Matrix<T> Matrix<T>::transpose() const {
    if (size() == 0)
        throw EmptyException(__func__);

    Matrix<T> result(cols(), rows());

    for (size_t i = 0; i < rows(); i++)
        for (size_t j = 0; j < cols(); j++)
            result(j, i) = get(i, j);

    return result;
}

template<class T> T Matrix<T>::determinant() const {
    if (size() == 0)
        throw EmptyException(__func__);

    if (rows() != cols())
        throw ShapeException(__func__);

    T result = 0;

    if (size() == 1)
        result = get(0, 0);

    else {
        T sign = 1;

        for (size_t j = 0; j < cols(); j++, sign *= -1)
            result += sign * get(0, j) * minor(0, j).determinant();
    }

    return result;
}

template<class T> Matrix<T> Matrix<T>::inverse() const {
    if (size() == 0)
        throw EmptyException(__func__);

    if (rows() != cols())
        throw ShapeException(__func__);

    Matrix<T> adjugate(rows(), cols()); T sign = 1;

    if (size() == 1)
        adjugate(0, 0) = 1;

    else {
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < cols(); j++) {
                adjugate(i, j) = sign * get(i, j) * minor(i, j).determinant();

                // Знак!
                sign *= -1;
            }
        }
    }

    return adjugate / determinant();
}


//: Сложение

template<class T> template<class S> Matrix<T> &Matrix<T>::add(const S &scalar) {
    return *this = *this + scalar;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator +=(const S &scalar) {
    return add(scalar);
}

template<class T> template<class S> decltype(auto) Matrix<T>::sum(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Matrix<decltype(get(0, 0) + scalar)> result(*this);

    for (size_t i = 0; i < result.rows(); i++)
        for (size_t j = 0; j < result.cols(); j++)
            result(i, j) += scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator +(const S &scalar) const {
    return sum(scalar);
}

template<class T> template<class S> Matrix<T> &Matrix<T>::add(const Matrix<S> &matrix) {
    return *this = *this + matrix;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator +=(const Matrix<S> &matrix) {
    return add(matrix);
}

template<class T> template<class S> decltype(auto) Matrix<T>::sum(const Matrix<S> &matrix) const {
    if (size() == 0 || matrix.size() == 0)
        throw EmptyException(__func__);

    if (rows() != matrix.rows() || cols() != matrix.cols())
        throw MatchException(__func__);

    Matrix<decltype(get(0, 0) + matrix(0, 0))> result(*this);

    for (size_t i = 0; i < result.rows(); i++)
        result[i] += matrix[i];

    return result;
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator +(const Matrix<S> &matrix) const {
    return sum(matrix);
}


//: Вычитание

template<class T> template<class S> Matrix<T> &Matrix<T>::subtract(const S &scalar) {
    return *this = *this - scalar;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator -=(const S &scalar) {
    return subtract(scalar);
}

template<class T> template<class S> decltype(auto) Matrix<T>::difference(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Matrix<decltype(get(0, 0) - scalar)> result(*this);

    for (size_t i = 0; i < result.rows(); i++)
        for (size_t j = 0; j < result.cols(); j++)
            result(i, j) -= scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator -(const S &scalar) const {
    return difference(scalar);
}

template<class T> template<class S> Matrix<T> &Matrix<T>::subtract(const Matrix<S> &matrix) {
    return *this = *this - matrix;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator -=(const Matrix<S> &matrix) {
    return subtract(matrix);
}

template<class T> template<class S> decltype(auto) Matrix<T>::difference(const Matrix<S> &matrix) const {
    if (size() == 0 || matrix.size() == 0)
        throw EmptyException(__func__);

    if (rows() != matrix.rows() || cols() != matrix.cols())
        throw MatchException(__func__);

    Matrix<decltype(get(0, 0) - matrix(0, 0))> result(*this);

    for (size_t i = 0; i < result.rows(); i++)
        result[i] -= matrix[i];

    return result;
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator -(const Matrix<S> &matrix) const {
    return difference(matrix);
}


//: Умножение

template<class T> template<class S> Matrix<T> &Matrix<T>::multiply(const S &scalar) {
    return *this = *this * scalar;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator *=(const S &scalar) {
    return multiply(scalar);
}

template<class T> template<class S> decltype(auto) Matrix<T>::product(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Matrix<decltype(get(0, 0) * scalar)> result(*this);

    for (size_t i = 0; i < result.rows(); i++)
        result[i] *= scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator *(const S &scalar) const {
    return product(scalar);
}

template<class T> template<class S> Matrix<T> &Matrix<T>::multiply(const Matrix<S> &matrix) {
    return *this = *this * matrix;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator *=(const Matrix<S> &matrix) {
    return multiply(matrix);
}

template<class T> template<class S> decltype(auto) Matrix<T>::product(const Matrix<S> &matrix) const {
    if (size() == 0 || matrix.size() == 0)
        throw EmptyException(__func__);

    if (rows() != matrix.cols() || cols() != matrix.rows())
        throw MatchException(__func__);

    Matrix<decltype(get(0, 0) * matrix(0, 0))> result(rows(), rows());

    for (size_t i = 0; i < result.rows(); i++) {
        for (size_t j = 0; j < result.cols(); j++) {
            result(i, j) = 0;

            for (size_t k = 0; k < cols(); k++)
                result(i, j) += get(i, k) * matrix(k, j);
        }
    }

    return result;
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator *(const Matrix<S> &matrix) const {
    return product(matrix);
}


//: Деление

template<class T> template<class S> Matrix<T> &Matrix<T>::divide(const S &scalar) {
    return *this = *this / scalar;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator /=(const S &scalar) {
    return divide(scalar);
}

template<class T> template<class S> decltype(auto) Matrix<T>::quotient(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Matrix<decltype(get(0, 0) / scalar)> result(*this);

    for (size_t i = 0; i < result.rows(); i++)
        result[i] /= scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator /(const S &scalar) const {
    return quotient(scalar);
}

template<class T> template<class S> Matrix<T> &Matrix<T>::divide(const Matrix<S> &matrix) {
    return *this = *this / matrix;
}

template<class T> template<class S> Matrix<T> &Matrix<T>::operator /=(const Matrix<S> &matrix) {
    return divide(matrix);
}

template<class T> template<class S> decltype(auto) Matrix<T>::quotient(const Matrix<S> &matrix) const {
    if (size() == 0 || matrix.size() == 0)
        throw EmptyException(__func__);

    if (rows() != cols() || matrix.rows() != matrix.cols())
        throw ShapeException(__func__);

    if (size() != matrix.size())
        throw MatchException(__func__);

    return product(matrix.inverse());
}

template<class T> template<class S> decltype(auto) Matrix<T>::operator /(const Matrix<S> &matrix) const {
    return quotient(matrix);
}


//: Сравнение

template<class T> template<class S> bool Matrix<T>::operator ==(const Matrix<S> &matrix) const {
    if (size() == 0 || matrix.size() == 0)
        throw EmptyException(__func__);

    if (rows() != matrix.rows() || cols() != matrix.cols())
        throw MatchException(__func__);

    bool result = true;

    for (size_t i = 0; i < size(); i++)
        if (get[i] != matrix[i])
            result = false;

    return result;
}

template<class T> template<class S> bool Matrix<T>::operator !=(const Matrix<S> &matrix) const {
    return !(*this == matrix);
}


//: Закрытые методы

template<class T> Matrix<T> Matrix<T>::minor(size_t m, size_t n) const {
    Matrix<T> res(rows() - 1, cols() - 1);

    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++)
            res(i, j) = get(i, j);

        for (size_t j = n + 1; j < cols(); j++)
            res(i, j - 1) = get(i, j);
    }

    for (size_t i = m + 1; i < rows(); i++) {
        for (size_t j = 0; j < n; j++)
            res(i - 1, j) = get(i, j);

        for (size_t j = n + 1; j < cols(); j++)
            res(i - 1, j - 1) = get(i, j);
    }

    return res;
}


//: Итератор

template<class T> Matrix<T>::Iterator::Iterator(const Matrix<T> &matrix, size_t elem)
    : m_data(matrix.m_data), m_rows(matrix.m_rows), m_cols(matrix.m_cols), m_elem(elem) {}

template<class T> Matrix<T>::Iterator::Iterator(const Iterator &iterator)
    : m_data(iterator.m_data), m_rows(iterator.m_rows), m_cols(iterator.m_cols), m_elem(iterator.m_elem) {}

template<class T> Matrix<T>::Iterator::Iterator(Iterator &&iterator)
    : m_data(iterator.m_data), m_rows(iterator.m_rows), m_cols(iterator.m_cols), m_elem(iterator.m_elem) {}

template<class T> Matrix<T>::Iterator::operator bool() const {
    return m_data.expired();
}

template<class T> bool Matrix<T>::Iterator::operator ==(const Matrix<T>::Iterator &iterator) const {
    return m_elem == iterator.m_elem;
}

template<class T> bool Matrix<T>::Iterator::operator !=(const Matrix<T>::Iterator &iterator) const {
    return m_elem != iterator.m_elem;
}

template<class T> typename Matrix<T>::Iterator &Matrix<T>::Iterator::operator ++() {
    if (m_elem < m_rows * m_cols) ++m_elem; return *this;
}

template<class T> typename Matrix<T>::Iterator Matrix<T>::Iterator::operator ++(int) {
    Matrix<T>::Iterator previous = Matrix<T>::Iterator(*this); ++(*this); return previous;
}

template<class T> typename Matrix<T>::Iterator &Matrix<T>::Iterator::operator --() {
    if (m_elem > 0) --m_elem; return *this;
}

template<class T> typename Matrix<T>::Iterator Matrix<T>::Iterator::operator --(int) {
    Matrix<T>::Iterator previous = Matrix<T>::Iterator(*this); --(*this); return previous;
}

template<class T> T &Matrix<T>::Iterator::operator *() {
    if (m_data.expired())
        throw EmptyException(__func__);

    if (m_elem == m_rows * m_cols)
        throw DerefException(__func__);

    return m_data.lock().get()[m_elem / m_cols][m_elem % m_cols];
}

template<class T> const T &Matrix<T>::Iterator::operator *() const {
    if (m_data.expired())
        throw EmptyException(__func__);

    if (m_elem == m_rows * m_cols)
        throw DerefException(__func__);

    return m_data.lock().get()[m_elem / m_cols][m_elem % m_cols];
}

template<class T> T *Matrix<T>::Iterator::operator ->() {
    if (m_data.expired())
        throw EmptyException(__func__);

    if (m_elem == m_rows * m_cols)
        throw DerefException(__func__);

    return &m_data.lock().get()[m_elem / m_cols][m_elem % m_cols];
}

template<class T> const T *Matrix<T>::Iterator::operator ->() const {
    if (m_data.expired())
        throw EmptyException(__func__);

    if (m_elem == m_rows * m_cols)
        throw DerefException(__func__);

    return &m_data.lock().get()[m_elem / m_cols][m_elem % m_cols];
}

template<class T> typename Matrix<T>::Iterator Matrix<T>::begin() {
    return Matrix<T>::Iterator(*this, 0);
}

template<class T> typename Matrix<T>::Iterator Matrix<T>::end() {
    return Matrix<T>::Iterator(*this, size());
}


//: Константный итератор

template<class T> Matrix<T>::ConstIterator::ConstIterator(const Matrix<T> &matrix, size_t elem)
    : m_data(matrix.m_data), m_rows(matrix.m_rows), m_cols(matrix.m_cols), m_elem(elem) {}

template<class T> Matrix<T>::ConstIterator::ConstIterator(const ConstIterator &iterator)
    : m_data(iterator.m_data), m_rows(iterator.m_rows), m_cols(iterator.m_cols), m_elem(iterator.m_elem) {}

template<class T> Matrix<T>::ConstIterator::ConstIterator(ConstIterator &&iterator)
    : m_data(iterator.m_data), m_rows(iterator.m_rows), m_cols(iterator.m_cols), m_elem(iterator.m_elem) {}

template<class T> Matrix<T>::ConstIterator::operator bool() const {
    return m_data.expired();
}

template<class T> bool Matrix<T>::ConstIterator::operator ==(const Matrix<T>::ConstIterator &iterator) const {
    return m_elem == iterator.m_elem;
}

template<class T> bool Matrix<T>::ConstIterator::operator !=(const Matrix<T>::ConstIterator &iterator) const {
    return m_elem != iterator.m_elem;
}

template<class T> typename Matrix<T>::ConstIterator &Matrix<T>::ConstIterator::operator ++() {
    if (m_elem < m_rows * m_cols) ++m_elem; return *this;
}

template<class T> typename Matrix<T>::ConstIterator Matrix<T>::ConstIterator::operator ++(int) {
    Matrix<T>::ConstIterator previous = Matrix<T>::ConstIterator(*this); ++(*this); return previous;
}

template<class T> typename Matrix<T>::ConstIterator &Matrix<T>::ConstIterator::operator --() {
    if (m_elem > 0) --m_elem; return *this;
}

template<class T> typename Matrix<T>::ConstIterator Matrix<T>::ConstIterator::operator --(int) {
    Matrix<T>::ConstIterator previous = Matrix<T>::ConstIterator(*this); --(*this); return previous;
}

template<class T> const T &Matrix<T>::ConstIterator::operator *() const {
    if (m_data.expired())
        throw EmptyException(__func__);

    if (m_elem == m_rows * m_cols)
        throw DerefException(__func__);

    return m_data.lock().get()[m_elem / m_cols][m_elem % m_cols];
}

template<class T> const T *Matrix<T>::ConstIterator::operator ->() const {
    if (m_data.expired())
        throw EmptyException(__func__);

    if (m_elem == m_rows * m_cols)
        throw DerefException(__func__);

    return &m_data.lock().get()[m_elem / m_cols][m_elem % m_cols];
}

template<class T> typename Matrix<T>::ConstIterator Matrix<T>::begin() const {
    return cbegin();
}

template<class T> typename Matrix<T>::ConstIterator Matrix<T>::end() const {
    return cend();
}

template<class T> typename Matrix<T>::ConstIterator Matrix<T>::cbegin() const {
    return Matrix<T>::ConstIterator(*this, 0);
}

template<class T> typename Matrix<T>::ConstIterator Matrix<T>::cend() const {
    return Matrix<T>::ConstIterator(*this, size());
}

template<class T> ostream &operator <<(ostream &stream, const Matrix<T> &matrix) {
    for (size_t i = 0; i < matrix.rows(); i++)
        stream << matrix[i] << endl;

    return stream;
}