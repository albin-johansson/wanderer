#pragma once

#include "core/aliases/delta_time.hpp"
#include "core/levels/level.hpp"

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
 * \param level the currently active level.
 * \param dt the current delta time.
 */
void update_movement(level& level, const delta_time dt);

/// \} End of movement

}  // namespace wanderer::sys
