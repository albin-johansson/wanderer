#include "level_switch_animation_system.hpp"

#include "components/level_switch_target.hpp"
#include "core/game_constants.hpp"
#include "systems/animation/custom_animation_system.hpp"

namespace wanderer::sys {

void StartLevelChangeAnimation(entt::registry& registry, const MapID map)
{
  const auto entity = StartBondAnimation(registry, glob::switch_level_id);

  auto& target = registry.emplace<LevelSwitchTarget>(entity);
  target.id = map;
}

}  // namespace wanderer::sys
