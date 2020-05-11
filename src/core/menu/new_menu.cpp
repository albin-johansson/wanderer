#include "new_menu.h"

#include <action.h>

#include <fstream>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;
using namespace centurion::video;

namespace albinjohansson::wanderer {

inline MenuID menu_from_action(ActionID id)
{
  switch (id) {  // NOLINT
    case ActionID::GotoHome:
      return MenuID::Home;
    case ActionID::GotoSettings:
      return MenuID::Settings;
    case ActionID::GotoControls:
      return MenuID::Controls;
    case ActionID::GotoInGame:
      return MenuID::InGame;
    case ActionID::GotoCredits:
      return MenuID::Home;  // FIXME add MenuID::Credits
    case ActionID::GotoInventory:
      return MenuID::Inventory;
    default:
      throw std::logic_error{"Failed to deduce menu associated with action!"};
  }
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
    const auto actionID = to_action(value.at("action").get<std::string>());

    const auto menuID = menu_from_action(actionID);
    auto action = std::make_unique<GotoMenuAction>(menuStateMachine, menuID);

    const auto x = 200.0f;
    const auto y = 200.0f + static_cast<float>(i * 150);

    auto button = std::make_unique<MenuButton>(
        text, centurion::math::FRect{x, y, 200, 50}, std::move(action));

    m_buttons.push_back(std::move(button));
    ++i;
  }
}

void NewMenu::draw(Renderer& renderer,
                   const Viewport& viewport,
                   const FontBundle& fonts) const noexcept
{}

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

bool NewMenu::blocking() const noexcept
{
  return m_blocking;
}

}  // namespace albinjohansson::wanderer