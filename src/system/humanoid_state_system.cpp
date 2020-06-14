#include "humanoid_state_system.h"

#include <centurion_as_ctn.h>

#include "humanoid_animation_system.h"
#include "humanoid_state.h"

namespace wanderer::system::humanoid {
namespace {

void update_attack(entt::registry& registry, const entt::entity entity)
{
  if (registry.has<HumanoidAttack>(entity)) {
    const auto& attack = registry.get<HumanoidAttack>(entity);
    if (attack.done) {
      registry.remove<HumanoidAttack>(entity);
      registry.emplace_or_replace<HumanoidIdle>(entity);
      enter_idle_animation(registry, entity);
    }
  }
}

}  // namespace

void update_state(entt::registry& registry)
{
  const auto entities = registry.view<Humanoid>();
  for (const auto entity : entities) {
    update_attack(registry, entity);
  }
}

}  // namespace wanderer::system::humanoid
