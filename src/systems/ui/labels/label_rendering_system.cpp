#include "label_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/label.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/render_text.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

[[nodiscard]] auto menu_font(const text_size size)
{
  switch (size)
  {
    default:
      [[fallthrough]];

    case text_size::small:
      return glob::menu_font_s;

    case text_size::medium:
      return glob::menu_font_m;

    case text_size::large:
      return glob::menu_font_l;
  }
}

void render_labels(const entt::registry& registry, graphics_context& graphics)
{
  const auto active = registry.ctx<const ctx::active_menu>().entity;
  auto& renderer = graphics.renderer();

  for (auto&& [entity, label, associated] :
       registry.view<const comp::label, const comp::associated_menu>().each())
  {
    if (active.get() == associated.entity)
    {
      if (!label.texture)
      {
        renderer.set_color(label.color);

        const auto& font = renderer.get_font(menu_font(label.size));
        label.texture = render_text(renderer, label.text, font);
      }

      renderer.render(*label.texture, from_grid(label.position));
    }
  }
}

}  // namespace wanderer::sys
