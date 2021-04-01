#pragma once

#include <entt.hpp>

#include "render_bounds.hpp"
#include "viewport.hpp"

namespace wanderer::sys {

/**
 * \brief Calculates and returns the current render bounds.
 *
 * \pre The viewport entity must have a `Viewport` component.
 *
 * \param registry the current registry.
 * \param viewportEntity the viewport entity.
 * \param rows the number of rows in the current tilemap.
 * \param cols the number of columns in the current tilemap.
 *
 * \return the render bounds that should be used when rendering the tilemap.
 */
[[nodiscard]] auto get_render_bounds(const entt::registry& registry,
                                     comp::viewport::entity viewportEntity,
                                     int rows,
                                     int cols) -> comp::render_bounds;

[[nodiscard]] auto to_rect(const comp::render_bounds& bounds) noexcept -> cen::frect;

}  // namespace wanderer::sys
