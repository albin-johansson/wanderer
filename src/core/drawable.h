#pragma once
#include "renderer.h"
#include "viewport.h"
#include <memory>

namespace albinjohansson::wanderer {

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
   * @param viewport a reference to the viewport that will be used.
   * @since 0.1.0
   */
  virtual void Draw(Renderer& renderer, const Viewport& viewport) const = 0;
};

using IDrawable_uptr = std::unique_ptr<IDrawable>;
using IDrawable_sptr = std::shared_ptr<IDrawable>;
using IDrawable_wptr = std::weak_ptr<IDrawable>;

}