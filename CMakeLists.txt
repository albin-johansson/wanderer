cmake_minimum_required(VERSION 3.15)

project(wanderer
    VERSION 0.1.0
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/albin-johansson/wanderer")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

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

if (WIN32)
  find_env_var(SDL2DIR SDL2)
  find_env_var(SDL2IMAGEDIR SDL2_image)
  find_env_var(SDL2MIXERDIR SDL2_mixer)
  find_env_var(SDL2TTFDIR SDL2_ttf)
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(src)
add_subdirectory(test)