cmake_minimum_required(VERSION 3.15)
project(WandererSource)

function(wanderer_set_properties [target [outputName]])
    set_target_properties(${ARGV0} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            OUTPUT_NAME ${ARGV1})
endfunction()

set(SOURCE_FILES
        core/game.h
        core/game.cpp
        core/application.cpp
        core/application.h
        core/make_player.h
        core/make_player.cpp
        core/game_loop.h
        core/hitbox.cpp
        core/hitbox.h
        core/game_loop.cpp
        core/direction.h
        core/game_constants.h
        core/viewport.cpp
        core/viewport.h
        core/make_viewport.cpp
        core/make_viewport.h

        core/math/vector_2.h
        core/math/random.cpp
        core/math/random.h
        core/math/math.h

        utility/types.h
        utility/input.cpp
        utility/input.h

        component/player.h
        component/movable.h
        component/collision.h
        component/entity_state.h
        component/binds.h
        component/animated.h
        component/drawable.h

        system/render_entities.cpp
        system/render_entities.h
        system/update_movement.cpp
        system/update_movement.h
        system/update_interpolation.h
        system/update_interpolation.cpp
        system/update_viewport.cpp
        system/update_viewport.h
        system/update_translation_viewport.cpp
        system/update_translation_viewport.h
        system/humanoid_animation_system.cpp
        system/humanoid_animation_system.h
        system/update_animation.cpp
        system/update_animation.h

        system/input/update_input.cpp
        system/input/update_input.h
        system/input/handle_move_input.cpp
        system/input/handle_move_input.h
        system/input/handle_idle_input.cpp
        system/input/handle_idle_input.h)

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${WANDERER_LIB_TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wdouble-promotion
            -Wswitch-default
            -Wswitch-enum
            -Wunused
            -Wuninitialized
            -Wsuggest-final-types
            -Wsuggest-final-methods
            -Wduplicated-cond
            -Wconversion)
endif ()

wanderer_set_properties(${WANDERER_LIB_TARGET} "Wanderer")

# Library directories
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/centurion)
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/entt)
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/json)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC core)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC core/math)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC component)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC system)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC system/input)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC utility)

#target_compile_definitions(${WANDERER_LIB} PUBLIC WANDERER_DEBUG)

target_link_libraries(${WANDERER_LIB_TARGET}
        PUBLIC ${CENTURION_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY})

add_executable(${WANDERER_EXE_TARGET} main.cpp)

wanderer_set_properties(${WANDERER_EXE_TARGET} "Wanderer")

target_link_libraries(${WANDERER_EXE_TARGET}
        PUBLIC mingw32 # TODO check if this is necessary
        PUBLIC ${WANDERER_LIB_TARGET}
        PUBLIC ${CENTURION_LIBRARY}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})

copy_directory_post_build(${WANDERER_EXE_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/resource)


