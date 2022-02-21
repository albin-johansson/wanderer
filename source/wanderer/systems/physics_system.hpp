#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup physics-system Physics system
 *
 * \brief Manages physics related aspects of the game.
 */

/// \addtogroup physics-system
/// \{

/**
 * \brief Updates the position of all movable game objects in a level.
 *
 * \param registry the level registry.
 * \param dt the current delta time.
 */
void update_movable_game_objects(entt::registry& registry, float32 dt);

/// \} End of group physics-system

}  // namespace wanderer::sys