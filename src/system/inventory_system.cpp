#include "inventory_system.hpp"

#include "container_trigger.hpp"
#include "update_triggers.hpp"

namespace wanderer::sys::inventory {

void update_triggers(entt::registry& registry,
                     const comp::player::entity player)
{
  const auto removePredicate =
      [](const comp::is_within_container_trigger& isWithinTrigger,
         const comp::container_trigger::entity triggerEntity) {
        return isWithinTrigger.triggerEntity == triggerEntity;
      };

  sys::update_triggers<comp::container_trigger,
                       comp::is_within_container_trigger>(registry,
                                                          player,
                                                          removePredicate);
}

void render(const entt::registry& registry, cen::renderer& renderer)
{
}

}  // namespace wanderer::sys::inventory
