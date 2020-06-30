#include "make_viewport.h"

#include "game_constants.h"

namespace wanderer {

auto make_viewport(entt::registry& registry) -> ViewportEntity
{
  const auto entity = registry.create();

  auto& viewport = registry.emplace<Viewport>(entity);
  viewport.bounds.set(
      {{0, 0}, {g_logicalWidth<float>, g_logicalHeight<float>}});
  viewport.levelSize.width = 1000;
  viewport.levelSize.height = 1000;  // FIXME update automatically
  return ViewportEntity{entity};
}

}  // namespace wanderer
