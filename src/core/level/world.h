#pragma once
#include "tickable.h"
#include "drawable.h"
#include "level.h"
#include "entity.h"
#include "tile_map.h"
#include "image_generator.h"

namespace wanderer::core {

class World;

using World_uptr = std::unique_ptr<World>;
using World_sptr = std::shared_ptr<World>;
using World_wptr = std::weak_ptr<World>;

class World final : public ITickable {
 private:
  visuals::ImageGenerator_sptr imageGenerator = nullptr;
  IEntity_sptr player = nullptr;
  TileMap_uptr tileMap = nullptr;

  void SavePositions();

  void Interpolate(float alpha);

 public:
  World(visuals::ImageGenerator_sptr imageGenerator, IEntity_sptr player);

  ~World() override;

  static World_uptr Create(visuals::ImageGenerator_sptr imageGenerator, IEntity_sptr player);

  void Tick(float delta) override;

  void Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha);

  [[nodiscard]] int GetWidth() const noexcept;

  [[nodiscard]] int GetHeight() const noexcept;
};

}
