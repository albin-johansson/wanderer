#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

namespace wanderer::sys::depthdrawable {

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
