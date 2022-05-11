#ifndef EVENT_HPP
#define EVENT_HPP

#include "graph.hpp"
#include "trans.hpp"

enum Brand {
    brandLoad,
    brandTranslate,
    brandScale,
    brandRotate,
    brandGraph,
    brandQuit,
};

struct Load {
    const char *fileName;
};

struct Event {
    Brand brand;

    union {
        Load            load;
        Translate  translate;
        Scale          scale;
        Rotate        rotate;
        Graph          graph;
    };
};

//! Событие загрузки
void eventLoad(Event &, Load &);

//! Событие переноса
void eventTranslate(Event &, Translate &);

//! Событие масштабирования
void eventScale(Event &, Scale &);

//! Событие поворота
void eventRotate(Event &, Rotate &);

//! Событие отрисовки
void eventGraph(Event &, Graph &);

//! Событие финализации
void eventQuit(Event &);

#endif // EVENT_HPP
