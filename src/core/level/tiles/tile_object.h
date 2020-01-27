#pragma once
#include <memory>
#include "game_object.h"
#include "tile_id.h"
#include "tile.h"
#include "vector_2.h"
#include "hitbox.h"
#include "rectangle.h"
#include "render_depth.h"
#include "hitbox.h"
#include "renderer.h"

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
  int depth = RenderDepth::max;
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

  void tick(IWandererCore& core, float delta) override;

  void draw(const centurion::Renderer& renderer, const Viewport& viewport) const override;

  void SetDepth(int depth) noexcept;

  void SetHitbox(const Hitbox& hitbox) noexcept;

  void add_hitbox(const centurion::FRect& rectangle, const Vector2& offset) override;

  void set_blocked(bool blocked) noexcept override;

  [[nodiscard]]
  float get_x() const noexcept override;

  [[nodiscard]]
  float get_y() const noexcept override;

  [[nodiscard]]
  float get_center_y() const noexcept override;

  [[nodiscard]]
  int get_depth() const noexcept override;

  [[nodiscard]]
  float get_width() const noexcept override;

  [[nodiscard]]
  float get_height() const noexcept override;

  [[nodiscard]]
  const Hitbox& get_hitbox() const noexcept override;

  [[nodiscard]]
  uint64_t get_unique_id() const noexcept override;
};

}
