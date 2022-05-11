#ifndef ERROR_HPP
#define ERROR_HPP

enum Error {
    errorNone,
    errorCode,
    errorHeap,
    errorOpen,
    errorRead,
};

// Сообщение об ошибке
const char *errorMessage(Error);

#endif // ERROR_HPP
