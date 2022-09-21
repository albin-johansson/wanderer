cmake_minimum_required(VERSION 3.15)

project(wanderer-test CXX)

enable_testing()

file(GLOB_RECURSE TEST_FILES
     CONFIGURE_DEPENDS
     src/**/*.cpp
     src/*.cpp
     )

add_executable(${TARGET_WANDERER_TEST} ${TEST_FILES})
add_dependencies(${TARGET_WANDERER_TEST} ${TARGET_WANDERER_LIB})

wanderer_add_compiler_options(${TARGET_WANDERER_TEST})

target_include_directories(${TARGET_WANDERER_TEST} PUBLIC src)

target_link_libraries(${TARGET_WANDERER_TEST}
                      PRIVATE
                      ${TARGET_WANDERER_LIB}
                      SDL2::SDL2main
                      GTest::gtest
                      )

target_precompile_headers(${TARGET_WANDERER_TEST} REUSE_FROM ${TARGET_WANDERER_LIB})

add_test(NAME ${TARGET_WANDERER_TEST} COMMAND ${TARGET_WANDERER_TEST})
