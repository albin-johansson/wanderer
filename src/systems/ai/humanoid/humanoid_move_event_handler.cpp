#include "humanoid_move_event_handler.hpp"

#include "components/ai/humanoid.hpp"
#include "humanoid_animation_system.hpp"

namespace wanderer::sys {

void OnMoveBegin(const BeginHumanoidMoveEvent& event)
{
  auto& registry = event.registry.get();
  assert(!registry.all_of<comp::HumanoidMove>(event.entity));

  const auto entity = event.entity;
  registry.emplace<comp::HumanoidMove>(entity);
  EnterMoveAnimation(event.registry, entity, event.dir);
}

void OnMoveEnd(const EndHumanoidMoveEvent& event)
{
  auto& registry = event.registry.get();
  assert(registry.all_of<comp::HumanoidMove>(event.entity));

  const auto entity = event.entity;
  registry.emplace<comp::HumanoidIdle>(entity);
  assert(!registry.all_of<comp::HumanoidMove>(entity));

  EnterIdleAnimation(event.registry, entity);
}

}  // namespace wanderer::sys
