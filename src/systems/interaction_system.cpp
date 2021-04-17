#include "interaction_system.hpp"

#include "components/inventory/container_trigger.hpp"
#include "components/map/portal.hpp"
#include "core/null_entity.hpp"
#include "ctx/player.hpp"
#include "events/close_inventory_event.hpp"
#include "events/show_inventory_event.hpp"
#include "events/switch_map_event.hpp"

namespace wanderer::sys {
namespace {

void enqueue_switch_map_event(entt::registry& registry,
                              entt::dispatcher& dispatcher,
                              const entt::entity portalEntity)
{
  const auto& portal = registry.get<comp::portal>(portalEntity);
  dispatcher.enqueue<event::switch_map>(portal.target.value());
}

void enqueue_inventory_event(entt::registry& registry,
                             entt::dispatcher& dispatcher,
                             const entt::entity triggerEntity)
{
  if (registry.empty<comp::active_inventory>())
  {
    const auto& trigger = registry.get<comp::container_trigger>(triggerEntity);
    dispatcher.enqueue<event::show_inventory>(trigger.inventoryEntity);
  }
  else
  {
    dispatcher.enqueue<event::close_inventory>();
  }
}

}  // namespace

void on_interact(const event::interact& event)
{
  auto& registry = event.registry.get();
  auto& dispatcher = event.dispatcher.get();
  const auto player = registry.ctx<ctx::player>().entity;

  if (const auto* p = registry.try_get<comp::is_within_portal>(player))
  {
    enqueue_switch_map_event(registry, dispatcher, p->portalEntity);
  }
  else if (const auto* ct = registry.try_get<comp::is_within_container_trigger>(player))
  {
    enqueue_inventory_event(registry, dispatcher, ct->triggerEntity);
  }
}

}  // namespace wanderer::sys
