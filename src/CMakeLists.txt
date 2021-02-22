cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    game.hpp
    game.cpp
    wanderer_engine.cpp
    wanderer_engine.hpp
    game_loop.hpp

    component/animated.hpp
    component/animated_tile.hpp
    component/container_trigger.hpp
    component/cursors.hpp
    component/depth_drawable.hpp
    component/gold.hpp
    component/hitbox.hpp
    component/humanoid_state.hpp
    component/inventory.hpp
    component/item.hpp
    component/level_switch_animation.hpp
    component/menu.hpp
    component/movable.hpp
    component/object.hpp
    component/particle.hpp
    component/player.hpp
    component/portal.hpp
    component/render_bounds.hpp
    component/spawnpoint.hpp
    component/tile.hpp
    component/tile_layer.hpp
    component/tile_object.hpp
    component/tilemap.hpp
    component/tileset.hpp
    component/viewport.hpp

    component/event/begin_attack_event.hpp
    component/event/begin_humanoid_move_event.hpp
    component/event/close_inventory_event.hpp
    component/event/end_attack_event.hpp
    component/event/end_humanoid_move_event.hpp
    component/event/interact_event.hpp
    component/event/level_fade_events.hpp
    component/event/particle_event.hpp
    component/event/quit_event.hpp
    component/event/show_inventory_event.hpp
    component/event/switch_map_event.hpp
    component/event/switch_menu_event.hpp

    component/input/binds.hpp
    component/input/button.hpp
    component/input/key_bind.hpp

    core/centurion_utils.hpp
    core/direction.hpp
    core/game_constants.hpp
    core/graphics_context.cpp
    core/graphics_context.hpp
    core/make_renderer.cpp
    core/make_renderer.hpp
    core/menu_constants.hpp
    core/menu_id.hpp
    core/null_entity.hpp
    core/serialization.hpp
    core/stack_resource.hpp

    core/action/action.hpp
    core/action/quit_action.cpp
    core/action/quit_action.hpp
    core/action/switch_menu_action.cpp
    core/action/switch_menu_action.hpp

    core/aliases/aabb_tree.hpp
    core/aliases/buffer.hpp
    core/aliases/delta.hpp
    core/aliases/depth.hpp
    core/aliases/entity_type.hpp
    core/aliases/ints.hpp
    core/aliases/map_id.hpp
    core/aliases/maybe.hpp
    core/aliases/milliseconds.hpp
    core/aliases/texture_cache.hpp
    core/aliases/texture_handle.hpp
    core/aliases/texture_id.hpp
    core/aliases/tile_id.hpp

    core/ecs/event_connections.cpp
    core/ecs/event_connections.hpp
    core/ecs/make_dispatcher.cpp
    core/ecs/make_dispatcher.hpp

    core/level/add_ground_layers.cpp
    core/level/add_ground_layers.hpp
    core/level/add_objects.cpp
    core/level/add_objects.hpp
    core/level/add_tile_objects.cpp
    core/level/add_tile_objects.hpp
    core/level/create_tilemap.cpp
    core/level/create_tilemap.hpp
    core/level/create_tileset.cpp
    core/level/create_tileset.hpp
    core/level/level.cpp
    core/level/level.hpp
    core/level/level_manager.cpp
    core/level/level_manager.hpp

    core/math/angles.hpp
    core/math/floating.hpp
    core/math/get_random.hpp
    core/math/index_to_matrix.hpp
    core/math/vector2.hpp

    core/ecs/add_humanoid_state_dependencies.cpp
    core/ecs/add_humanoid_state_dependencies.hpp
    core/ecs/make_registry.cpp
    core/ecs/make_registry.hpp
    core/ecs/registry_utils.hpp

    core/resource/texture_loader.hpp

    io/map/parse_ir.hpp
    io/map/parse_layers.cpp
    io/map/parse_layers.hpp
    io/map/parse_object_layer.cpp
    io/map/parse_object_layer.hpp
    io/map/parse_tile.cpp
    io/map/parse_tile.hpp
    io/map/parse_tile_layer.cpp
    io/map/parse_tile_layer.hpp
    io/map/parse_tilesets.cpp
    io/map/parse_tilesets.hpp
    io/map/parse_world.cpp
    io/map/parse_world.hpp

    io/menu/menu_action.hpp
    io/menu/parse_menu.cpp
    io/menu/parse_menu.hpp

    io/saves/load_game.cpp
    io/saves/load_game.hpp
    io/saves/parse_save_file.cpp
    io/saves/parse_save_file.hpp
    io/saves/save_file_info.hpp
    io/saves/save_game.cpp
    io/saves/save_game.hpp

    io/files_directory.cpp
    io/files_directory.hpp
    io/ini.hpp

    system/animation_system.cpp
    system/animation_system.hpp
    system/depth_drawables_system.cpp
    system/depth_drawables_system.hpp
    system/interaction_handler_system.cpp
    system/interaction_handler_system.hpp
    system/inventory_system.cpp
    system/inventory_system.hpp
    system/particle_system.cpp
    system/particle_system.hpp
    system/render_bounds_system.cpp
    system/render_bounds_system.hpp
    system/update_triggers.hpp

    system/hud/level_switch_animation_system.cpp
    system/hud/level_switch_animation_system.hpp

    system/humanoid/humanoid_animation_system.cpp
    system/humanoid/humanoid_animation_system.hpp
    system/humanoid/humanoid_attack_event_handler.cpp
    system/humanoid/humanoid_attack_event_handler.hpp
    system/humanoid/humanoid_factory_system.cpp
    system/humanoid/humanoid_factory_system.hpp
    system/humanoid/humanoid_move_event_handler.cpp
    system/humanoid/humanoid_move_event_handler.hpp
    system/humanoid/humanoid_state_system.cpp
    system/humanoid/humanoid_state_system.hpp

    system/input/idle_input_system.cpp
    system/input/idle_input_system.hpp
    system/input/input_system.cpp
    system/input/input_system.hpp
    system/input/move_input_system.cpp
    system/input/move_input_system.hpp

    system/layer/layer_rendering_system.cpp
    system/layer/layer_rendering_system.hpp
    system/layer/layer_system.hpp

    system/menu/button_system.cpp
    system/menu/button_system.hpp
    system/menu/menu_system.cpp
    system/menu/menu_system.hpp

    system/movement/hitbox_system.cpp
    system/movement/hitbox_system.hpp
    system/movement/movable_system.hpp
    system/movement/movable_system.cpp
    system/movement/movement_system.cpp
    system/movement/movement_system.hpp
    system/movement/portal_system.cpp
    system/movement/portal_system.hpp

    system/saves/saves_system.cpp
    system/saves/saves_system.hpp

    system/tile/tile_animation_system.cpp
    system/tile/tile_animation_system.hpp
    system/tile/tile_rendering_system.cpp
    system/tile/tile_rendering_system.hpp

    system/viewport/make_viewport.cpp
    system/viewport/make_viewport.hpp
    system/viewport/viewport_system.cpp
    system/viewport/viewport_system.hpp)

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

wanderer_set_compiler_options(${WANDERER_LIB_TARGET})

target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/cereal)
add_header_only_lib(libENTT ${LIBRARY_DIR}/entt ${LIBRARY_DIR}/entt/entt.hpp)
add_header_only_lib(libJSON ${LIBRARY_DIR}/json ${LIBRARY_DIR}/json/json.hpp)
add_header_only_lib(libABBY ${LIBRARY_DIR}/abby ${LIBRARY_DIR}/abby/abby.hpp)
add_header_only_lib(libDate ${LIBRARY_DIR}/date ${LIBRARY_DIR}/date/date.h)

set(NAMED_TYPE_SOURCES
    ${LIBRARY_DIR}/namedtype/named_type.hpp
    ${LIBRARY_DIR}/namedtype/named_type_impl.hpp
    ${LIBRARY_DIR}/namedtype/crtp.hpp
    ${LIBRARY_DIR}/namedtype/underlying_functionalities.hpp)
add_header_only_lib(libNamedType ${LIBRARY_DIR}/namedtype ${NAMED_TYPE_SOURCES})

# Library directories
target_include_directories(${WANDERER_LIB_TARGET}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${LIBRARY_DIR}/centurion
    SYSTEM PUBLIC ${LIBRARY_DIR}/step)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET}
    PUBLIC .
    PUBLIC component
    PUBLIC component/event
    PUBLIC component/input
    PUBLIC core
    PUBLIC core/action
    PUBLIC core/aliases
    PUBLIC core/ecs
    PUBLIC core/level
    PUBLIC core/math
    PUBLIC core/resource
    PUBLIC io
    PUBLIC io/map
    PUBLIC io/menu
    PUBLIC io/saves
    PUBLIC system
    PUBLIC system/hud
    PUBLIC system/humanoid
    PUBLIC system/input
    PUBLIC system/layer
    PUBLIC system/menu
    PUBLIC system/movement
    PUBLIC system/saves
    PUBLIC system/tile
    PUBLIC system/viewport)

#target_compile_definitions(${WANDERER_LIB} PUBLIC WANDERER_DEBUG)

target_link_libraries(${WANDERER_LIB_TARGET}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC libENTT
    PUBLIC libJSON
    PUBLIC libABBY
    PUBLIC libNamedType
    PUBLIC libDate)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  add_executable(${WANDERER_EXE_TARGET} WIN32 main.cpp)
else ()
  add_executable(${WANDERER_EXE_TARGET} main.cpp)
endif ()

target_link_libraries(${WANDERER_EXE_TARGET} PUBLIC ${WANDERER_LIB_TARGET})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  copy_directory_post_build(${WANDERER_EXE_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resource)
