#include "humanoid_state_system.hpp"

#include <cassert>  // assert

#include "components/ai/humanoid_state.hpp"
#include "components/physics/movable.hpp"
#include "events/end_attack_event.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"
#include "systems/physics/direction_system.hpp"

namespace wanderer::sys {
namespace {

void update_attacking_humanoids(entt::registry& registry, entt::dispatcher& dispatcher)
{
  for (auto&& [entity, attack] : registry.view<comp::humanoid_attack>().each()) {
    if (attack.done) {
      dispatcher.enqueue<end_attack_event>(registry,
                                           dispatcher,
                                           entity,
                                           attack.weapon,
                                           direction::down);
    }
  }
}

}  // namespace

void make_humanoid_idle(entt::registry& registry, const entt::entity entity)
{
  assert(registry.all_of<comp::humanoid>(entity));
  assert(!registry.all_of<comp::humanoid_idle>(entity));

  auto& movable = registry.get<comp::movable>(entity);
  movable.velocity.reset();

  registry.emplace<comp::humanoid_idle>(entity);
  enter_idle_animation(registry, entity);
}

void make_humanoid_move(entt::registry& registry, entt::entity entity)
{
  assert(registry.all_of<comp::humanoid>(entity));
  assert(!registry.all_of<comp::humanoid_move>(entity));

  auto& movable = registry.get<comp::movable>(entity);

  registry.emplace<comp::humanoid_move>(entity);
  enter_move_animation(registry, entity, dominant_direction(movable));
}

void update_humanoid_states(entt::registry& registry, entt::dispatcher& dispatcher)
{
  update_attacking_humanoids(registry, dispatcher);
}

}  // namespace wanderer::sys
