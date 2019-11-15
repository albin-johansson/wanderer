#pragma once
#include "rectangle.h"
#include "drawable.h"

namespace wanderer::core {

class MenuButton final : public core::IDrawable {
 private:
  core::Rectangle bounds;

 public:
  MenuButton(float x, float y, float width, float height);

  ~MenuButton() noexcept override;

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const noexcept override;

  bool Contains(float mx, float my) const noexcept;
};

}
