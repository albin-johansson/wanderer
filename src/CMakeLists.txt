cmake_minimum_required(VERSION 3.15)
project(${CMAKE_PROJECT_NAME}_run)

set(SOURCE_FILES
        main.cpp
        core/some_class.h
        core/some_class.cpp
        service/bool_converter.h
        view/window.h
        view/window.cpp
        view/renderer.h
        view/renderer.cpp
        )

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

link_directories(${SDL2_LIBRARY})
link_directories(${SDL2_IMAGE_LIBRARIES})
link_directories(${SDL2_MIXER_LIBRARIES})
link_directories(${SDL2_TTF_LIBRARIES})

# Project directories
include_directories(controller)
include_directories(core)
include_directories(view)
include_directories(util)
include_directories(service)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
        mingw32
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder next to the executable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/src)

