#include "inventory_system.hpp"

#include <cassert>  // assert

#include "container_trigger.hpp"
#include "game_constants.hpp"
#include "inventory.hpp"
#include "update_triggers.hpp"

namespace wanderer::sys::inventory {
namespace {

inline constexpr auto nRows = 4;        ///< Amount of inventory cell rows.
inline constexpr auto nCols = 5;        ///< Amount of inventory cell columns.
inline constexpr auto cellWidth = 32;   ///< Width of inventory cells.
inline constexpr auto cellHeight = 32;  ///< Height of inventory cells.
inline constexpr auto offset = 2;       ///< Space in between inventory cells.

[[nodiscard]] constexpr auto get_render_origin() -> cen::ipoint
{
  constexpr cen::iarea area{(cellWidth + offset) * nCols,
                            (cellHeight + offset) * nRows};

  constexpr auto logicalSize = glob::logicalSize<>;
  constexpr auto x = (logicalSize.width - area.width) / 2;
  constexpr auto y = (logicalSize.height - area.height) / 2;

  return {x, y};
}

}  // namespace

void update_triggers(entt::registry& registry,
                     const comp::player::entity player)
{
  const auto removePredicate =
      [](const comp::is_within_container_trigger& isWithinTrigger,
         const comp::container_trigger::entity triggerEntity) {
        return isWithinTrigger.triggerEntity == triggerEntity;
      };

  sys::update_triggers<comp::container_trigger,
                       comp::is_within_container_trigger>(registry,
                                                          player,
                                                          removePredicate);
}

void render(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view =
      registry.view<const comp::inventory, const comp::active_inventory>();
  if (view.empty()) {
    return;
  }

  assert(view.size() == 1);

  const auto& inventory = registry.get<comp::inventory>(view.front());
  constexpr auto origin = get_render_origin();

  renderer.set_color(glob::transparentBlack);
  renderer.fill_rect<int>({{}, glob::logicalSize<>});

  auto i = 0;
  for (auto row = 0; row < nRows; ++row) {
    for (auto col = 0; col < nCols; ++col, ++i) {
      if (i >= inventory.capacity) {
        renderer.set_color(cen::colors::black);
      } else {
        renderer.set_color(cen::colors::gray);
      }

      const cen::ipoint pos{origin.x() + (col * (cellWidth + offset)),
                            origin.y() + (row * (cellHeight + offset))};
      constexpr cen::iarea cellSize{cellWidth, cellHeight};

      renderer.draw_rect<int>({pos, cellSize});
    }
  }
}

}  // namespace wanderer::sys::inventory
