#pragma once
#include <renderer.h>

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class IMenuDrawable {
 public:
  virtual ~IMenuDrawable() = default;

  virtual void draw(ctn::Renderer& renderer,
                    const Viewport& viewport) const = 0;
};

}  // namespace wanderer
