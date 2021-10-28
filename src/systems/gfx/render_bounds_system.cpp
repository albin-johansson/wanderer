#include "render_bounds_system.hpp"

#include "components/level_size.hpp"
#include "components/render_bounds.hpp"
#include "components/viewport.hpp"
#include "core/game_constants.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto CalculateMinCol(const float viewportX) noexcept -> uint64
{
  const auto minCol = viewportX / glob::tile_width<>;
  if (minCol > 0) {
    return static_cast<uint64>(minCol);
  }
  else {
    return 0u;
  }
}

[[nodiscard]] auto CalculateMinRow(const float viewportY) noexcept -> uint64
{
  const auto minRow = viewportY / glob::tile_height<>;
  if (minRow > 0) {
    return static_cast<uint64>(minRow);
  }
  else {
    return 0u;
  }
}

[[nodiscard]] auto CalculateMaxCol(const float viewportMaxX,
                                   const uint64 numCols) noexcept -> uint64
{
  const auto maxCol = static_cast<uint64>(viewportMaxX / glob::tile_width<>) + 1u;
  if (maxCol < numCols) {
    return maxCol;
  }
  else {
    return numCols;
  }
}

[[nodiscard]] auto CalculateMaxRow(const float viewportMaxY,
                                   const uint64 numRows) noexcept -> uint64
{
  const auto maxRow = static_cast<uint64>(viewportMaxY / glob::tile_height<>) + 1u;
  if (maxRow < numRows) {
    return maxRow;
  }
  else {
    return numRows;
  }
}

}  // namespace

void UpdateRenderBounds(entt::registry& registry)
{
  const auto& viewport = registry.ctx<ctx::Viewport>();
  const auto& size = registry.ctx<ctx::LevelSize>();

  auto& bounds = registry.set<ctx::RenderBounds>();
  bounds.min_col = CalculateMinCol(viewport.bounds.x());
  bounds.min_row = CalculateMinRow(viewport.bounds.y());
  bounds.max_col = CalculateMaxCol(viewport.bounds.max_x(), size.col_count);
  bounds.max_row = CalculateMaxRow(viewport.bounds.max_y(), size.row_count);
}

}  // namespace wanderer::sys
