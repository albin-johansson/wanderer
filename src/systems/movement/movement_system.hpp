#pragma once

#include <entt.hpp>  // registry

#include "core/aliases/aabb_tree.hpp"
#include "core/aliases/delta_time.hpp"

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
void update_movement(entt::registry& registry, aabb_tree& tree, const delta_time dt);

/// \} End of movement

}  // namespace wanderer::sys
