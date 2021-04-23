#include "menu_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/button_group.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/menu.hpp"
#include "core/graphics/render_text.hpp"
#include "core/menu_constants.hpp"
#include "core/resources.hpp"
#include "systems/ui/buttons/button_rendering_system.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/checkboxes/checkbox_rendering_system.hpp"
#include "systems/ui/grid.hpp"
#include "systems/ui/labels/label_rendering_system.hpp"
#include "systems/ui/labels/label_system.hpp"
#include "systems/ui/lazy-textures/lazy_texture_rendering_system.hpp"
#include "systems/ui/lines/line_rendering_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline const auto backdrop_path = resources::texture("backdrop.png");

void render_title(const std::string& title,
                  const comp::menu_drawable& drawable,
                  cen::renderer& renderer)
{
  if (title.empty())
  {
    return;
  }

  if (!drawable.texture)
  {
    renderer.set_color(cen::colors::white);
    drawable.texture = render_text(renderer, title, renderer.get_font(glob::menu_font_l));
  }

  const auto& texture = *drawable.texture;

  if (!drawable.position)
  {
    const auto x = (glob::logical_width<float> / 2.0f) - (texture.width() / 2.0f);
    constexpr auto y = row_to_y(2);
    drawable.position = {x, y};
  }

  renderer.render(texture, *drawable.position);
}

}  // namespace

void render_menu(const entt::registry& registry, graphics_context& graphics)
{
  const auto menuEntity = registry.ctx<const ctx::active_menu>().entity;

  const auto& menu = registry.get<comp::menu>(menuEntity);
  const auto& drawable = registry.get<comp::menu_drawable>(menuEntity);

  auto& renderer = graphics.renderer();

  if (menu.blocking)
  {
    const auto index = graphics.load("backdrop"_hs, backdrop_path);
    renderer.render(graphics.find(index), cen::irect{{}, glob::logical_size<>});
    renderer.fill_with(glob::transparent_black);
  }

  if (const auto* pack = registry.try_get<comp::line_pack>(menuEntity))
  {
    render_lines(registry, graphics, *pack);
  }

  render_lazy_textures(registry, graphics);
  render_labels(registry, graphics);

  if (const auto* pack = registry.try_get<comp::button_pack>(menuEntity))
  {
    render_buttons(registry, graphics, *pack);
  }

  if (const auto* group = registry.try_get<comp::button_group>(menuEntity))
  {
    render_button_group(registry, graphics, *group);
  }

  if (const auto* pack = registry.try_get<comp::checkbox_pack>(menuEntity))
  {
    render_checkboxes(registry, graphics, *pack);
  }

  render_title(menu.title, drawable, renderer);

  if (menu.blocking)
  {
    constexpr auto id = "developed_by_albin_johansson"_hs;
    auto& cache = graphics.small_font_cache();

    if (!cache.has_stored(id))
    {
      renderer.set_color(cen::colors::white);
      cache.store_blended_utf8(id, "Developed by Albin Johansson", renderer);
    }

    const auto& texture = cache.get_stored(id);
    const auto y = glob::logical_height<int> - texture.height() - 6;
    renderer.render(texture, cen::point(6, y));
  }
}

}  // namespace wanderer::sys
