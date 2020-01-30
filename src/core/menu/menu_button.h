#pragma once
#include <memory>
#include <string>
#include <image.h>
#include <rectangle.h>
#include "wanderer_stdinc.h"
#include "menu_drawable.h"

namespace albinjohansson::wanderer {

/**
 * The MenuButton class is a simple representation of a graphical button.
 *
 * @since 0.1.0
 */
class MenuButton final : public IMenuDrawable {
 private:
  centurion::FRect bounds;
  mutable unique<centurion::Image> normalImg = nullptr;
  mutable unique<centurion::Image> enlargedImg = nullptr;
  const std::string text = "";
  bool enlarged = false;

  void render_text(const centurion::Renderer& renderer,
                   float x,
                   float y,
                   unique<centurion::Image>& img,
                   const centurion::Font& font) const;

 public:
  /**
   * @param text the text of the button.
   * @param x the x-coordinate of the button.
   * @param y the y-coordinate of the button.
   * @param width the width of the button.
   * @param height the height of the button.
   * @since 0.1.0
   */
  MenuButton(std::string text, float x, float y, float width, float height);

  ~MenuButton() override;

  void draw(centurion::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void set_enlarged(bool enlarged) noexcept;

  [[nodiscard]]
  bool contains(float mx, float my) const noexcept;
};

}
