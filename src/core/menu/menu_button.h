#pragma once
#include "rectangle.h"
#include "drawable.h"

namespace wanderer::core {

/**
 * The MenuButton class is a simple representation of a graphical button.
 *
 * @since 0.1.0
 */
class MenuButton final : public IDrawable {
 private:
  Rectangle bounds;

 public:
  /**
   * @param x the x-coordinate of the button.
   * @param y the y-coordinate of the button.
   * @param width the width of the button.
   * @param height the height of the button.
   * @since 0.1.0
   */
  MenuButton(float x, float y, float width, float height);

  ~MenuButton() noexcept override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override;

  bool Contains(float mx, float my) const noexcept;
};

}
