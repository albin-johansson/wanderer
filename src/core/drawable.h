#pragma once
#include "renderer.h"

namespace wanderer::core {

/**
 * The IDrawable interface specifies objects that can be drawn using a renderer.
 *
 * @since 0.1.0
 */
class IDrawable {
 protected:
  IDrawable() = default;
 public:
  virtual ~IDrawable() = default;

  /**
   * Draws the object.
   *
   * @param renderer the renderer that will be used.
   * @since 0.1.0
   */
  virtual void Draw(visuals::Renderer& renderer) const noexcept = 0;
};

}