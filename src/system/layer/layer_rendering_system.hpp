#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

#include "render_bounds.hpp"
#include "tileset.hpp"

namespace wanderer::sys {

/**
 * \brief Renders all of the ground layers in a map.
 *
 * \param registry the registry that holds the layers.
 * \param tileset the tileset that will be used.
 * \param renderer the renderer that will be used.
 * \param bounds the render bounds that will be used.
 *
 * \since 0.1.0
 */
void render_ground_layers(const entt::registry& registry,
                          comp::tileset::entity tileset,
                          cen::renderer& renderer,
                          const comp::render_bounds& bounds);

}  // namespace wanderer::sys
