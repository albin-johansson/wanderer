#include "debug_rendering_system.hpp"

#include <cassert>  // assert

#include "components/associated_entity.hpp"
#include "components/chase.hpp"
#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/player.hpp"
#include "components/portal.hpp"
#include "components/tile.hpp"
#include "components/trigger.hpp"
#include "components/ui/menu.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/ui/menus/menu_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

void RenderHitboxes(const entt::registry& registry, cen::renderer& renderer)
{
  constexpr auto filter = entt::exclude_t<Tile>();
  for (auto&& [entity, hitbox] : registry.view<Hitbox>(filter).each()) {
    if (registry.all_of<Trigger>(entity)) {
      renderer.set_color(cen::colors::cyan);
    }
    else {
      renderer.set_color(cen::colors::lime);
    }

    for (const auto& [offset, size] : hitbox.boxes) {
      const cen::frect rect{to_point(hitbox.origin + offset), size};

      renderer.set_color(renderer.get_color().with_alpha(100));
      renderer.draw_rect_t(rect);
    }

    renderer.set_color(renderer.get_color().with_alpha(255));
    renderer.draw_rect_t(hitbox.bounds);
  }
}

void RenderTriggerIndicators(const entt::registry& registry, cen::renderer& renderer)
{
  const auto entity = singleton_entity<const Player>(registry);
  if (const auto* within = registry.try_get<IsWithinTrigger>(entity)) {
    assert(registry.all_of<Hitbox>(within->trigger_entity));

    const auto& hitbox = registry.get<Hitbox>(within->trigger_entity);
    renderer.set_color(cen::colors::cyan.with_alpha(100));
    renderer.fill_rect_t(hitbox.bounds);
  }
}

void RenderChaseRanges(const entt::registry& registry, cen::renderer& renderer)
{
  renderer.set_color(cen::colors::red);

  for (auto&& [entity, drawable, chase] : registry.view<Drawable, Chase>().each()) {
    renderer.draw_circle_t(drawable.dst.center(), chase.range);
  }
}

void RenderDevelopmentBuildLabel(GraphicsContext& graphics)
{
  auto& renderer = graphics.GetRenderer();
  const auto& cache = graphics.GetSmallFontCacheWhite();

  constexpr char str[] = "Development build";
  const auto [width, height] = cache.get_font().string_size(str).value();
  const auto x = glob::logical_width<int> - width - 6;
  const auto y = glob::logical_height<int> - height - 6;
  renderer.render_text(cache, str, {x, y});
}

}  // namespace

void RenderDebugInfo(const entt::registry& registry)
{
  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();
  auto& renderer = graphics.GetRenderer();
  RenderHitboxes(registry, renderer);
  RenderTriggerIndicators(registry, renderer);
  RenderChaseRanges(registry, renderer);
}

void RenderMenuDebugInfo(const entt::registry& registry)
{
  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();
  auto& renderer = graphics.GetRenderer();

  const auto menuEntity = registry.ctx<ActiveMenu>().entity;
  const auto& menu = registry.get<Menu>(menuEntity);

  if (menu.render_background) {
    renderer.set_color(cen::colors::light_gray.with_alpha(50));

    const auto endX = glob::logical_width<>;
    const auto endY = glob::logical_height<>;

    for (auto row = 0; row < glob::menu_rows; ++row) {
      const auto y = row * glob::menu_row_size;
      renderer.draw_line<float>({0, y}, {endX, y});
    }

    for (auto col = 0; col < glob::menu_columns; ++col) {
      const auto x = col * glob::menu_col_size;
      renderer.draw_line<float>({x, 0}, {x, endY});
    }

    renderer.draw_line<float>({0, endY - 1}, {endX, endY - 1});
    renderer.draw_line<float>({endX - 1, 0}, {endX - 1, endY});
  }

  RenderDevelopmentBuildLabel(graphics);
}

}  // namespace wanderer::sys
