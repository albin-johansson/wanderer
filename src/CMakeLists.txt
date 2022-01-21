cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    profile.hpp
    )

add_library(${WANDERER_LIB} ${SOURCE_FILES})

target_include_directories(${WANDERER_LIB}
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}

                           SYSTEM PUBLIC
                           ${LIBRARY_DIR}/centurion
                           )

target_link_libraries(${WANDERER_LIB} PUBLIC
                      SDL2::SDL2
                      SDL2::SDL2_image
                      SDL2::SDL2_mixer
                      SDL2::SDL2_ttf
                      EnTT::EnTT
                      glm::glm
                      fmt::fmt
                      magic_enum::magic_enum
                      ${WANDERER_PROTO}
                      )

if (MSVC)
  target_compile_options(${WANDERER_LIB} PUBLIC
                         /EHsc
                         /MP
                         /W4
                         /Zc:__cplusplus
                         /Zc:preprocessor
                         /wd5105  # Disable C5105: "macro expansion producing 'defined' has undefined behavior"
                         )
endif ()

target_precompile_headers(${WANDERER_LIB} PRIVATE
                          <centurion.hpp>
                          <entt/entt.hpp>
                          <glm/glm.hpp>
                          )

add_executable(${WANDERER_EXE} WIN32 main.cpp)

add_dependencies(${WANDERER_EXE} ${WANDERER_LIB})

target_link_libraries(${WANDERER_EXE} PUBLIC
                      ${WANDERER_LIB}
                      SDL2::SDL2main
                      )

target_precompile_headers(${WANDERER_EXE} REUSE_FROM ${WANDERER_LIB})

if (WIN32)
  copy_directory_post_build(${WANDERER_EXE} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

copy_directory_post_build(${WANDERER_EXE} ${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources)
