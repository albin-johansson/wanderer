#include "level_system.hpp"

#include <cassert>  // assert

#include "components/level.hpp"
#include "components/level_switch_target.hpp"
#include "components/movable.hpp"
#include "components/player.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "systems/gfx/viewport_system.hpp"

namespace wanderer::sys {

auto PrepareCurrentLevelBeforeSwitch(entt::registry& shared,
                                     const CustomAnimationHalfwayEvent& event) -> MapID
{
  assert(event.id == glob::switch_level_id);
  auto& level = sys::CurrentLevel(shared);

  const auto player = singleton_entity<Player>(level.registry);
  auto& movable = level.registry.get<Movable>(player);
  movable.velocity.x = 0;
  movable.velocity.y = 0;

  sys::CenterViewportOn(level.registry, movable.position);

  const auto next = level.registry.get<LevelSwitchTarget>(event.entity).id;
  level.registry.destroy(event.entity);

  return next;
}

void EnableLevel(entt::registry& shared, MapID id)
{
  shared.clear<ActiveLevel>();

  for (auto&& [entity, level] : shared.view<Level>().each()) {
    if (level.id == id) {
      shared.emplace<ActiveLevel>(entity);
      break;
    }
  }

  assert(shared.size<ActiveLevel>() == 1);
}

auto CurrentLevel(entt::registry& shared) -> Level&
{
  return shared.get<Level>(singleton_entity<const ActiveLevel>(shared));
}

auto CurrentLevel(const entt::registry& shared) -> const Level&
{
  return shared.get<Level>(singleton_entity<const ActiveLevel>(shared));
}

auto IsCurrentLevelOutside(const entt::registry& shared) -> bool
{
  const auto level = singleton_entity<const ActiveLevel>(shared);
  return shared.all_of<OutsideLevel>(level);
}

}  // namespace wanderer::sys
