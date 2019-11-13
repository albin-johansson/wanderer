#pragma once
#include "drawable.h"
#include "tile.h"
#include <vector>
#include <memory>
#include "rectangle.h"
#include "image.h"

namespace wanderer::core {

using TileMatrix = std::vector<std::vector<ITile_sptr>>;

/**
 * The TileMap class represents a map of tiles, used to build the game world.
 *
 * @since 0.1.0
 */
class TileMap final : public IDrawable {
 private:
  std::unique_ptr<TileMatrix> tiles = nullptr;
  int nRows;
  int nCols;

  /**
   * Returns a vector that contains all of the tiles inside the specified bounds.
   *
   * @param bounds the rectangle that serves as the bounds to look for tiles in.
   * @return a vector that contains all of the tiles inside the specified bounds.
   * @since 0.1.0
   */
  std::vector<ITile_sptr> GetTiles(const Rectangle& bounds) const;

 public:
  /**
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMap(int nRows, int nCols);

  ~TileMap() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override;

  /**
   * Sets the tile at the specified position.
   *
   * @param row the row index of the position that will be set.
   * @param col the column index of the position that will be set.
   * @param tile a shared pointer to the tile that will be used.
   * @throws std::out_of_range if the specified position is out-of-bounds.
   * @throws NullPointerException if the supplied tile pointer is null.
   * @since 0.1.0
   */
  void SetTile(int row, int col, ITile_sptr tile);

  /**
   * Returns the number of rows in the tile map.
   *
   * @return the number of rows in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetRows() const noexcept { return nRows; }

  /**
   * Returns the number of columns in the tile map.
   *
   * @return the number of columns in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetCols() const noexcept { return nCols; }

};

using TileMap_uptr = std::unique_ptr<TileMap>;
using TileMap_sptr = std::shared_ptr<TileMap>;
using TileMap_wptr = std::weak_ptr<TileMap>;

}
