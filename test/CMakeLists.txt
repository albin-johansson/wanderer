cmake_minimum_required(VERSION 3.15)

project(wanderer-test CXX)

find_package(GTest CONFIG REQUIRED)

enable_testing()

set(TEST_FILES
    unit/dev_console_system_test.cpp
    unit/event_connections_test.cpp
    unit/hitbox_test.cpp
    unit/humanoid_state_test.cpp
    unit/load_save_game_test.cpp
    unit/test_main.cpp
    )

add_executable(${WANDERER_TEST} ${TEST_FILES})
add_dependencies(${WANDERER_TEST} ${WANDERER_LIB})

target_precompile_headers(${WANDERER_TEST} REUSE_FROM ${WANDERER_LIB})

target_include_directories(${WANDERER_TEST} PUBLIC unit)

target_link_libraries(${WANDERER_TEST} PUBLIC
    ${WANDERER_LIB}
    SDL2::SDL2main
    GTest::gtest
    )

add_test(NAME ${WANDERER_TEST} COMMAND ${WANDERER_TEST})

if (WIN32)
  copy_directory_post_build(${WANDERER_TEST} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

copy_directory_post_build(${WANDERER_TEST} ${CMAKE_CURRENT_SOURCE_DIR}/test-resources "${CMAKE_CURRENT_BINARY_DIR}/test-resources")
copy_directory_post_build(${WANDERER_TEST} ${RESOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/resources")
