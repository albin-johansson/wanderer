#pragma once
#include "renderer.h"
#include "viewport.h"
#include "font_bundle.h"

namespace albinjohansson::wanderer {

class IMenuDrawable {
 protected:
  IMenuDrawable() = default;

 public:
  virtual ~IMenuDrawable() = default;

  virtual void Draw(Renderer& renderer, const Viewport& viewport, FontBundle& fonts) const = 0;
};

}
