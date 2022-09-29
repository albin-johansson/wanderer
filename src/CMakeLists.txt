cmake_minimum_required(VERSION 3.15)

project(wanderer-source CXX)

file(GLOB_RECURSE SOURCE_FILES
     CONFIGURE_DEPENDS
     **/*.cpp
     **/*.hpp)

add_library(${TARGET_WANDERER_LIB} ${SOURCE_FILES})

add_dependencies(${TARGET_WANDERER_LIB} ${TARGET_WANDERER_PROTO})

target_include_directories(${TARGET_WANDERER_LIB}
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}

                           SYSTEM PUBLIC
                           ${WANDERER_LIBRARY_DIR}/centurion
                           ${Boost_INCLUDE_DIRS}
                           ${STB_INCLUDE_DIRS}
                           )

target_link_libraries(${TARGET_WANDERER_LIB} PUBLIC
                      ${TARGET_WANDERER_PROTO}
                      SDL2::SDL2
                      $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
                      $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
                      EnTT::EnTT
                      GLEW::GLEW
                      OpenGL::GL
                      glm::glm
                      fmt::fmt
                      spdlog::spdlog
                      magic_enum::magic_enum
                      yaml-cpp
                      nlohmann_json::nlohmann_json
                      argparse::argparse
                      box2d::box2d
                      EASTL
                      ${Boost_LIBRARIES}
                      )

target_compile_definitions(${TARGET_WANDERER_LIB} PUBLIC
                           CENTURION_NO_SDL_IMAGE
                           GLEW_NO_GLU
                           BOOST_ENABLE_ASSERT_DEBUG_HANDLER
                           BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
                           BOOST_NO_CXX98_FUNCTION_BASE
                           SPDLOG_FMT_EXTERNAL
                           SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG
                           )

wanderer_add_compiler_options(${TARGET_WANDERER_LIB})

target_precompile_headers(${TARGET_WANDERER_LIB} PRIVATE
                          <concepts>
                          <cstddef>
                          <cstdint>
                          <exception>
                          <filesystem>
                          <fstream>
                          <functional>
                          <istream>
                          <memory>
                          <ostream>
                          <sstream>
                          <utility>

                          <EASTL/algorithm.h>
                          <EASTL/hash_map.h>
                          <EASTL/vector.h>
                          <EASTL/optional.h>
                          <EASTL/string.h>
                          <EASTL/string_view.h>
                          <EASTL/vector.h>
                          <EASTL/vector_map.h>
                          )

if (CMAKE_BUILD_TYPE STREQUAL RELEASE)
  add_executable(${TARGET_WANDERER_EXE} WIN32 main.cpp)
else ()
  add_executable(${TARGET_WANDERER_EXE} main.cpp)
endif ()

wanderer_add_compiler_options(${TARGET_WANDERER_EXE})

add_dependencies(${TARGET_WANDERER_EXE} ${TARGET_WANDERER_LIB})

target_link_libraries(${TARGET_WANDERER_EXE} PRIVATE
                      ${TARGET_WANDERER_LIB}
                      SDL2::SDL2main
                      )

target_precompile_headers(${TARGET_WANDERER_EXE} REUSE_FROM ${TARGET_WANDERER_LIB})

copy_directory_post_build(${TARGET_WANDERER_LIB}
                          "${CMAKE_CURRENT_SOURCE_DIR}/../assets"
                          "${CMAKE_CURRENT_BINARY_DIR}/assets")

copy_directory_post_build(${TARGET_WANDERER_LIB}
                          "${CMAKE_CURRENT_SOURCE_DIR}/../shaders"
                          "${CMAKE_CURRENT_BINARY_DIR}/shaders")