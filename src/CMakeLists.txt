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

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${BINARIES_DIR}"
#        ${CMAKE_BINARY_DIR})

#add_custom_command(
#        TARGET foo POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${CMAKE_SOURCE_DIR}/test/input.txt
#        ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

#add_custom_command(TARGET MyTarget PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/config/ $<TARGET_FILE_DIR:MyTarget>)

message(${CMAKE_BINARY_DIR}/src!)
configure_file(${BINARIES_DIR}/SDL2.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/SDL2_image.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/SDL2_mixer.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/SDL2_ttf.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/SDL2_image.dll ${CMAKE_BINARY_DIR}/src COPYONLY)

configure_file(${BINARIES_DIR}/libFLAC-8.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libfreetype-6.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libjpeg-9.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libmodplug-1.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libmpg123-0.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libogg-0.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libopus-0.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libpng16-16.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libtiff-5.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libvorbis-0.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libvorbisfile-3.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/libwebp-7.dll ${CMAKE_BINARY_DIR}/src COPYONLY)
configure_file(${BINARIES_DIR}/zlib1.dll ${CMAKE_BINARY_DIR}/src COPYONLY)

