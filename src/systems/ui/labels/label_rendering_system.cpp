#include "label_rendering_system.hpp"

#include "components/ui/associated_menu.hpp"
#include "components/ui/label.hpp"
#include "components/ui/menu.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/render_text.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto GetMenuFont(const TextSize size)
{
  switch (size) {
    default:
      [[fallthrough]];

    case TextSize::Small:
      return glob::menu_font_s;

    case TextSize::Medium:
      return glob::menu_font_m;

    case TextSize::Large:
      return glob::menu_font_l;
  }
}

}  // namespace

void RenderLabels(const entt::registry& registry, GraphicsContext& graphics)
{
  const auto active = registry.ctx<ActiveMenu>().entity;
  auto& renderer = graphics.GetRenderer();

  for (auto&& [entity, label, associated] : registry.view<Label, AssociatedMenu>().each())
  {
    if (active == associated.entity) {
      if (!label.texture) {
        renderer.set_color(label.color);

        const auto& font = renderer.get_font(GetMenuFont(label.size));
        label.texture = RenderText(renderer, label.text, font);
      }

      renderer.render(*label.texture, FromGrid(label.position));
    }
  }
}

}  // namespace wanderer::sys
