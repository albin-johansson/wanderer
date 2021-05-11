#pragma once

#include <entt.hpp>  // registry
#include <rune.hpp>  // delta_time

#include "core/aliases/aabb_tree.hpp"

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
void update_movement(entt::registry& registry,
                     aabb_tree& tree,
                     const rune::delta_time dt);

/// \} End of movement

}  // namespace wanderer::sys
