#include "render_bounds_system.h"

#include <cassert>

#include "game_constants.h"
#include "math_utils.h"
#include "viewport.h"

namespace wanderer::system {

auto calculate_render_bounds(entt::registry& registry,
                             const Viewport::entity viewportEntity,
                             const int rows,
                             const int cols) -> RenderBounds
{
  const auto* viewport = registry.try_get<Viewport>(viewportEntity.get());
  assert(viewport);

  const auto& viewportBounds = viewport->bounds;

  RenderBounds bounds;
  bounds.minCol = Math::round(viewportBounds.x()) / g_tileSize<int>;
  bounds.minRow = Math::round(viewportBounds.y()) / g_tileSize<int>;
  bounds.maxCol = (Math::round(viewportBounds.max_x()) / g_tileSize<int>)+1;
  bounds.maxRow = (Math::round(viewportBounds.max_y()) / g_tileSize<int>)+1;

  if (bounds.minCol < 0) {
    bounds.minCol = 0;
  }

  if (bounds.minRow < 0) {
    bounds.minRow = 0;
  }

  if (bounds.maxRow > rows) {
    bounds.maxRow = rows;
  }

  if (bounds.maxCol > cols) {
    bounds.maxCol = cols;
  }

  return bounds;
}

}  // namespace wanderer::system
