cmake_minimum_required(VERSION 3.15)
project(Wanderer)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(src)
add_subdirectory(test)