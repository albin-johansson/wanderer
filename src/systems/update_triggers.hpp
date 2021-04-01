#pragma once

#include <entt.hpp>

#include "hitbox.hpp"
#include "hitbox_system.hpp"
#include "player.hpp"

namespace wanderer::sys {

template <typename Trigger, typename IsWithinTrigger, typename RemovalPred>
void update_triggers(entt::registry& registry, RemovalPred&& predicate)
{
  const auto player = registry.ctx<ctx::player>().entity;
  const auto& playerHitbox = registry.get<comp::hitbox>(player);

  const auto view = registry.view<Trigger, comp::hitbox>();
  view.each([&](const entt::entity e, const Trigger&, comp::hitbox& hitbox) {
    const auto triggerEntity = typename Trigger::entity{e};
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
  });
}

}  // namespace wanderer::sys
