#include "model.hpp"
#include "react.hpp"

Error react(Event &event) {
    Error error = errorNone;

    static Model model = modelInit();

    if (event.brand == brandLoad)
        error = modelLoad(model, event.load);

    else if (event.brand == brandTranslate)
        modelTranslate(model, event.translate);

    else if (event.brand == brandScale)
        modelScale(model, event.scale);

    else if (event.brand == brandRotate)
        modelRotate(model, event.rotate);

    else if (event.brand == brandGraph)
        modelGraph(model, event.graph);

    else if (event.brand == brandQuit)
        modelDrop(model);

    else error = errorCode;

    return error;
}
