#include "render_bounds_system.hpp"

#include "game_constants.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto calculate_min_col(float viewportX) noexcept -> int
{
  const auto minCol = static_cast<int>(viewportX / g_tileSize<float>);
  if (minCol > 0) {
    return minCol;
  } else {
    return 0;
  }
}

[[nodiscard]] auto calculate_min_row(float viewportY) noexcept -> int
{
  const auto minRow = static_cast<int>(viewportY / g_tileSize<float>);
  if (minRow > 0) {
    return minRow;
  } else {
    return 0;
  }
}

[[nodiscard]] auto calculate_max_col(float viewportMaxX, int numCols) noexcept
    -> int
{
  const auto maxCol = static_cast<int>(viewportMaxX / g_tileSize<float>) + 1;
  if (maxCol < numCols) {
    return maxCol;
  } else {
    return numCols;
  }
}

[[nodiscard]] auto calculate_max_row(float viewportMaxY, int numRows) noexcept
    -> int
{
  const auto maxRow = static_cast<int>(viewportMaxY / g_tileSize<float>) + 1;
  if (maxRow < numRows) {
    return maxRow;
  } else {
    return numRows;
  }
}

}  // namespace

auto calculate_render_bounds(entt::registry& registry,
                             const comp::viewport::entity viewportEntity,
                             const int rows,
                             const int cols) -> comp::render_bounds
{
  const auto& viewport = registry.get<comp::viewport>(viewportEntity.get());

  comp::render_bounds bounds;
  bounds.minCol = calculate_min_col(viewport.bounds.x());
  bounds.minRow = calculate_min_row(viewport.bounds.y());
  bounds.maxCol = calculate_max_col(viewport.bounds.max_x(), cols);
  bounds.maxRow = calculate_max_row(viewport.bounds.max_y(), rows);

  return bounds;
}

}  // namespace wanderer::sys
