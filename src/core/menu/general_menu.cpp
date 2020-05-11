#include "general_menu.h"

#include "action.h"

namespace albinjohansson::wanderer {

GeneralMenu::GeneralMenu(const char* menuJson)
{}

void GeneralMenu::handle_input(const Input& input) noexcept
{
  const auto mx = input.get_mouse_x();
  const auto my = input.get_mouse_y();
  for (const auto& button : buttons) {
  }
}

void GeneralMenu::draw(centurion::video::Renderer& renderer,
                       const Viewport& viewport,
                       const FontBundle& fonts) const
{
  for (const auto& button : buttons) {
    button->draw(renderer, viewport, fonts);
  }
}

void GeneralMenu::set_blocking(bool blocking_) noexcept
{
  blocking = blocking_;
}

void GeneralMenu::set_buttons(
    std::vector<std::unique_ptr<MenuButton>>&& buttons_)
{
  buttons = std::move(buttons_);
}

bool GeneralMenu::is_blocking() const noexcept
{
  return blocking;
}

}  // namespace albinjohansson::wanderer
