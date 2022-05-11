#include "event.hpp"

void eventLoad(Event &event, Load &load) {
    event.brand = brandLoad;
    event.load  =      load;
}

void eventTranslate(Event &event, Translate &translate) {
    event.brand     = brandTranslate;
    event.translate = translate;
}

void eventScale(Event &event, Scale &scale) {
    event.brand = brandScale;
    event.scale =      scale;
}

void eventRotate(Event &event, Rotate &rotate) {
    event.brand  = brandRotate;
    event.rotate =      rotate;
}

void eventGraph(Event &event, Graph &graph) {
    event.brand = brandGraph;
    event.graph =      graph;
}

void eventQuit(Event &event) {
    event.brand = brandQuit;
}
