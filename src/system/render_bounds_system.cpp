#include "render_bounds_system.h"

#include <stdexcept>

#include "game_constants.h"
#include "viewport.h"

namespace wanderer {

RenderBounds calculate_render_bounds(entt::registry& registry,
                                     const entt::entity viewportEntity,
                                     const int rows,
                                     const int cols)
{
  const auto* viewport = registry.try_get<Viewport>(viewportEntity);
  if (!viewport) {
    throw std::runtime_error{"Failed to obtain viewport for render bounds!"};
  }

  const auto& viewportBounds = viewport->bounds();

  RenderBounds bounds;
  bounds.minCol = static_cast<int>(viewportBounds.x()) / g_tileSize<int>;
  bounds.minRow = static_cast<int>(viewportBounds.y()) / g_tileSize<int>;
  bounds.maxCol =
      (static_cast<int>(viewportBounds.max_x()) / g_tileSize<int>)+1;
  bounds.maxRow =
      (static_cast<int>(viewportBounds.max_y()) / g_tileSize<int>)+1;

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

}  // namespace wanderer
