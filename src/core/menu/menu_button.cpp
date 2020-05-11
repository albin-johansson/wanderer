#include "menu_button.h"

#include <colors.h>

#include <utility>

#include "renderer.h"

using namespace centurion;
using namespace centurion::video;
using namespace centurion::math;

namespace albinjohansson::wanderer {

MenuButton::MenuButton(std::string text, FRect bounds, unique<IAction> action)
    : m_bounds{bounds}, m_action{std::move(action)}, m_text{std::move(text)}
{}

MenuButton::~MenuButton() = default;

void MenuButton::render_text(const Renderer& renderer,
                             float x,
                             float y,
                             std::unique_ptr<Image>& img,
                             const Font& font) const
{
  if (!img) {
    img = renderer.create_image(m_text, font);
  }
  renderer.render_f(*img, {x, y});
}

bool MenuButton::contains(float mx, float my) const noexcept
{
  return m_bounds.contains(mx, my);
}

void MenuButton::draw(Renderer& renderer,
                      const Viewport&,
                      const FontBundle& fonts) const
{
  if (!m_text.empty()) {
    // FIXME this render method is very inefficient

    const auto& font = m_enlarged ? fonts.get_font_36() : fonts.get_font_24();

    const auto width = static_cast<float>(font.get_string_width(m_text));
    const auto height = static_cast<float>(font.get_string_height(m_text));
    const auto x = m_bounds.get_center_x() - (width / 2.0f);
    const auto y = m_bounds.get_center_y() - (height / 2.0f);

    renderer.set_color(white);

    if (m_enlarged) {
      render_text(renderer, x, y, m_enlargedImg, font);
    } else {
      render_text(renderer, x, y, m_normalImg, font);
    }
  }
}

void MenuButton::trigger() noexcept
{
  m_action->execute();
}

void MenuButton::set_enlarged(bool enlarged) noexcept
{
  this->m_enlarged = enlarged;
}

}  // namespace albinjohansson::wanderer
