#include "hud_rendering_system.hpp"

#include "components/ctx/binds.hpp"
#include "components/inventory/container_trigger.hpp"
#include "components/map/portal.hpp"
#include "components/player.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/menu_constants.hpp"
#include "systems/levels/level_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

void render_message(graphics_context& graphics, const auto& text)
{
  const auto& cache = graphics.small_font_cache();
  const auto width = cache.get_font().string_width(text).value();
  graphics.render_outlined_text(text, cen::point(center_x(width), 100));
}

}  // namespace

void render_hud(const entt::registry& shared, graphics_context& graphics)
{
  const auto& binds = shared.ctx<const ctx::binds>();
  const auto& level = current_level(shared);

  const auto player = singleton_entity<const comp::player>(level.registry);
  if (level.registry.all_of<comp::is_within_portal>(player))
  {
    if (sys::is_current_level_outside(shared))
    {
      render_message(graphics, "Press \"" + binds.interact.name() + "\" to enter");
    }
    else
    {
      render_message(graphics, "Press \"" + binds.interact.name() + "\" to exit");
    }
  }
  else if (level.registry.all_of<comp::is_within_container_trigger>(player))
  {
    render_message(graphics, "Press \"" + binds.interact.name() + "\" to open container");
  }
}

}  // namespace wanderer::sys
