#ifndef EDGES_HPP
#define EDGES_HPP

// Файловый ввод
#include <cstdio>

#include "fiber.hpp"
#include "verts.hpp"

struct Edges {
    int    count;
    Fiber *array;
};

//! Инициализация
void edgesInit(Edges &);

//! Финализация
void edgesDrop(Edges &);

//! Чтение из файла
Error edgesRead(Edges &, FILE *);

//! Отрисовка
void edgesGraph(Edges &, Verts &, Graph &);

#endif // EDGES_HPP