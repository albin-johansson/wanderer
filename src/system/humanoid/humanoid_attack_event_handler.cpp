#include "humanoid_attack_event_handler.hpp"

#include <cassert>

#include "component/humanoid_state.hpp"
#include "humanoid_animation_system.hpp"

namespace wanderer::sys::humanoid {

void on_attack_begin(const begin_attack_event& event)
{
  assert(event.registry != nullptr);
  assert(!event.registry->has<comp::humanoid_attack>(event.sourceEntity));

  auto& attack =
      event.registry->emplace<comp::humanoid_attack>(event.sourceEntity);
  attack.weapon = event.weapon;

  // TODO enter correct animation according to weapon
  enter_melee_animation(*event.registry, event.sourceEntity);
}

void on_attack_end(const end_attack_event& event)
{
  assert(event.registry != nullptr);
  assert(event.registry->has<comp::humanoid_attack>(event.sourceEntity));

  event.registry->emplace<comp::humanoid_idle>(event.sourceEntity);

  assert(!event.registry->has<comp::humanoid_attack>(event.sourceEntity));

  // TODO deal damage (need target area)

  enter_idle_animation(*event.registry, event.sourceEntity);
}

}  // namespace wanderer::sys::humanoid
