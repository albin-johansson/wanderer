#pragma once
#include "viewport.h"
#include "font_bundle.h"

namespace centurion {

class Renderer;

}

namespace albinjohansson::wanderer {

class IMenuDrawable {
 protected:
  IMenuDrawable() = default;

 public:
  virtual ~IMenuDrawable() = default;

  virtual void draw(centurion::Renderer& renderer,
                    const Viewport& viewport,
                    const FontBundle& fonts) const = 0;
};

}
