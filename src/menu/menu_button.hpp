#pragma once

#include <cen/point.hpp>
#include <cen/rect.hpp>
#include <cen/renderer.hpp>
#include <cen/texture.hpp>
#include <optional>  // optional
#include <string>    // string

#include "menu_action.hpp"

namespace wanderer {

class menu_button final
{
 public:
  menu_button(menu_action action, std::string text);

  void render(cen::renderer& renderer) const;

  void set_hover(bool hover);

  void set_bounds(const cen::frect& bounds) noexcept;

  [[nodiscard]] auto contains(const cen::fpoint& point) const noexcept -> bool
  {
    return m_bounds.contains(point);
  }

  [[nodiscard]] auto action() const noexcept -> menu_action
  {
    return m_action;
  }

 private:
  menu_action m_action;
  cen::frect m_bounds;
  std::string m_text;

  // The mutables are obtained using renderer during first render iteration
  mutable std::optional<cen::texture> m_texture;
  mutable std::optional<cen::texture> m_hoverTexture;
  mutable std::optional<cen::fpoint> m_textPos;

  bool m_hover{false};

  void render_text(cen::renderer& renderer) const;

  void load_normal_text(cen::renderer& renderer) const;

  void load_hover_text(cen::renderer& renderer) const;
};

}  // namespace wanderer
