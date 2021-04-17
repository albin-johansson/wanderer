#pragma once

#include <entt.hpp>  // registry

#include "components/ctx/player.hpp"
#include "components/hitbox.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer::sys {

template <typename Trigger, typename IsWithinTrigger, typename RemovalPredicate>
void update_triggers(entt::registry& registry, RemovalPredicate&& predicate)
{
  const auto player = registry.ctx<ctx::player>().entity;
  const auto& playerHitbox = registry.get<comp::hitbox>(player);

  for (auto&& [entity, trigger, hitbox] : registry.view<Trigger, comp::hitbox>().each())
  {
    const auto triggerEntity = typename Trigger::entity{entity};
    hitbox.enabled = true;

    if (sys::intersects(playerHitbox, hitbox))
    {
      registry.emplace_or_replace<IsWithinTrigger>(player, triggerEntity);
    }
    else if (const auto* ptr = registry.try_get<IsWithinTrigger>(player))
    {
      if (predicate(*ptr, triggerEntity))
      {
        registry.remove<IsWithinTrigger>(player);
      }
    }

    hitbox.enabled = false;
  }
}

}  // namespace wanderer::sys
