#include "button_system.hpp"
#include "checkbox.hpp"
#include "checkbox_system.hpp"
#include "grid_system.hpp"
#include "label_system.hpp"
#include "line_system.hpp"
#include "menu.hpp"
#include "menu_constants.hpp"
#include "menu_system.hpp"
#include "render_text.hpp"

namespace wanderer::sys {
namespace {

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
    const auto x = (glob::logical_width<int> / 2) - (texture.width() / 2);
    const auto y = convert_row_to_y(2);
    drawable.position = {x, y};
  }

  renderer.render<int>(texture, *drawable.position);
}

}  // namespace

void render_menu(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view =
      registry
          .view<const comp::active_menu, const comp::menu, const comp::menu_drawable>();
  view.each([&](const entt::entity entity,
                const comp::menu& menu,
                const comp::menu_drawable& drawable) {
    if (menu.blocking)
    {
      renderer.fill_with(glob::transparent_black);
    }

    if (const auto* pack = registry.try_get<comp::line_pack>(entity))
    {
      render_lines(registry, renderer, *pack);
    }

    if (const auto* pack = registry.try_get<comp::label_pack>(entity))
    {
      render_labels(registry, renderer, *pack);
    }

    if (const auto* pack = registry.try_get<comp::button_pack>(entity))
    {
      render_buttons(registry, renderer, *pack);
    }

    if (const auto* pack = registry.try_get<comp::checkbox_pack>(entity))
    {
      render_checkboxes(registry, renderer, *pack);
    }

    render_title(menu.title, drawable, renderer);
  });
}

}  // namespace wanderer::sys
