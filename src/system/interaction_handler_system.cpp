#include "interaction_handler_system.hpp"

#include "hitbox.hpp"
#include "null_entity.hpp"
#include "portal.hpp"
#include "switch_map_event.hpp"

namespace wanderer::sys {

void on_interact(const comp::interact_event& event)
{
  assert(event.registry);
  assert(event.dispatcher);
  assert(event.player != null<comp::player>());

  auto* registry = event.registry;
  const auto player = event.player;

  if (const auto* iwp = registry->try_get<comp::is_within_portal>(player)) {
    const auto& portal = registry->get<comp::portal>(iwp->portalEntity);
    event.dispatcher->enqueue<comp::switch_map_event>(portal.target.value());
  }
}

}  // namespace wanderer::sys
