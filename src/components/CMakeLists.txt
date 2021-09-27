cmake_minimum_required(VERSION 3.15)

project(wanderer-src-components CXX)

set(WANDERER_COMPONENT_SOURCES

    ${PROJECT_SOURCE_DIR}/animated.hpp
    ${PROJECT_SOURCE_DIR}/bed_trigger.hpp
    ${PROJECT_SOURCE_DIR}/chase.hpp
    ${PROJECT_SOURCE_DIR}/container_trigger.hpp
    ${PROJECT_SOURCE_DIR}/custom_animation.hpp
    ${PROJECT_SOURCE_DIR}/depth_drawable.hpp
    ${PROJECT_SOURCE_DIR}/float3.hpp
    ${PROJECT_SOURCE_DIR}/hitbox.hpp
    ${PROJECT_SOURCE_DIR}/humanoid_state.hpp
    ${PROJECT_SOURCE_DIR}/inventory.hpp
    ${PROJECT_SOURCE_DIR}/item.hpp
    ${PROJECT_SOURCE_DIR}/key_bind.hpp
    ${PROJECT_SOURCE_DIR}/level.hpp
    ${PROJECT_SOURCE_DIR}/level_switch_target.hpp
    ${PROJECT_SOURCE_DIR}/movable.hpp
    ${PROJECT_SOURCE_DIR}/object.hpp
    ${PROJECT_SOURCE_DIR}/outside_level.hpp
    ${PROJECT_SOURCE_DIR}/particle.hpp
    ${PROJECT_SOURCE_DIR}/plant.hpp
    ${PROJECT_SOURCE_DIR}/player.hpp
    ${PROJECT_SOURCE_DIR}/point_light.hpp
    ${PROJECT_SOURCE_DIR}/portal.hpp
    ${PROJECT_SOURCE_DIR}/roam.hpp
    ${PROJECT_SOURCE_DIR}/spawnpoint.hpp
    ${PROJECT_SOURCE_DIR}/tile.hpp
    ${PROJECT_SOURCE_DIR}/tile_animation.hpp
    ${PROJECT_SOURCE_DIR}/tile_layer.hpp
    ${PROJECT_SOURCE_DIR}/tile_object.hpp
    ${PROJECT_SOURCE_DIR}/tilemap.hpp
    ${PROJECT_SOURCE_DIR}/tileset.hpp
    ${PROJECT_SOURCE_DIR}/trigger.hpp

    ${PROJECT_SOURCE_DIR}/ctx/active_menu.hpp
    ${PROJECT_SOURCE_DIR}/ctx/binds.hpp
    ${PROJECT_SOURCE_DIR}/ctx/cursors.hpp
    ${PROJECT_SOURCE_DIR}/ctx/level_size.hpp
    ${PROJECT_SOURCE_DIR}/ctx/render_bounds.hpp
    ${PROJECT_SOURCE_DIR}/ctx/renderer_snapshot.hpp
    ${PROJECT_SOURCE_DIR}/ctx/settings.hpp
    ${PROJECT_SOURCE_DIR}/ctx/time_of_day.hpp
    ${PROJECT_SOURCE_DIR}/ctx/viewport.hpp

    ${PROJECT_SOURCE_DIR}/ui/associated_menu.hpp
    ${PROJECT_SOURCE_DIR}/ui/button.hpp
    ${PROJECT_SOURCE_DIR}/ui/button_group.hpp
    ${PROJECT_SOURCE_DIR}/ui/checkbox.hpp
    ${PROJECT_SOURCE_DIR}/ui/fps_data.hpp
    ${PROJECT_SOURCE_DIR}/ui/label.hpp
    ${PROJECT_SOURCE_DIR}/ui/lazy_texture.hpp
    ${PROJECT_SOURCE_DIR}/ui/line.hpp
    ${PROJECT_SOURCE_DIR}/ui/menu.hpp
    ${PROJECT_SOURCE_DIR}/ui/saves_menu.hpp

    PARENT_SCOPE)