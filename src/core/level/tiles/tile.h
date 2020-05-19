#pragma once
#include <rect.h>
#include <renderer.h>
#include <texture.h>

#include <memory>

#include "game_object.h"
#include "hitbox.h"
#include "render_depth.h"
#include "tile_animation.h"
#include "tile_id.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class Vector2;
class TileSet;
struct Frame;

/**
 * The Tile class represents a type of tile. Note! The Tile class is designed to
 * represent a type of tile, and as such, only one instance is meant to be
 * created for each type. For storage of a tile map, all that is needed is a
 * matrix of tile identifiers.
 *
 * @since 0.1.0
 */
class Tile final {
 private:
  friend class TileBuilder;

  SharedPtr<ctn::Texture> sheet = nullptr;

  TileID id = Tile::EMPTY;
  int depth = RenderDepth::min;

  ctn::IRect source;
  Hitbox hitbox;
  TileAnimation animation;

  bool isBlocked = false;
  bool isAnimated = false;
  bool isObject = false;

  Tile();

  /**
   * Sets the render depth of the tile. An illegal value will be adjusted to the
   * closest legal value.
   *
   * @param depth the render depth value that will be used.
   * @since 0.1.0
   */
  void set_depth(int depth) noexcept;

 public:
  /**
   * The tile ID of all empty tiles.
   *
   * @since 0.1.0
   */
  static constexpr TileID EMPTY = 0;

  ~Tile();

  /**
   * Renders the tile at a specific position.
   *
   * @param pos the position of the rendered tile.
   * @param renderer the renderer that will be used.
   * @param tileSet the associated tile set.
   * @since 0.1.0
   */
  void draw(const Vector2& pos,
            ctn::Renderer& renderer,
            const TileSet& tileSet) const;

  /**
   * Updates the state of the tile.
   *
   * @since 0.1.0
   */
  void tick();

  /**
   * Indicates whether or not the tile is blocked.
   *
   * @return true if the tile is blocked; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_blocked() const noexcept { return isBlocked; }

  /**
   * Indicates whether or not the tile is animated.
   *
   * @return true if the tile is animated; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_animated() const noexcept { return isAnimated; }

  /**
   * Indicates whether or not the tile is an "object".
   *
   * @return true if the tile represents an object; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_object() const noexcept { return isObject; }

  /**
   * Returns the render depth of the tile.
   *
   * @return the render depth of the tile.
   * @since 0.1.0
   */
  [[nodiscard]] int get_depth() const noexcept { return depth; }

  /**
   * Returns the tile ID that will be used for rendering the tile. If the tile
   * isn't animated, the returned will always the same as Tile::GetId().
   *
   * @return the tile ID that will be used for rendering the tile.
   * @since 0.1.0
   */
  [[nodiscard]] TileID get_frame_id() const;

  /**
   * Returns the type ID the tile.
   *
   * @return the type ID the tile.
   * @since 0.1.0
   */
  [[nodiscard]] TileID get_id() const noexcept { return id; }

  /**
   * Returns the source rectangle associated with the tile. The source rectangle
   * represents the area in the tile sheet that holds the texture for the tile.
   *
   * @return the source rectangle associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] const ctn::IRect& get_source() const noexcept { return source; }

  [[nodiscard]] const Hitbox& get_hitbox() const noexcept { return hitbox; }
};

}  // namespace albinjohansson::wanderer
