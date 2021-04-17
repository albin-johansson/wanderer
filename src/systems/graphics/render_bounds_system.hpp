#pragma once

#include <centurion.hpp>  // frect
#include <entt.hpp>       // registry

#include "components/ctx/render_bounds.hpp"

namespace wanderer::sys {

/// \name Render bounds
/// \{

/**
 * \brief Updates the current render bounds.
 *
 * \note This function overwrites the `render_bounds` context variable for the supplied
 * registry, so the supplied registry doesn't need to contain a `render_bounds` context
 * variable before calling this function.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param nRows the amount of tile rows in the current level.
 * \param nCols the amount of tile columns in the current level.
 */
void update_render_bounds(entt::registry& registry, int nRows, int nCols);

/// \} End of render bounds

}  // namespace wanderer::sys
