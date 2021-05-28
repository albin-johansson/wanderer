#include "hud_rendering_system.hpp"

#include <format>  // format

#include "components/bed_trigger.hpp"
#include "components/ctx/binds.hpp"
#include "components/inventory/container_trigger.hpp"
#include "components/map/portal.hpp"
#include "components/player.hpp"
#include "components/ui/fps_data.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/menu_constants.hpp"
#include "systems/levels/level_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto enter_fmt = "Press \"{}\" to enter";
inline constexpr auto exit_fmt = "Press \"{}\" to exit";
inline constexpr auto sleep_fmt = "Press \"{}\" to sleep";
inline constexpr auto container_fmt = "Press \"{}\" to open container";

inline constexpr auto cell_count = 10;
inline constexpr auto cell_width = 30;
inline constexpr auto cell_height = 30;
inline constexpr auto cell_spacing = 2;
inline constexpr cen::color cell_color{0xAA, 0xAA, 0xAA, 0xCC};

void render_hint(graphics_context& graphics, const auto& text)
{
  const auto& cache = graphics.small_font_cache();
  const auto width = cache.get_font().string_width(text).value();
  graphics.render_outlined_text(text, cen::point(center_x(width), 100));
}

void render_hints(const entt::registry& shared, graphics_context& graphics)
{
  const auto& binds = shared.ctx<const ctx::binds>();
  const auto& level = current_level(shared);

  const auto player = singleton_entity<const comp::player>(level.registry);
  if (level.registry.all_of<comp::is_within_portal>(player))
  {
    if (sys::is_current_level_outside(shared))
    {
      render_hint(graphics, std::format(enter_fmt, binds.interact.name()));
    }
    else
    {
      render_hint(graphics, std::format(exit_fmt, binds.interact.name()));
    }
  }
  else if (level.registry.all_of<comp::is_within_container_trigger>(player))
  {
    render_hint(graphics, std::format(container_fmt, binds.interact.name()));
  }
  else if (level.registry.all_of<comp::is_within_bed_trigger>(player))
  {
    render_hint(graphics, std::format(sleep_fmt, binds.interact.name()));
  }
}

void render_item_bar(graphics_context& graphics)
{
  constexpr auto width = cell_count * cell_width + (cell_count * cell_spacing);
  constexpr auto x = center_x(width);
  constexpr auto y = glob::logical_height<int> - cell_height - 6;

  auto& renderer = graphics.renderer();
  for (auto i = 0; i < cell_count; ++i)
  {
    const auto cell =
        cen::rect(x + (i * (cell_width + cell_spacing)), y, cell_width, cell_height);

    renderer.set_color(cell_color);
    renderer.fill_rect(cell);

    renderer.set_color(cen::colors::black);
    renderer.draw_rect(cell);
  }
}

}  // namespace

void render_hud(const entt::registry& shared, graphics_context& graphics)
{
  render_hints(shared, graphics);
  render_item_bar(graphics);
}

}  // namespace wanderer::sys
