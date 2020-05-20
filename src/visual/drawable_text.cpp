#include "drawable_text.h"

using namespace centurion;

namespace wanderer {

DrawableText::DrawableText(std::string text, FPoint position)
    : m_text{text}, m_position{position}
{}

void DrawableText::draw(Renderer& renderer) const
{
  if (m_text.empty()) {
    return;
  }

  SharedPtr<Font> font = nullptr;
  switch (m_size) {
    default:
      [[fallthrough]];
    case Size::Small:
      font = renderer.font("tp-sm");
      break;
    case Size::Medium:
      font = renderer.font("tp-md");
      break;
    case Size::Large:
      font = renderer.font("tp-lg");
      break;
  }

  if ((!m_texture || !m_isValid) && font) {
    renderer.set_color(m_color);
    m_texture = renderer.text_blended(m_text.c_str(), *font);
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

}  // namespace wanderer
