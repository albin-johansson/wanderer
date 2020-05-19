#include "menu_impl.h"

#include "action.h"

using namespace centurion;

namespace wanderer {

MenuImpl::MenuImpl() = default;

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
    const auto containsCursor = button->contains(mx, my);
    button->set_enlarged(!leftReleased && containsCursor);
    if (leftReleased && containsCursor) {
      button->trigger();
    }
  }

  for (auto& bind : m_binds) {
    bind->update(input);
  }
}

}  // namespace wanderer