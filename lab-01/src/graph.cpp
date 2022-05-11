#include "graph.hpp"

void graphInit(Graph &graph, QPainter &painter) {
    graph.painter = &painter;
}

void graphLine(Graph &graph, int px, int py, int qx, int qy) {
    if (graph.painter) graph.painter->drawLine(px, py, qx, qy);
}
