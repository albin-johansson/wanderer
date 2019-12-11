#pragma once
#include "game_object.h"
#include "tile_id.h"
#include "render_depth.h"
#include "tile_animation.h"
#include <memory>

namespace albinjohansson::wanderer {

class Image;
class Vector2;
class TileSet;
class Frame;

/**
 * The Tile class represents a type of tile. Note! The Tile class is designed to represent a type
 * of tile, and as such, only one instance is meant to be created for each type. For storage of a
 * tile map, all that is needed is a matrix of tile identifiers.
 *
 * @since 0.1.0
 */
class Tile final {
 private:
  std::shared_ptr<Image> sheet = nullptr;
  Rectangle hitbox; // TODO create Hitbox class which holds multiple rectangles

  TileAnimation animation;

  TileID id = Tile::EMPTY;
  int depth = RenderDepth::MIN;

  bool isBlocked = false;
  bool isAnimated = false;
  bool isObject = false;

 public:
  static constexpr float SIZE = 64;
  static constexpr TileID EMPTY = 0;

  Tile() noexcept;

  ~Tile() noexcept;

  void Draw(const Vector2& pos,
            Renderer& renderer,
            const Viewport& viewport,
            const TileSet& tileSet) const;

  void Tick();

  void SetSheet(std::shared_ptr<Image> sheet);

  void SetBlocked(bool isBlocked) noexcept;

  void SetAnimated(bool isAnimated) noexcept;

  void SetObject(bool isObject) noexcept;

  void SetDepth(int depth) noexcept;

  void SetId(TileID id) noexcept;

  void SetAnimation(const TileAnimation& animation) noexcept;

  void SetHitbox(const Rectangle& hitbox) noexcept;

  /**
   * Indicates whether or not the tile is blocked.
   *
   * @return true if the tile is blocked; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsBlocked() const noexcept;

  [[nodiscard]] bool IsAnimated() const noexcept;

  [[nodiscard]] bool IsObject() const noexcept;

  [[nodiscard]] int GetDepth() const noexcept;

  [[nodiscard]] TileID GetFrameId() const;

  /**
   * Returns the type ID the tile.
   *
   * @return the type ID the tile.
   * @since 0.1.0
   */
  [[nodiscard]] TileID GetId() const noexcept;

  [[nodiscard]] Image& GetImage() const noexcept;

};

}
