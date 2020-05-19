#include "drawable_text.h"

using namespace centurion;

namespace albinjohansson::wanderer {

DrawableText::DrawableText(std::string text, FPoint position)
    : m_text{text}, m_position{position}
{}

void DrawableText::draw(Renderer& renderer, const FontBundle& fonts) const
{
  if (m_text.empty()) {
    return;
  }

  if (!m_texture || !m_isValid) {
    renderer.set_color(m_color);
    m_texture = renderer.text_blended(m_text.c_str(), get_font(fonts));
    m_isValid = true;
  }

  if (m_texture && m_isValid) {
    renderer.render_f(*m_texture, {m_position.x(), m_position.y()});
  }
}

void DrawableText::set_size(DrawableText::Size size) noexcept
{
  if (m_size != size) {
    m_size = size;
    m_isValid = false;
  }
}

void DrawableText::set_position(FPoint position) noexcept
{
  m_position = position;
}

void DrawableText::set_color(const Color& color) noexcept
{
  if (m_color != color) {
    m_color = color;
    m_isValid = false;
  }
}

const Font& DrawableText::get_font(const FontBundle& fonts) const noexcept
{
  switch (m_size) {
    default:
      [[fallthrough]];
    case Size::Small:
      return fonts.get_font_12();
    case Size::Medium:
      return fonts.get_font_24();
    case Size::Large:
      return fonts.get_font_36();
  }
}

}  // namespace albinjohansson::wanderer
