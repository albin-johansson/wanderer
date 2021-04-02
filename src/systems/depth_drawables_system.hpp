#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "graphics_context.hpp"
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
 */
void update_tile_object_animations(entt::registry& registry);

/**
 * \brief Renders all depth drawables.
 *
 * \note Make sure to call `sort(entt::registry&)` before invoking this
 * function.
 *
 * \param registry the registry that holds the depth drawables.
 * \param graphics the graphics context that will be used.
 *
 * \since 0.1.0
 */
void render_drawables(const entt::registry& registry, graphics_context& graphics);

}  // namespace wanderer::sys
