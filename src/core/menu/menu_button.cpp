#include "menu_button.h"

using namespace centurion;

namespace albinjohansson::wanderer {

MenuButton::MenuButton(std::string text, FRect bounds, Unique<IAction> action)
    : m_bounds{bounds},
      m_action{std::move(action)},
      m_text{std::make_unique<DrawableText>(text, FPoint{0, 0})}
{
  m_text->set_color(white);
}

MenuButton::~MenuButton() = default;

bool MenuButton::contains(float mx, float my) const noexcept
{
  return m_bounds.contains(mx, my);
}

void MenuButton::draw(Renderer& renderer,
                      const Viewport&,
                      const FontBundle& fonts) const
{
  if (m_enlarged) {
    m_text->set_size(DrawableText::Size::Large);
  } else {
    m_text->set_size(DrawableText::Size::Medium);
  }

  const auto& font = m_enlarged ? fonts.get_font_36() : fonts.get_font_24();

  const auto width = static_cast<float>(font.string_width(m_text->text()));
  const auto height = static_cast<float>(font.string_height(m_text->text()));

  const auto x = m_bounds.center_x() - (width / 2.0f);
  const auto y = m_bounds.center_y() - (height / 2.0f);

  m_text->set_position({x, y});
  m_text->draw(renderer, fonts);
}

void MenuButton::trigger() noexcept
{
  if (m_action) {
    m_action->execute();
  }
}

void MenuButton::set_enlarged(bool enlarged) noexcept
{
  this->m_enlarged = enlarged;
}

}  // namespace albinjohansson::wanderer
