#include "bed_trigger_system.hpp"

#include "components/bed_trigger.hpp"
#include "update_triggers.hpp"

namespace wanderer::sys {

void update_bed_triggers(entt::registry& registry)
{
  const auto removalPredicate = [](const comp::is_within_bed_trigger& isWithinTrigger,
                                   const comp::bed_trigger::entity triggerEntity) {
    return isWithinTrigger.trigger_entity == triggerEntity;
  };

  sys::update_triggers<comp::bed_trigger, comp::is_within_bed_trigger>(registry,
                                                                       removalPredicate);
}

}  // namespace wanderer::sys
