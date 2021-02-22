#pragma once

#include <entt.hpp>

#include "delta.hpp"
#include "level.hpp"

namespace wanderer::sys {

/**
 * \brief Updates the state of components related to movement.
 *
 * \details This system iterates entities with `movable` components, whilst
 * also checking if they feature a `hitbox` component. This system will
 * perform collision detection for those movables that feature hitboxes.
 *
 * \param level the currently active level.
 * \param dt the delta time.
 */
void update_movement(level& level, const delta_t dt);

}  // namespace wanderer::sys
