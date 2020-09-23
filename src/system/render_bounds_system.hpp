/**
 * @brief Provides the system for determining what should be rendered.
 * @file render_bounds_system.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "component/render_bounds.hpp"
#include "component/viewport.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::sys {

/**
 * @brief Calculates and returns the current render bounds.
 *
 * @pre The viewport entity must have a `Viewport` component.
 *
 * @param registry the current registry.
 * @param viewportEntity the viewport entity.
 * @param rows the number of rows in the current tilemap.
 * @param cols the number of columns in the current tilemap.
 * @return the render bounds that should be used when rendering the tilemap.
 */
[[nodiscard]] auto calculate_render_bounds(
    entt::registry& registry,
    comp::viewport::entity viewportEntity,
    int rows,
    int cols) -> comp::render_bounds;

}  // namespace wanderer::sys
