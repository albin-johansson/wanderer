cmake_minimum_required(VERSION 3.15)
project(${CMAKE_PROJECT_NAME}_src)

set(SOURCE_FILES
        service/bool_converter.h
        view/window.h
        view/window.cpp
        view/renderer.h
        view/renderer.cpp
        core/wanderer_core.h
        core/wanderer_core_impl.cpp
        core/wanderer_core_impl.h
        core/wanderer_core_factory.h
        controller/wanderer_controller.h
        controller/wanderer_controller_impl.cpp
        controller/wanderer_controller_impl.h
        controller/wanderer_controller_factory.h.cpp
        core/tickable.h
        core/math/vector_2.cpp
        core/math/vector_2.h)

# Prepares the Wanderer "library", which excludes linking and the main.cpp file
add_library(${WANDERER_LIB} ${SOURCE_FILES})

target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC controller)
target_include_directories(${WANDERER_LIB} PUBLIC core)
target_include_directories(${WANDERER_LIB} PUBLIC view)
target_include_directories(${WANDERER_LIB} PUBLIC util)
target_include_directories(${WANDERER_LIB} PUBLIC service)
target_include_directories(${WANDERER_LIB} PUBLIC core/math)

# Prepares the actual executable
add_executable(${WANDERER_EXECUTABLE} main.cpp)

target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_LIBRARY})
target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_MIXER_LIBRARIES})
target_link_directories(${WANDERER_EXECUTABLE} PUBLIC ${SDL2_TTF_LIBRARIES})

target_link_libraries(${WANDERER_EXECUTABLE}
        mingw32
        ${WANDERER_LIB}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${WANDERER_EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/src)

# Copies all of the resources and puts the in the build folder
add_custom_command(TARGET ${WANDERER_EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        ${CMAKE_BINARY_DIR}/test/resources)

