#include "menu_button.hpp"

#include <entt.hpp>
#include <utility>  // move

namespace wanderer {
namespace {

inline constexpr auto fontID = "typewriter_s"_hs;

[[nodiscard]] auto to_texture(cen::renderer& renderer, const std::string& text)
    -> cen::texture
{
  const auto& font = renderer.get_font(fontID);
  return renderer.render_blended_utf8(text.c_str(), font);
}

}  // namespace

menu_button::menu_button(menu_action action, std::string text)
    : m_action{action},
      m_text{std::move(text)}
{}

void menu_button::render_text(cen::renderer& renderer) const
{
  if (!m_textPos) {
    const auto& font = renderer.get_font(fontID);
    const auto [width, height] = font.string_size(m_text.c_str());
    const auto x = m_bounds.center_x() - (width / 2.0f);
    const auto y = m_bounds.center_y() - (height / 2.0f);
    m_textPos = {x, y};
  }
  renderer.render(m_hover ? m_hoverTexture.value() : m_texture.value(),
                  *m_textPos);
}

void menu_button::load_normal_text(cen::renderer& renderer) const
{
  renderer.set_color(cen::colors::white);
  m_texture.emplace(to_texture(renderer, m_text));
}

void menu_button::load_hover_text(cen::renderer& renderer) const
{
  renderer.set_color(cen::colors::white);

  auto& font = renderer.get_font(fontID);
  font.set_bold(true);

  m_hoverTexture.emplace(to_texture(renderer, m_text));

  font.set_bold(false);
}

void menu_button::render(cen::renderer& renderer) const
{
  if (!m_texture) {
    load_normal_text(renderer);
  }

  if (!m_hoverTexture) {
    load_hover_text(renderer);
  }

  renderer.set_color(cen::colors::red);
  renderer.draw_rect(m_bounds);

  render_text(renderer);
}

void menu_button::set_hover(bool hover)
{
  m_hover = hover;
}

void menu_button::set_bounds(const cen::frect& bounds) noexcept
{
  m_bounds = bounds;
}

}  // namespace wanderer
