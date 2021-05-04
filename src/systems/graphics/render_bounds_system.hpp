#pragma once

#include <entt.hpp>       // registry

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
 */
void update_render_bounds(entt::registry& registry);

/// \} End of render bounds

}  // namespace wanderer::sys
