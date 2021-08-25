cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    wanderer_engine.cpp
    wanderer_engine.hpp

    components/animated.hpp
    components/bed_trigger.hpp
    components/chase.hpp
    components/container_trigger.hpp
    components/custom_animation.hpp
    components/depth_drawable.hpp
    components/float3.hpp
    components/hitbox.hpp
    components/humanoid_state.hpp
    components/inventory.hpp
    components/item.hpp
    components/key_bind.hpp
    components/level.hpp
    components/level_switch_target.hpp
    components/movable.hpp
    components/object.hpp
    components/outside_level.hpp
    components/particle.hpp
    components/plant.hpp
    components/player.hpp
    components/point_light.hpp
    components/portal.hpp
    components/roam.hpp
    components/spawnpoint.hpp
    components/tile.hpp
    components/tile_animation.hpp
    components/tile_layer.hpp
    components/tile_object.hpp
    components/tilemap.hpp
    components/tileset.hpp

    components/ctx/active_menu.hpp
    components/ctx/binds.hpp
    components/ctx/cursors.hpp
    components/ctx/level_size.hpp
    components/ctx/render_bounds.hpp
    components/ctx/renderer_snapshot.hpp
    components/ctx/settings.hpp
    components/ctx/time_of_day.hpp
    components/ctx/viewport.hpp

    components/ui/associated_menu.hpp
    components/ui/button.hpp
    components/ui/button_group.hpp
    components/ui/checkbox.hpp
    components/ui/fps_data.hpp
    components/ui/label.hpp
    components/ui/lazy_texture.hpp
    components/ui/line.hpp
    components/ui/menu.hpp
    components/ui/saves_menu.hpp

    core/common_concepts.hpp
    core/day_of_week.hpp
    core/direction.hpp
    core/game.hpp
    core/game.cpp
    core/game_constants.hpp
    core/grid_position.hpp
    core/menu_action.hpp
    core/menu_id.hpp
    core/resources.cpp
    core/resources.hpp
    core/serialization.hpp
    core/text_size.hpp

    core/algorithms/accumulate.hpp

    core/aliases/aabb_tree.hpp
    core/aliases/buffer.hpp
    core/aliases/depth.hpp
    core/aliases/entity_type.hpp
    core/aliases/float2.hpp
    core/aliases/ints.hpp
    core/aliases/map_id.hpp
    core/aliases/maybe.hpp
    core/aliases/milliseconds.hpp
    core/aliases/ref.hpp
    core/aliases/str.hpp
    core/aliases/texture_id.hpp
    core/aliases/texture_index.hpp
    core/aliases/tile_id.hpp

    core/ecs/add_humanoid_state_dependencies.cpp
    core/ecs/add_humanoid_state_dependencies.hpp
    core/ecs/event_connections.cpp
    core/ecs/event_connections.hpp
    core/ecs/make_dispatcher.cpp
    core/ecs/make_dispatcher.hpp
    core/ecs/make_registry.cpp
    core/ecs/make_registry.hpp
    core/ecs/null_entity.hpp
    core/ecs/registry_utils.hpp

    core/graphics/graphics_context.cpp
    core/graphics/graphics_context.hpp
    core/graphics/render_text.cpp
    core/graphics/render_text.hpp

    core/math/angles.hpp
    core/math/floating.hpp

    core/utils/centurion_utils.hpp
    core/utils/file_utils.cpp
    core/utils/file_utils.hpp
    core/utils/time_utils.cpp
    core/utils/time_utils.hpp

    events/begin_attack_event.hpp
    events/begin_humanoid_move_event.hpp
    events/button_pressed_event.hpp
    events/close_inventory_event.hpp
    events/custom_animation_halfway_event.hpp
    events/day_changed_event.hpp
    events/end_attack_event.hpp
    events/end_humanoid_move_event.hpp
    events/fullscreen_toggled_event.hpp
    events/integer_scaling_toggled_event.hpp
    events/interact_event.hpp
    events/level_fade_events_event.hpp
    events/load_game_event.hpp
    events/menu_switched_event.hpp
    events/quit_event.hpp
    events/show_inventory_event.hpp
    events/sleep_event.hpp
    events/spawn_particles_event.hpp
    events/switch_map_event.hpp
    events/switch_menu_event.hpp

    io/directories.cpp
    io/directories.hpp
    io/rune_configuration.cpp
    io/rune_configuration.hpp

    io/parsing/common.hpp
    io/parsing/common.cpp
    io/parsing/csv.cpp
    io/parsing/csv.hpp
    io/parsing/parse_ir.hpp
    io/parsing/parse_layers.cpp
    io/parsing/parse_layers.hpp
    io/parsing/parse_tilesets.cpp
    io/parsing/parse_tilesets.hpp
    io/parsing/parse_world.cpp
    io/parsing/parse_world.hpp

    io/parsing/objects/parse_container.cpp
    io/parsing/objects/parse_container.hpp
    io/parsing/objects/parse_hitbox.cpp
    io/parsing/objects/parse_hitbox.hpp
    io/parsing/objects/parse_light.cpp
    io/parsing/objects/parse_light.hpp
    io/parsing/objects/parse_object_layer.cpp
    io/parsing/objects/parse_object_layer.hpp
    io/parsing/objects/parse_plant.cpp
    io/parsing/objects/parse_plant.hpp
    io/parsing/objects/parse_portal.cpp
    io/parsing/objects/parse_portal.hpp
    io/parsing/objects/parse_spawnpoint.cpp
    io/parsing/objects/parse_spawnpoint.hpp

    io/parsing/tiles/make_tile_matrix.cpp
    io/parsing/tiles/make_tile_matrix.hpp
    io/parsing/tiles/parse_ground_layer.cpp
    io/parsing/tiles/parse_ground_layer.hpp
    io/parsing/tiles/parse_tile.cpp
    io/parsing/tiles/parse_tile.hpp
    io/parsing/tiles/parse_tile_layer.cpp
    io/parsing/tiles/parse_tile_layer.hpp
    io/parsing/tiles/parse_tile_objects.cpp
    io/parsing/tiles/parse_tile_objects.hpp

    io/saves/delete_save.cpp
    io/saves/delete_save.hpp
    io/saves/load_game.cpp
    io/saves/load_game.hpp
    io/saves/parse_save_file.cpp
    io/saves/parse_save_file.hpp
    io/saves/save_game.cpp
    io/saves/save_game.hpp

    systems/interaction_system.cpp
    systems/interaction_system.hpp
    systems/time_system.cpp
    systems/time_system.hpp
    systems/plant_system.cpp
    systems/plant_system.hpp

    systems/ai/chase_system.cpp
    systems/ai/chase_system.hpp
    systems/ai/roam_system.cpp
    systems/ai/roam_system.hpp

    systems/configuration/load_binds_system.cpp
    systems/configuration/load_binds_system.hpp
    systems/configuration/settings_system.cpp
    systems/configuration/settings_system.hpp

    systems/graphics/animation_system.cpp
    systems/graphics/animation_system.hpp
    systems/graphics/custom_animation_system.cpp
    systems/graphics/custom_animation_system.hpp
    systems/graphics/debug_rendering_system.cpp
    systems/graphics/debug_rendering_system.hpp
    systems/graphics/depth_system.cpp
    systems/graphics/depth_system.hpp
    systems/graphics/drawable_system.cpp
    systems/graphics/drawable_system.hpp
    systems/graphics/render_bounds_system.cpp
    systems/graphics/render_bounds_system.hpp
    systems/graphics/viewport_system.cpp
    systems/graphics/viewport_system.hpp

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
    systems/input/movement_input_system.cpp
    systems/input/movement_input_system.hpp

    systems/layers/tile_layer_rendering_system.cpp
    systems/layers/tile_layer_rendering_system.hpp

    systems/levels/level_save_system.cpp
    systems/levels/level_save_system.hpp
    systems/levels/level_system.cpp
    systems/levels/level_system.hpp

    systems/levels/io/level_factory_system.cpp
    systems/levels/io/level_factory_system.hpp
    systems/levels/io/load_ground_layers.cpp
    systems/levels/io/load_ground_layers.hpp
    systems/levels/io/load_humanoids.cpp
    systems/levels/io/load_humanoids.hpp
    systems/levels/io/load_levels.cpp
    systems/levels/io/load_levels.hpp
    systems/levels/io/load_objects.cpp
    systems/levels/io/load_objects.hpp
    systems/levels/io/load_tile_objects.cpp
    systems/levels/io/load_tile_objects.hpp
    systems/levels/io/load_tilemap.cpp
    systems/levels/io/load_tilemap.hpp
    systems/levels/io/load_tileset.cpp
    systems/levels/io/load_tileset.hpp
    systems/levels/io/load_tileset_textures.cpp
    systems/levels/io/load_tileset_textures.hpp

    systems/movement/direction_system.hpp
    systems/movement/direction_system.cpp
    systems/movement/hitbox_system.cpp
    systems/movement/hitbox_system.hpp
    systems/movement/movement_system.cpp
    systems/movement/movement_system.hpp

    systems/registry/registry_serialization_system.cpp
    systems/registry/registry_serialization_system.hpp
    systems/registry/shared_registry_factory_system.cpp
    systems/registry/shared_registry_factory_system.hpp

    systems/tiles/tile_animation_system.cpp
    systems/tiles/tile_animation_system.hpp
    systems/tiles/tile_object_animation_system.cpp
    systems/tiles/tile_object_animation_system.hpp
    systems/tiles/tile_rendering_system.cpp
    systems/tiles/tile_rendering_system.hpp
    systems/tiles/tile_system.cpp
    systems/tiles/tile_system.hpp

    systems/triggers/bed_trigger_system.cpp
    systems/triggers/bed_trigger_system.hpp
    systems/triggers/container_trigger_system.cpp
    systems/triggers/container_trigger_system.hpp
    systems/triggers/portal_trigger_system.cpp
    systems/triggers/portal_trigger_system.hpp
    systems/triggers/update_triggers.hpp

    systems/ui/cursor_system.cpp
    systems/ui/cursor_system.hpp
    systems/ui/fps_system.cpp
    systems/ui/fps_system.hpp
    systems/ui/grid.hpp

    systems/ui/buttons/button_factory_system.cpp
    systems/ui/buttons/button_factory_system.hpp
    systems/ui/buttons/button_rendering_system.cpp
    systems/ui/buttons/button_rendering_system.hpp
    systems/ui/buttons/button_system.cpp
    systems/ui/buttons/button_system.hpp

    systems/ui/checkboxes/checkbox_factory_system.cpp
    systems/ui/checkboxes/checkbox_factory_system.hpp
    systems/ui/checkboxes/checkbox_rendering_system.hpp
    systems/ui/checkboxes/checkbox_rendering_system.cpp

    systems/ui/hud/hud_rendering_system.cpp
    systems/ui/hud/hud_rendering_system.hpp
    systems/ui/hud/inventory_rendering_system.cpp
    systems/ui/hud/inventory_rendering_system.hpp
    systems/ui/hud/level_switch_animation_system.cpp
    systems/ui/hud/level_switch_animation_system.hpp

    systems/ui/labels/label_factory_system.cpp
    systems/ui/labels/label_factory_system.hpp
    systems/ui/labels/label_rendering_system.cpp
    systems/ui/labels/label_rendering_system.hpp
    systems/ui/labels/label_system.cpp
    systems/ui/labels/label_system.hpp

    systems/ui/lazy-textures/lazy_texture_factory_system.cpp
    systems/ui/lazy-textures/lazy_texture_factory_system.hpp
    systems/ui/lazy-textures/lazy_texture_rendering_system.cpp
    systems/ui/lazy-textures/lazy_texture_rendering_system.hpp

    systems/ui/lines/line_factory_system.cpp
    systems/ui/lines/line_factory_system.hpp
    systems/ui/lines/line_rendering_system.hpp
    systems/ui/lines/line_rendering_system.cpp

    systems/ui/menus/menu_factory_system.cpp
    systems/ui/menus/menu_factory_system.hpp
    systems/ui/menus/menu_rendering_system.cpp
    systems/ui/menus/menu_rendering_system.hpp
    systems/ui/menus/menu_system.cpp
    systems/ui/menus/menu_system.hpp

    systems/ui/menus/controls/controls_menu_factory_system.cpp
    systems/ui/menus/controls/controls_menu_factory_system.hpp

    systems/ui/menus/home/home_menu_factory_system.cpp
    systems/ui/menus/home/home_menu_factory_system.hpp

    systems/ui/menus/in-game/in_game_menu_factory_system.cpp
    systems/ui/menus/in-game/in_game_menu_factory_system.hpp

    systems/ui/menus/saves/saves_menu_entry_factory_system.cpp
    systems/ui/menus/saves/saves_menu_entry_factory_system.hpp
    systems/ui/menus/saves/saves_menu_factory_system.cpp
    systems/ui/menus/saves/saves_menu_factory_system.hpp
    systems/ui/menus/saves/saves_menu_system.cpp
    systems/ui/menus/saves/saves_menu_system.hpp

    systems/ui/menus/settings/settings_menu_factory_system.cpp
    systems/ui/menus/settings/settings_menu_factory_system.hpp
    systems/ui/menus/settings/settings_menu_system.cpp
    systems/ui/menus/settings/settings_menu_system.hpp

    systems/vfx/light_system.cpp
    systems/vfx/light_system.hpp
    systems/vfx/particle_system.hpp
    systems/vfx/particle_system.cpp
    )

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

wanderer_set_compiler_options(${WANDERER_LIB_TARGET})

add_header_only_lib(libCenturion ${LIBRARY_DIR}/centurion ${LIBRARY_DIR}/centurion/centurion.hpp)
add_header_only_lib(libNenya ${LIBRARY_DIR}/nenya ${LIBRARY_DIR}/nenya/nenya.hpp)
add_header_only_lib(libJSON ${LIBRARY_DIR}/json ${LIBRARY_DIR}/json/json.hpp)
add_header_only_lib(libENTT ${LIBRARY_DIR}/entt ${LIBRARY_DIR}/entt/entt.hpp)

# Library directories
target_include_directories(${WANDERER_LIB_TARGET}
    SYSTEM PUBLIC ${SDL2_INCLUDE_DIR}
    SYSTEM PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_MIXER_INCLUDE_DIRS}
    SYSTEM PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    SYSTEM PUBLIC ${LIBRARY_DIR}/cereal
    SYSTEM PUBLIC ${LIBRARY_DIR}/rune)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC .)

target_link_libraries(${WANDERER_LIB_TARGET}
    PUBLIC ${SDL2_IMAGE_LIBRARIES}
    PUBLIC ${SDL2_MIXER_LIBRARIES}
    PUBLIC ${SDL2_TTF_LIBRARIES}
    PUBLIC ${SDL2_LIBRARY}
    PUBLIC libCenturion
    PUBLIC libNenya
    PUBLIC libENTT
    PUBLIC libJSON)

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
