#include "menu_button.h"

#include <colors.h>

#include <utility>

#include "renderer.h"

using namespace centurion;
using namespace centurion::video;

namespace albinjohansson::wanderer {

MenuButton::MenuButton(
    std::string text, float x, float y, float width, float height)
    : text(std::move(text))
{
  bounds.set_x(x);
  bounds.set_y(y);
  bounds.set_width(width);
  bounds.set_height(height);
}

MenuButton::~MenuButton() = default;

void MenuButton::render_text(const Renderer& renderer,
                             float x,
                             float y,
                             std::unique_ptr<Image>& img,
                             const Font& font) const
{
  if (!img) {
    img = renderer.create_image(text, font);
  }
  renderer.render_f(*img, {x, y});
}

bool MenuButton::contains(float mx, float my) const noexcept
{
  return bounds.contains(mx, my);
}

void MenuButton::draw(Renderer& renderer,
                      const Viewport&,
                      const FontBundle& fonts) const
{
  if (!text.empty()) {
    const auto& font = enlarged ? fonts.get_font_36() : fonts.get_font_24();

    const auto width = static_cast<float>(font.get_string_width(text));
    const auto height = static_cast<float>(font.get_string_height(text));
    const auto x = bounds.get_center_x() - (width / 2.0f);
    const auto y = bounds.get_center_y() - (height / 2.0f);

    renderer.set_color(white);

    if (enlarged) {
      render_text(renderer, x, y, enlargedImg, font);
    } else {
      render_text(renderer, x, y, normalImg, font);
    }
  }
}

void MenuButton::set_enlarged(bool enlarged) noexcept
{
  this->enlarged = enlarged;
}

}  // namespace albinjohansson::wanderer
