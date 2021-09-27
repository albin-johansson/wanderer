#include "inventory_rendering_system.hpp"

#include <rune/everything.hpp>  // index_to_matrix

#include "common/maybe.hpp"
#include "components/items/inventory.hpp"
#include "components/items/item.hpp"
#include "core/game_constants.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

inline constexpr cen::color cell_color{0xAA, 0xAA, 0xAA, 0xCC};

inline constexpr int n_rows = 4;        ///< Amount of inventory cell rows.
inline constexpr int n_cols = 5;        ///< Amount of inventory cell columns.
inline constexpr int cell_width = 48;   ///< Width of inventory cells.
inline constexpr int cell_height = 48;  ///< Height of inventory cells.
inline constexpr int spacing = 4;       ///< Space in between inventory cells.

inline constexpr cen::iarea cell_size{cell_width, cell_height};

inline constexpr int bar_cell_count = 10;
inline constexpr int bar_cell_width = 30;
inline constexpr int bar_cell_height = 30;
inline constexpr int bar_cell_spacing = 2;

[[nodiscard]] consteval auto get_render_origin() -> cen::ipoint
{
  constexpr cen::iarea area{(cell_width + spacing) * n_cols,
                            (cell_height + spacing) * n_rows};

  constexpr auto logicalSize = glob::logical_size<>;
  constexpr auto x = (logicalSize.width - area.width) / 2;
  constexpr auto y = (logicalSize.height - area.height) / 2;

  return {x, y};
}

inline constexpr cen::ipoint origin = get_render_origin();

}  // namespace

void render_inventory_bar(const entt::registry& registry, graphics_context& graphics)
{
  constexpr auto totalWidth =
      bar_cell_count * bar_cell_width + (bar_cell_count * bar_cell_spacing);
  constexpr auto x = center_x(totalWidth);
  constexpr auto y = glob::logical_height<int> - bar_cell_height - glob::default_margin;

  auto& renderer = graphics.get_renderer();
  for (auto i = 0; i < bar_cell_count; ++i) {
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

void render_inventory(const entt::registry& registry,
                      graphics_context& graphics,
                      const cen::ipoint& mousePos)
{
  auto& renderer = graphics.get_renderer();

  const auto getCellPos = [](const int row, const int col) noexcept {
    return cen::ipoint{origin.x() + (col * (cell_width + spacing)),
                       origin.y() + (row * (cell_height + spacing))};
  };

  for (auto&& [entity, inventory] :
       registry.view<comp::inventory, comp::active_inventory>().each())
  {
    renderer.fill_with(glob::transparent_black);

    const auto nItems = inventory.items.size();
    maybe<int> hoverIndex;
    int index = 0;

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
