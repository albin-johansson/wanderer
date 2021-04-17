#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Tile objects
/// \{

/**
 * \brief Updates the animations of all tile objects.
 *
 * \param registry the current level registry.
 */
void update_tile_object_animations(entt::registry& registry);

/// \} End of tile objects

}  // namespace wanderer::sys
