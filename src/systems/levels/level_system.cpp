#include "level_system.hpp"

#include <cassert>  // assert

#include "components/lvl/level.hpp"
#include "components/lvl/level_switch_target.hpp"
#include "components/physics/movable.hpp"
#include "components/player.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "systems/gfx/viewport_system.hpp"

namespace wanderer::sys {

auto prepare_current_level_before_switch(entt::registry& shared,
                                         const custom_animation_halfway_event& event)
    -> map_id
{
  assert(event.id == glob::switch_level_id);
  auto& level = sys::current_level(shared);

  const auto player = singleton_entity<comp::Player>(level.registry);
  auto& movable = level.registry.get<comp::Movable>(player);
  movable.velocity.reset();

  sys::center_viewport_on(level.registry, movable.position);

  const auto next = level.registry.get<comp::LevelSwitchTarget>(event.entity).id;
  level.registry.destroy(event.entity);

  return next;
}

void enable_level(entt::registry& shared, const map_id id)
{
  shared.clear<comp::ActiveLevel>();

  for (auto&& [entity, level] : shared.view<comp::Level>().each()) {
    if (level.id == id) {
      shared.emplace<comp::ActiveLevel>(entity);
      break;
    }
  }

  assert(shared.size<comp::ActiveLevel>() == 1);
}

auto current_level(entt::registry& shared) -> comp::Level&
{
  return shared.get<comp::Level>(singleton_entity<const comp::ActiveLevel>(shared));
}

auto current_level(const entt::registry& shared) -> const comp::Level&
{
  return shared.get<comp::Level>(singleton_entity<const comp::ActiveLevel>(shared));
}

auto is_current_level_outside(const entt::registry& shared) -> bool
{
  const auto level = singleton_entity<const comp::ActiveLevel>(shared);
  return shared.all_of<comp::OutsideLevel>(level);
}

}  // namespace wanderer::sys
