#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/**
 * \brief Sorts all depth drawables.
 *
 * \param registry the current level registry.
 *
 * \since 0.1.0
 */
void update_depth(entt::registry& registry);

}  // namespace wanderer::sys
