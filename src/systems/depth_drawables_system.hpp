#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "render_bounds.hpp"
#include "tilemap.hpp"

namespace wanderer::sys {

/**
 * \brief Updates all depth drawables that are also movable.
 *
 * \details This function will update the `depth_drawable`s using the current
 * positions of the associated `movable` components.
 *
 * \param registry the registry that holds the depth drawables and movables.
 *
 * \since 0.1.0
 */
void update_drawable_movables(entt::registry& registry);

/**
 * \brief Sorts all depth drawables according to their depth and center
 * y-coordinate.
 *
 * \param registry the registry that holds the depth drawables.
 *
 * \since 0.1.0
 */
void sort_drawables(entt::registry& registry);

/**
 * \brief Updates tile animations for tile objects that are depth drawables.
 *
 * \param registry the current registry.
 * \param tileset the tileset that will be used.
 */
void update_tile_object_animations(entt::registry& registry,
                                   comp::tileset::entity tileset);

/**
 * \brief Renders all depth drawables.
 *
 * \note Make sure to call `sort(entt::registry&)` before invoking this
 * function.
 *
 * \param registry the registry that holds the depth drawables.
 * \param renderer the renderer that will be used.
 * \param bounds the render bounds that will be used.
 *
 * \since 0.1.0
 */
void render_drawables(const entt::registry& registry,
                      cen::renderer& renderer,
                      const comp::render_bounds& bounds);

}  // namespace wanderer::sys
