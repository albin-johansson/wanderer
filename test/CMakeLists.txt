cmake_minimum_required(VERSION 3.15)
project(${WANDERER_TEST})

set(CATCH_INCLUDE_DIR catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(${WANDERER_TEST}
        unittests/test_main.cpp
        unittests/window_test.cpp
        unittests/bool_converter_test.cpp
        unittests/renderer_test.cpp
        unittests/vector_2_test.cpp
        unittests/objects_test.cpp
        unittests/rectangle_test.cpp
        unittests/font_test.cpp
        unittests/image_test.cpp
        unittests/viewport_test.cpp)

target_include_directories(${WANDERER_TEST} PUBLIC unittests)

target_link_directories(${WANDERER_TEST} PUBLIC ${SDL2_LIBRARY})
target_link_directories(${WANDERER_TEST} PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_directories(${WANDERER_TEST} PUBLIC ${SDL2_MIXER_LIBRARIES})
target_link_directories(${WANDERER_TEST} PUBLIC ${SDL2_TTF_LIBRARIES})

target_link_libraries(${WANDERER_TEST}
        mingw32
        Catch
        ${WANDERER_LIB}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${WANDERER_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/test)

# Copies all of the resources and puts the in the build folder
add_custom_command(TARGET ${WANDERER_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        ${CMAKE_BINARY_DIR}/test/resources)