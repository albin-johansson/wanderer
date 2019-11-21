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
  Player_uptr player = nullptr;
  IEntity_uptr skeleton = nullptr;

  void SavePositions();

  void Interpolate(float alpha);

 public:
  explicit WorldImpl(visuals::ImageGenerator& imageGenerator);

  ~WorldImpl() override;

  static IWorld_uptr Create(visuals::ImageGenerator& imageGenerator);

  void PlayerHandleInput(const Input& input, const IGame& game) override;

  void Tick(const IGame& game, float delta) override;

  void Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) override;

  int GetWidth() const noexcept override;

  int GetHeight() const noexcept override;

  float GetPlayerWidth() const noexcept override;

  float GetPlayerHeight() const noexcept override;

  Vector2 GetPlayerPosition() const noexcept override;

  Vector2 GetPlayerInterpolatedPosition() const noexcept override;
};

}
