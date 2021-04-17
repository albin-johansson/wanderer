#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Depth
/// \{

/**
 * \brief Sorts all depth drawables.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 *
 * \since 0.1.0
 */
void update_depth(entt::registry& registry);

/// \} End of depth

}  // namespace wanderer::sys
