#include "button_rendering_system.hpp"

#include "components/ui/associated_menu.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/menu.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/render_text.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {
namespace {

constexpr auto button_outline_fg_color = cen::colors::ghost_white;
constexpr auto button_outline_bg_color = button_outline_fg_color.with_alpha(0x22);
constexpr auto button_font = glob::menu_font_m;

void UpdateBounds(const comp::Button& button, cen::frect& bounds, cen::renderer& renderer)
{
  const auto& font = renderer.get_font(button_font);
  const auto [width, height] = font.string_size(button.text).value();

  const auto pos = FromGrid(button.position);
  bounds.set_size({width * 1.25f, height * 1.5f});
  bounds.set_x(pos.x() - (bounds.width() / 2.0f));
  bounds.set_y(pos.y() + ((glob::menu_row_size - bounds.height()) / 2.0f));
}

void InitText(const comp::ButtonDrawable& drawable,
              const std::string& text,
              cen::renderer& renderer)
{
  const auto& font = renderer.get_font(button_font);

  renderer.set_color(cen::colors::white);
  drawable.texture.emplace(RenderText(renderer, text, font));
}

void RenderText(const comp::Button& button,
                const comp::ButtonDrawable& drawable,
                cen::renderer& renderer)
{
  if (button.text.empty()) {
    return;
  }

  if (!drawable.text_pos) {
    const auto& font = renderer.get_font(button_font);
    const auto [width, height] = font.string_size(button.text).value();
    drawable.text_pos = {drawable.bounds.center_x() - (width / 2.0f),
                         drawable.bounds.center_y() - (height / 2.0f)};
  }

  auto& texture = drawable.texture.value();
  texture.set_alpha((button.state & comp::Button::enable_bit) ? 255 : 100);

  renderer.render(texture, *drawable.text_pos);
  texture.set_alpha(255);
}

void RenderOutline(const comp::ButtonDrawable& drawable, cen::renderer& renderer)
{
  renderer.set_color(button_outline_bg_color);
  renderer.fill_rect(drawable.bounds);

  renderer.set_color(button_outline_fg_color);
  renderer.draw_rect(drawable.bounds);
}

void RenderButton(const entt::registry& registry,
                  GraphicsContext& graphics,
                  const entt::entity buttonEntity)
{
  auto& renderer = graphics.GetRenderer();
  const auto& button = registry.get<comp::Button>(buttonEntity);
  const auto& drawable = registry.get<comp::ButtonDrawable>(buttonEntity);

  if (!(button.state & comp::Button::visible_bit)) {
    return;
  }

  if (!drawable.texture) {
    UpdateBounds(button, drawable.bounds, renderer);
    InitText(drawable, button.text, renderer);
  }

  if (button.state & comp::Button::hover_bit && button.state & comp::Button::enable_bit) {
    RenderOutline(drawable, renderer);
  }

  RenderText(button, drawable, renderer);
}

}  // namespace

void RenderButtons(const entt::registry& registry, GraphicsContext& graphics)
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;

  constexpr auto filter = entt::exclude<comp::Checkbox>;
  for (auto&& [entity, button, associated] :
       registry.view<comp::Button, comp::AssociatedMenu>(filter).each())
  {
    if (associated.entity == menuEntity) {
      RenderButton(registry, graphics, entity);
    }
  }
}

void RenderButtonGroupIndicators(const entt::registry& registry,
                                 GraphicsContext& graphics)
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;

  for (auto&& [entity, group, associated] :
       registry.view<comp::ButtonGroup, comp::AssociatedMenu>().each())
  {
    if (associated.entity == menuEntity && group.selected != entt::null) {
      auto& renderer = graphics.GetRenderer();
      const auto& drawable = registry.get<comp::ButtonDrawable>(group.selected);
      renderer.set_color(cen::colors::dark_green);
      renderer.fill_rect(drawable.bounds);
    }
  }
}

}  // namespace wanderer::sys
