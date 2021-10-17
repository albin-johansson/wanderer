#pragma once

#include <entt.hpp>             // registry
#include <rune/everything.hpp>  // delta_time

#include "common/aabb_tree.hpp"

namespace wanderer::sys {

/// \name Movement
/// \{

/**
 * \brief Updates the movement of movable entities.
 *
 * \details Whilst this function will primarily update entities with `movable` components,
 * it also checks if the entities has `hitbox` components, for which it will perform
 * collision detection.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param tree the AABB tree used by the level.
 * \param dt the current delta time.
 */
void UpdateMovement(entt::registry& registry, aabb_tree& tree, const float dt);

/// \} End of movement

}  // namespace wanderer::sys
