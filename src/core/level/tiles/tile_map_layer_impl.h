#pragma once
#include "tile_map_layer.h"
#include <vector>

namespace albinjohansson::wanderer {

class TileMapLayerImpl final : public ITileMapLayer {
 private:
  const int nRows;
  const int nCols;
  std::vector<TileID> tiles;

 public:
  TileMapLayerImpl(int nRows, int nCols, std::vector<TileID> tiles);

  ~TileMapLayerImpl() override;

  void Update(const TileMapBounds& bounds, TileSet& tileSet) override;

  void Draw(Renderer& renderer,
            const TileMapBounds& bounds,
            const Viewport& viewport,
            const TileSet& tileSet) const override;

  [[nodiscard]] TileID GetTileId(int row, int col) const override;

  [[nodiscard]] const std::vector<TileID>& GetTiles() const noexcept override {
    return tiles;
  }

  [[nodiscard]] int GetIndex(int row, int col) const noexcept override {
    return row * nCols + col;
  }
};

}
