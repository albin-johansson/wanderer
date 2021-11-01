cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

set(SOURCE_FILES
    profile.hpp
    wanderer_std.hpp

    components/associated_entity.hpp
    components/associated_object.hpp
    components/binds.hpp
    components/cursors.hpp
    components/key_bind.hpp
    components/level_size.hpp
    components/object.hpp
    components/plant.hpp
    components/player.hpp
    components/render_bounds.hpp
    components/renderer_snapshot.hpp
    components/settings.hpp
    components/tilemap.hpp
    components/time_of_day.hpp
    components/trigger.hpp
    components/viewport.hpp

    components/chase.hpp
    components/humanoid.hpp
    components/roam.hpp

    components/animation.hpp
    components/custom_animation.hpp
    components/drawable.hpp
    components/point_light.hpp
    components/tile_animation.hpp

    components/items/inventory.hpp

    components/level.hpp
    components/level_switch_target.hpp
    components/portal.hpp
    components/spawnpoint.hpp

    components/vector3.hpp
    components/hitbox.hpp
    components/movable.hpp
    components/particle.hpp

    components/tile.hpp
    components/tile_layer.hpp
    components/tile_object.hpp
    components/tileset.hpp

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
    game.cpp
    game.hpp
    core/game_constants.hpp
    core/grid_position.hpp
    core/menu_action.hpp
    core/menu_id.hpp
    core/resources.cpp
    core/resources.hpp
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

    io/saves/delete_save.cpp
    io/saves/delete_save.hpp

    io/saves/load/load_game.cpp
    io/saves/load/load_game.hpp
    io/saves/load/restore_data.cpp
    io/saves/load/restore_data.hpp
    io/saves/load/restore_level_registry.cpp
    io/saves/load/restore_level_registry.hpp
    io/saves/load/restore_shared_registry.cpp
    io/saves/load/restore_shared_registry.hpp

    io/saves/save/save_game.cpp
    io/saves/save/save_game.hpp
    io/saves/save/save_shared_registry.cpp
    io/saves/save/save_shared_registry.hpp

    io/maps/create_humanoids.cpp
    io/maps/create_humanoids.hpp
    io/maps/create_layers.cpp
    io/maps/create_layers.hpp
    io/maps/create_object_layer.cpp
    io/maps/create_object_layer.hpp
    io/maps/create_tile_layer.cpp
    io/maps/create_tile_layer.hpp
    io/maps/create_tileset.cpp
    io/maps/create_tileset.hpp
    io/maps/hitboxes.cpp
    io/maps/hitboxes.hpp
    io/maps/load_levels.cpp
    io/maps/load_levels.hpp
    io/maps/tactile_io_utils.hpp

    systems/interaction_system.cpp
    systems/interaction_system.hpp
    systems/level_system.cpp
    systems/level_system.hpp
    systems/plant_system.cpp
    systems/plant_system.hpp
    systems/registry_system.cpp
    systems/registry_system.hpp
    systems/tile_system.cpp
    systems/tile_system.hpp
    systems/time_system.cpp
    systems/time_system.hpp
    systems/trigger_system.cpp
    systems/trigger_system.hpp

    systems/ai/chase_system.cpp
    systems/ai/chase_system.hpp
    systems/ai/roam_system.cpp
    systems/ai/roam_system.hpp

    systems/ai/humanoid/humanoid_animation_system.cpp
    systems/ai/humanoid/humanoid_animation_system.hpp
    systems/ai/humanoid/humanoid_attack_event_handler.cpp
    systems/ai/humanoid/humanoid_attack_event_handler.hpp
    systems/ai/humanoid/humanoid_factory_system.cpp
    systems/ai/humanoid/humanoid_factory_system.hpp
    systems/ai/humanoid/humanoid_move_event_handler.cpp
    systems/ai/humanoid/humanoid_move_event_handler.hpp
    systems/ai/humanoid/humanoid_state_system.cpp
    systems/ai/humanoid/humanoid_state_system.hpp

    systems/animation/animation_system.cpp
    systems/animation/animation_system.hpp
    systems/animation/custom_animation_system.cpp
    systems/animation/custom_animation_system.hpp
    systems/animation/tile_animation_system.cpp
    systems/animation/tile_animation_system.hpp
    systems/animation/tile_object_animation_system.cpp
    systems/animation/tile_object_animation_system.hpp

    systems/configuration/load_binds_system.cpp
    systems/configuration/load_binds_system.hpp
    systems/configuration/settings_system.cpp
    systems/configuration/settings_system.hpp

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
    systems/gfx/tile_layer_rendering_system.cpp
    systems/gfx/tile_layer_rendering_system.hpp
    systems/gfx/tile_rendering_system.cpp
    systems/gfx/tile_rendering_system.hpp
    systems/gfx/viewport_system.cpp
    systems/gfx/viewport_system.hpp

    systems/input/idle_input_system.cpp
    systems/input/idle_input_system.hpp
    systems/input/input_system.cpp
    systems/input/input_system.hpp
    systems/input/key_bind_system.cpp
    systems/input/key_bind_system.hpp
    systems/input/movement_input_system.cpp
    systems/input/movement_input_system.hpp

    systems/physics/direction_system.cpp
    systems/physics/direction_system.hpp
    systems/physics/hitbox_system.cpp
    systems/physics/hitbox_system.hpp
    systems/physics/movement_system.cpp
    systems/physics/movement_system.hpp
    systems/physics/particle_system.cpp
    systems/physics/particle_system.hpp

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

    systems/ui/menus/saves/saves_menu_entry_factory_system.cpp
    systems/ui/menus/saves/saves_menu_entry_factory_system.hpp
    systems/ui/menus/saves/saves_menu_system.cpp
    systems/ui/menus/saves/saves_menu_system.hpp
    )

add_library(${WANDERER_LIB} ${SOURCE_FILES})

target_include_directories(${WANDERER_LIB}
    PUBLIC
    ${PROJECT_SOURCE_DIR}

    SYSTEM PUBLIC
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${JSON_INCLUDE_DIRS}
    ${CENTURION_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${GENERATED_PROTOBUF_DIR}
    ${LIBRARY_DIR}/entt
    ${LIBRARY_DIR}/cereal
    ${LIBRARY_DIR}/rune
    ${LIBRARY_DIR}/init
    ${LIBRARY_DIR}/nenya
    ${LIBRARY_DIR}/glm
    ${LIBRARY_DIR}/magic-enum
    ${LIBRARY_DIR}/tactile/tactile-base/include
    ${LIBRARY_DIR}/tactile/tactile-io/include
    )

target_link_libraries(${WANDERER_LIB} PUBLIC
    ${WANDERER_PROTO}
    ${CENTURION_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_LIBRARY}
    ${BINARY_DIR}/TactileIO.lib
    )

if (MSVC)
  target_compile_options(${WANDERER_LIB} PUBLIC
      /EHsc
      /MP
      /W4
      /Zc:__cplusplus
      /Zc:preprocessor
      /wd5105  # Disable C5105: "macro expansion producing 'defined' has undefined behavior"
      )
endif ()

target_precompile_headers(${WANDERER_LIB} PRIVATE
    <entt.hpp>
    <centurion.hpp>
    <json.hpp>
    <nenya.hpp>
    <init/ini.hpp>
    <rune/rune.hpp>
    <glm/glm.hpp>
    )

if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  add_executable(${WANDERER_EXE} WIN32 main.cpp)
else ()
  add_executable(${WANDERER_EXE} main.cpp)
endif ()

add_dependencies(${WANDERER_EXE} ${WANDERER_LIB})

target_link_libraries(${WANDERER_EXE} PUBLIC ${WANDERER_LIB})
target_precompile_headers(${WANDERER_EXE} REUSE_FROM ${WANDERER_LIB})

if (WIN32)
  copy_directory_post_build(${WANDERER_EXE} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

copy_directory_post_build(${WANDERER_EXE} ${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources)
