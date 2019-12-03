#pragma once
#include "tile_map.h"
#include "image_generator.h"
#include "tile.h"
#include "entity.h"
#include "rectangle.h"
#include "image.h"
#include "tile_map_bounds.h"
#include "tile_set.h"
#include <vector>

namespace albinjohansson::wanderer {

// TODO Tiled map loading
//  - Layers
//  - Animated tiles

/**
 * The TileMapImpl class represents a map of tiles, used to build the game world.
 *
 * @since 0.1.0
 */
class TileMapImpl final : public ITileMap {
 private:
  std::unique_ptr<TileSet> tileSet = nullptr;
  std::vector<ITileMapLayer_uptr> layers; // TODO separate different layers such as ground, etc?

  // std::vector<TileMapLayer_uptr> groundLayers;
  // std::vector<TileMapLayer_uptr> objectLayers

  int nRows;
  int nCols;

  [[nodiscard]] TileMapBounds CalculateMapBounds(const Rectangle& bounds) const noexcept;

 public:
  /**
   * @param tileSet a unique pointer associated to the tile set.
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMapImpl(std::unique_ptr<TileSet> tileSet, int nRows, int nCols);

  ~TileMapImpl() override;

  void Tick(const Viewport& viewport) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;

  void AddLayer(ITileMapLayer_uptr layer) override;

  [[nodiscard]] inline int GetRows() const noexcept override { return nRows; }

  [[nodiscard]] int GetCols() const noexcept override { return nCols; }

  [[nodiscard]] int GetWidth() const noexcept override {
    return nCols * static_cast<int>(Tile::SIZE);
  }

  [[nodiscard]] inline int GetHeight() const noexcept override {
    return nRows * static_cast<int>(Tile::SIZE);
  }

};

}
