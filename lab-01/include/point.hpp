#ifndef POINT_HPP
#define POINT_HPP

#include <cstdio>

#include "error.hpp"
#include "trans.hpp"

struct Point {
    double x;
    double y;
    double z;
};

//! Обнуление точки
void pointZero(Point &);

//! Перенос точки
void pointTranslate(Point &, Translate &);

//! Масштабирование точки
void pointScale(Point &, Scale &, Point &);

//! Поворот точки
void pointRotate(Point &, Rotate &, Point &);

//! Чтение точки из файла
Error pointRead(Point &, FILE *);

//! Запись точки в файл
void pointDump(Point &, FILE *);

#endif // POINT_HPP
