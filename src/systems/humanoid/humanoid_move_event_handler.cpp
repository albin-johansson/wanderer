#include "humanoid_move_event_handler.hpp"

#include "components/humanoid_state.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"

namespace wanderer::sys {

void on_move_begin(const begin_humanoid_move_event& event)
{
  auto& registry = event.registry.get();
  assert(!registry.all_of<comp::humanoid_move>(event.entity));

  const auto entity = event.entity;
  registry.emplace<comp::humanoid_move>(entity);
  enter_move_animation(event.registry, entity, event.dir);
}

void on_move_end(const end_humanoid_move_event& event)
{
  auto& registry = event.registry.get();
  assert(registry.all_of<comp::humanoid_move>(event.entity));

  const auto entity = event.entity;
  registry.emplace<comp::humanoid_idle>(entity);
  assert(!registry.all_of<comp::humanoid_move>(entity));

  enter_idle_animation(event.registry, entity);
}

}  // namespace wanderer::sys
