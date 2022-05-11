// Работа с кучей
#include <cstdlib>

// Тригонометрия
#include <cmath>

#include "binio.hpp"
#include "point.hpp"

void pointZero(Point &point) {
    point.x = 0.0;
    point.y = 0.0;
    point.z = 0.0;
}

void pointTranslate(Point &point, Translate &translate) {
    point.x += translate.x;
    point.y += translate.y;
}

void pointScale(Point &point, Scale &scale, Point &origin) {
    point.x = scale.k * point.x + (1.0 - scale.k) * origin.x;
    point.y = scale.k * point.y + (1.0 - scale.k) * origin.y;
    point.z = scale.k * point.z + (1.0 - scale.k) * origin.z;
}

static void pointRotateA(Point &point, double a, Point &origin) {
    double dx = point.x - origin.x;
    double dz = point.z - origin.z;

    point.x = origin.x + dx * cos(a) - dz * sin(a);
    point.z = origin.z + dx * sin(a) + dz * cos(a);
}

static void pointRotateB(Point &point, double b, Point &origin) {
    double dy = point.y - origin.y;
    double dz = point.z - origin.z;

    point.y = origin.y + dy * cos(b) - dz * sin(b);
    point.z = origin.z + dy * sin(b) + dz * cos(b);
}

void pointRotate(Point &point, Rotate &rotate, Point &origin) {
    pointRotateA(point, rotate.a, origin);
    pointRotateB(point, rotate.b, origin);
}

Error pointRead(Point &point, FILE *file) {
    Error error = errorNone;

    double x, y, z;

    if (error == errorNone && !read(x, file))
        error = errorRead;

    if (error == errorNone && !read(y, file))
        error = errorRead;

    if (error == errorNone && !read(z, file))
        error = errorRead;

    if (error == errorNone) {
        point.x = x;
        point.y = y;
        point.z = z;
    }

    return error;
}

void pointDump(Point &point, FILE *file) {
    dump(point.x, file);
    dump(point.y, file);
    dump(point.z, file);
}
