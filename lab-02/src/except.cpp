#include "except.hpp"

WhereException::WhereException(const char *where) : message(where) {
    time_t t = time(nullptr);

    message.append(" at ");
    message.append(ctime(&t));
}

const char *WhereException::what() const noexcept {
    return message.c_str();
}

void WhereException::describe(const char *description) {
    message.append(description);
}

AllocException::AllocException(const char *where) : WhereException(where) {
    describe("ошибка выделения памяти");
}

DerefException::DerefException(const char *where) : WhereException(where) {
    describe("ошибка разыменования итератора");
}

EmptyException::EmptyException(const char *where) : WhereException(where) {
    describe("обработка пустой матрицы");
}

IndexException::IndexException(const char *where) : WhereException(where) {
    describe("выход за область допустимых индексов");
}

MatchException::MatchException(const char *where) : WhereException(where) {
    describe("несогласованность размерностей");
}

ShapeException::ShapeException(const char *where) : WhereException(where) {
    describe("несоответствие формы");
}