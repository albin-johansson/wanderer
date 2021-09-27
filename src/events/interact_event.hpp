#pragma once

#include <entt.hpp>  // registry, dispatcher

#include "common/ref.hpp"

namespace wanderer {

/// \brief Emitted when the player interacted with something in the game world.
/// \ingroup events
struct interact_event final
{
  ref<entt::registry> registry;
  ref<entt::dispatcher> dispatcher;
};

}  // namespace wanderer
