#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer::sys {

/// \name Tiles
/// \{

/**
 * \brief Updates the state of all tile animations.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void UpdateTileAnimations(entt::registry& registry);

/// \} End of tiles

}  // namespace wanderer::sys
