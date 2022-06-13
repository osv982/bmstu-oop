project(lab-04 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(run
    "inc/timed.hpp"
    "src/timed.cpp"
    "inc/brain.hpp"
    "src/brain.cpp"
    "inc/cabin.hpp"
    "src/cabin.cpp"
    "inc/doors.hpp"
    "src/doors.cpp"
    "inc/press.hpp"
    "src/press.cpp"
    "inc/floor.hpp"
    "src/floor.cpp"
    "src/start.cpp"    
)

# Директория с заголовочными файлами
target_include_directories(run PRIVATE inc)

# Поиск компонентов Qt5
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Связывание компонентов Qt5 с исполняемым файлом
target_link_libraries(run Qt5::Core Qt5::Gui Qt5::Widgets)