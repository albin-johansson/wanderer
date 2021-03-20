#include "checkbox_rendering_system.hpp"

#include "button_system.hpp"
#include "grid_system.hpp"
#include "render_text.hpp"

namespace wanderer::sys {

void render_checkboxes(const entt::registry& registry,
                       cen::renderer& renderer,
                       const comp::checkbox_pack& pack)
{
  for (const auto entity : pack.checkboxes)
  {
    const auto& button = registry.get<comp::button>(entity);
    const auto& checkbox = registry.get<comp::checkbox>(entity);

    const auto x = convert_column_to_x(button.col);
    const auto y = convert_row_to_y(button.row);

    const cen::irect rect{x, y, 10, 10};

    if (checkbox.checked)
    {
      renderer.set_color(cen::colors::lime);
      renderer.fill_rect(rect);
    }

    renderer.set_color(cen::colors::white);
    renderer.draw_rect(rect);

    const auto& drawable = registry.get<comp::button_drawable>(entity);
    if (!drawable.texture)
    {
      drawable.bounds = cen::cast<cen::frect>(rect);

      const auto& font = renderer.get_font(glob::menu_font_m);

      renderer.set_color(cen::colors::white);
      drawable.texture.emplace(render_text(renderer, button.text, font));
    }

    renderer.render<int>(*drawable.texture, {x + 14, y - 2});
  }
}

}  // namespace wanderer::sys
