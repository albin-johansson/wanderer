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
        component/humanoid_state.h
        component/binds.h
        component/animated.h
        component/drawable.h
        component/tilemap.h
        component/tile_layer.h
        component/tileset.h
        component/tile.h
        component/animated_tile.h
        component/render_bounds.h

        system/render_movables_system.cpp
        system/render_movables_system.h
        system/movement_system.cpp
        system/movement_system.h
        system/interpolation_system.h
        system/interpolation_system.cpp
        system/viewport_system.cpp
        system/viewport_system.h
        system/translation_viewport_system.cpp
        system/translation_viewport_system.h
        system/humanoid_animation_system.cpp
        system/humanoid_animation_system.h
        system/animation_system.cpp
        system/animation_system.h
        system/humanoid_state_system.cpp
        system/humanoid_state_system.h
        system/ground_layer_rendering_system.cpp
        system/ground_layer_rendering_system.h
        system/render_bounds_system.cpp
        system/render_bounds_system.h

        system/input/input_system.cpp
        system/input/input_system.h
        system/input/move_input_system.cpp
        system/input/move_input_system.h
        system/input/idle_input_system.cpp
        system/input/idle_input_system.h

        parse/tile/make_tile.cpp
        parse/tile/make_tile.h
        parse/tile/make_map.h
        parse/tile/make_map.cpp
        parse/tile/make_tileset.cpp
        parse/tile/make_tileset.h)

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
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/step)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC core)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC core/math)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC component)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC system)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC system/input)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC utility)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC parse)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC parse/tile)
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC parse/menu)

#target_compile_definitions(${WANDERER_LIB} PUBLIC WANDERER_DEBUG)

target_link_libraries(${WANDERER_LIB_TARGET}
        PUBLIC ${CENTURION_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${STEP_LIBRARY})

add_executable(${WANDERER_EXE_TARGET} main.cpp)

wanderer_set_properties(${WANDERER_EXE_TARGET} "Wanderer")

target_link_libraries(${WANDERER_EXE_TARGET}
        PUBLIC ${WANDERER_LIB_TARGET}
        PUBLIC ${CENTURION_LIBRARY}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})

copy_directory_post_build(${WANDERER_EXE_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/resource)


