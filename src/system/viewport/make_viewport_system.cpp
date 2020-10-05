#include "make_viewport_system.hpp"

#include "game_constants.hpp"

namespace wanderer::sys::viewport {

auto make_viewport(entt::registry& registry) -> comp::viewport::entity
{
  const auto entity = registry.create();

  auto& viewport = registry.emplace<comp::viewport>(entity);
  viewport.bounds = {{}, {g_logicalWidth<float>, g_logicalHeight<float>}};
  viewport.levelSize.width = 1000;
  viewport.levelSize.height = 1000;  // FIXME update automatically

  return comp::viewport::entity{entity};
}

}  // namespace wanderer::sys::viewport
