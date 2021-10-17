#include "hud_rendering_system.hpp"

#include <array>                // array
#include <format>               // format_to_n
#include <rune/everything.hpp>  // formatted_string
#include <string_view>          // string_view

#include "common/ref.hpp"
#include "components/ctx/binds.hpp"
#include "components/lvl/portal.hpp"
#include "components/player.hpp"
#include "components/trigger.hpp"
#include "components/ui/fps_data.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "inventory_rendering_system.hpp"
#include "systems/levels/level_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto enter_fmt = "Press \" {}\" to enter";
inline constexpr auto exit_fmt = "Press \" {}\" to exit";
inline constexpr auto sleep_fmt = "Press \" {}\" to sleep";
inline constexpr auto container_fmt = "Press \" {}\" to open container";

void render_hint(GraphicsContext& graphics,
                 const std::string_view fmt,
                 const std::string& key)
{
  const rune::formatted_string<64> hint{fmt, key};
  const auto& cache = graphics.small_font_cache();
  const auto width = cache.get_font().string_width(hint.data()).value();
  graphics.render_outlined_text(hint.view(), cen::point(center_x(width), 100));
}

void render_hints(const entt::registry& shared, GraphicsContext& graphics)
{
  const auto& binds = shared.ctx<ctx::Binds>();
  const auto& level = CurrentLevel(shared);

  const auto player = singleton_entity<comp::Player>(level.registry);

  if (const auto* within = level.registry.try_get<comp::IsWithinTrigger>(player)) {
    const auto& trigger = level.registry.get<comp::Trigger>(within->trigger_entity);
    switch (trigger.type) {
      case comp::TriggerType::portal: {
        if (sys::IsCurrentLevelOutside(shared)) {
          render_hint(graphics, enter_fmt, binds.interact.name());
        }
        else {
          render_hint(graphics, exit_fmt, binds.interact.name());
        }
        break;
      }
      case comp::TriggerType::container: {
        render_hint(graphics, container_fmt, binds.interact.name());
        break;
      }
      case comp::TriggerType::bed: {
        render_hint(graphics, sleep_fmt, binds.interact.name());
        break;
      }
    }
  }
}

}  // namespace

void render_hud(const entt::registry& shared,
                const cen::ipoint mousePos)
{
  auto& graphics = shared.ctx<ref<GraphicsContext>>().get();
  render_hints(shared, graphics);

  const auto& level = CurrentLevel(shared);
  RenderInventoryBar(level.registry, graphics);
  RenderInventory(level.registry, graphics, mousePos);
}

}  // namespace wanderer::sys
