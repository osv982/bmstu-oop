#ifndef VERTS_HPP
#define VERTS_HPP

// Файловый ввод
#include <cstdio>

#include "point.hpp"

struct Verts {
    int    count;
    Point *array;
};

//! Инициализация
void vertsInit(Verts &);

//! Финализация
void vertsDrop(Verts &);

//! Чтение из файла
Error vertsRead(Verts &, FILE *);

//! Перенос
void vertsTranslate(Verts &, Translate &);

//! Масштабирование
void vertsScale(Verts &, Scale &, Point &);

//! Поворот
void vertsRotate(Verts &, Rotate &, Point &);

#endif // VERTS_HPP