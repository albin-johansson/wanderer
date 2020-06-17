#include "humanoid_attack_event_handler.h"

#include <cassert>

#include "humanoid_animation_system.h"
#include "humanoid_state.h"

namespace wanderer::system::humanoid {

void on_attack_begin(const BeginAttackEvent& event)
{
  assert(event.registry != nullptr);
  assert(!event.registry->has<HumanoidAttack>(event.sourceEntity));

  event.registry->remove_if_exists<HumanoidIdle>(event.sourceEntity);
  event.registry->remove_if_exists<HumanoidMove>(event.sourceEntity);

  auto& attack = event.registry->emplace<HumanoidAttack>(event.sourceEntity);
  attack.weapon = event.weapon;

  // TODO enter correct animation according to weapon
  enter_melee_animation(*event.registry, event.sourceEntity);
}

void on_attack_end(const EndAttackEvent& event)
{
  assert(event.registry != nullptr);
  assert(event.registry->has<HumanoidAttack>(event.sourceEntity));

  event.registry->remove<HumanoidAttack>(event.sourceEntity);
  event.registry->emplace<HumanoidIdle>(event.sourceEntity);

  // TODO deal damage (need target area)

  enter_idle_animation(*event.registry, event.sourceEntity);
}

}  // namespace wanderer::system::humanoid
