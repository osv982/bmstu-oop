#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <QPainter>

struct Graph {
    QPainter *painter;
};

// Инициализация отрисовщика
void graphInit(Graph &, QPainter &);

// Отрисовка отрезка
void graphLine(Graph &, int, int, int, int);

#endif // GRAPH_HPP
