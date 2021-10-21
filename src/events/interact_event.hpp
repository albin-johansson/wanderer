#pragma once

#include <entt.hpp>  // registry, dispatcher

#include "wanderer_std.hpp"

namespace wanderer {

/// \brief Emitted when the player interacted with something in the game world.
/// \ingroup events
struct InteractEvent final
{
  ref<entt::registry> registry;
  ref<entt::dispatcher> dispatcher;
};

}  // namespace wanderer
