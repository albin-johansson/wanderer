cmake_minimum_required(VERSION 3.15)

project(wanderer-src CXX)

add_subdirectory(core)
add_subdirectory(events)
add_subdirectory(io)
add_subdirectory(systems)

set(SOURCE_FILES
    profile.hpp
    wanderer_engine.cpp
    wanderer_engine.hpp

    components/key_bind.hpp
    components/object.hpp
    components/plant.hpp
    components/player.hpp
    components/tiles/tileset.hpp
    components/trigger.hpp

    components/ai/chase.hpp
    components/ai/humanoid_state.hpp
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
    components/gfx/depth_drawable.hpp
    components/gfx/point_light.hpp
    components/gfx/tile_animation.hpp

    components/items/container_ref.hpp
    components/items/inventory.hpp
    components/items/item.hpp

    components/lvl/level.hpp
    components/lvl/level_switch_target.hpp
    components/lvl/outside_level.hpp
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

    ${WANDERER_CORE_SOURCES}
    ${WANDERER_EVENT_SOURCES}
    ${WANDERER_IO_SOURCES}
    ${WANDERER_SYSTEM_SOURCES}
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
