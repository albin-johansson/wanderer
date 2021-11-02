#include "trigger_system.hpp"

#include "components/hitbox.hpp"
#include "components/player.hpp"
#include "components/trigger.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/physics/hitbox_system.hpp"

namespace wanderer::sys {

void UpdateTriggers(entt::registry& registry)
{
  const auto player = singleton_entity<Player>(registry);
  const auto& playerHitbox = registry.get<Hitbox>(player);

  for (auto&& [triggerEntity, trigger, hitbox] : registry.view<Trigger, Hitbox>().each())
  {
    hitbox.enabled = true;

    if (sys::Intersects(playerHitbox, hitbox)) {
      registry.emplace_or_replace<IsWithinTrigger>(player, triggerEntity);
    }
    else if (const auto* within = registry.try_get<IsWithinTrigger>(player)) {
      if (within->trigger_entity == triggerEntity) {
        registry.remove<IsWithinTrigger>(player);
      }
    }

    hitbox.enabled = false;
  }
}

}  // namespace wanderer::sys