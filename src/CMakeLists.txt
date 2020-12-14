cmake_minimum_required(VERSION 3.15)

project(WandererSrc CXX)

function(wanderer_set_properties [target [outputName]])
  set_target_properties(${ARGV0} PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      OUTPUT_NAME ${ARGV1})
endfunction()

set(SOURCE_FILES
    game.hpp
    game.cpp
    wanderer_app.cpp
    wanderer_app.hpp
    game_loop.hpp

    core/direction.hpp
    core/game_constants.hpp
    core/null_entity.hpp
    core/add_humanoid_state_dependencies.cpp
    core/add_humanoid_state_dependencies.hpp
    core/event_connections.cpp
    core/event_connections.hpp
    core/make_dispatcher.hpp
    core/make_dispatcher.cpp
    core/make_renderer.cpp
    core/make_renderer.hpp
    core/stack_resource.hpp
    core/make_registry.cpp
    core/make_registry.hpp
    core/centurion_utils.hpp
    core/cursor_manager.cpp
    core/cursor_manager.hpp

    core/level/level.hpp
    core/level/level.cpp
    core/level/level_factory.hpp
    core/level/level_factory.cpp
    core/level/level_manager.cpp
    core/level/level_manager.hpp

    core/aliases/ints.hpp
    core/aliases/delta.hpp
    core/aliases/tile_id.hpp
    core/aliases/depth.hpp
    core/aliases/buffer.hpp
    core/aliases/entity_type.hpp
    core/aliases/texture_handle.hpp
    core/aliases/maybe.hpp
    core/aliases/texture_cache.hpp
    core/aliases/aabb_tree.hpp
    core/aliases/milliseconds.hpp
    core/aliases/map_id.hpp

    core/resource/texture_loader.hpp

    core/math/vector2.hpp
    core/math/get_random.hpp
    core/math/index_to_matrix.hpp
    core/math/floating.hpp
    core/math/angles.hpp

    menu/menu.hpp
    menu/menu.cpp
    menu/menu_button.cpp
    menu/menu_button.hpp
    menu/menu_action.hpp
    menu/menu_id.hpp
    menu/key_bind.hpp
    menu/menu_constants.hpp
    menu/menu_manager.hpp
    menu/menu_manager.cpp

    component/player.hpp
    component/movable.hpp
    component/hitbox.hpp
    component/humanoid_state.hpp
    component/binds.hpp
    component/animated.hpp
    component/tilemap.hpp
    component/tile_layer.hpp
    component/tileset.hpp
    component/tile.hpp
    component/animated_tile.hpp
    component/render_bounds.hpp
    component/depth_drawable.hpp
    component/viewport.hpp
    component/map_position.hpp
    component/spawnpoint.hpp
    component/tile_object.hpp
    component/portal.hpp

    component/event/begin_attack_event.hpp
    component/event/end_attack_event.hpp
    component/event/begin_humanoid_move_event.hpp
    component/event/end_humanoid_move_event.hpp
    component/event/interact_event.hpp
    component/event/switch_map_event.hpp

    system/depth_drawables_system.cpp
    system/depth_drawables_system.hpp
    system/animation_system.cpp
    system/animation_system.hpp
    system/render_bounds_system.cpp
    system/render_bounds_system.hpp
    system/interaction_handler_system.cpp
    system/interaction_handler_system.hpp

    system/movement/movement_system.cpp
    system/movement/movement_system.hpp
    system/movement/hitbox_system.cpp
    system/movement/hitbox_system.hpp
    system/movement/movable_system.hpp
    system/movement/movable_system.cpp
    system/movement/portal_system.cpp
    system/movement/portal_system.hpp

    system/viewport/viewport_system.cpp
    system/viewport/viewport_system.hpp
    system/viewport/make_viewport.cpp
    system/viewport/make_viewport.hpp

    system/tile/tile_animation_system.cpp
    system/tile/tile_animation_system.hpp
    system/tile/tile_rendering_system.cpp
    system/tile/tile_rendering_system.hpp

    system/layer/layer_rendering_system.cpp
    system/layer/layer_rendering_system.hpp
    system/layer/layer_system.hpp

    system/humanoid/humanoid_animation_system.cpp
    system/humanoid/humanoid_animation_system.hpp
    system/humanoid/humanoid_state_system.cpp
    system/humanoid/humanoid_state_system.hpp
    system/humanoid/humanoid_factory_system.cpp
    system/humanoid/humanoid_factory_system.hpp
    system/humanoid/humanoid_attack_event_handler.cpp
    system/humanoid/humanoid_attack_event_handler.hpp
    system/humanoid/humanoid_move_event_handler.cpp
    system/humanoid/humanoid_move_event_handler.hpp

    system/input/input_system.cpp
    system/input/input_system.hpp
    system/input/move_input_system.cpp
    system/input/move_input_system.hpp
    system/input/idle_input_system.cpp
    system/input/idle_input_system.hpp

    parse/map/make_tile.cpp
    parse/map/make_tile.hpp
    parse/map/parse_map.hpp
    parse/map/parse_map.cpp
    parse/map/make_tileset.cpp
    parse/map/make_tileset.hpp
    parse/map/add_tile_objects.cpp
    parse/map/add_tile_objects.hpp

    parse/menu/parse_menu.cpp
    parse/menu/parse_menu.hpp)

add_library(${WANDERER_LIB_TARGET} ${SOURCE_FILES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${WANDERER_LIB_TARGET} PRIVATE
      /EHsc
      /MP
      /W3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${WANDERER_LIB_TARGET} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Wdouble-promotion
      -Wswitch-default
      -Wswitch-enum
      -Wunused
      -Wuninitialized
      -Wsuggest-final-types
      -Wsuggest-final-methods
      -Wsuggest-override
      -Wduplicated-cond
      -Wconversion)
endif ()

wanderer_set_properties(${WANDERER_LIB_TARGET} "Wanderer")

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
    PUBLIC component
    PUBLIC component/event
    PUBLIC system
    PUBLIC system/input
    PUBLIC system/humanoid
    PUBLIC system/tile
    PUBLIC system/layer
    PUBLIC system/viewport
    PUBLIC system/collision
    PUBLIC system/menu
    PUBLIC system/movement
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
    PUBLIC ${CENTURION_IMPORT_LIB}
    PUBLIC libENTT
    PUBLIC libJSON
    PUBLIC libABBY
    PUBLIC libNamedType)


if (CMAKE_BUILD_TYPE STREQUAL "Release")
  add_executable(${WANDERER_EXE_TARGET} WIN32 main.cpp)
else ()
  add_executable(${WANDERER_EXE_TARGET} main.cpp)
endif ()

wanderer_set_properties(${WANDERER_EXE_TARGET} "Wanderer")

target_link_libraries(${WANDERER_EXE_TARGET}
    PUBLIC ${WANDERER_LIB_TARGET})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  copy_directory_post_build(${WANDERER_EXE_TARGET} ${BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

copy_directory_post_build(${WANDERER_EXE_TARGET} ${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resource)
