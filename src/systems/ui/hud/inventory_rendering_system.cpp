#include "inventory_rendering_system.hpp"

#include <rune/rune.hpp>  // index_to_matrix

#include "components/items/inventory.hpp"
#include "core/game_constants.hpp"
#include "systems/ui/grid.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

constexpr cen::color cell_color{0xAA, 0xAA, 0xAA, 0xCC};

constexpr int32 n_rows = 4;        ///< Amount of inventory cell rows.
constexpr int32 n_cols = 5;        ///< Amount of inventory cell columns.
constexpr int32 cell_width = 48;   ///< Width of inventory cells.
constexpr int32 cell_height = 48;  ///< Height of inventory cells.
constexpr int32 spacing = 4;       ///< Space in between inventory cells.

constexpr cen::iarea cell_size{cell_width, cell_height};

constexpr int32 bar_cell_count = 10;
constexpr int32 bar_cell_width = 30;
constexpr int32 bar_cell_height = 30;
constexpr int32 bar_cell_spacing = 2;

[[nodiscard]] consteval auto GetRenderOrigin() -> cen::ipoint
{
  constexpr cen::iarea area{(cell_width + spacing) * n_cols,
                            (cell_height + spacing) * n_rows};

  constexpr auto logicalSize = glob::logical_size<>;
  constexpr auto x = (logicalSize.width - area.width) / 2;
  constexpr auto y = (logicalSize.height - area.height) / 2;

  return {x, y};
}

constexpr cen::ipoint origin = GetRenderOrigin();

}  // namespace

void RenderInventoryBar(const entt::registry& registry, GraphicsContext& graphics)
{
  constexpr auto totalWidth =
      bar_cell_count * bar_cell_width + (bar_cell_count * bar_cell_spacing);
  constexpr auto x = CenterX(totalWidth);
  constexpr auto y = glob::logical_height<int> - bar_cell_height - glob::default_margin;

  auto& renderer = graphics.GetRenderer();
  for (int32 i = 0; i < bar_cell_count; ++i) {
    const auto cell = cen::rect(x + (i * (bar_cell_width + bar_cell_spacing)),
                                y,
                                bar_cell_width,
                                bar_cell_height);

    renderer.set_color(cell_color);
    renderer.fill_rect(cell);

    renderer.set_color(cen::colors::black);
    renderer.draw_rect(cell);
  }
}

void RenderInventory(const entt::registry& registry,
                     GraphicsContext& graphics,
                     const cen::ipoint& mousePos)
{
  auto& renderer = graphics.GetRenderer();

  const auto getCellPos = [](const int row, const int col) noexcept {
    return cen::ipoint{origin.x() + (col * (cell_width + spacing)),
                       origin.y() + (row * (cell_height + spacing))};
  };

  for (auto&& [entity, inventory] : registry.view<Inventory, ActiveInventory>().each()) {
    renderer.fill_with(glob::transparent_black);

    const auto nItems = inventory.items.size();
    maybe<int32> hoverIndex;
    int32 index = 0;

    for (auto row = 0; row < n_rows; ++row) {
      for (auto col = 0; col < n_cols; ++col, ++index) {
        const cen::irect rect{getCellPos(row, col), cell_size};

        if (rect.contains(mousePos)) {
          hoverIndex = index;
        }

        renderer.set_color(index >= inventory.capacity ? cen::colors::black : cell_color);
        renderer.fill_rect(rect);

        if (index < nItems) {
          // TODO render item preview
        }
      }
    }

    if (hoverIndex) {
      const auto [row, col] = rune::index_to_matrix(*hoverIndex, n_cols);
      const cen::irect rect{getCellPos(row, col), cell_size};

      renderer.set_color(cen::colors::lime_green);
      renderer.draw_rect(rect);
    }
  }
}

}  // namespace wanderer::sys
