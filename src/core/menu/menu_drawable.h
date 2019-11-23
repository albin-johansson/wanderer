#pragma once
#include "renderer.h"
#include "font_bundle.h"

namespace albinjohansson::wanderer {

class IMenuDrawable {
 protected:
  IMenuDrawable() = default;

 public:
  virtual ~IMenuDrawable() = default;

  virtual void Draw(Renderer& renderer, FontBundle& fonts) const = 0;
};

}