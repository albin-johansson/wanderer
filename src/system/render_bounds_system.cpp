#include "render_bounds_system.hpp"

#include "game_constants.hpp"
#include "math_utils.hpp"
#include "viewport.hpp"

using wanderer::comp::RenderBounds;
using wanderer::comp::Viewport;

namespace wanderer::sys {

auto calculate_render_bounds(entt::registry& registry,
                             const Viewport::entity viewportEntity,
                             const int rows,
                             const int cols) -> RenderBounds
{
  const auto& viewport = registry.get<Viewport>(viewportEntity.get());
  const auto& viewportBounds = viewport.bounds;

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

}  // namespace wanderer::sys
