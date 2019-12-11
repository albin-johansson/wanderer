#pragma once
#include "game_object.h"
#include "tile_id.h"
#include "tile.h"
#include "vector_2.h"
#include "render_depth.h"
#include <memory>
#include <vector>
#include <utility>

namespace albinjohansson::wanderer {

class TileSet;

class TileObject final : public IGameObject { // TODO rename to StaticTileObject?
 private:
  std::shared_ptr<TileSet> tileSet = nullptr;
  Vector2 position;
  const TileID id;
  int depth = RenderDepth::MAX;
  float centerY = 0;

 public:
  TileObject(TileID id, const Vector2& position, std::shared_ptr<TileSet> tileSet);

  ~TileObject() noexcept override;

  void Tick(IWandererCore& core, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void SetDepth(int depth) noexcept;

  [[nodiscard]] float GetX() const noexcept override;

  [[nodiscard]] float GetY() const noexcept override;

  [[nodiscard]] float GetCenterY() const noexcept override;

  [[nodiscard]] int GetDepth() const noexcept override;

  [[nodiscard]] float GetWidth() const noexcept override;

  [[nodiscard]] float GetHeight() const noexcept override;

  [[nodiscard]] Rectangle GetHitbox() const noexcept override;
};

}
