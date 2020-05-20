#include "menu_button.h"

using namespace centurion;

namespace wanderer {

MenuButton::MenuButton(std::string text,
                       FRect bounds,
                       UniquePtr<IAction> action)
    : m_bounds{bounds},
      m_action{std::move(action)},
      m_text{std::make_unique<DrawableText>(text, FPoint{0, 0})}
{
  m_text->set_color(color::white);
}

MenuButton::~MenuButton() = default;

bool MenuButton::contains(float mx, float my) const noexcept
{
  return m_bounds.contains(mx, my);
}

void MenuButton::draw(Renderer& renderer, const Viewport&) const
{
  if (m_enlarged) {
    m_text->set_size(DrawableText::Size::Large);
  } else {
    m_text->set_size(DrawableText::Size::Medium);
  }

  // FIXME these calculations do not need to be repeated if the chosen font is
  //  the same

  auto font = m_enlarged ? renderer.font("tp-lg") : renderer.font("tp-md");
  if (font) {
    const auto width = static_cast<float>(font->string_width(m_text->text()));
    const auto height = static_cast<float>(font->string_height(m_text->text()));

    const auto x = m_bounds.center_x() - (width / 2.0f);
    const auto y = m_bounds.center_y() - (height / 2.0f);

    m_text->set_position({x, y});
    m_text->draw(renderer);
  }
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

}  // namespace wanderer
