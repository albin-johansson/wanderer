cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    game.hpp
    game.cpp
    wanderer_app.cpp
    wanderer_app.hpp
    game_loop.hpp

    component/animated.hpp
    component/animated_tile.hpp
    component/binds.hpp
    component/container_trigger.hpp
    component/depth_drawable.hpp
    component/gold.hpp
    component/hitbox.hpp
    component/humanoid_state.hpp
    component/inventory.hpp
    component/item.hpp
    component/level_switch_animation.hpp
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
    component/event/end_attack_event.hpp
    component/event/begin_humanoid_move_event.hpp
    component/event/end_humanoid_move_event.hpp
    component/event/interact_event.hpp
    component/event/switch_map_event.hpp
    component/event/level_fade_events.hpp
    component/event/show_inventory_event.hpp
    component/event/close_inventory_event.hpp

    core/centurion_utils.hpp
    core/cursor_manager.cpp
    core/cursor_manager.hpp
    core/direction.hpp
    core/game_constants.hpp
    core/graphics_context.cpp
    core/graphics_context.hpp
    core/make_renderer.cpp
    core/make_renderer.hpp
    core/null_entity.hpp
    core/serialization.hpp
    core/stack_resource.hpp

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

    core/event/event_connections.cpp
    core/event/event_connections.hpp
    core/event/make_dispatcher.cpp
    core/event/make_dispatcher.hpp

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

    core/registry/add_humanoid_state_dependencies.cpp
    core/registry/add_humanoid_state_dependencies.hpp
    core/registry/make_registry.cpp
    core/registry/make_registry.hpp

    core/resource/texture_loader.hpp

    menu/key_bind.hpp
    menu/menu.cpp
    menu/menu.hpp
    menu/menu_action.hpp
    menu/menu_button.cpp
    menu/menu_button.hpp
    menu/menu_constants.hpp
    menu/menu_id.hpp
    menu/menu_manager.cpp
    menu/menu_manager.hpp

    parse/map/parse_ir.hpp
    parse/map/parse_layers.cpp
    parse/map/parse_layers.hpp
    parse/map/parse_object_layer.cpp
    parse/map/parse_object_layer.hpp
    parse/map/parse_tile.cpp
    parse/map/parse_tile.hpp
    parse/map/parse_tile_layer.cpp
    parse/map/parse_tile_layer.hpp
    parse/map/parse_tilesets.cpp
    parse/map/parse_tilesets.hpp
    parse/map/parse_world.cpp
    parse/map/parse_world.hpp

    parse/menu/parse_menu.cpp
    parse/menu/parse_menu.hpp

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
    system/viewport/viewport_system.hpp
    )

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

wanderer_set_compiler_options(${WANDERER_LIB_TARGET})

target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/cereal)
add_header_only_lib(libENTT ${LIBRARY_DIR}/entt ${LIBRARY_DIR}/entt/entt.hpp)
add_header_only_lib(libJSON ${LIBRARY_DIR}/json ${LIBRARY_DIR}/json/json.hpp)
add_header_only_lib(libABBY ${LIBRARY_DIR}/abby ${LIBRARY_DIR}/abby/abby.hpp)

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
    PUBLIC core
    PUBLIC core/math
    PUBLIC core/resource
    PUBLIC core/aliases
    PUBLIC core/level
    PUBLIC core/registry
    PUBLIC core/event
    PUBLIC component
    PUBLIC component/event
    PUBLIC system
    PUBLIC system/input
    PUBLIC system/humanoid
    PUBLIC system/saves
    PUBLIC system/tile
    PUBLIC system/layer
    PUBLIC system/viewport
    PUBLIC system/collision
    PUBLIC system/menu
    PUBLIC system/movement
    PUBLIC system/hud
    PUBLIC menu
    PUBLIC parse
    PUBLIC parse/map
    PUBLIC parse/menu)

#target_compile_definitions(${WANDERER_LIB} PUBLIC WANDERER_DEBUG)

target_link_libraries(${WANDERER_LIB_TARGET}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC libENTT
    PUBLIC libJSON
    PUBLIC libABBY
    PUBLIC libNamedType)

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
