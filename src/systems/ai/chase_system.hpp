#pragma once

#include <entt.hpp>  // registry, dispatcher

namespace wanderer::sys {

/// \name AI
/// \{

/**
 * \brief Updates entities with `chase` components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void UpdateChase(entt::registry& registry);

/// \} End of AI

}  // namespace wanderer::sys
