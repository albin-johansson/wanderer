#include "humanoid_move_event_handler.hpp"

#include "component/humanoid_state.hpp"
#include "humanoid_animation_system.hpp"

namespace wanderer::sys::humanoid {

void on_move_begin(const begin_humanoid_move_event& event)
{
  assert(event.registry != nullptr);
  assert(!event.registry->has<comp::humanoid_move>(event.entity));

  const auto entity = event.entity;

  event.registry->emplace<comp::humanoid_move>(entity);

  humanoid::enter_move_animation(*event.registry, entity, event.direction);
}

void on_move_end(const end_humanoid_move_event& event)
{
  assert(event.registry != nullptr);
  assert(event.registry->has<comp::humanoid_move>(event.entity));

  const auto entity = event.entity;

  //  event.registry->remove<HumanoidMove>(entity);
  event.registry->emplace<comp::humanoid_idle>(entity);
  assert(!event.registry->has<comp::humanoid_move>(entity));

  humanoid::enter_idle_animation(*event.registry, entity);
}

}  // namespace wanderer::sys::humanoid
