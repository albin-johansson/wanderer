cmake_minimum_required(VERSION 3.15)
project(${CMAKE_PROJECT_NAME}_src)

set(SOURCE_FILES
        controller/wanderer_controller.h
        controller/wanderer_controller_impl.cpp
        controller/wanderer_controller_impl.h
        controller/wanderer_controller_factory.h
        controller/input.cpp
        controller/input.h

        controller/gameloop/game_loop.h
        controller/gameloop/smooth_fixed_timestep_loop.cpp
        controller/gameloop/smooth_fixed_timestep_loop.h

        core/wanderer_core.h
        core/wanderer_core_impl.cpp
        core/wanderer_core_impl.h
        core/wanderer_core_factory.h
        core/game_object.h
        core/drawable.h
        core/direction.h
        core/viewport.cpp
        core/viewport.h
        core/animated.h
        core/sortable_drawable.h
        core/render_depth.h
        core/game_constants.h
        core/game_object_id.h
        core/game_object_id.cpp

        core/util/require.h
        core/util/bad_state_exception.h
        core/util/bad_state_exception.cpp

        core/math/hitbox.cpp
        core/math/hitbox.h
        core/math/vector_2.cpp
        core/math/vector_2.h
        core/math/random_utils.cpp
        core/math/random_utils.h
        core/math/math.h
        core/math/area.h
        core/math/tvector.h

        core/menu/menu.h
        core/menu/menu_id.h
        core/menu/menu_state_machine.h
        core/menu/menu_state_machine_impl.cpp
        core/menu/menu_state_machine_impl.h
        core/menu/home_menu.cpp
        core/menu/home_menu.h
        core/menu/in_game_menu.cpp
        core/menu/in_game_menu.h
        core/menu/menu_button.cpp
        core/menu/menu_button.h
        core/menu/settings_menu.cpp
        core/menu/settings_menu.h
        core/menu/abstract_menu.cpp
        core/menu/abstract_menu.h
        core/menu/controls_menu.cpp
        core/menu/controls_menu.h
        core/menu/inventory_menu.cpp
        core/menu/inventory_menu.h
        core/menu/menu_drawable.h

        core/level/portal.cpp
        core/level/portal.h

        core/level/tiles/tile.h
        core/level/tiles/tile.cpp
        core/level/tiles/tile_set.cpp
        core/level/tiles/tile_set.h
        core/level/tiles/tile_map_impl.cpp
        core/level/tiles/tile_map_impl.h
        core/level/tiles/tile_map_layer_impl.cpp
        core/level/tiles/tile_map_layer_impl.h
        core/level/tiles/tile_map_bounds.h
        core/level/tiles/tile_animation.cpp
        core/level/tiles/tile_animation.h
        core/level/tiles/tile_id.h
        core/level/tiles/tile_object.cpp
        core/level/tiles/tile_object.h
        core/level/tiles/map_position.h
        core/level/tiles/tile_map.h
        core/level/tiles/tile_map_layer.h
        core/level/tiles/tile_map_layer_builder.cpp
        core/level/tiles/tile_map_layer_builder.h
        core/level/tiles/tile_map_builder.cpp
        core/level/tiles/tile_map_builder.h
        core/level/tiles/tile_builder.cpp
        core/level/tiles/tile_builder.h
        core/level/tiles/tile_set_builder.cpp
        core/level/tiles/tile_set_builder.h

        core/entities/entity.h
        core/entities/movable_object.h
        core/entities/movable_delegate.cpp
        core/entities/movable_delegate.h
        core/entities/entity_sheet.cpp
        core/entities/entity_sheet.h
        core/entities/abstract_entity.cpp
        core/entities/abstract_entity.h
        core/entities/entity_manager.cpp
        core/entities/entity_manager.h
        core/entities/entity_id.h
        core/entities/spawnpoint.cpp
        core/entities/spawnpoint.h

        core/entities/skeleton/skeleton.cpp
        core/entities/skeleton/skeleton.h
        core/entities/skeleton/skeleton_state_machine.cpp
        core/entities/skeleton/skeleton_state_machine.h
        core/entities/skeleton/skeleton_idle_state.cpp
        core/entities/skeleton/skeleton_idle_state.h
        core/entities/skeleton/skeleton_moving_state.cpp
        core/entities/skeleton/skeleton_moving_state.h
        core/entities/skeleton/skeleton_attack_state.cpp
        core/entities/skeleton/skeleton_attack_state.h
        core/entities/skeleton/skeleton_dying_state.cpp
        core/entities/skeleton/skeleton_dying_state.h

        core/entities/player/player.h
        core/entities/player/player_impl.cpp
        core/entities/player/player_impl.h
        core/entities/player/player_moving_state.cpp
        core/entities/player/player_moving_state.h
        core/entities/player/player_idle_state.cpp
        core/entities/player/player_idle_state.h
        core/entities/player/player_state_machine_impl.cpp
        core/entities/player/player_state_machine_impl.h
        core/entities/player/player_attack_state.cpp
        core/entities/player/player_attack_state.h
        core/entities/player/player_dying_state.cpp
        core/entities/player/player_dying_state.h
        core/entities/player/player_state.h
        core/entities/player/player_state_machine.h

        core/entities/entitystate/abstract_entity_state_machine.h
        core/entities/entitystate/entity_state.h
        core/entities/entitystate/entity_state_machine.h
        core/entities/entitystate/entity_state_id.h

        core/entities/entitystate/delegates/entity_draw_delegate.cpp
        core/entities/entitystate/delegates/entity_draw_delegate.h
        core/entities/entitystate/delegates/entity_move_delegate.cpp
        core/entities/entitystate/delegates/entity_move_delegate.h
        core/entities/entitystate/delegates/entity_dying_delegate.cpp
        core/entities/entitystate/delegates/entity_dying_delegate.h
        core/entities/entitystate/delegates/entity_attack_delegate.cpp
        core/entities/entitystate/delegates/entity_attack_delegate.h
        core/entities/entitystate/delegates/entity_idle_delegate.cpp
        core/entities/entitystate/delegates/entity_idle_delegate.h

        visuals/animation.cpp
        visuals/animation.h
        visuals/font_bundle.cpp
        visuals/font_bundle.h
        visuals/hud.cpp
        visuals/hud.h

        audio/sound_engine.cpp
        audio/sound_engine.h

        service/menu_parser.h
        service/menu_parser.cpp
        service/pugi_utils.cpp
        service/pugi_utils.h

        ${TILED_INCLUDE_DIR}/tiled_map_parser.cpp
        ${TILED_INCLUDE_DIR}/tiled_map_parser.h
        ${TILED_INCLUDE_DIR}/tiled_map.cpp
        ${TILED_INCLUDE_DIR}/tiled_map.h
        ${TILED_INCLUDE_DIR}/tiled_tile_set.cpp
        ${TILED_INCLUDE_DIR}/tiled_tile_set.h
        ${TILED_INCLUDE_DIR}/tiled_animation.cpp
        ${TILED_INCLUDE_DIR}/tiled_animation.h
        ${TILED_INCLUDE_DIR}/tiled_object.cpp
        ${TILED_INCLUDE_DIR}/tiled_object.h
        ${TILED_INCLUDE_DIR}/tiled_layer.cpp
        ${TILED_INCLUDE_DIR}/tiled_layer.h
        ${TILED_INCLUDE_DIR}/tiled_tile.cpp
        ${TILED_INCLUDE_DIR}/tiled_tile.h
        ${TILED_INCLUDE_DIR}/tiled_property.h
        ${TILED_INCLUDE_DIR}/tiled_object_group.cpp
        ${TILED_INCLUDE_DIR}/tiled_object_group.h

        core/util/wanderer_stdinc.h

        core/menu/general_menu.h
        core/menu/general_menu.cpp
        core/action.h
        core/menu/button_action.h
        )

add_library(${WANDERER_LIB} ${SOURCE_FILES})

target_compile_options(${WANDERER_LIB} PRIVATE
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

set_target_properties(${WANDERER_LIB} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${LIBRARY_DIR})
target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${GSL_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${PUGI_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${CENTURION_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB} SYSTEM PUBLIC ${TILED_INCLUDE_DIR})

target_include_directories(${WANDERER_LIB} PUBLIC controller)
target_include_directories(${WANDERER_LIB} PUBLIC controller/gameloop)
target_include_directories(${WANDERER_LIB} PUBLIC core)
target_include_directories(${WANDERER_LIB} PUBLIC core/menu)
target_include_directories(${WANDERER_LIB} PUBLIC core/math)
target_include_directories(${WANDERER_LIB} PUBLIC core/level)
target_include_directories(${WANDERER_LIB} PUBLIC core/level/tiles)
target_include_directories(${WANDERER_LIB} PUBLIC core/util)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/player)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/skeleton)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/entitystate)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/entitystate/delegates)
target_include_directories(${WANDERER_LIB} PUBLIC visuals)
target_include_directories(${WANDERER_LIB} PUBLIC util)
target_include_directories(${WANDERER_LIB} PUBLIC service)
target_include_directories(${WANDERER_LIB} PUBLIC audio)

#include(CheckIPOSupported)
#check_ipo_supported(RESULT supported OUTPUT error)

#if (supported)
#    message(STATUS "IPO / LTO enabled")
#    set_property(TARGET ${WANDERER_LIB} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
#else ()
#    message(STATUS "IPO / LTO not supported: <${error}>")
#endif ()

target_link_libraries(${WANDERER_LIB}
        # PUBLIC ${CENTURION_LIBRARIES}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY})

# Prepares the actual executable
add_executable(${WANDERER_EXECUTABLE} main.cpp)
set_target_properties(${WANDERER_EXECUTABLE} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

target_link_libraries(${WANDERER_EXECUTABLE}
        PUBLIC mingw32
        PUBLIC ${WANDERER_LIB}
        # PUBLIC ${CENTURION_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES})

# Copies all of the files in the bin folder and puts them next to the executable
add_custom_command(
        TARGET ${WANDERER_EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${BINARIES_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})

# Copies all of the resources and puts the in the build folder
add_custom_command(
        TARGET ${WANDERER_EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCES_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/resources)

