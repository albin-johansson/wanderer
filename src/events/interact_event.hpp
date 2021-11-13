#pragma once

#include <entt/entt.hpp>  // registry, dispatcher

#include "wanderer_std.hpp"

namespace wanderer {

/// \brief Emitted when the player interacted with something in the game world.
/// \ingroup events
struct InteractEvent final
{
  Ref<entt::registry> registry;
  Ref<entt::dispatcher> dispatcher;
};

}  // namespace wanderer
