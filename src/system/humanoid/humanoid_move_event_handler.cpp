#include "humanoid_move_event_handler.h"

#include "humanoid_animation_system.h"
#include "humanoid_state.h"

namespace wanderer::system::humanoid {

void on_move_begin(const BeginHumanoidMoveEvent& event)
{
  assert(event.registry != nullptr);
  assert(!event.registry->has<HumanoidMove>(event.entity));

  const auto entity = event.entity;

  event.registry->remove_if_exists<HumanoidIdle>(entity);
  event.registry->emplace<HumanoidMove>(entity);

  humanoid::enter_move_animation(*event.registry, entity, event.direction);
}

void on_move_end(const EndHumanoidMoveEvent& event)
{
  assert(event.registry != nullptr);
  assert(event.registry->has<HumanoidMove>(event.entity));

  const auto entity = event.entity;

  event.registry->remove<HumanoidMove>(entity);
  event.registry->emplace<HumanoidIdle>(entity);

  humanoid::enter_idle_animation(*event.registry, entity);
}

}  // namespace wanderer::system::humanoid
