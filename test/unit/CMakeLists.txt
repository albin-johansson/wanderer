cmake_minimum_required(VERSION 3.15)

project(wanderer-test-unit CXX)

set(TEST_FILES
    dev_console_system_test.cpp
    event_connections_test.cpp
    hitbox_test.cpp
    humanoid_state_test.cpp
    load_save_game_test.cpp
    test_main.cpp
    )

add_executable(${WANDERER_TEST} ${TEST_FILES})
add_dependencies(${WANDERER_TEST} ${WANDERER_LIB})

target_precompile_headers(${WANDERER_TEST} REUSE_FROM ${WANDERER_LIB})

target_include_directories(${WANDERER_TEST} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${WANDERER_TEST}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gtest_SOURCE_DIR})

target_link_libraries(${WANDERER_TEST}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC ${WANDERER_LIB}
    PUBLIC gtest)

add_test(NAME ${WANDERER_TEST} COMMAND ${WANDERER_TEST})

if (WIN32)
  copy_directory_post_build(${WANDERER_TEST} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

copy_directory_post_build(${WANDERER_TEST} ${CMAKE_CURRENT_SOURCE_DIR}/../resources "${CMAKE_CURRENT_BINARY_DIR}/resources")
copy_directory_post_build(${WANDERER_TEST} ${RESOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/resources")
