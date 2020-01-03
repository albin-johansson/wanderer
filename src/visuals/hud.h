#pragma once

namespace albinjohansson::wanderer {

class Renderer;
class IWandererCore;

class HUD final {
 private:
  void DrawHealthBar(Renderer& renderer, IWandererCore& core) const;

 public:
  HUD();

  ~HUD();

  void Draw(Renderer& renderer, IWandererCore& core) const;
};

}
