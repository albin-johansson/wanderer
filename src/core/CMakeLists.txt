cmake_minimum_required(VERSION 3.15)

project(wanderer-src-core CXX)

set(WANDERER_CORE_SOURCES

    ${PROJECT_SOURCE_DIR}/common_concepts.hpp
    ${PROJECT_SOURCE_DIR}/day_of_week.hpp
    ${PROJECT_SOURCE_DIR}/direction.hpp
    ${PROJECT_SOURCE_DIR}/game.cpp
    ${PROJECT_SOURCE_DIR}/game.hpp
    ${PROJECT_SOURCE_DIR}/game_constants.hpp
    ${PROJECT_SOURCE_DIR}/grid_position.hpp
    ${PROJECT_SOURCE_DIR}/menu_action.hpp
    ${PROJECT_SOURCE_DIR}/menu_id.hpp
    ${PROJECT_SOURCE_DIR}/resources.cpp
    ${PROJECT_SOURCE_DIR}/resources.hpp
    ${PROJECT_SOURCE_DIR}/serialization.hpp
    ${PROJECT_SOURCE_DIR}/text_size.hpp

    ${PROJECT_SOURCE_DIR}/algorithms/accumulate.hpp

    ${PROJECT_SOURCE_DIR}/aliases/aabb_tree.hpp
    ${PROJECT_SOURCE_DIR}/aliases/buffer.hpp
    ${PROJECT_SOURCE_DIR}/aliases/depth.hpp
    ${PROJECT_SOURCE_DIR}/aliases/entity_type.hpp
    ${PROJECT_SOURCE_DIR}/aliases/float2.hpp
    ${PROJECT_SOURCE_DIR}/aliases/ints.hpp
    ${PROJECT_SOURCE_DIR}/aliases/map_id.hpp
    ${PROJECT_SOURCE_DIR}/aliases/maybe.hpp
    ${PROJECT_SOURCE_DIR}/aliases/milliseconds.hpp
    ${PROJECT_SOURCE_DIR}/aliases/ref.hpp
    ${PROJECT_SOURCE_DIR}/aliases/str.hpp
    ${PROJECT_SOURCE_DIR}/aliases/texture_id.hpp
    ${PROJECT_SOURCE_DIR}/aliases/texture_index.hpp
    ${PROJECT_SOURCE_DIR}/aliases/tile_id.hpp

    ${PROJECT_SOURCE_DIR}/ecs/add_humanoid_state_dependencies.cpp
    ${PROJECT_SOURCE_DIR}/ecs/add_humanoid_state_dependencies.hpp
    ${PROJECT_SOURCE_DIR}/ecs/event_connections.cpp
    ${PROJECT_SOURCE_DIR}/ecs/event_connections.hpp
    ${PROJECT_SOURCE_DIR}/ecs/make_dispatcher.cpp
    ${PROJECT_SOURCE_DIR}/ecs/make_dispatcher.hpp
    ${PROJECT_SOURCE_DIR}/ecs/make_registry.cpp
    ${PROJECT_SOURCE_DIR}/ecs/make_registry.hpp
    ${PROJECT_SOURCE_DIR}/ecs/null_entity.hpp
    ${PROJECT_SOURCE_DIR}/ecs/registry_utils.hpp

    ${PROJECT_SOURCE_DIR}/graphics/graphics_context.cpp
    ${PROJECT_SOURCE_DIR}/graphics/graphics_context.hpp
    ${PROJECT_SOURCE_DIR}/graphics/render_text.cpp
    ${PROJECT_SOURCE_DIR}/graphics/render_text.hpp

    ${PROJECT_SOURCE_DIR}/math/angles.hpp
    ${PROJECT_SOURCE_DIR}/math/floating.hpp

    ${PROJECT_SOURCE_DIR}/utils/centurion_utils.hpp
    ${PROJECT_SOURCE_DIR}/utils/file_utils.cpp
    ${PROJECT_SOURCE_DIR}/utils/file_utils.hpp
    ${PROJECT_SOURCE_DIR}/utils/time_utils.cpp
    ${PROJECT_SOURCE_DIR}/utils/time_utils.hpp

    PARENT_SCOPE)