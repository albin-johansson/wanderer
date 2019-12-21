#pragma once
#include "game_object.h"
#include "tile_id.h"
#include "tile.h"
#include "vector_2.h"
#include "hitbox.h"
#include "rectangle.h"
#include "render_depth.h"
#include <memory>
#include <hitbox.h>

namespace albinjohansson::wanderer {

class TileSet;

/**
 * The TileObject class represents a tile object, a special kind of tile.
 *
 * @see IGameObject
 * @since 0.1.0
 */
class TileObject final : public IGameObject {
 private:
  std::shared_ptr<TileSet> tileSet = nullptr;
  Vector2 position;
  Hitbox hitbox;
  uint64_t uniqueId = 0;
  int depth = RenderDepth::MAX;
  float centerY = 0;
  const TileID id;

 public:
  /**
   * @param id the tile ID associated with the object.
   * @param position the position of the tile object.
   * @param tileSet the associated tile set.
   * @throws NullPointerException if the supplied tile set is null.
   * @since 0.1.0
   */
  TileObject(TileID id, const Vector2& position, const std::shared_ptr<TileSet>& tileSet);

  ~TileObject() noexcept override;

  void Tick(IWandererCore& core, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void SetDepth(int depth) noexcept;

  void SetHitbox(const Hitbox& hitbox) noexcept;

  void AddHitbox(const Rectangle& rectangle, const Vector2& offset) override;

  void SetBlocked(bool blocked) noexcept override;

  [[nodiscard]] float GetX() const noexcept override;

  [[nodiscard]] float GetY() const noexcept override;

  [[nodiscard]] float GetCenterY() const noexcept override;

  [[nodiscard]] int GetDepth() const noexcept override;

  [[nodiscard]] float GetWidth() const noexcept override;

  [[nodiscard]] float GetHeight() const noexcept override;

  [[nodiscard]] const Hitbox& GetHitbox() const noexcept override;

  [[nodiscard]] uint64_t GetUniqueID() const noexcept override;
};

}
