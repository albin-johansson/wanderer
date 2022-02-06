cmake_minimum_required(VERSION 3.15)

project(wanderer-test CXX)

enable_testing()

set(TEST_FILES
    unit-tests/test_main.cpp
    )

add_executable(${TARGET_WANDERER_TEST} ${TEST_FILES})
add_dependencies(${TARGET_WANDERER_TEST} ${TARGET_WANDERER_LIB})

wanderer_add_compiler_options(${TARGET_WANDERER_TEST})

target_include_directories(${TARGET_WANDERER_TEST} PUBLIC unit-tests)

target_link_libraries(${TARGET_WANDERER_TEST}
                      PRIVATE
                      ${TARGET_WANDERER_LIB}
                      SDL2::SDL2main
                      doctest::doctest
                      )

target_precompile_headers(${TARGET_WANDERER_TEST} REUSE_FROM ${TARGET_WANDERER_LIB})

add_test(NAME ${TARGET_WANDERER_TEST} COMMAND ${TARGET_WANDERER_TEST})

copy_directory_post_build(${TARGET_WANDERER_TEST} "${CMAKE_CURRENT_SOURCE_DIR}/test-resources" "${CMAKE_CURRENT_BINARY_DIR}/test-resources")
copy_directory_post_build(${TARGET_WANDERER_TEST} ${WANDERER_RESOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/resources")
