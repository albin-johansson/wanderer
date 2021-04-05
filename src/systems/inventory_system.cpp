#include "inventory_system.hpp"

#include "container_trigger.hpp"
#include "game_constants.hpp"
#include "index_to_matrix.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "maybe.hpp"
#include "update_triggers.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto n_rows = 4;        ///< Amount of inventory cell rows.
inline constexpr auto n_cols = 5;        ///< Amount of inventory cell columns.
inline constexpr auto cell_width = 32;   ///< Width of inventory cells.
inline constexpr auto cell_height = 32;  ///< Height of inventory cells.
inline constexpr auto offset = 2;        ///< Space in between inventory cells.

inline constexpr cen::iarea cell_size{cell_width, cell_height};

[[nodiscard]] constexpr auto get_render_origin() -> cen::ipoint
{
  constexpr cen::iarea area{(cell_width + offset) * n_cols,
                            (cell_height + offset) * n_rows};

  constexpr auto logicalSize = glob::logical_size<>;
  constexpr auto x = (logicalSize.width - area.width) / 2;
  constexpr auto y = (logicalSize.height - area.height) / 2;

  return {x, y};
}

inline constexpr cen::ipoint origin = get_render_origin();

[[nodiscard]] auto get_rect(const int row, const int col)
{
  const cen::ipoint pos{origin.x() + (col * (cell_width + offset)),
                        origin.y() + (row * (cell_height + offset))};
  return cen::irect{pos, cell_size};
}

}  // namespace

void update_inventory_triggers(entt::registry& registry)
{
  using trigger_t = comp::container_trigger;
  using is_within_trigger_t = comp::is_within_container_trigger;

  const auto removePredicate = [](const is_within_trigger_t& isWithinTrigger,
                                  const trigger_t::entity triggerEntity) {
    return isWithinTrigger.triggerEntity == triggerEntity;
  };

  sys::update_triggers<trigger_t, is_within_trigger_t>(registry, removePredicate);
}

void render_inventory(const entt::registry& registry,
                      cen::renderer& renderer,
                      const cen::ipoint& mousePos)
{
  const auto view = registry.view<const comp::inventory, const comp::active_inventory>();
  view.each([&](const comp::inventory& inventory) {
    const auto nItems = inventory.items.size();

    renderer.fill_with(glob::transparent_black);

    maybe<int> hoverIndex;
    auto index = 0;
    for (auto row = 0; row < n_rows; ++row)
    {
      for (auto col = 0; col < n_cols; ++col, ++index)
      {
        const auto rect = get_rect(row, col);
        if (rect.contains(mousePos))
        {
          hoverIndex = index;
        }

        renderer.set_color(index >= inventory.capacity ? cen::colors::black
                                                       : cen::colors::gray);
        renderer.fill_rect(rect);

        if (index < nItems)
        {
          const auto& item = registry.get<comp::item>(inventory.items.at(index));
          renderer.render(*item.texture, rect);
        }
      }
    }

    if (hoverIndex)
    {
      const auto [row, col] = index_to_matrix(*hoverIndex, n_cols);
      const auto rect = get_rect(row, col);
      renderer.set_color(cen::colors::dark_green);
      renderer.draw_rect(rect);
    }
  });
}

}  // namespace wanderer::sys
