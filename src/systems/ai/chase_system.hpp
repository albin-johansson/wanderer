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
 * \param dispatcher the dispatcher that will be used.
 */
void update_chase(entt::registry& registry, entt::dispatcher& dispatcher);

/// \} End of AI

}  // namespace wanderer::sys
