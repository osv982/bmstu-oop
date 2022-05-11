#include "error.hpp"

const char *errorMessage(Error error) {
    const char *message;

    if (error == errorNone)
        message = nullptr;

    else if (error == errorCode)
        message = "Некорректная программа";

    else if (error == errorHeap)
        message = "Недостаточно памяти";

    else if (error == errorOpen)
        message = "Невозможно открыть файл";

    else if (error == errorRead)
        message = "Нарушен формат файла";

    return message;
}
