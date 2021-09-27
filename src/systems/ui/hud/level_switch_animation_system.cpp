#include "level_switch_animation_system.hpp"

#include "components/lvl/level_switch_target.hpp"
#include "core/game_constants.hpp"
#include "systems/graphics/custom_animation_system.hpp"

namespace wanderer::sys {

void start_level_change_animation(entt::registry& registry, map_id map)
{
  const auto entity = start_bond_animation(registry, glob::switch_level_id);

  auto& target = registry.emplace<comp::level_switch_target>(entity);
  target.id = map;
}

}  // namespace wanderer::sys
