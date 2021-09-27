#include "trigger_system.hpp"

#include "components/hitbox.hpp"
#include "components/player.hpp"
#include "components/trigger.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer::sys {

void update_triggers(entt::registry& registry, entt::dispatcher& dispatcher)
{
  const auto player = singleton_entity<comp::player>(registry);
  const auto& playerHitbox = registry.get<comp::hitbox>(player);

  for (auto&& [triggerEntity, trigger, hitbox] :
       registry.view<comp::trigger, comp::hitbox>().each())
  {
    hitbox.enabled = true;

    if (sys::intersects(playerHitbox, hitbox)) {
      registry.emplace_or_replace<comp::is_within_trigger>(player, triggerEntity);
    }
    else if (const auto* within = registry.try_get<comp::is_within_trigger>(player)) {
      if (within->trigger_entity == triggerEntity) {
        registry.remove<comp::is_within_trigger>(player);
      }
    }

    hitbox.enabled = false;
  }
}

}  // namespace wanderer::sys