#pragma once
#include <memory>
#include <renderer.h>
#include "wanderer_stdinc.h"
#include "vector_2.h"

namespace albinjohansson::wanderer {

class IWandererCore;
class TileObject;
class ITileMapLayer;
class IEntity;
class IMovableObject;
class Viewport;
class Spawnpoint;

/**
 * The ITileMap interface specifies objects that represent maps that are constructed from tiles.
 *
 * @since 0.1.0
 */
class ITileMap {
 public:
  virtual ~ITileMap() = default;

  /**
   * Updates the state of the tile map.
   *
   * @param core the associated core instance.
   * @param viewport the associated viewport.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void tick(IWandererCore& core, const Viewport& viewport, float delta) = 0;

  /**
   * Renders the tile map.
   *
   * @param renderer the renderer that will be used.
   * @param viewport the viewport that will be used.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  virtual void draw(centurion::Renderer& renderer,
                    const Viewport& viewport,
                    float alpha) noexcept = 0;

  /**
   * Adds a layer to the tile map.
   *
   * @param layer the layer that will be added.
   * @since 0.1.0
   */
  virtual void add_layer(unique<ITileMapLayer>&& layer) = 0;

  /**
   * Sets the player instance used by the map.
   *
   * @param player the player instance that will be added.
   * @since 0.1.0
   */
  virtual void set_player(const shared<IEntity>& player) = 0;

  [[nodiscard]]
  virtual bool is_blocked(const IMovableObject* object, float delta) const = 0;

  /**
   * Returns the number of rows in the tile map.
   *
   * @return the number of rows in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual int get_rows() const noexcept = 0;

  /**
   * Returns the number of columns in the tile map.
   *
   * @return the number of columns in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual int get_cols() const noexcept = 0;

  /**
   * Returns the width of the tile map.
   *
   * @return the width of the tile map.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual int get_width() const noexcept = 0;

  /**
   * Returns the height of the tile map.
   *
   * @return the height of the tile map.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual int get_height() const noexcept = 0;

  /**
   * Returns the spawn position of the player in the map.
   *
   * @return the spawn position of the player in the map.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual Vector2 get_player_spawn_position() const = 0;

};

}
