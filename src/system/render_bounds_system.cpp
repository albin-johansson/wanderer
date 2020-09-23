#include "render_bounds_system.hpp"

#include "floating.hpp"
#include "game_constants.hpp"

namespace wanderer::sys {

auto calculate_render_bounds(entt::registry& registry,
                             const comp::viewport::entity viewportEntity,
                             const int rows,
                             const int cols) -> comp::render_bounds
{
  const auto& viewport = registry.get<comp::viewport>(viewportEntity.get());
  const auto& viewportBounds = viewport.bounds;

  comp::render_bounds bounds;
  bounds.minCol = round(viewportBounds.x()) / g_tileSize<int>;
  bounds.minRow = round(viewportBounds.y()) / g_tileSize<int>;
  bounds.maxCol = (round(viewportBounds.max_x()) / g_tileSize<int>)+1;
  bounds.maxRow = (round(viewportBounds.max_y()) / g_tileSize<int>)+1;

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

}  // namespace wanderer::sys
