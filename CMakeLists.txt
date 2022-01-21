cmake_minimum_required(VERSION 3.15)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

project(wanderer
        VERSION 0.1.0
        LANGUAGES CXX
        HOMEPAGE_URL "https://github.com/albin-johansson/wanderer")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Helper variables for directory paths
set(ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(BINARY_DIR "${ROOT_DIR}/bin")
set(RESOURCE_DIR "${ROOT_DIR}/resources")
set(LIBRARY_DIR "${ROOT_DIR}/lib")
set(GENERATED_PROTOBUF_DIR "${ROOT_DIR}/proto/generated")

set(TARGET_WANDERER_PROTO WandererProto)
set(TARGET_WANDERER_LIB WandererCore)
set(TARGET_WANDERER_TEST WandererTests)
set(TARGET_WANDERER_EXE Wanderer)

include(Utilities)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2-image CONFIG REQUIRED)
find_package(SDL2-mixer CONFIG REQUIRED)
find_package(SDL2-ttf CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

add_subdirectory(proto)
add_subdirectory(src)
add_subdirectory(test)