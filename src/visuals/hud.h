#pragma once

namespace centurion {

class Renderer;

}

namespace albinjohansson::wanderer {

class IWandererCore;

class HUD final {
 private:
  void DrawHealthBar(centurion::Renderer& renderer, IWandererCore& core) const;

 public:
  HUD();

  ~HUD();

  void Draw(centurion::Renderer& renderer, IWandererCore& core) const;
};

}
