#pragma once
#include "world.h"
#include "tickable.h"
#include "drawable.h"
#include "level.h"
#include "entity.h"
#include "tile_map.h"
#include "image_generator.h"
#include "player.h"
#include <vector>

namespace wanderer::core {

class WorldImpl final : public IWorld {
 private:
  std::vector<IEntity_sptr> entities;
  Player_sptr player = nullptr;
  TileMap_uptr tileMap = nullptr;

  void SavePositions();

  void Interpolate(float alpha);

 public:
  explicit WorldImpl(visuals::ImageGenerator& imageGenerator);

  ~WorldImpl() override;

  [[nodiscard]] static IWorld_uptr Create(visuals::ImageGenerator& imageGenerator);

  void PlayerHandleInput(const Input& input, const IGame& game) override;

  void Tick(const IGame& game, float delta) override;

  void Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) override;

  [[nodiscard]] int GetWidth() const noexcept override;

  [[nodiscard]] int GetHeight() const noexcept override;

  [[nodiscard]] float GetPlayerWidth() const noexcept override;

  [[nodiscard]] float GetPlayerHeight() const noexcept override;

  [[nodiscard]] Vector2 GetPlayerPosition() const noexcept override;

  [[nodiscard]] Vector2 GetPlayerInterpolatedPosition() const noexcept override;

  [[nodiscard]] static bool CompareGameObjects(const IGameObject_sptr& first,
                                               const IGameObject_sptr& second) noexcept;

};

}
