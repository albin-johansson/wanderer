#pragma once
#include <renderer.h>

#include "font_bundle.h"
#include "viewport.h"

namespace wanderer {

class IMenuDrawable {
 public:
  virtual ~IMenuDrawable() = default;

  virtual void draw(ctn::Renderer& renderer,
                    const Viewport& viewport,
                    const FontBundle& fonts) const = 0;
};

}  // namespace wanderer
