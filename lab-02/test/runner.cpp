#include "CppUTest/CommandLineTestRunner.h"

// Генератор
#include <cstdlib>

// Инициализация
#include <ctime>

int main(int argc, char *argv[]) {

    // Инициализация генератора
    std::srand(std::time(nullptr));

    return CommandLineTestRunner::RunAllTests(argc, argv);
}