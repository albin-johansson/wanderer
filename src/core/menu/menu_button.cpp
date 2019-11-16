#include "menu_button.h"
#include <utility>

namespace wanderer::core {

MenuButton::MenuButton(std::string text, float x, float y, float width, float height)
    : text(std::move(text)) {
  bounds.SetX(x);
  bounds.SetY(y);
  bounds.SetWidth(width);
  bounds.SetHeight(height);
}

MenuButton::~MenuButton() noexcept = default;

bool MenuButton::Contains(float mx, float my) const noexcept {
  return bounds.Contains(mx, my);
}

void MenuButton::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  renderer.SetColor(0, 0xFF, 0);
  renderer.RenderFillRect(bounds.GetX(), bounds.GetY(), bounds.GetWidth(), bounds.GetHeight());

  auto font = renderer.GetFont();
  if (!text.empty() && font != nullptr) {
    auto width = font->GetStringWidth(text);
    auto height = font->GetStringHeight(text);
    auto x = bounds.GetCenterX() - (width / 2.0f);
    auto y = bounds.GetCenterY() - (height / 2.0f);

    if (texture == nullptr) {
      renderer.SetColor(0xFF, 0, 0);
      renderer.RenderText(text, x, y);
    } else {
      renderer.RenderTexture(texture, x, y);
    }
  }
}

void MenuButton::LoadTexture(const visuals::Renderer& renderer) {
  texture = renderer.CreateTexture(text);
}

}
