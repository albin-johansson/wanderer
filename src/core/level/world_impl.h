#pragma once
#include "world.h"
#include "tickable.h"
#include "drawable.h"
#include "level.h"
#include "entity.h"
#include "tile_map.h"
#include "image_generator.h"
#include "player.h"

namespace wanderer::core {

class WorldImpl final : public IWorld {
 private:
  TileMap_uptr tileMap = nullptr;
  Player_sptr player = nullptr;

  void SavePositions();

  void Interpolate(float alpha);

 public:
  WorldImpl(visuals::ImageGenerator& imageGenerator, Player_sptr player);

  ~WorldImpl() override;

  static IWorld_uptr Create(visuals::ImageGenerator& imageGenerator, Player_sptr player);

  void Tick(const IGame& game, float delta) override;

  void Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) override;

  [[nodiscard]] int GetWidth() const noexcept override;

  [[nodiscard]] int GetHeight() const noexcept override;

};

}
