cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    game.hpp
    game.cpp
    wanderer_engine.cpp
    wanderer_engine.hpp
    semi_fixed_game_loop.hpp

    components/animated.hpp
    components/animated_tile.hpp
    components/chase.hpp
    components/cursors.hpp
    components/depth_drawable.hpp
    components/hitbox.hpp
    components/humanoid_state.hpp
    components/level_switch_animation.hpp
    components/movable.hpp
    components/object.hpp
    components/particle.hpp
    components/player.hpp
    components/portal.hpp
    components/render_bounds.hpp
    components/spawnpoint.hpp
    components/tile.hpp
    components/tile_layer.hpp
    components/tile_object.hpp
    components/tilemap.hpp
    components/tileset.hpp
    components/viewport.hpp

    components/events/begin_attack_event.hpp
    components/events/begin_humanoid_move_event.hpp
    components/events/button_pressed_event.hpp
    components/events/close_inventory_event.hpp
    components/events/end_attack_event.hpp
    components/events/end_humanoid_move_event.hpp
    components/events/interact_event.hpp
    components/events/level_fade_events.hpp
    components/events/particle_event.hpp
    components/events/quit_event.hpp
    components/events/show_inventory_event.hpp
    components/events/switch_map_event.hpp
    components/events/switch_menu_event.hpp

    components/input/binds.hpp
    components/input/key_bind.hpp

    components/inventory/container_trigger.hpp
    components/inventory/gold.hpp
    components/inventory/inventory.hpp
    components/inventory/item.hpp

    components/ui/button.hpp
    components/ui/checkbox.hpp
    components/ui/label.hpp
    components/ui/line.hpp
    components/ui/menu.hpp
    components/ui/saves_menu.hpp

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
    core/render_text.cpp
    core/render_text.hpp
    core/serialization.hpp
    core/stack_resource.hpp

    core/actions/action.hpp
    core/actions/quit_action.cpp
    core/actions/quit_action.hpp
    core/actions/switch_menu_action.cpp
    core/actions/switch_menu_action.hpp

    core/aliases/aabb_tree.hpp
    core/aliases/buffer.hpp
    core/aliases/delta.hpp
    core/aliases/depth.hpp
    core/aliases/entity_type.hpp
    core/aliases/ints.hpp
    core/aliases/map_id.hpp
    core/aliases/maybe.hpp
    core/aliases/milliseconds.hpp
    core/aliases/texture_handle.hpp
    core/aliases/texture_id.hpp
    core/aliases/texture_index.hpp
    core/aliases/tile_id.hpp

    core/ecs/event_connections.cpp
    core/ecs/event_connections.hpp
    core/ecs/make_dispatcher.cpp
    core/ecs/make_dispatcher.hpp

    core/levels/add_ground_layers.cpp
    core/levels/add_ground_layers.hpp
    core/levels/add_objects.cpp
    core/levels/add_objects.hpp
    core/levels/add_tile_objects.cpp
    core/levels/add_tile_objects.hpp
    core/levels/create_tilemap.cpp
    core/levels/create_tilemap.hpp
    core/levels/create_tileset.cpp
    core/levels/create_tileset.hpp
    core/levels/level.cpp
    core/levels/level.hpp
    core/levels/level_manager.cpp
    core/levels/level_manager.hpp

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

    core/resources/texture_loader.hpp

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

    systems/animation_system.cpp
    systems/animation_system.hpp
    systems/chase_system.cpp
    systems/chase_system.hpp
    systems/depth_drawables_system.cpp
    systems/depth_drawables_system.hpp
    systems/interaction_handler_system.cpp
    systems/interaction_handler_system.hpp
    systems/inventory_system.cpp
    systems/inventory_system.hpp
    systems/particle_system.cpp
    systems/particle_system.hpp
    systems/render_bounds_system.cpp
    systems/render_bounds_system.hpp
    systems/update_triggers.hpp

    systems/hud/level_switch_animation_system.cpp
    systems/hud/level_switch_animation_system.hpp

    systems/humanoid/humanoid_animation_system.cpp
    systems/humanoid/humanoid_animation_system.hpp
    systems/humanoid/humanoid_attack_event_handler.cpp
    systems/humanoid/humanoid_attack_event_handler.hpp
    systems/humanoid/humanoid_factory_system.cpp
    systems/humanoid/humanoid_factory_system.hpp
    systems/humanoid/humanoid_move_event_handler.cpp
    systems/humanoid/humanoid_move_event_handler.hpp
    systems/humanoid/humanoid_state_system.cpp
    systems/humanoid/humanoid_state_system.hpp

    systems/input/idle_input_system.cpp
    systems/input/idle_input_system.hpp
    systems/input/input_system.cpp
    systems/input/input_system.hpp
    systems/input/key_bind_system.cpp
    systems/input/key_bind_system.hpp
    systems/input/move_input_system.cpp
    systems/input/move_input_system.hpp

    systems/layer/layer_rendering_system.cpp
    systems/layer/layer_rendering_system.hpp
    systems/layer/layer_system.hpp

    systems/movement/hitbox_system.cpp
    systems/movement/hitbox_system.hpp
    systems/movement/movable_system.hpp
    systems/movement/movable_system.cpp
    systems/movement/movement_system.cpp
    systems/movement/movement_system.hpp
    systems/movement/portal_system.cpp
    systems/movement/portal_system.hpp

    systems/saves/saves_system.cpp
    systems/saves/saves_system.hpp

    systems/tile/tile_animation_system.cpp
    systems/tile/tile_animation_system.hpp
    systems/tile/tile_rendering_system.cpp
    systems/tile/tile_rendering_system.hpp

    systems/ui/create_action.cpp
    systems/ui/create_action.hpp
    systems/ui/grid_system.hpp
    systems/ui/menu_system.cpp
    systems/ui/menu_system.hpp
    systems/ui/saves_menu_system.cpp
    systems/ui/saves_menu_system.hpp
    systems/ui/settings_menu_system.cpp
    systems/ui/settings_menu_system.hpp

    systems/ui/buttons/button_factory_system.cpp
    systems/ui/buttons/button_factory_system.hpp
    systems/ui/buttons/button_rendering_system.cpp
    systems/ui/buttons/button_rendering_system.hpp
    systems/ui/buttons/button_system.cpp
    systems/ui/buttons/button_system.hpp

    systems/ui/checkboxes/checkbox_factory_system.cpp
    systems/ui/checkboxes/checkbox_factory_system.hpp
    systems/ui/checkboxes/checkbox_rendering_system.cpp
    systems/ui/checkboxes/checkbox_rendering_system.hpp

    systems/ui/labels/label_rendering_system.cpp
    systems/ui/labels/label_rendering_system.hpp
    systems/ui/labels/make_label.cpp
    systems/ui/labels/make_label.hpp

    systems/ui/lines/line_rendering_system.cpp
    systems/ui/lines/line_rendering_system.hpp
    systems/ui/lines/make_line.cpp
    systems/ui/lines/make_line.hpp

    systems/ui/menus/menu_factory_system.cpp
    systems/ui/menus/menu_factory_system.hpp
    systems/ui/menus/menu_rendering_system.cpp
    systems/ui/menus/menu_rendering_system.hpp

    systems/viewport/make_viewport.cpp
    systems/viewport/make_viewport.hpp
    systems/viewport/viewport_system.cpp
    systems/viewport/viewport_system.hpp
    )

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

wanderer_set_compiler_options(${WANDERER_LIB_TARGET})

target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC ${LIBRARY_DIR}/cereal)
add_header_only_lib(libENTT ${LIBRARY_DIR}/entt ${LIBRARY_DIR}/entt/entt.hpp)
add_header_only_lib(libJSON ${LIBRARY_DIR}/json ${LIBRARY_DIR}/json/json.hpp)
add_header_only_lib(libABBY ${LIBRARY_DIR}/abby ${LIBRARY_DIR}/abby/abby.hpp)
add_header_only_lib(libDate ${LIBRARY_DIR}/date ${LIBRARY_DIR}/date/date.h)
add_header_only_lib(libCenturion ${LIBRARY_DIR}/centurion ${LIBRARY_DIR}/centurion/centurion.hpp)

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
    SYSTEM PUBLIC ${LIBRARY_DIR}/step)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET}
    PUBLIC .
    PUBLIC components
    PUBLIC components/events
    PUBLIC components/input
    PUBLIC components/inventory
    PUBLIC components/ui
    PUBLIC core
    PUBLIC core/actions
    PUBLIC core/aliases
    PUBLIC core/ecs
    PUBLIC core/levels
    PUBLIC core/math
    PUBLIC core/resources
    PUBLIC io
    PUBLIC io/map
    PUBLIC io/menu
    PUBLIC io/saves
    PUBLIC systems
    PUBLIC systems/hud
    PUBLIC systems/humanoid
    PUBLIC systems/input
    PUBLIC systems/layer
    PUBLIC systems/ui
    PUBLIC systems/ui/buttons
    PUBLIC systems/ui/checkboxes
    PUBLIC systems/ui/labels
    PUBLIC systems/ui/lines
    PUBLIC systems/ui/menus
    PUBLIC systems/movement
    PUBLIC systems/saves
    PUBLIC systems/tile
    PUBLIC systems/viewport)

#target_compile_definitions(${WANDERER_LIB} PUBLIC WANDERER_DEBUG)

target_link_libraries(${WANDERER_LIB_TARGET}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC libCenturion
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

copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources)
