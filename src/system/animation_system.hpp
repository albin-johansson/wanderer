#pragma once

#include <entt.hpp>

namespace wanderer::sys {

/**
 * \brief Updates all `animated` components in a registry.
 *
 * \param registry the registry that contains the animated components.
 *
 * \since 0.1.0
 */
void update_animations(entt::registry& registry) noexcept;

}  // namespace wanderer::sys
