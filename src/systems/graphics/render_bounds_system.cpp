#include "render_bounds_system.hpp"

#include "components/ctx/level_size.hpp"
#include "components/ctx/render_bounds.hpp"
#include "components/ctx/viewport.hpp"
#include "core/game_constants.hpp"

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

void update_render_bounds(entt::registry& registry)
{
  const auto& viewport = registry.ctx<ctx::viewport>();
  const auto& size = registry.ctx<ctx::level_size>();

  auto& bounds = registry.set<ctx::render_bounds>();
  bounds.min_col = calculate_min_col(viewport.bounds.x());
  bounds.min_row = calculate_min_row(viewport.bounds.y());
  bounds.max_col = calculate_max_col(viewport.bounds.max_x(), size.col_count);
  bounds.max_row = calculate_max_row(viewport.bounds.max_y(), size.row_count);
}

}  // namespace wanderer::sys
