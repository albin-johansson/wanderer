cmake_minimum_required(VERSION 3.15)

project(wanderer-systems CXX)

set(WANDERER_SYSTEM_SOURCES

    ${PROJECT_SOURCE_DIR}/interaction_system.cpp
    ${PROJECT_SOURCE_DIR}/interaction_system.hpp
    ${PROJECT_SOURCE_DIR}/time_system.cpp
    ${PROJECT_SOURCE_DIR}/time_system.hpp
    ${PROJECT_SOURCE_DIR}/plant_system.cpp
    ${PROJECT_SOURCE_DIR}/plant_system.hpp

    ${PROJECT_SOURCE_DIR}/ai/chase_system.cpp
    ${PROJECT_SOURCE_DIR}/ai/chase_system.hpp
    ${PROJECT_SOURCE_DIR}/ai/roam_system.cpp
    ${PROJECT_SOURCE_DIR}/ai/roam_system.hpp

    ${PROJECT_SOURCE_DIR}/configuration/load_binds_system.cpp
    ${PROJECT_SOURCE_DIR}/configuration/load_binds_system.hpp
    ${PROJECT_SOURCE_DIR}/configuration/settings_system.cpp
    ${PROJECT_SOURCE_DIR}/configuration/settings_system.hpp

    ${PROJECT_SOURCE_DIR}/graphics/animation_system.cpp
    ${PROJECT_SOURCE_DIR}/graphics/animation_system.hpp
    ${PROJECT_SOURCE_DIR}/graphics/custom_animation_system.cpp
    ${PROJECT_SOURCE_DIR}/graphics/custom_animation_system.hpp
    ${PROJECT_SOURCE_DIR}/graphics/debug_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/graphics/debug_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/graphics/depth_system.cpp
    ${PROJECT_SOURCE_DIR}/graphics/depth_system.hpp
    ${PROJECT_SOURCE_DIR}/graphics/drawable_system.cpp
    ${PROJECT_SOURCE_DIR}/graphics/drawable_system.hpp
    ${PROJECT_SOURCE_DIR}/graphics/render_bounds_system.cpp
    ${PROJECT_SOURCE_DIR}/graphics/render_bounds_system.hpp
    ${PROJECT_SOURCE_DIR}/graphics/viewport_system.cpp
    ${PROJECT_SOURCE_DIR}/graphics/viewport_system.hpp

    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_animation_system.cpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_animation_system.hpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_attack_event_handler.cpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_attack_event_handler.hpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_move_event_handler.cpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_move_event_handler.hpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_state_system.cpp
    ${PROJECT_SOURCE_DIR}/humanoid/humanoid_state_system.hpp

    ${PROJECT_SOURCE_DIR}/input/idle_input_system.cpp
    ${PROJECT_SOURCE_DIR}/input/idle_input_system.hpp
    ${PROJECT_SOURCE_DIR}/input/input_system.cpp
    ${PROJECT_SOURCE_DIR}/input/input_system.hpp
    ${PROJECT_SOURCE_DIR}/input/key_bind_system.cpp
    ${PROJECT_SOURCE_DIR}/input/key_bind_system.hpp
    ${PROJECT_SOURCE_DIR}/input/movement_input_system.cpp
    ${PROJECT_SOURCE_DIR}/input/movement_input_system.hpp

    ${PROJECT_SOURCE_DIR}/layers/tile_layer_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/layers/tile_layer_rendering_system.hpp

    ${PROJECT_SOURCE_DIR}/levels/level_save_system.cpp
    ${PROJECT_SOURCE_DIR}/levels/level_save_system.hpp
    ${PROJECT_SOURCE_DIR}/levels/level_system.cpp
    ${PROJECT_SOURCE_DIR}/levels/level_system.hpp

    ${PROJECT_SOURCE_DIR}/levels/io/level_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/level_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_ground_layers.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_ground_layers.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_humanoids.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_humanoids.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_levels.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_levels.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_objects.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_objects.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tile_objects.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tile_objects.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tilemap.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tilemap.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tileset.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tileset.hpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tileset_textures.cpp
    ${PROJECT_SOURCE_DIR}/levels/io/load_tileset_textures.hpp

    ${PROJECT_SOURCE_DIR}/movement/direction_system.hpp
    ${PROJECT_SOURCE_DIR}/movement/direction_system.cpp
    ${PROJECT_SOURCE_DIR}/movement/hitbox_system.cpp
    ${PROJECT_SOURCE_DIR}/movement/hitbox_system.hpp
    ${PROJECT_SOURCE_DIR}/movement/movement_system.cpp
    ${PROJECT_SOURCE_DIR}/movement/movement_system.hpp

    ${PROJECT_SOURCE_DIR}/registry/registry_serialization_system.cpp
    ${PROJECT_SOURCE_DIR}/registry/registry_serialization_system.hpp
    ${PROJECT_SOURCE_DIR}/registry/shared_registry_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/registry/shared_registry_factory_system.hpp

    ${PROJECT_SOURCE_DIR}/tiles/tile_animation_system.cpp
    ${PROJECT_SOURCE_DIR}/tiles/tile_animation_system.hpp
    ${PROJECT_SOURCE_DIR}/tiles/tile_object_animation_system.cpp
    ${PROJECT_SOURCE_DIR}/tiles/tile_object_animation_system.hpp
    ${PROJECT_SOURCE_DIR}/tiles/tile_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/tiles/tile_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/tiles/tile_system.cpp
    ${PROJECT_SOURCE_DIR}/tiles/tile_system.hpp

    ${PROJECT_SOURCE_DIR}/triggers/bed_trigger_system.cpp
    ${PROJECT_SOURCE_DIR}/triggers/bed_trigger_system.hpp
    ${PROJECT_SOURCE_DIR}/triggers/container_trigger_system.cpp
    ${PROJECT_SOURCE_DIR}/triggers/container_trigger_system.hpp
    ${PROJECT_SOURCE_DIR}/triggers/portal_trigger_system.cpp
    ${PROJECT_SOURCE_DIR}/triggers/portal_trigger_system.hpp
    ${PROJECT_SOURCE_DIR}/triggers/update_triggers.hpp

    ${PROJECT_SOURCE_DIR}/ui/cursor_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/cursor_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/fps_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/fps_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/grid.hpp

    ${PROJECT_SOURCE_DIR}/ui/buttons/button_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/buttons/button_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/buttons/button_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/buttons/button_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/buttons/button_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/buttons/button_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/checkboxes/checkbox_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/checkboxes/checkbox_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/checkboxes/checkbox_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/checkboxes/checkbox_rendering_system.cpp

    ${PROJECT_SOURCE_DIR}/ui/hud/hud_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/hud/hud_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/hud/inventory_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/hud/inventory_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/hud/level_switch_animation_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/hud/level_switch_animation_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/labels/label_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/labels/label_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/labels/label_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/labels/label_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/labels/label_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/labels/label_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/lazy-textures/lazy_texture_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/lazy-textures/lazy_texture_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/lazy-textures/lazy_texture_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/lazy-textures/lazy_texture_rendering_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/lines/line_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/lines/line_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/lines/line_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/lines/line_rendering_system.cpp

    ${PROJECT_SOURCE_DIR}/ui/menus/menu_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/menu_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/menus/menu_rendering_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/menu_rendering_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/menus/menu_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/menu_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/menus/controls/controls_menu_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/controls/controls_menu_factory_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/menus/home/home_menu_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/home/home_menu_factory_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/menus/in-game/in_game_menu_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/in-game/in_game_menu_factory_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/menus/saves/saves_menu_entry_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/saves/saves_menu_entry_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/menus/saves/saves_menu_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/saves/saves_menu_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/menus/saves/saves_menu_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/saves/saves_menu_system.hpp

    ${PROJECT_SOURCE_DIR}/ui/menus/settings/settings_menu_factory_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/settings/settings_menu_factory_system.hpp
    ${PROJECT_SOURCE_DIR}/ui/menus/settings/settings_menu_system.cpp
    ${PROJECT_SOURCE_DIR}/ui/menus/settings/settings_menu_system.hpp

    ${PROJECT_SOURCE_DIR}/vfx/light_system.cpp
    ${PROJECT_SOURCE_DIR}/vfx/light_system.hpp
    ${PROJECT_SOURCE_DIR}/vfx/particle_system.hpp
    ${PROJECT_SOURCE_DIR}/vfx/particle_system.cpp

    PARENT_SCOPE)