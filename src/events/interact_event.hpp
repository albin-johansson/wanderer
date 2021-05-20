#pragma once

#include <entt.hpp>    // registry, dispatcher
#include <functional>  // reference_wrapper

namespace wanderer {

/// \brief Emitted when the player interacted with something in the game world.
/// \ingroup events
struct interact_event final
{
  std::reference_wrapper<entt::registry> registry;
  std::reference_wrapper<entt::dispatcher> dispatcher;
};

}  // namespace wanderer
