#include "menu_button.h"

namespace wanderer::core {

MenuButton::MenuButton(float x, float y, float width, float height) {
  bounds.SetY(x);
  bounds.SetY(y);
  bounds.SetWidth(width);
  bounds.SetHeight(height);
}

MenuButton::~MenuButton() noexcept = default;

bool MenuButton::Contains(float mx, float my) const noexcept {
  return bounds.Contains(mx, my);
}

void MenuButton::Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const noexcept {
  renderer.SetColor(0xCC, 0xCC, 0xCC);
  renderer.RenderFillRect(bounds.GetX(), bounds.GetY(), bounds.GetWidth(), bounds.GetHeight());
}

}
