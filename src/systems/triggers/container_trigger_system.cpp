#include "container_trigger_system.hpp"

#include "components/container_trigger.hpp"
#include "update_triggers.hpp"

namespace wanderer::sys {

void update_container_triggers(entt::registry& registry)
{
  const auto removalPredicate =
      [](const comp::is_within_container_trigger& isWithinTrigger,
         const comp::container_trigger::entity triggerEntity) {
        return isWithinTrigger.trigger_entity == triggerEntity;
      };

  sys::update_triggers<comp::container_trigger, comp::is_within_container_trigger>(
      registry,
      removalPredicate);
}

}  // namespace wanderer::sys
