cmake_minimum_required(VERSION 3.15)
project(${WANDERER_TEST})

set(CATCH_INCLUDE_DIR catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch SYSTEM INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(${WANDERER_TEST}
        unittests/test_main.cpp
        unittests/vector_2_test.cpp
        unittests/objects_test.cpp
        unittests/viewport_test.cpp
        unittests/hitbox_test.cpp
        unittests/random_utils_test.cpp)

set_target_properties(${WANDERER_TEST} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

target_include_directories(${WANDERER_TEST} PUBLIC unittests)

target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${LIBRARY_DIR})
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${LIBRARY_DIR}/gsl)
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${LIBRARY_DIR}/pugixml)
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${LIBRARY_DIR}/centurion)
target_include_directories(${WANDERER_TEST} SYSTEM PUBLIC ${LIBRARY_DIR}/tiled)

target_link_libraries(${WANDERER_TEST}
        mingw32
        Catch
        ${WANDERER_LIB}
        ${CENTURION_LIBRARIES}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${WANDERER_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${BINARIES_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})

# Copies all of the resources and puts the in the build folder
add_custom_command(TARGET ${WANDERER_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCES_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/resources)