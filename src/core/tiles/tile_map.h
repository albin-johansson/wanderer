#pragma once
#include "image_generator.h"
#include "drawable.h"
#include "tile.h"
#include <vector>
#include <memory>
#include "rectangle.h"
#include "image.h"
#include "tile_set.h"

namespace wanderer::core {

using TileMatrix = std::vector<std::vector<int>>;

class TileMap;

using TileMap_uptr = std::unique_ptr<TileMap>;
using TileMap_sptr = std::shared_ptr<TileMap>;
using TileMap_wptr = std::weak_ptr<TileMap>;

/**
 * The TileMap class represents a map of tiles, used to build the game world.
 *
 * @since 0.1.0
 */
class TileMap final : public IDrawable {
 private:
  std::unique_ptr<TileMatrix> tiles = nullptr;
  TileSet tileSet;
  int nRows;
  int nCols;

  void CalculateRenderBounds(const Rectangle& bounds,
                             int& minRow,
                             int& maxRow,
                             int& minCol,
                             int& maxCol) const noexcept;

 public:
  /**
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMap(visuals::ImageGenerator_sptr imageGenerator, int nRows, int nCols);

  ~TileMap() override;

  static TileMap_uptr Create(visuals::ImageGenerator_sptr imageGenerator,
                             int nRows,
                             int nCols);

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override;

  /**
   * Sets the tile at the specified position.
   *
   * @param row the row index of the position that will be set.
   * @param col the column index of the position that will be set.
   * @param id the tile ID that will be set..
   * @throws std::out_of_range if the specified position is out-of-bounds.
   * @since 0.1.0
   */
  void SetTile(int row, int col, int id);

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

}
