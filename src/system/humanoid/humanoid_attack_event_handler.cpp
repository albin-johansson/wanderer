#include "humanoid_attack_event_handler.hpp"

#include <cassert>

#include "humanoid_animation_system.hpp"
#include "humanoid_state.hpp"

namespace wanderer::sys::humanoid {

void on_attack_begin(const BeginAttackEvent& event)
{
  assert(event.registry != nullptr);
  assert(!event.registry->has<comp::HumanoidAttack>(event.sourceEntity));

  auto& attack =
      event.registry->emplace<comp::HumanoidAttack>(event.sourceEntity);
  attack.weapon = event.weapon;

  // TODO enter correct animation according to weapon
  enter_melee_animation(*event.registry, event.sourceEntity);
}

void on_attack_end(const EndAttackEvent& event)
{
  assert(event.registry != nullptr);
  assert(event.registry->has<comp::HumanoidAttack>(event.sourceEntity));

  event.registry->emplace<comp::HumanoidIdle>(event.sourceEntity);

  assert(!event.registry->has<comp::HumanoidAttack>(event.sourceEntity));

  // TODO deal damage (need target area)

  enter_idle_animation(*event.registry, event.sourceEntity);
}

}  // namespace wanderer::sys::humanoid
