#include "core/render_text.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/checkboxes/checkbox_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void render_checkboxes(const entt::registry& registry,
                       cen::renderer& renderer,
                       const comp::checkbox_pack& pack)
{
  for (const auto entity : pack.checkboxes)
  {
    const auto& button = registry.get<comp::button>(entity);
    const auto& checkbox = registry.get<comp::checkbox>(entity);
    const auto& drawable = registry.get<comp::button_drawable>(entity);

    if (checkbox.checked)
    {
      renderer.set_color(cen::colors::lime);
      renderer.fill_rect(drawable.bounds);
    }

    renderer.set_color(cen::colors::white);
    renderer.draw_rect(drawable.bounds);

    if (!drawable.texture)
    {
      const auto& font = renderer.get_font(glob::menu_font_m);

      renderer.set_color(cen::colors::white);
      drawable.texture.emplace(render_text(renderer, button.text, font));
    }

    renderer.render(*drawable.texture, drawable.textPos.value());
  }
}

}  // namespace wanderer::sys
