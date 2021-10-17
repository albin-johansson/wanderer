#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Animation
/// \{

/**
 * \brief Updates all `animation` components in a registry.
 *
 * \ingroup systems
 *
 * \param registry the registry that contains the animated components.
 *
 * \since 0.1.0
 */
void UpdateAnimations(entt::registry& registry);

/// \} End of animation

}  // namespace wanderer::sys
