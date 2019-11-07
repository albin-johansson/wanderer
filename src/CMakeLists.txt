cmake_minimum_required(VERSION 3.15)
project(${CMAKE_PROJECT_NAME}App)

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
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

target_link_directories(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY})
target_link_directories(${PROJECT_NAME} PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_directories(${PROJECT_NAME} PUBLIC ${SDL2_MIXER_LIBRARIES})
target_link_directories(${PROJECT_NAME} PUBLIC ${SDL2_TTF_LIBRARIES})

# Project directories
target_include_directories(${PROJECT_NAME} PUBLIC controller)
target_include_directories(${PROJECT_NAME} PUBLIC core)
target_include_directories(${PROJECT_NAME} PUBLIC view)
target_include_directories(${PROJECT_NAME} PUBLIC util)
target_include_directories(${PROJECT_NAME} PUBLIC service)

target_link_libraries(${PROJECT_NAME}
        mingw32
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${BINARIES_DIR}"
        ${CMAKE_BINARY_DIR}/src)

# Copies all of the resources and puts the in the build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        ${CMAKE_BINARY_DIR}/test/resources)

