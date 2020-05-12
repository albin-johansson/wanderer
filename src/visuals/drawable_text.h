#pragma once
#include <color.h>
#include <point.h>
#include <renderer.h>

#include "menu_drawable.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class DrawableText {
 public:
  enum class Size { Small, Medium, Large };

  DrawableText(std::string text, ctn::FPoint position);

  ~DrawableText() noexcept = default;

  void draw(ctn::Renderer& renderer, const FontBundle& fonts) const;

  void set_size(Size size) noexcept;

  void set_position(ctn::FPoint position) noexcept;

  void set_color(const ctn::Color& color) noexcept;

  [[nodiscard]] Size size() const noexcept
  {
    return m_size;
  }

  [[nodiscard]] ctn::FPoint position() const noexcept
  {
    return m_position;
  }

  [[nodiscard]] const std::string& text() const noexcept
  {
    return m_text;
  }

  [[nodiscard]] const ctn::Color& color() const noexcept
  {
    return m_color;
  }

 private:
  mutable Unique<ctn::Texture> m_texture = nullptr;
  std::string m_text = "";
  ctn::FPoint m_position = {0, 0};
  ctn::Color m_color = ctn::white;
  Size m_size = Size::Medium;
  mutable bool m_isValid = false;

  const ctn::Font& get_font(const FontBundle& fonts) const noexcept;
};

}  // namespace albinjohansson::wanderer
