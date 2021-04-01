#include "render_bounds_system.hpp"

#include "game_constants.hpp"
#include "viewport.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto calculate_min_col(const float viewportX) noexcept -> int
{
  const auto minCol = static_cast<int>(viewportX / glob::tile_width<>);
  if (minCol > 0)
  {
    return minCol;
  }
  else
  {
    return 0;
  }
}

[[nodiscard]] auto calculate_min_row(const float viewportY) noexcept -> int
{
  const auto minRow = static_cast<int>(viewportY / glob::tile_height<>);
  if (minRow > 0)
  {
    return minRow;
  }
  else
  {
    return 0;
  }
}

[[nodiscard]] auto calculate_max_col(const float viewportMaxX, const int numCols) noexcept
    -> int
{
  const auto maxCol = static_cast<int>(viewportMaxX / glob::tile_width<>) + 1;
  if (maxCol < numCols)
  {
    return maxCol;
  }
  else
  {
    return numCols;
  }
}

[[nodiscard]] auto calculate_max_row(const float viewportMaxY, const int numRows) noexcept
    -> int
{
  const auto maxRow = static_cast<int>(viewportMaxY / glob::tile_height<>) + 1;
  if (maxRow < numRows)
  {
    return maxRow;
  }
  else
  {
    return numRows;
  }
}

}  // namespace

auto get_render_bounds(const entt::registry& registry, const int rows, const int cols)
    -> comp::render_bounds
{
  const auto& viewport = registry.ctx<comp::viewport>();

  comp::render_bounds bounds;
  bounds.minCol = calculate_min_col(viewport.bounds.x());
  bounds.minRow = calculate_min_row(viewport.bounds.y());
  bounds.maxCol = calculate_max_col(viewport.bounds.max_x(), cols);
  bounds.maxRow = calculate_max_row(viewport.bounds.max_y(), rows);

  return bounds;
}

auto to_rect(const comp::render_bounds& bounds) noexcept -> cen::frect
{
  const auto x = static_cast<float>(bounds.minCol) * glob::tile_width<>;
  const auto y = static_cast<float>(bounds.minRow) * glob::tile_height<>;

  const auto w = static_cast<float>(bounds.maxCol - bounds.minCol) * glob::tile_width<>;
  const auto h = static_cast<float>(bounds.maxRow - bounds.minRow) * glob::tile_height<>;

  return cen::frect{{x, y}, {w, h}};
}

}  // namespace wanderer::sys
