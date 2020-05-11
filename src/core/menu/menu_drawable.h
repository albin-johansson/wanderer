#pragma once
#include <renderer.h>

#include "font_bundle.h"
#include "viewport.h"

namespace albinjohansson::wanderer {

class IMenuDrawable {
 protected:
  IMenuDrawable() = default;

 public:
  virtual ~IMenuDrawable() = default;

  virtual void draw(ctn::Renderer& renderer,
                    const Viewport& viewport,
                    const FontBundle& fonts) const = 0;
};

}  // namespace albinjohansson::wanderer
