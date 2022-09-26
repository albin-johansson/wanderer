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
                           ${Boost_INCLUDE_DIRS})

target_link_libraries(${TARGET_WANDERER_LIB}
                      PUBLIC
                      ${TARGET_WANDERER_PROTO}
                      SDL2::SDL2
                      SDL2::SDL2_image
                      $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
                      $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
                      EnTT::EnTT
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

target_compile_definitions(${TARGET_WANDERER_LIB}
                           PUBLIC
                           BOOST_ENABLE_ASSERT_DEBUG_HANDLER
                           BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
                           BOOST_NO_CXX98_FUNCTION_BASE
                           SPDLOG_FMT_EXTERNAL
                           )

wanderer_add_compiler_options(${TARGET_WANDERER_LIB})

target_precompile_headers(${TARGET_WANDERER_LIB} PRIVATE
                          <algorithm>
                          <array>
                          <charconv>
                          <chrono>
                          <concepts>
                          <cstddef>
                          <cstdint>
                          <cstring>
                          <cstdlib>
                          <ctime>
                          <cmath>
                          <deque>
                          <exception>
                          <filesystem>
                          <fstream>
                          <functional>
                          <iterator>
                          <limits>
                          <locale>
                          <map>
                          <memory>
                          <optional>
                          <ostream>
                          <queue>
                          <random>
                          <span>
                          <sstream>
                          <string>
                          <string_view>
                          <system_error>
                          <type_traits>
                          <unordered_map>
                          <utility>
                          <variant>
                          <vector>
                          )

if (CMAKE_BUILD_TYPE STREQUAL RELEASE)
  add_executable(${TARGET_WANDERER_EXE} WIN32 main.cpp)
else ()
  add_executable(${TARGET_WANDERER_EXE} main.cpp)
endif ()

wanderer_add_compiler_options(${TARGET_WANDERER_EXE})

add_dependencies(${TARGET_WANDERER_EXE} ${TARGET_WANDERER_LIB})

target_link_libraries(${TARGET_WANDERER_EXE}
                      PRIVATE
                      ${TARGET_WANDERER_LIB}
                      SDL2::SDL2main
                      )

target_precompile_headers(${TARGET_WANDERER_EXE} REUSE_FROM ${TARGET_WANDERER_LIB})
