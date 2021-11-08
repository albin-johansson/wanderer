#include "hud_rendering_system.hpp"

#include <array>        // array
#include <format>       // format_to_n
#include <string_view>  // string_view

#include <rune/rune.hpp>  // formatted_string

#include "components/binds.hpp"
#include "components/player.hpp"
#include "components/portal.hpp"
#include "components/trigger.hpp"
#include "components/ui/fps_data.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "inventory_rendering_system.hpp"
#include "systems/level_system.hpp"
#include "systems/ui/grid.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

constexpr auto enter_fmt = "Press \" {}\" to enter";
constexpr auto exit_fmt = "Press \" {}\" to exit";
constexpr auto sleep_fmt = "Press \" {}\" to sleep";
constexpr auto container_fmt = "Press \" {}\" to open container";

void RenderHint(GraphicsContext& graphics,
                const std::string_view fmt,
                const std::string& key)
{
  const rune::formatted_string<64> hint{fmt, key};
  const auto& cache = graphics.GetSmallFontCacheWhite();
  const auto width = cache.get_font().string_width(hint.data()).value();
  graphics.RenderOutlinedText(hint.view(), cen::point(CenterX(width), 100));
}

void RenderHints(const entt::registry& shared, GraphicsContext& graphics)
{
  const auto& binds = shared.ctx<ctx::Binds>();
  const auto& level = CurrentLevel(shared);

  const auto player = singleton_entity<Player>(level.registry);

  if (const auto* within = level.registry.try_get<IsWithinTrigger>(player)) {
    const auto& trigger = level.registry.get<Trigger>(within->trigger_entity);
    switch (trigger.type) {
      case TriggerType::portal: {
        if (sys::IsCurrentLevelOutside(shared)) {
          RenderHint(graphics, enter_fmt, binds.interact.name());
        }
        else {
          RenderHint(graphics, exit_fmt, binds.interact.name());
        }
        break;
      }
      case TriggerType::container: {
        RenderHint(graphics, container_fmt, binds.interact.name());
        break;
      }
      case TriggerType::bed: {
        RenderHint(graphics, sleep_fmt, binds.interact.name());
        break;
      }
    }
  }
}

}  // namespace

void RenderHud(const entt::registry& shared, cen::ipoint mousePos)
{
  auto& graphics = shared.ctx<Ref<GraphicsContext>>().get();
  RenderHints(shared, graphics);

  const auto& level = CurrentLevel(shared);
  RenderInventoryBar(level.registry, graphics);
  RenderInventory(level.registry, graphics, mousePos);
}

}  // namespace wanderer::sys
