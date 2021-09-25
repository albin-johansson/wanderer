cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(events)

set(SOURCE_FILES
    profile.hpp
    wanderer_engine.cpp
    wanderer_engine.hpp

    ${WANDERER_COMPONENT_SOURCES}
    ${WANDERER_CORE_SOURCES}
    ${WANDERER_EVENT_SOURCES}
    ${WANDERER_IO_SOURCES}
    ${WANDERER_GENERATED_PROTOBUF_SOURCES}

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

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${WANDERER_LIB_TARGET} PUBLIC
      /EHsc
      /MP
      /W3
      /Zc:__cplusplus
      /Zc:preprocessor
      /wd5105  # Disable C5105: "macro expansion producing 'defined' has undefined behavior"
      )
endif ()

target_precompile_headers(${WANDERER_LIB_TARGET}
    PRIVATE
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
    ${LIBRARY_DIR}/nenya)

# Wanderer directories
target_include_directories(${WANDERER_LIB_TARGET} PUBLIC .)

target_link_libraries(${WANDERER_LIB_TARGET} PUBLIC
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_LIBRARY}
    ${PROTOBUF_LIBRARIES})

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
