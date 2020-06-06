cmake_minimum_required(VERSION 3.15)
project(WandererTest)

set(TEST_FILES
        unittest/test_main.cpp
        unittest/hitbox_test.cpp)

add_executable(${WANDERER_TEST_TARGET} ${TEST_FILES})
add_dependencies(${WANDERER_TEST_TARGET} ${WANDERER_LIB_TARGET})

set_target_properties(${WANDERER_TEST_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

add_library(Doctest INTERFACE)
target_include_directories(Doctest INTERFACE doctest)
include(doctest)

add_test(NAME ${WANDERER_TEST_TARGET}
        COMMAND ${WANDERER_TEST_TARGET})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${WANDERER_TEST_TARGET} PRIVATE
            -Wno-unused-result
            )
endif ()

target_include_directories(${WANDERER_TEST_TARGET} PUBLIC unittest)

target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/centurion)
target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/json)
target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/entt)
target_include_directories(${WANDERER_TEST_TARGET} SYSTEM PUBLIC doctest)

target_link_libraries(${WANDERER_TEST_TARGET}
        PUBLIC Doctest
        PUBLIC ${WANDERER_LIB_TARGET}
        PUBLIC ${CENTURION_LIBRARY}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})

if (WIN32)
    copy_directory_post_build(${WANDERER_TEST_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()
copy_directory_post_build(${WANDERER_TEST_TARGET} ${RESOURCE_DIR}
        "${CMAKE_CURRENT_BINARY_DIR}/resource")