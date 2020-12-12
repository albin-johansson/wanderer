#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

#include "tilemap.hpp"

namespace wanderer::sys::depthdrawable {

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
void update_movable(entt::registry& registry);

/**
 * \brief Sorts all depth drawables according to their depth and center
 * y-coordinate.
 *
 * \param registry the registry that holds the depth drawables.
 *
 * \since 0.1.0
 */
void sort(entt::registry& registry);

/**
 * \brief Updates tile animations for tile objects that are depth drawables.
 *
 * \param registry the current registry.
 * \param tileset the tileset that will be used.
 */
void update_tile_animations(entt::registry& registry,
                            const comp::tileset& tileset);

/**
 * \brief Renders all depth drawables.
 *
 * \note Make sure to call `sort(entt::registry&)` before invoking this
 * function.
 *
 * \param registry the registry that holds the depth drawables.
 * \param renderer the renderer that will be used.
 *
 * \since 0.1.0
 */
void render(const entt::registry& registry, cen::renderer& renderer);

}  // namespace wanderer::sys::depthdrawable
