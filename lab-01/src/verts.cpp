// Работа с кучей
#include <cstdlib>

#include "verts.hpp"
#include "binio.hpp"

void vertsInit(Verts &verts) {
    verts.count = 0;
    verts.array = nullptr;
}

void vertsDrop(Verts &verts) {
    free(verts.array);
}

static Error vertsReadCount(Verts &verts, FILE *file) {
    Error error = errorNone;

    if (!read(verts.count, file) || verts.count < 0)
        error = errorRead;

    return error;
}

static Error vertsReadAlloc(Verts &verts) {
    Error error = errorNone;

    if (!(verts.array = (Point *) calloc(verts.count, sizeof(Point))))
        error = errorHeap;

    return error;
}

static Error vertsReadArray(Verts &verts, FILE *file) {
    Error error = errorNone;

    for (int i = 0; error == errorNone && i < verts.count; i++)
        error = pointRead(verts.array[i], file);

    return error;
}

Error vertsRead(Verts &verts, FILE *file) {
    Error error = errorNone;

    if (error == errorNone)
        error = vertsReadCount(verts, file);

    if (error == errorNone)
        error = vertsReadAlloc(verts);

    if (error == errorNone)
        error = vertsReadArray(verts, file);

    if (error != errorNone)
        vertsDrop(verts);

    return error;
}

void vertsTranslate(Verts &verts, Translate &translate) {
    for (int i = 0; i < verts.count; i++)
        pointTranslate(verts.array[i], translate);
}

void vertsScale(Verts &verts, Scale &scale, Point &origin) {
    for (int i = 0; i < verts.count; i++)
        pointScale(verts.array[i], scale, origin);
}

void vertsRotate(Verts &verts, Rotate &rotate, Point &origin) {
    for (int i = 0; i < verts.count; i++)
        pointRotate(verts.array[i], rotate, origin);
}