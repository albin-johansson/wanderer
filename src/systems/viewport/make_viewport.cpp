#include "game_constants.hpp"
#include "viewport_system.hpp"

namespace wanderer::sys {

auto make_viewport(entt::registry& registry, const cen::farea& levelSize)
    -> comp::viewport::entity
{
  const auto entity = registry.create();

  auto& viewport = registry.emplace<comp::viewport>(entity);
  viewport.bounds = {{}, glob::logical_size<cen::farea>};
  viewport.levelSize.width = levelSize.width;
  viewport.levelSize.height = levelSize.height;

  return comp::viewport::entity{entity};
}

}  // namespace wanderer::sys
