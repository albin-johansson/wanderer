#include "debug_rendering_system.hpp"

#include <cassert>  // assert

#include "components/ai/chase.hpp"
#include "components/ctx/active_menu.hpp"
#include "components/gfx/depth_drawable.hpp"
#include "components/items/container_ref.hpp"
#include "components/lvl/portal.hpp"
#include "components/physics/hitbox.hpp"
#include "components/player.hpp"
#include "components/trigger.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/ui/menus/menu_system.hpp"

namespace wanderer::sys {
namespace {

void render_hitboxes(const entt::registry& registry, cen::renderer& renderer)
{
  for (auto&& [entity, hitbox] : registry.view<comp::hitbox>().each()) {
    if (registry.all_of<comp::trigger>(entity)) {
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

void render_trigger_indicators(const entt::registry& registry, cen::renderer& renderer)
{
  const auto entity = singleton_entity<const comp::player>(registry);
  if (const auto* within = registry.try_get<comp::is_within_trigger>(entity)) {
    assert(registry.all_of<comp::hitbox>(within->trigger_entity));

    const auto& hitbox = registry.get<comp::hitbox>(within->trigger_entity);
    renderer.set_color(cen::colors::cyan.with_alpha(100));
    renderer.fill_rect_t(hitbox.bounds);
  }
}

void render_chase_ranges(const entt::registry& registry, cen::renderer& renderer)
{
  renderer.set_color(cen::colors::red);

  for (auto&& [entity, drawable, chase] :
       registry.view<comp::depth_drawable, comp::chase>().each())
  {
    renderer.draw_circle_t(drawable.dst.center(), chase.range);
  }
}

void render_development_build_label(graphics_context& graphics)
{
  auto& renderer = graphics.get_renderer();
  const auto& cache = graphics.small_font_cache();

  constexpr char str[] = "Development build";
  const auto [width, height] = cache.get_font().string_size(str).value();
  const auto x = glob::logical_width<int> - width - 6;
  const auto y = glob::logical_height<int> - height - 6;
  renderer.render_text(cache, str, {x, y});
}

}  // namespace

void render_debug_info(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.get_renderer();
  render_hitboxes(registry, renderer);
  render_trigger_indicators(registry, renderer);
  render_chase_ranges(registry, renderer);
}

void render_menu_debug_info(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.get_renderer();

  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;
  const auto& menu = registry.get<comp::menu>(menuEntity);

  if (menu.id != menu_id::in_game) {
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

  render_development_build_label(graphics);
}

}  // namespace wanderer::sys
