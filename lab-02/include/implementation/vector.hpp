//: Создание

template<class T> Vector<T>::Vector()
    : m_data(nullptr), m_size(0) {}

template<class T> Vector<T>::Vector(size_t size) : m_size(size) {
    try { m_data = shared_ptr<T[]>(new T[size]); }

    catch(bad_alloc) {
        throw AllocException(__func__);
    }
}

template<class T> Vector<T>::Vector(const Vector<T> &vector) : Vector(vector.size()) {
    for (size_t i = 0; i < size(); i++)
        set(i, vector[i]);
}

template<class T> Vector<T>::Vector(Vector<T> &&vector)
    : m_data(vector.m_data), m_size(vector.m_size) {}

template<class T> Vector<T>::Vector(T *data, size_t size) : Vector(size) {
    for (size_t i = 0; i < size; i++)
        set(i, data[i]);
}

template<class T> Vector<T>::Vector(initializer_list<T> list) : Vector(list.size()) {
    size_t i = 0;

    for (auto elem = list.begin(); elem != list.end(); ++elem, i++)
        set(i, *elem);
}

template<class T> Vector<T> Vector<T>::zero(size_t size) {
    Vector<T> vector(size);

    for (size_t i = 0; i < size; i++)
        vector[i] = 0;

    return vector;
}


//: Удаление

template<class T> Vector<T>::~Vector<T>()
    = default;


//: Присваивание

template<class T> Vector<T> &Vector<T>::operator =(const Vector <T> &vector) {
    return *this = Vector(vector);
}

template<class T> Vector<T> &Vector<T>::operator =(Vector<T> &&vector) {
    m_data = vector.m_data;
    m_size = vector.m_size;

    return *this;
}


//: Свойства

template<class T> size_t Vector<T>::size() const {
    return m_size;
}


//: Проекции

template<class T> T &Vector<T>::operator [](size_t i) {
    if (!size())
        throw EmptyException(__func__);

    if (i >= size())
        throw IndexException(__func__);

    return m_data.get()[i];
}

template<class T> const T &Vector<T>::operator [](size_t i) const {
    if (!size())
        throw EmptyException(__func__);

    if (i >= size())
        throw IndexException(__func__);

    return m_data.get()[i];
}

template<class T> const T &Vector<T>::get(size_t i) const {
    return (*this)[i];
}

template<class T> void Vector<T>::set(size_t i, const T &scalar) {
    (*this)[i] = scalar;
}


//: Сложение

template<class T> template<class S> Vector<T> &Vector<T>::add(const S &scalar) {
    return *this = *this + scalar;
}

template<class T> template<class S> Vector<T> &Vector<T>::operator +=(const S &scalar) {
    return add(scalar);
}

template<class T> template<class S> decltype(auto) Vector<T>::sum(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Vector<decltype(get(0) + scalar)> result(*this);

    for (size_t i = 0; i < result.size(); i++)
        result[i] += scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Vector<T>::operator +(const S &scalar) const {
    return sum(scalar);
}

template<class T> template<class S> Vector<T> &Vector<T>::add(const Vector<S> &vector) {
    return *this = *this + vector;
}

template<class T> template<class S> Vector<T> &Vector<T>::operator +=(const Vector<S> &vector) {
    return add(vector);
}

template<class T> template<class S> decltype(auto) Vector<T>::sum(const Vector<S> &vector) const {
    if (size() == 0 || vector.size() == 0)
        throw EmptyException(__func__);

    if (size() != vector.size())
        throw MatchException(__func__);

    Vector<decltype(get(0) + vector[0])> result(*this);

    for (size_t i = 0; i < result.size(); i++)
        result[i] += vector[i];

    return result;
}

template<class T> template<class S> decltype(auto) Vector<T>::operator +(const Vector<S> &vector) const {
    return sum(vector);
}


//: Вычитание

template<class T> template<class S> Vector<T> &Vector<T>::subtract(const S &scalar) {
    return *this = *this - scalar;
}

template<class T> template<class S> Vector<T> &Vector<T>::operator -=(const S &scalar) {
    return subtract(scalar);
}

template<class T> template<class S> decltype(auto) Vector<T>::difference(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Vector<decltype(get(0) - scalar)> result(*this);

    for (size_t i = 0; i < result.size(); i++)
        result[i] -= scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Vector<T>::operator -(const S &scalar) const {
    return difference(scalar);
}

template<class T> template<class S> Vector<T> &Vector<T>::subtract(const Vector<S> &vector) {
    return *this = *this - vector;
}

template<class T> template<class S> Vector<T> &Vector<T>::operator -=(const Vector<S> &vector) {
    return subtract(vector);
}

template<class T> template<class S> decltype(auto) Vector<T>::difference(const Vector<S> &vector) const {
    if (size() == 0 || vector.size() == 0)
        throw EmptyException(__func__);

    if (size() != vector.size())
        throw MatchException(__func__);

    Vector<decltype(get(0) - vector[0])> result(*this);

    for (size_t i = 0; i < result.size(); i++)
        result[i] -= vector[i];

    return result;
}

template<class T> template<class S> decltype(auto) Vector<T>::operator -(const Vector<S> &vector) const {
    return difference(vector);
}


//: Умножение

template<class T> template<class S> Vector<T> &Vector<T>::multiply(const S &scalar) {
    return *this = *this * scalar;
}

template<class T> template<class S> Vector<T> &Vector<T>::operator *=(const S &scalar) {
    return multiply(scalar);
}

template<class T> template<class S> decltype(auto) Vector<T>::product(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Vector<decltype(get(0) * scalar)> result(*this);

    for (size_t i = 0; i < result.size(); i++)
        result[i] *= scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Vector<T>::operator *(const S &scalar) const {
    return product(scalar);
}


//: Деление

template<class T> template<class S> Vector<T> &Vector<T>::divide(const S &scalar) {
    return *this = *this / scalar;
}

template<class T> template<class S> Vector<T> &Vector<T>::operator /=(const S &scalar) {
    return divide(scalar);
}

template<class T> template<class S> decltype(auto) Vector<T>::quotient(const S &scalar) const {
    if (size() == 0)
        throw EmptyException(__func__);

    Vector<decltype(get(0) / scalar)> result(*this);

    for (size_t i = 0; i < result.size(); i++)
        result[i] /= scalar;

    return result;
}

template<class T> template<class S> decltype(auto) Vector<T>::operator /(const S &scalar) const {
    return quotient(scalar);
}


//: Сравнение

template<class T> template<class S> bool Vector<T>::operator ==(const Vector<S> &vector) const {
    if (size() == 0 || vector.size() == 0)
        throw EmptyException(__func__);

    if (size() != vector.size())
        throw MatchException(__func__);

    bool result = true;

    for (size_t i = 0; result && i < size(); i++)
        if (get(i) != vector[i])
            result = false;

    return result;
}

template<class T> template<class S> bool Vector<T>::operator !=(const Vector<S> &vector) const {
    return !(*this == vector);
}


//: Итератор

template<class T> Vector<T>::Iterator::Iterator(const Vector<T> &vector, size_t elem)
    : m_data(vector.m_data), m_size(vector.m_size), m_elem(elem) {}

template<class T> Vector<T>::Iterator::Iterator(const Iterator &iterator)
    : m_data(iterator.m_data), m_size(iterator.m_size), m_elem(iterator.m_elem) {}

template<class T> Vector<T>::Iterator::Iterator(Iterator &&iterator)
    : m_data(iterator.m_data), m_size(iterator.m_size), m_elem(iterator.m_elem) {}

template<class T> Vector<T>::Iterator::operator bool() const {
    return !m_data.expired();
}

template<class T> bool Vector<T>::Iterator::operator ==(const Vector<T>::Iterator &iterator) const {
    return m_elem == iterator.m_elem;
}

template<class T> bool Vector<T>::Iterator::operator !=(const Vector<T>::Iterator &iterator) const {
    return m_elem != iterator.m_elem;
}

template<class T> typename Vector<T>::Iterator &Vector<T>::Iterator::operator ++() {
    if (m_elem < m_size) ++m_elem; return *this;
}

template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator ++(int) {
    Vector<T>::Iterator previous = Vector<T>::Iterator(*this); ++(*this); return previous;
}

template<class T> typename Vector<T>::Iterator &Vector<T>::Iterator::operator --() {
    if (m_elem > 0) --m_elem; return *this;
}

template<class T> typename Vector<T>::Iterator Vector<T>::Iterator::operator --(int) {
    Vector<T>::Iterator previous = Vector<T>::Iterator(*this); --(*this); return previous;
}

template<class T> T &Vector<T>::Iterator::operator *() {
    if (m_elem == m_size)
        throw DerefException(__func__);

    return m_data.lock().get()[m_elem];
}

template<class T> const T &Vector<T>::Iterator::operator *() const {
    if (m_elem == m_size)
        throw DerefException(__func__);

    return m_data.lock().get()[m_elem];
}

template<class T> T *Vector<T>::Iterator::operator ->() {
    if (m_elem == m_size)
        throw DerefException(__func__);

    return &m_data.lock().get()[m_elem];
}

template<class T> const T *Vector<T>::Iterator::operator ->() const {
    if (m_elem == m_size)
        throw DerefException(__func__);

    return &m_data.lock().get()[m_elem];
}

template<class T> typename Vector<T>::Iterator Vector<T>::begin() {
    return Vector<T>::Iterator(*this, 0);
}

template<class T> typename Vector<T>::Iterator Vector<T>::end() {
    return Vector<T>::Iterator(*this, m_size);
}


//: Константный итератор

template<class T> Vector<T>::ConstIterator::ConstIterator(const Vector<T> &vector, size_t elem)
    : m_data(vector.m_data), m_size(vector.m_size), m_elem(elem) {}

template<class T> Vector<T>::ConstIterator::ConstIterator(const ConstIterator &iterator)
    : m_data(iterator.m_data), m_size(iterator.m_size), m_elem(iterator.m_elem) {}

template<class T> Vector<T>::ConstIterator::ConstIterator(ConstIterator &&iterator)
    : m_data(iterator.m_data), m_size(iterator.m_size), m_elem(iterator.m_elem) {}

template<class T> Vector<T>::ConstIterator::operator bool() const {
    return !m_data.expired();
}

template<class T> bool Vector<T>::ConstIterator::operator ==(const Vector<T>::ConstIterator &iterator) const {
    return m_elem == iterator.m_elem;
}

template<class T> bool Vector<T>::ConstIterator::operator !=(const Vector<T>::ConstIterator &iterator) const {
    return m_elem != iterator.m_elem;
}

template<class T> typename Vector<T>::ConstIterator &Vector<T>::ConstIterator::operator ++() {
    if (m_elem < m_size) ++m_elem; return *this;
}

template<class T> typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator ++(int) {
    Vector<T>::ConstIterator previous = Vector<T>::ConstIterator(*this); ++(*this); return previous;
}

template<class T> typename Vector<T>::ConstIterator &Vector<T>::ConstIterator::operator --() {
    if (m_elem > 0) --m_elem; return *this;
}

template<class T> typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator --(int) {
    Vector<T>::ConstIterator previous = Vector<T>::ConstIterator(*this); --(*this); return previous;
}

template<class T> const T &Vector<T>::ConstIterator::operator *() const {
    if (m_elem == m_size)
        throw DerefException(__func__);

    return m_data.lock().get()[m_elem];
}

template<class T> const T *Vector<T>::ConstIterator::operator ->() const {
    if (m_elem == m_size)
        throw DerefException(__func__);

    return &m_data.lock().get()[m_elem];
}

template<class T> typename Vector<T>::ConstIterator Vector<T>::begin() const {
    return Vector<T>::ConstIterator(*this, 0);
}

template<class T> typename Vector<T>::ConstIterator Vector<T>::end() const {
    return Vector<T>::ConstIterator(*this, m_size);
}


//: Ввод-вывод

template<class T> ostream &operator <<(ostream &stream, const Vector<T> &vector) {
    for (size_t i = 0; i < vector.size(); i++)
        stream << vector[i] << " ";

    return stream;
}