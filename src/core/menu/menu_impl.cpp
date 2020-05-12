#include "menu_impl.h"

#include <fstream>
#include <iostream>
#include <json.hpp>

#include "action.h"
#include "goto_menu_action.h"

using json = nlohmann::json;
using namespace centurion;

namespace albinjohansson::wanderer {

MenuImpl::MenuImpl(ActionParser& actionParser, const char* jsonFile)
{
  // TODO create MenuParser that does the dirty work of this ctor
  std::ifstream stream{jsonFile};
  json json;
  stream >> json;

  m_title = json.at("title").get<std::string>();
  m_blocking = json.at("isBlocking").get<bool>();

  int i = 0;
  for (const auto& [key, value] : json.at("buttons").items()) {
    const auto text = value.at("text").get<std::string>();

    auto action = actionParser.parse(value.at("action"));
    const auto x = 200.0f;
    const auto y = 200.0f + static_cast<float>(i * 70);

    m_buttons.emplace_back(std::make_unique<MenuButton>(
        text, FRect{x, y, 200, 50}, std::move(action)));
    ++i;
  }

  // TODO load custom menu binds

  //  i = 0;
  //  for (auto& [key, value] : json.at("binds").items()) {
  //    const auto btn = value.at("key").get<std::string>();
  //  }
}

void MenuImpl::draw(Renderer& renderer,
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

void MenuImpl::handle_input(const Input& input) noexcept
{
  const auto mx = input.get_mouse_x();
  const auto my = input.get_mouse_y();
  const auto leftReleased = input.was_left_button_released();

  for (auto& button : m_buttons) {
    button->set_enlarged(!leftReleased && button->contains(mx, my));
  }

  for (auto& button : m_buttons) {
    if (leftReleased && button->contains(mx, my)) {
      button->trigger();
    }
  }
}

}  // namespace albinjohansson::wanderer