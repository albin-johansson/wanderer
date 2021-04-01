#include "button_system.hpp"

#include "grid_system.hpp"
#include "menu_constants.hpp"
#include "render_text.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto button_font = glob::menu_font_m;

void update_bounds(const comp::button& button,
                   const comp::button_drawable& drawable,
                   cen::renderer& renderer)
{
  auto& bounds = drawable.bounds;

  auto& font = renderer.get_font(button_font);
  const auto [width, height] = font.string_size(button.text);
  bounds.set_size({width * 1.25f, height * 1.75f});

  const auto halfWidth = static_cast<int>(bounds.width()) / 2;
  const auto halfHeight = static_cast<int>(bounds.height()) / 2;

  const auto x = convert_column_to_x(button.col) - halfWidth;
  const auto y = (button.row * glob::menu_row_size) - halfHeight;

  bounds.set_x(static_cast<float>(x));
  bounds.set_y(static_cast<float>(y));
}

void init_text(const comp::button_drawable& drawable,
               const std::string& text,
               cen::renderer& renderer)
{
  const auto& font = renderer.get_font(button_font);

  renderer.set_color(cen::colors::white);
  drawable.texture.emplace(render_text(renderer, text, font));
}

void render_text(const comp::button& button,
                 const comp::button_drawable& drawable,
                 cen::renderer& renderer)
{
  if (button.text.empty())
  {
    return;
  }

  if (!drawable.textPos)
  {
    const auto& font = renderer.get_font(button_font);
    const auto [width, height] = font.string_size(button.text);
    const auto x = drawable.bounds.center_x() - (width / 2.0f);
    const auto y = drawable.bounds.center_y() - (height / 2.0f);
    drawable.textPos = {x, y};
  }

  renderer.render(drawable.texture.value(), *drawable.textPos);
}

void render_background(const comp::button_drawable& drawable, cen::renderer& renderer)
{
  constexpr auto bg = cen::colors::ghost_white.with_alpha(0x22);

  renderer.set_color(bg);
  renderer.fill_rect(drawable.bounds);

  renderer.set_color(cen::colors::ghost_white);
  renderer.draw_rect(drawable.bounds);
}

}  // namespace

void render_buttons(const entt::registry& registry,
                    cen::renderer& renderer,
                    const comp::button_pack& pack)
{
  for (const auto entity : pack.buttons)
  {
    const auto& button = registry.get<comp::button>(entity);
    const auto& drawable = registry.get<comp::button_drawable>(entity);

    if (!drawable.texture)
    {
      update_bounds(button, drawable, renderer);
      init_text(drawable, button.text, renderer);
    }

    if (button.hover)
    {
      render_background(drawable, renderer);
    }

    render_text(button, drawable, renderer);
  }
}

}  // namespace wanderer::sys
