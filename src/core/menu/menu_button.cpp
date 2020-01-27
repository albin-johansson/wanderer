#include "menu_button.h"
#include "renderer.h"
#include <utility>

using namespace centurion;

namespace albinjohansson::wanderer {

MenuButton::MenuButton(std::string text, float x, float y, float width, float height)
    : text(std::move(text)) {
  bounds.set_x(x);
  bounds.set_y(y);
  bounds.set_width(width);
  bounds.set_height(height);
}

MenuButton::~MenuButton() = default;

void MenuButton::RenderText(const Renderer& renderer,
                            float x,
                            float y,
                            std::unique_ptr<Image>& img,
                            const centurion::Font& font) const {
  if (!img) {
    img = renderer.create_image(text, font);
  }
  renderer.draw_image(*img, x, y);
}

bool MenuButton::Contains(float mx, float my) const noexcept {
  return bounds.contains(mx, my);
}

void MenuButton::draw(Renderer& renderer, const Viewport&, const FontBundle& fonts) const {
  if (!text.empty()) {
    const auto& font = enlarged ? fonts.get_font_36() : fonts.get_font_24();

    const auto width = font.get_string_width(text);
    const auto height = font.get_string_height(text);
    const auto x = bounds.get_center_x() - (width / 2.0f);
    const auto y = bounds.get_center_y() - (height / 2.0f);

    renderer.set_color(0xFF, 0xFF, 0xFF);

    if (enlarged) {
      RenderText(renderer, x, y, enlargedImg, font);
    } else {
      RenderText(renderer, x, y, normalImg, font);
    }
  }
}

void MenuButton::SetEnlarged(bool enlarged) noexcept {
  this->enlarged = enlarged;
}

}
