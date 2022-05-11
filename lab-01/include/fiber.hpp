#ifndef FIBER_HPP
#define FIBER_HPP

// Файловый ввод
#include <cstdio>

#include "error.hpp"
#include "point.hpp"
#include "graph.hpp"

struct Fiber {
    int i;
    int j;
};

//! Чтение из файла
Error fiberRead(Fiber &, FILE *);

//! Отрисовка
void fiberGraph(Fiber &, Point *&, Graph &);

#endif // FIBER_HPP