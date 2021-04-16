#include "active_menu.hpp"
#include "button_group.hpp"
#include "button_system.hpp"
#include "checkbox.hpp"
#include "checkbox_system.hpp"
#include "grid.hpp"
#include "label_system.hpp"
#include "line_system.hpp"
#include "menu.hpp"
#include "menu_constants.hpp"
#include "menu_system.hpp"
#include "render_text.hpp"
#include "resources.hpp"

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
    render_lines(registry, renderer, *pack);
  }

  render_labels(registry, renderer);

  if (const auto* pack = registry.try_get<comp::button_pack>(menuEntity))
  {
    render_buttons(registry, renderer, *pack);
  }

  if (const auto* group = registry.try_get<comp::button_group>(menuEntity))
  {
    render_button_group(registry, renderer, *group);
  }

  if (const auto* pack = registry.try_get<comp::checkbox_pack>(menuEntity))
  {
    render_checkboxes(registry, renderer, *pack);
  }

  render_title(menu.title, drawable, renderer);

  if (menu.blocking)
  {
    constexpr auto id = 9'999;  // FIXME
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
