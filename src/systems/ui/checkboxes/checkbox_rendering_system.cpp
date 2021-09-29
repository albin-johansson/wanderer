#include "checkbox_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "core/graphics/render_text.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

void render_checkbox(const entt::registry& registry,
                     graphics_context& graphics,
                     const entt::entity checkboxEntity,
                     const comp::checkbox& checkbox)
{
  auto& renderer = graphics.get_renderer();
  const auto& drawable = registry.get<comp::button_drawable>(checkboxEntity);

  if (checkbox.checked) {
    renderer.set_color(cen::colors::lime);
    renderer.fill_rect(drawable.bounds);
  }

  renderer.set_color(cen::colors::white);
  renderer.draw_rect(drawable.bounds);

  if (!drawable.texture) {
    const auto& font = renderer.get_font(glob::menu_font_m);
    const auto& button = registry.get<comp::button>(checkboxEntity);

    renderer.set_color(cen::colors::white);
    drawable.texture.emplace(render_text(renderer, button.text, font));
  }

  renderer.render(*drawable.texture, drawable.text_pos.value());
}

}  // namespace

void render_checkboxes(const entt::registry& registry, graphics_context& graphics)
{
  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;

  for (auto&& [entity, checkbox, associated] :
       registry.view<comp::checkbox, comp::associated_menu>().each())
  {
    if (associated.entity == menuEntity) {
      render_checkbox(registry, graphics, entity, checkbox);
    }
  }
}

}  // namespace wanderer::sys
