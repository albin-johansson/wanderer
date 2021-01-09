#include "menu_button.hpp"

#include <entt.hpp>
#include <utility>  // move

#include "game_constants.hpp"
#include "menu_constants.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto to_texture(cen::renderer& renderer,
                              const std::string& text,
                              const cen::font& font) -> cen::texture
{
  return renderer.render_blended_utf8(text.c_str(), font);
}

}  // namespace

menu_button::menu_button(const menu_action action,
                         std::string text,
                         const int row,
                         const int col)
    : m_action{action}
    , m_text{std::move(text)}
    , m_row{row}
    , m_col{col}
{}

void menu_button::calculate_bounds(cen::renderer& renderer) const
{
  auto& font = renderer.get_font(g_menuSmallFont);
  const auto [width, height] = font.string_size(m_text.c_str());
  m_bounds.set_size({width * 1.25f, height * 1.75f});

  const auto calcX = [&]() -> int {
    const auto width = static_cast<int>(m_bounds.width());

    // make button centered if column index is -1
    if (m_col == -1) {
      return (glob::logicalWidth<int> / 2) - (width / 2);
    } else {
      return (m_col * g_menuColSize) - (width / 2);
    }
  };

  const auto y =
      static_cast<float>(m_row * g_menuRowSize) - (m_bounds.height() / 2.0f);

  m_bounds.set_x(static_cast<float>(calcX()));
  m_bounds.set_y(y);
}

void menu_button::render_text(cen::renderer& renderer) const
{
  if (m_text.empty()) {
    return;
  }

  if (!m_textPos) {
    const auto& font = renderer.get_font(g_menuSmallFont);
    const auto [width, height] = font.string_size(m_text.c_str());
    const auto x = m_bounds.center_x() - (width / 2.0f);
    const auto y = m_bounds.center_y() - (height / 2.0f);
    m_textPos = {x, y};
  }
  renderer.render(m_texture.value(), *m_textPos);
}

void menu_button::render_background(cen::renderer& renderer) const
{
  constexpr auto bg = cen::colors::ghost_white.with_alpha(0x22);

  renderer.set_color(bg);
  renderer.fill_rect(m_bounds);

  renderer.set_color(cen::colors::ghost_white);
  renderer.draw_rect(m_bounds);
}

void menu_button::load_normal_text(cen::renderer& renderer) const
{
  renderer.set_color(cen::colors::white);
  m_texture.emplace(
      to_texture(renderer, m_text, renderer.get_font(g_menuSmallFont)));
}

void menu_button::render(cen::renderer& renderer) const
{
  if (!m_texture) {
    calculate_bounds(renderer);
    load_normal_text(renderer);
  }

  if (m_hover) {
    render_background(renderer);
  }

  render_text(renderer);
}

void menu_button::set_hover(const bool hover)
{
  m_hover = hover;
}

}  // namespace wanderer
