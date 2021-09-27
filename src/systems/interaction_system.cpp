#include "interaction_system.hpp"

#include "components/bed_trigger.hpp"
#include "components/container_trigger.hpp"
#include "components/player.hpp"
#include "components/portal.hpp"
#include "core/ecs/null_entity.hpp"
#include "core/ecs/registry_utils.hpp"
#include "events/close_inventory_event.hpp"
#include "events/show_inventory_event.hpp"
#include "events/sleep_event.hpp"
#include "events/switch_map_event.hpp"

namespace wanderer::sys {
namespace {

void enqueue_switch_map_event(entt::registry& registry,
                              entt::dispatcher& dispatcher,
                              const entt::entity portalEntity)
{
  const auto& portal = registry.get<comp::portal>(portalEntity);
  dispatcher.enqueue<switch_map_event>(portal.target.value());
}

void enqueue_inventory_event(entt::registry& registry,
                             entt::dispatcher& dispatcher,
                             const entt::entity triggerEntity)
{
  if (registry.empty<comp::active_inventory>()) {
    const auto& trigger = registry.get<comp::container_trigger>(triggerEntity);
    dispatcher.enqueue<show_inventory_event>(trigger.inventory_entity);
  }
  else {
    dispatcher.enqueue<close_inventory_event>();
  }
}

void enqueue_sleep_event(entt::registry& registry, entt::dispatcher& dispatcher)
{
  dispatcher.enqueue<sleep_event>();
}

}  // namespace

void on_interact(const interact_event& event)
{
  auto& registry = event.registry.get();
  auto& dispatcher = event.dispatcher.get();
  const auto player = singleton_entity<comp::player>(registry);

  if (const auto* p = registry.try_get<comp::is_within_portal>(player)) {
    enqueue_switch_map_event(registry, dispatcher, p->portal_entity);
  }
  else if (const auto* ct = registry.try_get<comp::is_within_container_trigger>(player)) {
    enqueue_inventory_event(registry, dispatcher, ct->trigger_entity);
  }
  else if (const auto* bt = registry.try_get<comp::is_within_bed_trigger>(player)) {
    enqueue_sleep_event(registry, dispatcher);
  }
}

}  // namespace wanderer::sys
