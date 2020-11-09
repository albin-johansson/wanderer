#include "menu.hpp"

#include <cen/cursor.hpp>
#include <entt.hpp>

#include "game_constants.hpp"
#include "maybe.hpp"
#include "menu_constants.hpp"

namespace wanderer {

auto menu::query_buttons(const cen::mouse_state& mouseState)
    -> maybe<menu_action>
{
  static cen::cursor hand{cen::system_cursor::hand};

  maybe<menu_action> action;
  const auto mousePos = cen::cast<cen::fpoint>(mouseState.mouse_pos());
  bool hover{};

  for (auto& button : m_buttons) {
    if (button.contains(mousePos)) {
      hover = true;
      button.set_hover(true);
      if (mouseState.was_left_button_released()) {
        action = button.action();
      }
    } else {
      button.set_hover(false);
    }
  }

  if (hover) {
    hand.enable();
  } else {
    cen::cursor::reset();
  }

  return action;
}

auto menu::query_binds(const cen::key_state& keyState) -> maybe<menu_action>
{
  for (const auto& bind : m_binds) {
    if (keyState.was_just_released(bind.key)) {
      return bind.action;
    }
  }

  return std::nullopt;
}

void menu::load_title_texture(cen::renderer& renderer) const
{
  auto& font = renderer.get_font(g_menuMediumFont);
  renderer.set_color(cen::colors::white);
  m_titleTexture = renderer.render_blended_utf8(m_title.c_str(), font);
}

void menu::render_title(cen::renderer& renderer) const
{
  const auto& texture = m_titleTexture.value();

  if (!m_titlePos) {
    const auto x = (g_logicalWidth<int> / 2) - (texture.width() / 2);
    const auto y = g_menuRowSize * 2;
    m_titlePos = {x, y};
  }

  renderer.render<int>(texture, *m_titlePos);
}

void menu::render(cen::renderer& renderer) const
{
  for (const auto& button : m_buttons) {
    button.render(renderer);
  }

  if (m_title.empty()) {
    return;  // nothing more to do if there is no title
  }

  if (!m_titleTexture) {
    load_title_texture(renderer);
  }

  render_title(renderer);
}

}  // namespace wanderer
