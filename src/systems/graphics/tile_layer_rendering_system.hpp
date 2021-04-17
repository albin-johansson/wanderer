#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/**
 * \brief Renders all of the tile layers in a map.
 *
 * \param registry the current level registry.
 * \param graphics the graphics context that will be used for rendering.
 */
void render_tile_layers(const entt::registry& registry, graphics_context& graphics);

}  // namespace wanderer::sys
