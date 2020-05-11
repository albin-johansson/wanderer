#pragma once
#include <renderer.h>

#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class IWandererCore;

class HUD final {
 public:
  HUD();

  ~HUD();

  void draw(ctn::Renderer& renderer, IWandererCore& core) const;

 private:
  void draw_health_bar(ctn::Renderer& renderer, IWandererCore& core) const;
};

}  // namespace albinjohansson::wanderer
