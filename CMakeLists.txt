cmake_minimum_required(VERSION 3.15)

project(Wanderer CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(Utilities)

# Helper variables for directory paths
set(WANDERER_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/resource)
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

# The various targets used
set(WANDERER_LIB_TARGET libWanderer)
set(WANDERER_TEST_TARGET testWanderer)
set(WANDERER_EXE_TARGET Wanderer)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CENTURION_IMPORT_LIB ${BINARY_DIR}/Centurion${CMAKE_IMPORT_LIBRARY_SUFFIX})
elseif ()
    set(CENTURION_IMPORT_LIB ${BINARY_DIR}/libCenturion${CMAKE_IMPORT_LIBRARY_SUFFIX})
endif ()
message("Centurion import library: ${CENTURION_IMPORT_LIB}")

find_env_var(SDL2DIR SDL2)
find_env_var(SDL2IMAGEDIR SDL2_image)
find_env_var(SDL2MIXERDIR SDL2_mixer)
find_env_var(SDL2TTFDIR SDL2_ttf)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(src)
add_subdirectory(test)