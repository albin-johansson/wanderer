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
function(add_header_only_lib [name [includeDirectory [sources]]])
    add_library(${ARGV0} INTERFACE)
    target_sources(${ARGV0} INTERFACE ${ARGV2})
    target_include_directories(${ARGV0} SYSTEM INTERFACE ${ARGV1})
endfunction()