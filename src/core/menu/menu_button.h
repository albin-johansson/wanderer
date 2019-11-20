#pragma once
#include "rectangle.h"
#include "drawable.h"
#include <string>
#include <SDL_render.h>

namespace wanderer::core {

/**
 * The MenuButton class is a simple representation of a graphical button.
 *
 * @since 0.1.0
 */
class MenuButton final : public IDrawable {
 private:
  Rectangle bounds;
  const std::string text;
  SDL_Texture* texture = nullptr;

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

  ~MenuButton() noexcept override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

  void LoadTexture(const visuals::Renderer& renderer);

  bool Contains(float mx, float my) const noexcept;
};

}
