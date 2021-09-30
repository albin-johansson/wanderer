cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    profile.hpp
    wanderer_engine.cpp
    wanderer_engine.hpp

    common/aabb_tree.hpp
    common/buffer.hpp
    common/float2.hpp
    common/ints.hpp
    common/map_id.hpp
    common/maybe.hpp
    common/milliseconds.hpp
    common/ref.hpp
    common/str.hpp
    common/texture_id.hpp
    common/texture_index.hpp
    common/tile_id.hpp

    components/associated_entity.hpp
    components/key_bind.hpp
    components/object.hpp
    components/plant.hpp
    components/player.hpp
    components/tiles/tileset.hpp
    components/trigger.hpp

    components/ai/chase.hpp
    components/ai/humanoid.hpp
    components/ai/roam.hpp

    components/ctx/active_menu.hpp
    components/ctx/binds.hpp
    components/ctx/cursors.hpp
    components/ctx/level_size.hpp
    components/ctx/render_bounds.hpp
    components/ctx/renderer_snapshot.hpp
    components/ctx/settings.hpp
    components/ctx/time_of_day.hpp
    components/ctx/viewport.hpp

    components/gfx/animated.hpp
    components/gfx/custom_animation.hpp
    components/gfx/drawable.hpp
    components/gfx/point_light.hpp
    components/gfx/tile_animation.hpp

    components/items/inventory.hpp

    components/lvl/level.hpp
    components/lvl/level_switch_target.hpp
    components/lvl/portal.hpp
    components/lvl/spawnpoint.hpp

    components/physics/float3.hpp
    components/physics/hitbox.hpp
    components/physics/movable.hpp
    components/physics/particle.hpp

    components/tiles/tile.hpp
    components/tiles/tile_layer.hpp
    components/tiles/tile_object.hpp
    components/tiles/tilemap.hpp

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
    core/game.cpp
    core/game.hpp
    core/game_constants.hpp
    core/grid_position.hpp
    core/menu_action.hpp
    core/menu_id.hpp
    core/resources.cpp
    core/resources.hpp
    core/serialization.hpp
    core/text_size.hpp

    core/algorithms/accumulate.hpp

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

    core/math/floating.hpp

    core/utils/centurion_utils.hpp
    core/utils/file_utils.cpp
    core/utils/file_utils.hpp
    core/utils/time_utils.cpp
    core/utils/time_utils.hpp

    events/custom_animation_halfway_event.hpp
    events/day_changed_event.hpp
    events/humanoid_events.hpp
    events/menu_events.hpp
    events/interact_event.hpp
    events/inventory_events.hpp
    events/load_game_event.hpp
    events/quit_event.hpp
    events/sleep_event.hpp
    events/spawn_particles_event.hpp
    events/switch_map_event.hpp

    io/directories.cpp
    io/directories.hpp
    io/rune_configuration.cpp
    io/rune_configuration.hpp

    io/saves/delete_save.cpp
    io/saves/delete_save.hpp

    io/saves/load/load_game.cpp
    io/saves/load/load_game.hpp
    io/saves/load/restore_level_registry.cpp
    io/saves/load/restore_level_registry.hpp
    io/saves/load/restore_shared_registry.cpp
    io/saves/load/restore_shared_registry.hpp

    io/saves/save/save_game.cpp
    io/saves/save/save_game.hpp
    io/saves/save/save_shared_registry.cpp
    io/saves/save/save_shared_registry.hpp

    io/tmx/common.hpp
    io/tmx/common.cpp
    io/tmx/csv.cpp
    io/tmx/csv.hpp
    io/tmx/parse_ir.hpp
    io/tmx/parse_layers.cpp
    io/tmx/parse_layers.hpp
    io/tmx/parse_tilesets.cpp
    io/tmx/parse_tilesets.hpp
    io/tmx/parse_world.cpp
    io/tmx/parse_world.hpp

    io/tmx/objects/parse_container.cpp
    io/tmx/objects/parse_container.hpp
    io/tmx/objects/parse_hitbox.cpp
    io/tmx/objects/parse_hitbox.hpp
    io/tmx/objects/parse_light.cpp
    io/tmx/objects/parse_light.hpp
    io/tmx/objects/parse_object_layer.cpp
    io/tmx/objects/parse_object_layer.hpp
    io/tmx/objects/parse_plant.cpp
    io/tmx/objects/parse_plant.hpp
    io/tmx/objects/parse_portal.cpp
    io/tmx/objects/parse_portal.hpp
    io/tmx/objects/parse_spawnpoint.cpp
    io/tmx/objects/parse_spawnpoint.hpp

    io/tmx/tiles/make_tile_matrix.cpp
    io/tmx/tiles/make_tile_matrix.hpp
    io/tmx/tiles/parse_ground_layer.cpp
    io/tmx/tiles/parse_ground_layer.hpp
    io/tmx/tiles/parse_tile.cpp
    io/tmx/tiles/parse_tile.hpp
    io/tmx/tiles/parse_tile_layer.cpp
    io/tmx/tiles/parse_tile_layer.hpp
    io/tmx/tiles/parse_tile_objects.cpp
    io/tmx/tiles/parse_tile_objects.hpp

    systems/interaction_system.cpp
    systems/interaction_system.hpp
    systems/time_system.cpp
    systems/time_system.hpp
    systems/plant_system.cpp
    systems/plant_system.hpp
    systems/trigger_system.cpp
    systems/trigger_system.hpp

    systems/ai/chase_system.cpp
    systems/ai/chase_system.hpp
    systems/ai/roam_system.cpp
    systems/ai/roam_system.hpp

    systems/configuration/load_binds_system.cpp
    systems/configuration/load_binds_system.hpp
    systems/configuration/settings_system.cpp
    systems/configuration/settings_system.hpp

    systems/gfx/animation_system.cpp
    systems/gfx/animation_system.hpp
    systems/gfx/custom_animation_system.cpp
    systems/gfx/custom_animation_system.hpp
    systems/gfx/debug_rendering_system.cpp
    systems/gfx/debug_rendering_system.hpp
    systems/gfx/depth_system.cpp
    systems/gfx/depth_system.hpp
    systems/gfx/drawable_system.cpp
    systems/gfx/drawable_system.hpp
    systems/gfx/light_system.cpp
    systems/gfx/light_system.hpp
    systems/gfx/render_bounds_system.cpp
    systems/gfx/render_bounds_system.hpp
    systems/gfx/viewport_system.cpp
    systems/gfx/viewport_system.hpp

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
    systems/levels/level_system.cpp
    systems/levels/level_system.hpp

    systems/physics/direction_system.cpp
    systems/physics/direction_system.hpp
    systems/physics/hitbox_system.cpp
    systems/physics/hitbox_system.hpp
    systems/physics/movement_system.cpp
    systems/physics/movement_system.hpp
    systems/physics/particle_system.cpp
    systems/physics/particle_system.hpp

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
    )

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

if (MSVC)
  target_compile_options(${WANDERER_LIB_TARGET} PUBLIC
      /EHsc
      /MP
      /W3
      /Zc:__cplusplus
      /Zc:preprocessor
      /wd5105  # Disable C5105: "macro expansion producing 'defined' has undefined behavior"
      )
endif ()

target_precompile_headers(${WANDERER_LIB_TARGET} PRIVATE
    <entt.hpp>
    <centurion.hpp>
    <json.hpp>
    <nenya.hpp>
    <init/ini.hpp>
    <rune/everything.hpp>
    )

# Library directories
target_include_directories(${WANDERER_LIB_TARGET} SYSTEM PUBLIC
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${LIBRARY_DIR}/centurion
    ${LIBRARY_DIR}/entt
    ${LIBRARY_DIR}/json
    ${LIBRARY_DIR}/cereal
    ${LIBRARY_DIR}/rune
    ${LIBRARY_DIR}/init
    ${LIBRARY_DIR}/nenya
    ${GENERATED_PROTOBUF_DIR}
    )

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC .)

target_link_libraries(${WANDERER_LIB_TARGET} PUBLIC
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_LIBRARY}
    ${PROTOBUF_LIBRARIES}
    wandererproto
    )

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
