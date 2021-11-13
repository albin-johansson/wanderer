#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer::sys {

/// \name Tile layers
/// \{

/**
 * \brief Renders all of the tile layers in a map.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void RenderTileLayers(const entt::registry& registry);

/// \} End of tile layers

}  // namespace wanderer::sys
