#pragma once

#include <entt.hpp>  // registry, entity

#include "common/aabb_tree.hpp"
#include "common/float2.hpp"
#include "components/lvl/level.hpp"
#include "components/player.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Humanoids
/// \{

/**
 * \brief Creates a player entity.
 *
 * \ingroup systems
 *
 * \param level the level that will contain the player.
 * \param graphics the graphics context used to load the associated textures.
 *
 * \return the created player entity.
 */
auto make_player(comp::Level& level, graphics_context& graphics) -> entt::entity;

/**
 * \brief Creates a skeleton entity.
 *
 * \note The player entity must be created before this function is called!
 *
 * \ingroup systems
 *
 * \param level the level that will contain the skeleton.
 * \param position the initial position of the entity.
 * \param graphics the graphics context used to load the associated textures.
 *
 * \return the created skeleton entity.
 */
auto make_skeleton(comp::Level& level, float2 position, graphics_context& graphics)
    -> entt::entity;

/// \} End of humanoid

}  // namespace wanderer::sys
