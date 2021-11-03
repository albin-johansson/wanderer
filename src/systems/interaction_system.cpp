#include "interaction_system.hpp"

#include <cassert>  // assert

#include "components/associated_entity.hpp"
#include "components/inventory.hpp"
#include "components/player.hpp"
#include "components/portal.hpp"
#include "components/trigger.hpp"
#include "core/ecs/null_entity.hpp"
#include "core/ecs/registry_utils.hpp"
#include "events/inventory_events.hpp"
#include "events/sleep_event.hpp"
#include "events/switch_map_event.hpp"

namespace wanderer::sys {

void OnInteract(const InteractEvent& event)
{
  auto& registry = event.registry.get();
  auto& dispatcher = event.dispatcher.get();
  const auto player = singleton_entity<Player>(registry);

  if (const auto* within = registry.try_get<IsWithinTrigger>(player)) {
    assert(within->trigger_entity != entt::null);

    const auto& trigger = registry.get<Trigger>(within->trigger_entity);
    switch (trigger.type) {
      case TriggerType::portal: {
        const auto& portal = registry.get<Portal>(within->trigger_entity);
        dispatcher.enqueue<SwitchMapEvent>(portal.target.value());
        break;
      }
      case TriggerType::container: {
        if (registry.empty<ActiveInventory>()) {
          const auto& ref = registry.get<AssociatedEntity>(within->trigger_entity);
          dispatcher.enqueue<ShowInventoryEvent>(ref.entity);
        }
        else {
          dispatcher.enqueue<CloseInventoryEvent>();
        }

        break;
      }

      case TriggerType::bed: {
        dispatcher.enqueue<SleepEvent>();
        break;
      }
    }
  }
}

}  // namespace wanderer::sys
