#include "new_menu.h"

#include <action.h>

#include <fstream>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;
using namespace centurion;

namespace albinjohansson::wanderer {

inline MenuID menu_from_action(const std::string& action)
{
  if (action == "GotoHome") {
    return MenuID::Home;
  } else if (action == "GotoSettings") {
    return MenuID::Settings;
  } else if (action == "GotoControls") {
    return MenuID::Controls;
  } else if (action == "GotoSettings") {
    return MenuID::Settings;
  } else if (action == "GotoInGame") {
    return MenuID::InGame;
  } else if (action == "GotoInventory") {
    return MenuID::Inventory;
  } else {
    throw std::logic_error{"Failed to deduce menu associated with action!"};
  }

  // FIXME add MenuID::Credits
}

NewMenu::NewMenu(weak<IMenuStateMachine> menuStateMachine, const char* jsonFile)
{
  std::ifstream stream{jsonFile};
  json json;
  stream >> json;

  const auto title = json.at("title").get<std::string>();
  m_blocking = json.at("isBlocking").get<bool>();

  int i = 0;
  for (auto& [key, value] : json.at("buttons").items()) {
    const auto text = value.at("text").get<std::string>();
    const auto actionID = value.at("action").get<std::string>();

    const auto menuID = menu_from_action(actionID);
    auto action = std::make_unique<GotoMenuAction>(menuStateMachine, menuID);

    const auto x = 200.0f;
    const auto y = 200.0f + static_cast<float>(i * 150);

    auto button = std::make_unique<MenuButton>(
        text, ctn::FRect{x, y, 200, 50}, std::move(action));

    m_buttons.push_back(std::move(button));
    ++i;
  }
}

void NewMenu::draw(Renderer& renderer,
                   const Viewport& viewport,
                   const FontBundle& fonts) const noexcept
{
  if (m_blocking) {
    const auto& bounds = viewport.get_bounds();
    renderer.set_color({0, 0, 0, 0xAA});
    renderer.fill_rect_f(
        {-1.0f, -1.0f, bounds.width() + 1, bounds.height() + 1});
  }

  for (const auto& button : m_buttons) {
    button->draw(renderer, viewport, fonts);
  }
}

void NewMenu::handle_input(const Input& input) noexcept
{
  const auto mx = input.get_mouse_x();
  const auto my = input.get_mouse_y();
  const auto leftReleased = input.was_left_button_released();

  for (auto& button : m_buttons) {
    button->set_enlarged(!leftReleased && button->contains(mx, my));
  }

  for (auto& button : m_buttons) {
    if (leftReleased && button->contains(mx, my)) {
      button->trigger();  // TODO how will this be implemented?
    }
  }
}

bool NewMenu::is_blocking() const noexcept
{
  return m_blocking;
}

}  // namespace albinjohansson::wanderer