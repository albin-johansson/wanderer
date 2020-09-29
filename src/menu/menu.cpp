#include "menu.hpp"

#include <cen/cursor.hpp>

namespace wanderer {

auto menu::query_buttons(const cen::mouse_state& mouseState)
    -> std::optional<menu_action>
{
  static cen::cursor hand{cen::system_cursor::hand};

  std::optional<menu_action> action;
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

auto menu::query_binds(const cen::key_state& keyState)
    -> std::optional<menu_action>
{
  for (const auto& bind : m_binds) {
    if (bind.trigger == key_trigger::on_released) {
      if (keyState.was_just_released(bind.key)) {
        return bind.action;
      }
    } else {
      if (keyState.was_just_pressed(bind.key)) {
        return bind.action;
      }
    }
  }

  return std::nullopt;
}

void menu::render(cen::renderer& renderer) const
{
  for (const auto& button : m_buttons) {
    button.render(renderer);
  }
}

}  // namespace wanderer
