#include "trigger_system.hpp"

#include "components/physics/hitbox.hpp"
#include "components/player.hpp"
#include "components/trigger.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/physics/hitbox_system.hpp"

namespace wanderer::sys {

void UpdateTriggers(entt::registry& registry)
{
  const auto player = singleton_entity<comp::Player>(registry);
  const auto& playerHitbox = registry.get<comp::Hitbox>(player);

  for (auto&& [triggerEntity, trigger, hitbox] :
       registry.view<comp::Trigger, comp::Hitbox>().each())
  {
    hitbox.enabled = true;

    if (sys::Intersects(playerHitbox, hitbox)) {
      registry.emplace_or_replace<comp::IsWithinTrigger>(player, triggerEntity);
    }
    else if (const auto* within = registry.try_get<comp::IsWithinTrigger>(player)) {
      if (within->trigger_entity == triggerEntity) {
        registry.remove<comp::IsWithinTrigger>(player);
      }
    }

    hitbox.enabled = false;
  }
}

}  // namespace wanderer::sys