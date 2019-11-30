#pragma once
#include "image_generator.h"
#include "drawable.h"
#include "tile.h"
#include <vector>
#include <memory>
#include "rectangle.h"
#include "image.h"
#include "render_bounds.h"
#include "tile_map_layer.h"
#include "tile_image_set.h"

namespace albinjohansson::wanderer {

// TODO Tiled map loading
//  - Layers
//  - Animated tiles

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
  std::unique_ptr<TileImageSet> tileImages = nullptr;
  std::vector<TileMapLayer_uptr> layers; // TODO separate different layers such as ground, etc?

  // std::vector<TileMapLayer_uptr> groundLayers;
  // std::vector<TileMapLayer_uptr> objectLayers

  int nRows;
  int nCols;

  [[nodiscard]] RenderBounds CalculateRenderBounds(const Rectangle& bounds) const noexcept;

 public:
  /**
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMap(std::unique_ptr<TileImageSet> tileImages, int nRows, int nCols);

  ~TileMap() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;

  void AddLayer(TileMapLayer_uptr layer);

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

  [[nodiscard]] inline int GetWidth() const noexcept {
    return nCols * static_cast<int>(Tile::SIZE);
  }

  [[nodiscard]] inline int GetHeight() const noexcept {
    return nRows * static_cast<int>(Tile::SIZE);
  }

};

}
