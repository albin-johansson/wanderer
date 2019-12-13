cmake_minimum_required(VERSION 3.15)
project(${CMAKE_PROJECT_NAME}_src)

set(SOURCE_FILES
        service/bool_converter.h
        service/display_modes.cpp
        service/display_modes.h

        controller/key_state_manager.cpp
        controller/key_state_manager.h
        controller/wanderer_controller.h
        controller/wanderer_controller_impl.cpp
        controller/wanderer_controller_impl.h
        controller/wanderer_controller_factory.h
        controller/mouse_state_manager.cpp
        controller/mouse_state_manager.h

        controller/gameloop/game_loop.h
        controller/gameloop/smooth_fixed_timestep_loop.cpp
        controller/gameloop/smooth_fixed_timestep_loop.h

        core/wanderer_core.h
        core/wanderer_core_impl.cpp
        core/wanderer_core_impl.h
        core/wanderer_core_factory.h
        core/objects.h
        core/game_object.h
        core/drawable.h
        core/direction.h

        core/math/rectangle.cpp
        core/math/rectangle.h
        core/math/vector_2.cpp
        core/math/vector_2.h
        core/math/random_utils.cpp
        core/math/random_utils.h

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

        core/bad_state_exception.cpp
        core/bad_state_exception.h
        core/input.cpp
        core/input.h
        core/viewport.cpp
        core/viewport.h
        core/animated.h

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

        service/tiled/pugixml/pugixml.hpp
        service/tiled/pugixml/pugixml.cpp
        service/tiled/pugixml/pugiconfig.hpp
        service/tiled/tiled_map_parser.cpp
        service/tiled/tiled_map_parser.h

        core/item/item.h

        core/entities/entity.h
        core/entities/player.h
        core/entities/player_impl.cpp
        core/entities/player_impl.h
        core/entities/movable_object.h
        core/entities/movable_delegate.cpp
        core/entities/movable_delegate.h
        core/entities/entity_sheet.cpp
        core/entities/entity_sheet.h
        core/entities/abstract_entity.cpp
        core/entities/abstract_entity.h

        core/entities/mob/skeleton/skeleton.cpp
        core/entities/mob/skeleton/skeleton.h
        core/entities/mob/skeleton/skeleton_state_machine.cpp
        core/entities/mob/skeleton/skeleton_state_machine.h
        core/entities/mob/skeleton/skeleton_idle_state.cpp
        core/entities/mob/skeleton/skeleton_idle_state.h
        core/entities/mob/skeleton/skeleton_moving_state.cpp
        core/entities/mob/skeleton/skeleton_moving_state.h
        core/entities/mob/skeleton/skeleton_attack_state.cpp
        core/entities/mob/skeleton/skeleton_attack_state.h

        core/entities/entitystate/playerstate/player_moving_state.cpp
        core/entities/entitystate/playerstate/player_moving_state.h
        core/entities/entitystate/playerstate/player_idle_state.cpp
        core/entities/entitystate/playerstate/player_idle_state.h
        core/entities/entitystate/playerstate/player_state_machine_impl.cpp
        core/entities/entitystate/playerstate/player_state_machine_impl.h
        core/entities/entitystate/playerstate/player_attack_state.cpp
        core/entities/entitystate/playerstate/player_attack_state.h
        core/entities/entitystate/playerstate/player_dying_state.cpp
        core/entities/entitystate/playerstate/player_dying_state.h
        core/entities/entitystate/playerstate/player_state.h
        core/entities/entitystate/playerstate/player_state_machine.h

        core/entities/entitystate/abstract_entity_state_machine.h
        core/entities/entitystate/entity_draw_delegate.cpp
        core/entities/entitystate/entity_draw_delegate.h
        core/entities/entitystate/entity_state.h
        core/entities/entitystate/entity_state_machine.h
        core/entities/entitystate/entity_state_id.h
        core/entities/entitystate/entity_move_delegate.cpp
        core/entities/entitystate/entity_move_delegate.h
        core/entities/entitystate/entity_dying_delegate.cpp
        core/entities/entitystate/entity_dying_delegate.h
        core/entities/entitystate/entity_attack_delegate.cpp
        core/entities/entitystate/entity_attack_delegate.h
        core/entities/entitystate/entity_idle_delegate.cpp
        core/entities/entitystate/entity_idle_delegate.h

        visuals/window.h
        visuals/window.cpp
        visuals/renderer.h
        visuals/renderer.cpp
        visuals/image.cpp
        visuals/image.h
        visuals/animation.cpp
        visuals/animation.h
        visuals/image_generator.cpp
        visuals/image_generator.h
        visuals/font.cpp
        visuals/font.h

        audio/sound_effect.cpp
        audio/sound_effect.h
        audio/sound_engine.cpp
        audio/sound_engine.h

        visuals/font_bundle.cpp
        visuals/font_bundle.h

        core/level/portal.cpp
        core/level/portal.h
        core/level/tiles/tile_map.h
        core/level/tiles/tile_map_layer.h

        service/tiled/tiled_map.cpp
        service/tiled/tiled_map.h
        service/tiled/tiled_tile_set.cpp
        service/tiled/tiled_tile_set.h
        service/tiled/tiled_animation.cpp
        service/tiled/tiled_animation.h
        service/tiled/tiled_object.cpp
        service/tiled/tiled_object.h
        service/tiled/tiled_layer.cpp
        service/tiled/tiled_layer.h
        service/tiled/tiled_tile.cpp
        service/tiled/tiled_tile.h
        service/tiled/tiled_property.h

        core/sortable_drawable.h
        core/level/tiles/tile_object.cpp
        core/level/tiles/tile_object.h core/level/tiles/map_position.h core/render_depth.h)

# Prepares the Wanderer "library", which excludes linking and the main.cpp file
add_library(${WANDERER_LIB} ${SOURCE_FILES})

target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${WANDERER_LIB} PUBLIC controller)
target_include_directories(${WANDERER_LIB} PUBLIC controller/gameloop)
target_include_directories(${WANDERER_LIB} PUBLIC core)
target_include_directories(${WANDERER_LIB} PUBLIC visuals)
target_include_directories(${WANDERER_LIB} PUBLIC core/menu)
target_include_directories(${WANDERER_LIB} PUBLIC util)
target_include_directories(${WANDERER_LIB} PUBLIC service)
target_include_directories(${WANDERER_LIB} PUBLIC service/tiled)
target_include_directories(${WANDERER_LIB} PUBLIC service/tiled/pugixml)
target_include_directories(${WANDERER_LIB} PUBLIC core/math)
target_include_directories(${WANDERER_LIB} PUBLIC core/level)
target_include_directories(${WANDERER_LIB} PUBLIC core/level/tiles)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/entitystate)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/entitystate/playerstate)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/mob)
target_include_directories(${WANDERER_LIB} PUBLIC core/entities/mob/skeleton)
target_include_directories(${WANDERER_LIB} PUBLIC audio)

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
        ${CMAKE_BINARY_DIR}/src/resources)

