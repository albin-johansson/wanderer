#include "label_rendering_system.hpp"

#include "menu_constants.hpp"
#include "render_text.hpp"

namespace wanderer::sys {

void render_labels(const entt::registry& registry,
                   cen::renderer& renderer,
                   const comp::label_pack& pack)
{
  const auto& font = renderer.get_font(glob::menu_font_s);

  for (const auto entity : pack.labels)
  {
    const auto& label = registry.get<comp::label>(entity);

    if (!label.texture)
    {
      renderer.set_color(label.color);
      label.texture = render_text(renderer, label.text, font);
    }

    renderer.render(*label.texture, label.position);
  }
}

}  // namespace wanderer::sys
