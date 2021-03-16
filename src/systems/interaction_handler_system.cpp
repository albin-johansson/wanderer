#include "interaction_handler_system.hpp"

#include "close_inventory_event.hpp"
#include "container_trigger.hpp"
#include "null_entity.hpp"
#include "portal.hpp"
#include "show_inventory_event.hpp"
#include "switch_map_event.hpp"

namespace wanderer::sys {
namespace {

void enqueue_switch_map_event(entt::registry& registry,
                              entt::dispatcher& dispatcher,
                              const entt::entity portalEntity)
{
  const auto& portal = registry.get<comp::portal>(portalEntity);
  dispatcher.enqueue<comp::switch_map_event>(portal.target.value());
}

void enqueue_inventory_event(entt::registry& registry,
                             entt::dispatcher& dispatcher,
                             const comp::player::entity player,
                             const entt::entity triggerEntity)
{
  if (registry.empty<comp::active_inventory>())
  {
    const auto& trigger = registry.get<comp::container_trigger>(triggerEntity);
    dispatcher.enqueue<comp::show_inventory_event>(trigger.inventoryEntity);

  } else
  {
    dispatcher.enqueue<comp::close_inventory_event>();
  }
}

}  // namespace

void on_interact(const comp::interact_event& event)
{
  assert(event.registry);
  assert(event.dispatcher);
  assert(event.player != null<comp::player>());

  auto& registry = *event.registry;
  auto& dispatcher = *event.dispatcher;
  const auto player = event.player;

  if (const auto* p = registry.try_get<comp::is_within_portal>(player))
  {
    enqueue_switch_map_event(registry, dispatcher, p->portalEntity);

  } else if (const auto* ct =
                 registry.try_get<comp::is_within_container_trigger>(player))
  {
    enqueue_inventory_event(registry, dispatcher, player, ct->triggerEntity);
  }
}

}  // namespace wanderer::sys
