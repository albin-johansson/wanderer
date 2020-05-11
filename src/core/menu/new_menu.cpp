#include "new_menu.h"

#include <action.h>

#include <fstream>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;
using namespace centurion::video;

namespace albinjohansson::wanderer {

NewMenu::NewMenu(const char* jsonFile)
{
  std::ifstream stream{jsonFile};
  json json;
  stream >> json;

  const auto title = json.at("title").get<std::string>();
  m_blocking = json.at("isBlocking").get<bool>();

  int i = 0;
  for (auto& [key, value] : json.at("buttons").items()) {
    const auto text = value.at("text").get<std::string>();
    const auto action = value.at("action").get<std::string>();
    const auto actionID = to_action(action);

    auto button =
        std::make_unique<MenuButton>(text, 200, 200 + (i * 150), 200, 50);

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