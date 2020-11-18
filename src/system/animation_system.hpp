#pragma once

#include <entt.hpp>

namespace wanderer::sys::animated {

/**
 * \brief Updates all `animated` components in a registry.
 *
 * \param registry the registry that contains the animated components.
 *
 * \since 0.1.0
 */
void update(entt::registry& registry) noexcept;

}  // namespace wanderer::sys::animated
