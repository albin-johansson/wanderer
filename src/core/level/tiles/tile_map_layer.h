#pragma once
#include "tile_id.h"
#include "map_position.h"
#include <memory>
#include <vector>

namespace albinjohansson::wanderer {

class TileObject;
class TileMapBounds;
class ISortableDrawable;
class IGameObject;
class Renderer;
class Viewport;

/**
 * The ITileMapLayer interface specifies the layers that make up the tile maps.
 *
 * @since 0.1.0
 */
class ITileMapLayer {
 protected:
  ITileMapLayer() = default;

 public:
  virtual ~ITileMapLayer() = default;

  /**
   * Updates the state of the tiles within the supplied bounds.
   *
   * @param bounds the tile map bounds, in which all tiles will be updated.
   * @since 0.1.0
   */
  virtual void Update(const TileMapBounds& bounds) = 0;

  /**
   * Sets whether or not the layer is a ground layer.
   *
   * @param isGroundLayer true if the layer is a ground layer; false otherwise.
   * @since 0.1.0
   */
  virtual void SetGroundLayer(bool isGroundLayer) noexcept = 0;

  /**
   * Adds all of the game objects in the layer within the supplied bounds to the supplied vector.
   *
   * @param bounds the tile map bounds to look for drawables.
   * @param objects the vector of objects which the objects will be added to.
   * @since 0.1.0
   */
  virtual void AddObjects(const TileMapBounds& bounds,
                          std::vector<IGameObject*>& objects) = 0;

  /**
   * Returns the tile ID of the tile at the specified position.
   *
   * @param row the row index of the desired tile.
   * @param col the column index of the desired tile.
   * @return the tile ID of the tile at the specified position.
   * @since 0.1.0
   */
  [[nodiscard]] virtual TileID GetTileId(int row, int col) const = 0;

  /**
   * Returns the index of the tile at the specified position.
   *
   * @param row the row index.
   * @param col the column index.
   * @return the index of the tile at the specified position.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetIndex(int row, int col) const noexcept = 0;

  /**
   * Indicates whether or not the layer is a ground layer.
   *
   * @return true if the layer is a ground layer; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] virtual bool IsGroundLayer() const noexcept = 0;
};

}
