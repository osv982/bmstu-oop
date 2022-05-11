#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdio>

#include "verts.hpp"
#include "edges.hpp"
#include "error.hpp"
#include "event.hpp"
#include "graph.hpp"
#include "point.hpp"
#include "trans.hpp"

struct Model {
    Verts verts;
    Edges edges;

    Point origin;
};

//! Инициализация
Model &modelInit();

//! Освобождение памяти
void modelDrop(Model &);

//! Перенос модели
void modelTranslate(Model &, Translate &);

//! Масштабирование модели
void modelScale(Model &, Scale &);

//! Поворот модели
void modelRotate(Model &, Rotate &);

//! Отрисовка модели
void modelGraph(Model &, Graph &);

//! Чтение модели из файла
Error modelRead(Model &, FILE *);

//! Запись модели в файл
void modelDump(Model &, FILE *);

//! Загрузка модели из файла
Error modelLoad(Model &, Load &);

#endif // MODEL_HPP