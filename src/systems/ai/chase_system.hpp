#pragma once

#include <entt.hpp>  // registry, dispatcher

namespace wanderer::sys {

/// \name AI
/// \{

void update_chase(entt::registry& registry, entt::dispatcher& dispatcher);

/// \} End of AI

}  // namespace wanderer::sys
