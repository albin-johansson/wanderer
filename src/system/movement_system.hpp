#pragma once

#include <entt.hpp>

#include "aabb_tree.hpp"
#include "delta.hpp"
#include "level.hpp"

namespace wanderer::sys {

/**
 * @brief Updates the state of components related to movement.
 *
 * @details This system iterates entities with `movable` components, whilst
 * also checking if they feature `hitbox` and/or `depth_drawable` components.
 * This system will perform collision detection for movables with hitboxes.
 * Furthermore, `depth_drawable` components will have their coordinates
 * updated by this system.
 *
 * @param level the currently active level.
 * @param dt the delta time.
 */
void update_movement(level& level, delta dt);

}  // namespace wanderer::sys
