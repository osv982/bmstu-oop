#include <cstdlib>

#include "edges.hpp"
#include "binio.hpp"

void edgesInit(Edges &edges) {
    edges.count = 0;
    edges.array = nullptr;
}

void edgesDrop(Edges &edges) {
    free(edges.array);
}

static Error edgesReadCount(Edges &edges, FILE *file) {
    Error error = errorNone;

    if (!read(edges.count, file) || edges.count < 0)
        error = errorRead;

    return error;
}

static Error edgesReadAlloc(Edges &edges) {
    Error error = errorNone;

    if (!(edges.array = (Fiber *) calloc(edges.count, sizeof(Fiber))))
        error = errorHeap;

    return error;
}

static Error edgesReadArray(Edges &edges, FILE *file) {
    Error error = errorNone;

    for (int i = 0; error == errorNone && i < edges.count; i++)
        error = fiberRead(edges.array[i], file);

    return error;
}

Error edgesRead(Edges &edges, FILE *file) {
    Error error = errorNone;

    if (error == errorNone)
        error = edgesReadCount(edges, file);

    if (error == errorNone)
        error = edgesReadAlloc(edges);

    if (error == errorNone)
        error = edgesReadArray(edges, file);

    if (error != errorNone)
        edgesDrop(edges);

    return error;
}

void edgesGraph(Edges &edges, Verts &verts, Graph &graph) {
    for (int i = 0; i < edges.count; i++)
        fiberGraph(edges.array[i], verts.array, graph);
}