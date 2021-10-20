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

auto PrepareCurrentLevelBeforeSwitch(entt::registry& shared,
                                     const CustomAnimationHalfwayEvent& event) -> map_id
{
  assert(event.id == glob::switch_level_id);
  auto& level = sys::CurrentLevel(shared);

  const auto player = singleton_entity<comp::Player>(level.registry);
  auto& movable = level.registry.get<comp::Movable>(player);
  movable.velocity.x = 0;
  movable.velocity.y = 0;

  sys::CenterViewportOn(level.registry, movable.position);

  const auto next = level.registry.get<comp::LevelSwitchTarget>(event.entity).id;
  level.registry.destroy(event.entity);

  return next;
}

void EnableLevel(entt::registry& shared, map_id id)
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

auto CurrentLevel(entt::registry& shared) -> comp::Level&
{
  return shared.get<comp::Level>(singleton_entity<const comp::ActiveLevel>(shared));
}

auto CurrentLevel(const entt::registry& shared) -> const comp::Level&
{
  return shared.get<comp::Level>(singleton_entity<const comp::ActiveLevel>(shared));
}

auto IsCurrentLevelOutside(const entt::registry& shared) -> bool
{
  const auto level = singleton_entity<const comp::ActiveLevel>(shared);
  return shared.all_of<comp::OutsideLevel>(level);
}

}  // namespace wanderer::sys
