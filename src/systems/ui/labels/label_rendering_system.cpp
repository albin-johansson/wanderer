#include "label_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/label.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/render_text.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto menu_font(const text_size size)
{
  switch (size) {
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

}  // namespace

void RenderLabels(const entt::registry& registry, GraphicsContext& graphics)
{
  const auto active = registry.ctx<ctx::ActiveMenu>().entity;
  auto& renderer = graphics.get_renderer();

  for (auto&& [entity, label, associated] :
       registry.view<comp::Label, comp::AssociatedMenu>().each())
  {
    if (active == associated.entity) {
      if (!label.texture) {
        renderer.set_color(label.color);

        const auto& font = renderer.get_font(menu_font(label.size));
        label.texture = RenderText(renderer, label.text, font);
      }

      renderer.render(*label.texture, FromGrid(label.position));
    }
  }
}

}  // namespace wanderer::sys
