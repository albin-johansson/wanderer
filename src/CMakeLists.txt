cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    game.hpp
    game.cpp
    wanderer_engine.cpp
    wanderer_engine.hpp
    semi_fixed_game_loop.hpp

    components/chase.hpp
    components/float3.hpp
    components/hitbox.hpp
    components/humanoid_state.hpp
    components/movable.hpp
    components/object.hpp

    components/graphics/animated.hpp
    components/graphics/animated_tile.hpp
    components/graphics/depth_drawable.hpp
    components/graphics/level_switch_animation.hpp
    components/graphics/particle.hpp
    components/graphics/point_light.hpp

    components/input/key_bind.hpp

    components/inventory/container_trigger.hpp
    components/inventory/inventory.hpp
    components/inventory/item.hpp

    components/map/portal.hpp
    components/map/spawnpoint.hpp
    components/map/tile.hpp
    components/map/tile_layer.hpp
    components/map/tile_object.hpp
    components/map/tilemap.hpp

    components/ui/associated_menu.hpp
    components/ui/button.hpp
    components/ui/button_group.hpp
    components/ui/checkbox.hpp
    components/ui/cursors.hpp
    components/ui/label.hpp
    components/ui/line.hpp
    components/ui/menu.hpp
    components/ui/saves_menu.hpp

    core/centurion_utils.hpp
    core/common_concepts.hpp
    core/direction.hpp
    core/game_constants.hpp
    core/graphics_context.cpp
    core/graphics_context.hpp
    core/input.hpp
    core/make_renderer.cpp
    core/make_renderer.hpp
    core/menu_constants.hpp
    core/menu_id.hpp
    core/nenya.hpp
    core/null_entity.hpp
    core/render_text.cpp
    core/render_text.hpp
    core/serialization.hpp
    core/stack_resource.hpp
    core/text_size.hpp

    core/aliases/aabb_tree.hpp
    core/aliases/buffer.hpp
    core/aliases/delta.hpp
    core/aliases/depth.hpp
    core/aliases/entity_type.hpp
    core/aliases/float2.hpp
    core/aliases/ints.hpp
    core/aliases/map_id.hpp
    core/aliases/maybe.hpp
    core/aliases/milliseconds.hpp
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

    core/resources/resources.cpp
    core/resources/resources.hpp

    core/settings/setting_id.hpp

    ctx/active_menu.hpp
    ctx/binds.hpp
    ctx/outside_level.hpp
    ctx/player.hpp
    ctx/render_bounds.hpp
    ctx/settings.hpp
    ctx/tileset.hpp
    ctx/time_of_day.hpp
    ctx/viewport.hpp

    events/begin_attack_event.hpp
    events/begin_humanoid_move_event.hpp
    events/button_pressed_event.hpp
    events/close_inventory_event.hpp
    events/end_attack_event.hpp
    events/end_humanoid_move_event.hpp
    events/fullscreen_toggled_event.hpp
    events/integer_scaling_toggled_event.hpp
    events/interact_event.hpp
    events/level_fade_events_event.hpp
    events/quit_event.hpp
    events/show_inventory_event.hpp
    events/spawn_particles_event.hpp
    events/switch_map_event.hpp
    events/switch_menu_event.hpp

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

    systems/interaction_system.cpp
    systems/interaction_system.hpp
    systems/inventory_system.cpp
    systems/inventory_system.hpp
    systems/time_system.cpp
    systems/time_system.hpp
    systems/update_triggers.hpp

    systems/ai/chase_system.cpp
    systems/ai/chase_system.hpp

    systems/configuration/load_binds_system.cpp
    systems/configuration/load_binds_system.hpp
    systems/configuration/settings_system.cpp
    systems/configuration/settings_system.hpp

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

    systems/input/handle_idle_input.cpp
    systems/input/input_system.cpp
    systems/input/input_system.hpp
    systems/input/key_bind_system.cpp
    systems/input/key_bind_system.hpp
    systems/input/handle_move_input.cpp

    systems/layers/render_ground_layers.cpp
    systems/layers/layer_system.hpp

    systems/movement/hitbox_system.cpp
    systems/movement/hitbox_system.hpp
    systems/movement/movable_system.hpp
    systems/movement/movable_system.cpp
    systems/movement/movement_system.cpp
    systems/movement/movement_system.hpp
    systems/movement/portal_system.cpp
    systems/movement/portal_system.hpp

    systems/graphics/animation_system.cpp
    systems/graphics/animation_system.hpp
    systems/graphics/debug_rendering_system.cpp
    systems/graphics/debug_rendering_system.hpp
    systems/graphics/depth_system.cpp
    systems/graphics/depth_system.hpp
    systems/graphics/drawable_system.cpp
    systems/graphics/drawable_system.hpp
    systems/graphics/light_system.cpp
    systems/graphics/light_system.hpp
    systems/graphics/make_viewport.cpp
    systems/graphics/particle_system.hpp
    systems/graphics/particle_system.cpp
    systems/graphics/render_bounds_system.cpp
    systems/graphics/render_bounds_system.hpp
    systems/graphics/tile_animation_system.cpp
    systems/graphics/tile_animation_system.hpp
    systems/graphics/tile_object_animation_system.cpp
    systems/graphics/tile_object_animation_system.hpp
    systems/graphics/tile_rendering_system.cpp
    systems/graphics/tile_rendering_system.hpp
    systems/graphics/viewport_system.cpp
    systems/graphics/viewport_system.hpp

    systems/saves/saves_system.cpp
    systems/saves/saves_system.hpp

    systems/ui/grid.hpp

    systems/ui/buttons/button_factory_system.cpp
    systems/ui/buttons/button_system.cpp
    systems/ui/buttons/button_system.hpp
    systems/ui/buttons/render_button_group.cpp
    systems/ui/buttons/render_buttons.cpp

    systems/ui/checkboxes/add_checkbox.cpp
    systems/ui/checkboxes/checkbox_system.hpp
    systems/ui/checkboxes/render_checkboxes.cpp

    systems/ui/hud/level_switch_animation_system.cpp
    systems/ui/hud/level_switch_animation_system.hpp

    systems/ui/labels/label_system.hpp
    systems/ui/labels/make_label.cpp
    systems/ui/labels/render_labels.cpp

    systems/ui/lines/line_system.hpp
    systems/ui/lines/make_line.cpp
    systems/ui/lines/render_lines.cpp

    systems/ui/menus/create_controls_menu.cpp
    systems/ui/menus/create_controls_menu.hpp
    systems/ui/menus/create_home_menu.cpp
    systems/ui/menus/create_home_menu.hpp
    systems/ui/menus/create_in_game_menu.cpp
    systems/ui/menus/create_in_game_menu.hpp
    systems/ui/menus/create_saves_menu.cpp
    systems/ui/menus/create_settings_menu.cpp
    systems/ui/menus/create_settings_menu.hpp
    systems/ui/menus/make_menu.cpp
    systems/ui/menus/render_menu.cpp
    systems/ui/menus/menu_system.cpp
    systems/ui/menus/menu_system.hpp
    systems/ui/menus/saves_menu_system.cpp
    systems/ui/menus/saves_menu_system.hpp
    systems/ui/menus/sync_settings_menu.cpp
    )

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

wanderer_set_compiler_options(${WANDERER_LIB_TARGET})

add_header_only_lib(libENTT ${LIBRARY_DIR}/entt ${LIBRARY_DIR}/entt/entt.hpp)
add_header_only_lib(libJSON ${LIBRARY_DIR}/json ${LIBRARY_DIR}/json/json.hpp)
add_header_only_lib(libABBY ${LIBRARY_DIR}/abby ${LIBRARY_DIR}/abby/abby.hpp)
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
    SYSTEM PUBLIC ${LIBRARY_DIR}/cereal
    SYSTEM PUBLIC ${LIBRARY_DIR}/step)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET}
    PUBLIC .
    PUBLIC components
    PUBLIC components/graphics
    PUBLIC components/input
    PUBLIC components/inventory
    PUBLIC components/map
    PUBLIC components/ui
    PUBLIC core
    PUBLIC core/aliases
    PUBLIC core/ecs
    PUBLIC core/levels
    PUBLIC core/math
    PUBLIC core/resources
    PUBLIC core/settings
    PUBLIC ctx
    PUBLIC events
    PUBLIC io
    PUBLIC io/map
    PUBLIC io/menu
    PUBLIC io/saves
    PUBLIC systems
    PUBLIC systems/ai
    PUBLIC systems/configuration
    PUBLIC systems/graphics
    PUBLIC systems/humanoid
    PUBLIC systems/input
    PUBLIC systems/layers
    PUBLIC systems/ui
    PUBLIC systems/ui/buttons
    PUBLIC systems/ui/checkboxes
    PUBLIC systems/ui/hud
    PUBLIC systems/ui/labels
    PUBLIC systems/ui/lines
    PUBLIC systems/ui/menus
    PUBLIC systems/movement
    PUBLIC systems/saves
    PUBLIC systems/tile
    PUBLIC systems/viewport)

target_link_libraries(${WANDERER_LIB_TARGET}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC libCenturion
    PUBLIC libENTT
    PUBLIC libJSON
    PUBLIC libABBY
    PUBLIC libNamedType)

if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  add_executable(${WANDERER_EXE_TARGET} WIN32 main.cpp)
else ()
  add_executable(${WANDERER_EXE_TARGET} main.cpp)
endif ()

target_link_libraries(${WANDERER_EXE_TARGET} PUBLIC ${WANDERER_LIB_TARGET})

if (WIN32)
  copy_directory_post_build(${WANDERER_EXE_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources)
