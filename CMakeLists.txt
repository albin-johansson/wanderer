cmake_minimum_required(VERSION 3.15)
project(Wanderer)

# Copies a file.
#   target: the associated target.
#   from: the file that will be copied.
#   to: the target destination of the copied file.
function(copy_file_post_build [target [from [to]]])
    add_custom_command(
            TARGET ${ARGV0} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${ARGV1}
            ${ARGV2})
endfunction()

# Copies a directory.
#   target: the associated target.
#   from: the directory that will be copied.
#   to: the target destination of the copied directory.
function(copy_directory_post_build [target [from [to]]])
    add_custom_command(
            TARGET ${ARGV0} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${ARGV1}
            ${ARGV2})
endfunction()

# Checks if an environment variable is defined.
#   envVar: the name of the actual environment variable.
#   name: the name of the library associated with the environment variable.
function(find_env_var [envVar [name]])
    if (DEFINED ENV{${ARGV0}})
        message("Found ${ARGV1} environment variable! Path: " $ENV{${ARGV0}})
    else ()
        message("Couldn't find environment variable ${ARGV0}!")
    endif ()
endfunction()

# Creates an interface library target for a header-only library.
#   name: the name of the library target.
#   includeDirectory: the path of the directory that contains the headers of the library.
#   sources: the headers associated with the library.
function(wanderer_add_header_only_lib [name [includeDirectory [sources]]])
    add_library(${ARGV0} INTERFACE)
    target_sources(${ARGV0} INTERFACE ${ARGV2})
    target_include_directories(${ARGV0} SYSTEM INTERFACE ${ARGV1})
endfunction()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Helper variables for directory paths
set(WANDERER_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/resource)
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

# The various targets used
set(WANDERER_LIB_TARGET libWanderer)
set(WANDERER_TEST_TARGET testWanderer)
set(WANDERER_EXE_TARGET Wanderer)

set(CENTURION_LIBRARY ${BINARY_DIR}/libCenturion${CMAKE_IMPORT_LIBRARY_SUFFIX})
set(STEP_LIBRARY ${BINARY_DIR}/libstep${CMAKE_IMPORT_LIBRARY_SUFFIX})

find_env_var(SDL2DIR SDL2)
find_env_var(SDL2IMAGEDIR SDL2_image)
find_env_var(SDL2MIXERDIR SDL2_mixer)
find_env_var(SDL2TTFDIR SDL2_ttf)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(src)
add_subdirectory(test)