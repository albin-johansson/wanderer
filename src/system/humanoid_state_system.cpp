#include "humanoid_state_system.h"

#include <centurion_as_ctn.h>

#include "humanoid_animation_system.h"
#include "humanoid_state.h"

namespace wanderer {
namespace {

void update_attack(entt::registry& registry, entt::entity entity)
{
  if (registry.has<HumanoidAttack>(entity)) {
    const auto& attack = registry.get<HumanoidAttack>(entity);
    if (attack.done) {
      registry.remove<HumanoidAttack>(entity);
      registry.emplace_or_replace<HumanoidIdle>(entity);
      humanoid_enter_idle_animation(registry, entity);
    }
  }
}

}  // namespace

void humanoids_update_state(entt::registry& registry)
{
  const auto entities = registry.view<Humanoid>();
  for (const auto entity : entities) {
    update_attack(registry, entity);
  }
}

}  // namespace wanderer
