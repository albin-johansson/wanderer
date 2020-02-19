#pragma once
#include "renderer.h"

namespace albinjohansson::wanderer {

class IWandererCore;

class HUD final {
 private:
  void draw_health_bar(centurion::video::Renderer& renderer,
                       IWandererCore& core) const;

 public:
  HUD();

  ~HUD();

  void draw(centurion::video::Renderer& renderer, IWandererCore& core) const;
};

}  // namespace albinjohansson::wanderer
