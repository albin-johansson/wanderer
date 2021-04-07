#include "humanoid_move_event_handler.hpp"

#include "humanoid_animation_system.hpp"
#include "humanoid_state.hpp"

namespace wanderer::sys {

void on_move_begin(const event::begin_humanoid_move& event)
{
  auto& registry = event.registry.get();
  assert(!registry.has<comp::humanoid_move>(event.entity));

  const auto entity = event.entity;
  registry.emplace<comp::humanoid_move>(entity);
  enter_move_animation(event.registry, entity, event.dir);
}

void on_move_end(const event::end_humanoid_move& event)
{
  auto& registry = event.registry.get();
  assert(registry.has<comp::humanoid_move>(event.entity));

  const auto entity = event.entity;
  registry.emplace<comp::humanoid_idle>(entity);
  assert(!registry.has<comp::humanoid_move>(entity));

  enter_idle_animation(event.registry, entity);
}

}  // namespace wanderer::sys
