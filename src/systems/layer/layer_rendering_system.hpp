#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "graphics_context.hpp"
#include "render_bounds.hpp"
#include "tileset.hpp"

namespace wanderer::sys {

/**
 * \brief Renders all of the ground layers in a map.
 *
 * \param registry the registry that holds the layers.
 * \param graphics the graphics context that will be used when rendering.
 * \param bounds the render bounds that will be used.
 *
 * \since 0.1.0
 */
void render_ground_layers(const entt::registry& registry,
                          graphics_context& graphics,
                          const comp::render_bounds& bounds);

}  // namespace wanderer::sys
