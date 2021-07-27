#include "hud_rendering_system.hpp"

#include <format>  // format

#include "components/bed_trigger.hpp"
#include "components/container_trigger.hpp"
#include "components/ctx/binds.hpp"
#include "components/player.hpp"
#include "components/portal.hpp"
#include "components/ui/fps_data.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "inventory_rendering_system.hpp"
#include "systems/levels/level_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto enter_fmt = "Press \" {}\" to enter";
inline constexpr auto exit_fmt = "Press \" {}\" to exit";
inline constexpr auto sleep_fmt = "Press \" {}\" to sleep";
inline constexpr auto container_fmt = "Press \" {}\" to open container";

void render_hint(graphics_context& graphics, const auto& text)
{
  const auto& cache = graphics.small_font_cache();
  const auto width = cache.get_font().string_width(text).value();
  graphics.render_outlined_text(text, cen::point(center_x(width), 100));
}

void render_hints(const entt::registry& shared, graphics_context& graphics)
{
  const auto& binds = shared.ctx<ctx::binds>();
  const auto& level = current_level(shared);

  const auto player = singleton_entity<comp::player>(level.registry);
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

}  // namespace

void render_hud(const entt::registry& shared,
                graphics_context& graphics,
                const cen::ipoint mousePos)
{
  render_hints(shared, graphics);

  const auto& level = current_level(shared);
  render_inventory_bar(level.registry, graphics);
  render_inventory(level.registry, graphics, mousePos);
}

}  // namespace wanderer::sys
