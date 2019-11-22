#pragma once
#include "renderer.h"
#include "font_bundle.h"

namespace wanderer::core {

class IMenuDrawable {
 protected:
  IMenuDrawable() = default;

 public:
  virtual ~IMenuDrawable() = default;

  virtual void Draw(visuals::Renderer& renderer, visuals::FontBundle& fonts) const = 0;
};

}
