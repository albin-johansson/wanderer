#pragma once
#include "renderer.h"

namespace albinjohansson::wanderer {

class IWandererCore;

class HUD final {
 private:
  void draw_health_bar(centurion::Renderer& renderer, IWandererCore& core) const;

 public:
  HUD();

  ~HUD();

  void draw(centurion::Renderer& renderer, IWandererCore& core) const;
};

}
