#include "interaction_system.hpp"

#include <cassert>  // assert

#include "components/associated_entity.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/portal.hpp"
#include "components/player.hpp"
#include "components/trigger.hpp"
#include "core/ecs/null_entity.hpp"
#include "core/ecs/registry_utils.hpp"
#include "events/inventory_events.hpp"
#include "events/sleep_event.hpp"
#include "events/switch_map_event.hpp"

namespace wanderer::sys {

void on_interact(const interact_event& event)
{
  auto& registry = event.registry.get();
  auto& dispatcher = event.dispatcher.get();
  const auto player = singleton_entity<comp::Player>(registry);

  if (const auto* within = registry.try_get<comp::IsWithinTrigger>(player)) {
    assert(within->trigger_entity != entt::null);

    const auto& trigger = registry.get<comp::Trigger>(within->trigger_entity);
    switch (trigger.type) {
      case comp::TriggerType::portal: {
        const auto& portal = registry.get<comp::Portal>(within->trigger_entity);
        dispatcher.enqueue<switch_map_event>(portal.target.value());
        break;
      }
      case comp::TriggerType::container: {
        if (registry.empty<comp::ActiveInventory>()) {
          const auto& ref = registry.get<comp::AssociatedEntity>(within->trigger_entity);
          dispatcher.enqueue<show_inventory_event>(ref.entity);
        }
        else {
          dispatcher.enqueue<close_inventory_event>();
        }

        break;
      }

      case comp::TriggerType::bed: {
        dispatcher.enqueue<sleep_event>();
        break;
      }
    }
  }
}

}  // namespace wanderer::sys
