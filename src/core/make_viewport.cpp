#include "make_viewport.h"

#include "game_constants.h"
#include "viewport.h"

namespace wanderer {

entt::entity make_viewport(entt::registry& registry)
{
  const auto entity = registry.create();

  auto& viewport = registry.emplace<Viewport>(entity);
  viewport.set_bounds(
      {{0, 0}, {g_logicalWidth<float>, g_logicalHeight<float>}});
  viewport.set_level_size({1000, 1000});  // FIXME update automatically
  return entity;
}

}  // namespace wanderer
