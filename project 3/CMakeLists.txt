cmake_minimum_required(VERSION 3.17)
project(project_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_3 main.cpp)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("project 3")

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Users/wasic/Desktop/sfml/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(Minesweeper main.cpp Tile.cpp Tile.h TextureManager.cpp TextureManager.h Random.h Random.cpp)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)