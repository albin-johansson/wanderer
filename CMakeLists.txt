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
set(WANDERER_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(WANDERER_RESOURCE_DIR "${PROJECT_SOURCE_DIR}/resources")
set(WANDERER_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/lib")

set(TARGET_WANDERER_PROTO WandererProto)
set(TARGET_WANDERER_LIB WandererCore)
set(TARGET_WANDERER_TEST WandererTests)
set(TARGET_WANDERER_EXE Wanderer)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)

find_package(Boost REQUIRED)

function(copy_file_post_build [target [from [to]]])
  add_custom_command(
      TARGET ${ARGV0} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${ARGV1}
      ${ARGV2})
endfunction()

function(copy_directory_post_build [target [from [to]]])
  add_custom_command(
      TARGET ${ARGV0} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${ARGV1}
      ${ARGV2})
endfunction()

function(wanderer_add_compiler_options target)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${target} PRIVATE
                           /EHsc
                           /MP
                           /WX
                           /Zc:__cplusplus
                           /Zc:preprocessor
                           )
  elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang")
    target_compile_options(${target} PRIVATE
                           -Wall
                           -Wextra
                           -Wpedantic
                           -Wconversion
                           -Wsign-conversion
                           )
  endif ()
endfunction()

add_subdirectory(proto)
add_subdirectory(source)
add_subdirectory(test)