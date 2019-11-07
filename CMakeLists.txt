cmake_minimum_required(VERSION 3.15)
project(Wanderer)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)

# Names of targets
set(WANDERER_LIB ${PROJECT_NAME}_lib)
set(WANDERER_EXECUTABLE ${PROJECT_NAME}_exe)
set(WANDERER_TEST ${PROJECT_NAME}_test)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(src)
add_subdirectory(test)