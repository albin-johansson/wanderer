#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Tile objects
/// \{

/**
 * \brief Updates the animations of all tile objects.
 *
 * \details This function iterates all entities with both `tile_object` and
 * `drawable` components, and if any of the entities associated with a `tile_object`
 * has a `tile_animation` component, then the `drawable` is updated to render the
 * correct part of the associated tile sheet.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void UpdateTileObjectAnimations(entt::registry& registry);

/// \} End of tile objects

}  // namespace wanderer::sys
