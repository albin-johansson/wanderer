#include "menu_button.h"
#include <utility>

namespace albinjohansson::wanderer {

MenuButton::MenuButton(std::string text, float x, float y, float width, float height)
    : text(std::move(text)) {
  bounds.SetX(x);
  bounds.SetY(y);
  bounds.SetWidth(width);
  bounds.SetHeight(height);
}

MenuButton::~MenuButton() = default;

bool MenuButton::Contains(float mx, float my) const noexcept {
  return bounds.Contains(mx, my);
}

void MenuButton::Draw(Renderer& renderer, FontBundle& fonts) const {
  if (!text.empty()) {
    auto& font = enlarged ? fonts.GetFont36() : fonts.GetFont24();

    auto width = font.GetStringWidth(text);
    auto height = font.GetStringHeight(text);
    auto x = bounds.GetCenterX() - (width / 2.0f);
    auto y = bounds.GetCenterY() - (height / 2.0f);

    renderer.SetColor(0xFF, 0xFF, 0xFF);

    if (enlarged) {
      if (enlargedImg == nullptr) {
        enlargedImg = renderer.CreateTexture(text, font);
      }
      renderer.RenderTexture(*enlargedImg, x, y);
    } else {
      if (normalImg == nullptr) {
        normalImg = renderer.CreateTexture(text, font);
      }
      renderer.RenderTexture(*normalImg, x, y);
    }
  }
}

void MenuButton::SetEnlarged(bool enlarged) noexcept {
  this->enlarged = enlarged;
}

}
