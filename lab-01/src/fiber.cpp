#include "fiber.hpp"
#include "binio.hpp"

Error fiberRead(Fiber &fiber, FILE *file) {
    Error error = errorNone;

    if (error == errorNone && !read(fiber.i, file))
        error = errorRead;

    if (error == errorNone && !read(fiber.j, file))
        error = errorRead;

    return error;
}

void fiberGraph(Fiber &fiber, Point *&array, Graph &graph) {
    Point p = array[fiber.i];
    Point q = array[fiber.j];

    graphLine(graph, p.x, p.y, q.x, q.y);
}