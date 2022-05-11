// Работа с кучей
#include <cstdlib>

#include "model.hpp"
#include "binio.hpp"

Model &modelInit() {
    static Model model;

    vertsInit(model.verts);
    edgesInit(model.edges);

    pointZero(model.origin);

    return model;
}

void modelDrop(Model &model) {
    vertsDrop(model.verts);
    edgesDrop(model.edges);
}

void modelTranslate(Model &model, Translate &translate) {
    vertsTranslate(model.verts, translate);
    pointTranslate(model.origin, translate);
}

void modelScale(Model &model, Scale &scale) {
    vertsScale(model.verts, scale, model.origin);
}

void modelRotate(Model &model, Rotate &rotate) {
    vertsRotate(model.verts, rotate, model.origin);
}

void modelGraph(Model &model, Graph &graph) {
    edgesGraph(model.edges, model.verts, graph);
}

Error modelRead(Model &model, FILE *file) {
    Error error = vertsRead(model.verts, file);

    if (error == errorNone) {
        error = edgesRead(model.edges, file);

        if (error != errorNone)
            vertsDrop(model.verts);
    }

    return error;
}

Error modelLoad(Model &model, Load &load) {
    Error error = errorNone;

    FILE *file;

    if (!(file = fopen(load.fileName, "rb")))
        error = errorOpen;

    else {
        Model inter = modelInit();

        if ((error = modelRead(inter, file)) == errorNone) {
            modelDrop(model);
            model = inter;
        }

        fclose(file);
    }

    return error;
}