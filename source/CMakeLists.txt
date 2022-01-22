cmake_minimum_required(VERSION 3.15)

project(wanderer-source CXX)

set(SOURCE_FILES
    build.hpp
    common.hpp
    constants.hpp
    exception.hpp
    logging.cpp
    logging.hpp
    profile.hpp
    wanderer_game.cpp
    wanderer_game.hpp

    io/directories.cpp
    io/directories.hpp
    )

add_library(${TARGET_WANDERER_LIB} ${SOURCE_FILES})
add_dependencies(${TARGET_WANDERER_LIB} ${TARGET_WANDERER_PROTO})

target_include_directories(${TARGET_WANDERER_LIB}
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}

                           SYSTEM PUBLIC
                           "${WANDERER_LIBRARY_DIR}/centurion"
                           ${Boost_INCLUDE_DIRS}
                           )

target_link_libraries(${TARGET_WANDERER_LIB}
                      PUBLIC
                      ${TARGET_WANDERER_PROTO}
                      SDL2::SDL2-static
                      SDL2::SDL2_image
                      SDL2::SDL2_mixer
                      SDL2::SDL2_ttf
                      EnTT::EnTT
                      glm::glm
                      fmt::fmt
                      magic_enum::magic_enum
                      ${Boost_LIBRARIES}
                      )

target_compile_definitions(${TARGET_WANDERER_LIB}
                           PUBLIC
                           BOOST_ENABLE_ASSERT_DEBUG_HANDLER
                           BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
                           )

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${TARGET_WANDERER_LIB} PUBLIC
                         /EHsc
                         /MP
                         /W4
                         /Zc:__cplusplus
                         /Zc:preprocessor
                         )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|AppleClang")
  target_compile_options(${TARGET_WANDERER_LIB} PUBLIC
                         -Wall
                         -Wextra
                         -Wpedantic
                         -Wconversion
                         )
endif ()

target_precompile_headers(${TARGET_WANDERER_LIB} PRIVATE
                          <centurion.hpp>
                          <entt/entt.hpp>
                          <glm/glm.hpp>
                          )

add_executable(${TARGET_WANDERER_EXE} WIN32 ${SOURCE_FILES} main.cpp)

add_dependencies(${TARGET_WANDERER_EXE} ${TARGET_WANDERER_LIB})

target_link_libraries(${TARGET_WANDERER_EXE} PRIVATE
                      ${TARGET_WANDERER_LIB}
                      SDL2::SDL2main
                      )

target_precompile_headers(${TARGET_WANDERER_EXE} REUSE_FROM ${TARGET_WANDERER_LIB})

copy_directory_post_build(${TARGET_WANDERER_EXE} ${WANDERER_RESOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/resources")
