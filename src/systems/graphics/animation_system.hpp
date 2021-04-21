#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Animation
/// \{

/**
 * \brief Updates all `animated` components in a registry.
 *
 * \ingroup systems
 *
 * \param registry the registry that contains the animated components.
 *
 * \since 0.1.0
 */
void update_animations(entt::registry& registry);

/// \} End of animation

}  // namespace wanderer::sys
