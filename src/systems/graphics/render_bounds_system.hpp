#pragma once

#include <centurion.hpp>  // frect
#include <entt.hpp>       // registry

#include "ctx/render_bounds.hpp"

namespace wanderer::sys {

void update_render_bounds(entt::registry& registry, int nRows, int nCols);

/**
 * \brief Calculates and returns the current render bounds.
 *
 * \param registry the current registry.
 * \param rows the number of rows in the current tilemap.
 * \param cols the number of columns in the current tilemap.
 *
 * \return the render bounds that should be used when rendering the tilemap.
 */
[[nodiscard]] auto get_render_bounds(const entt::registry& registry, int rows, int cols)
    -> ctx::render_bounds;

[[nodiscard]] auto to_rect(const ctx::render_bounds& bounds) noexcept -> cen::frect;

}  // namespace wanderer::sys
