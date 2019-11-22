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

MenuButton::~MenuButton() {
  if (texture) {
    SDL_DestroyTexture(texture);
  }

  if (enlargedTexture) {
    SDL_DestroyTexture(enlargedTexture);
  }
}

bool MenuButton::Contains(float mx, float my) const noexcept {
  return bounds.Contains(mx, my);
}

void MenuButton::Draw(visuals::Renderer& renderer, visuals::FontBundle& fonts) const {

  if (!text.empty()) {
    auto& font = enlarged ? fonts.GetFont36() : fonts.GetFont24();

    auto width = font.GetStringWidth(text);
    auto height = font.GetStringHeight(text);
    auto x = bounds.GetCenterX() - (width / 2.0f);
    auto y = bounds.GetCenterY() - (height / 2.0f);

    renderer.SetColor(0xFF, 0xFF, 0xFF);

    if (enlarged) {
      if (enlargedTexture == nullptr) {
        enlargedTexture = renderer.CreateTexture(text, font);
      }

      renderer.RenderTexture(enlargedTexture, x, y);
    } else {
      if (texture == nullptr) {
        texture = renderer.CreateTexture(text, font);
      }

      renderer.RenderTexture(texture, x, y);
    }
  }
}

void MenuButton::SetEnlarged(bool enlarged) noexcept {
  this->enlarged = enlarged;
}

}
