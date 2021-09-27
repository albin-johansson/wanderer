#include "level_system.hpp"

#include <cassert>  // assert

#include "components/level_switch_target.hpp"
#include "components/movable.hpp"
#include "components/outside_level.hpp"
#include "components/player.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "systems/graphics/viewport_system.hpp"

namespace wanderer::sys {

auto prepare_current_level_before_switch(entt::registry& shared,
                                         const custom_animation_halfway_event& event)
    -> map_id
{
  assert(event.id == glob::switch_level_id);
  auto& level = sys::current_level(shared);

  const auto player = singleton_entity<comp::player>(level.registry);
  auto& movable = level.registry.get<comp::movable>(player);
  movable.velocity.reset();

  sys::center_viewport_on(level.registry, movable.position);

  const auto next = level.registry.get<comp::level_switch_target>(event.entity).id;
  level.registry.destroy(event.entity);

  return next;
}

void enable_level(entt::registry& shared, const map_id id)
{
  shared.clear<comp::active_level>();

  for (auto&& [entity, level] : shared.view<comp::level>().each()) {
    if (level.id == id) {
      shared.emplace<comp::active_level>(entity);
      break;
    }
  }

  assert(shared.size<comp::active_level>() == 1);
}

auto current_level(entt::registry& shared) -> comp::level&
{
  return shared.get<comp::level>(singleton_entity<const comp::active_level>(shared));
}

auto current_level(const entt::registry& shared) -> const comp::level&
{
  return shared.get<comp::level>(singleton_entity<const comp::active_level>(shared));
}

auto is_current_level_outside(const entt::registry& shared) -> bool
{
  const auto level = singleton_entity<const comp::active_level>(shared);
  return shared.all_of<comp::outside_level>(level);
}

}  // namespace wanderer::sys
