cmake_minimum_required(VERSION 3.7.0)

project(lab-01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(run
    src/start.cpp
    src/react.cpp
    src/event.cpp
    src/model.cpp
    src/point.cpp
    src/fiber.cpp
    src/graph.cpp
    src/error.cpp
    src/verts.cpp
    src/edges.cpp
)

target_include_directories(run
    PRIVATE include)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

target_link_libraries(run
    Qt::Core Qt::Gui Qt::Widgets)
