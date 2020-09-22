#include "make_viewport_system.h"

#include "game_constants.h"

using wanderer::comp::Viewport;

namespace wanderer::sys::viewport {

auto make_viewport(entt::registry& registry) -> Viewport::entity
{
  const auto entity = registry.create();

  auto& viewport = registry.emplace<Viewport>(entity);
  viewport.bounds = {{0, 0}, {g_logicalWidth<float>, g_logicalHeight<float>}};
  viewport.levelSize.width = 1000;
  viewport.levelSize.height = 1000;  // FIXME update automatically

  return Viewport::entity{entity};
}

}  // namespace wanderer::sys::viewport
