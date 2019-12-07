#pragma once
#include "tile_map_layer.h"
#include "tile_set.h"
#include "tile_id.h"
#include "drawable_tile.h"
#include <vector>

namespace albinjohansson::wanderer {

class TileMapLayerImpl final : public ITileMapLayer {
 private:
  const int nRows;
  const int nCols;
  TileSet_sptr tileSet = nullptr;
  std::vector<TileID> tiles;
  bool isGroundLayer = false;

 public:
  TileMapLayerImpl(TileSet_sptr tileSet, int nRows, int nCols, std::vector<TileID> tiles);

  ~TileMapLayerImpl() override;

  void Update(const TileMapBounds& bounds) override;

  void Draw(Renderer& renderer,
            const TileMapBounds& bounds,
            const Viewport& viewport) const override;



  [[nodiscard]] TileID GetTileId(int row, int col) const override;

//  [[nodiscard]] std::vector<DrawableTile_sptr> CreateDrawableTiles() const override;

//  [[nodiscard]] std::vector<ISortableDrawable_sptr> CreateDrawables() const override;

  [[nodiscard]] const std::vector<TileID>& GetTiles() const noexcept override;

  [[nodiscard]] int GetIndex(int row, int col) const noexcept override;

  void SetGroundLayer(bool isGroundLayer) noexcept override;

  [[nodiscard]] bool IsGroundLayer() const noexcept override;
};

}
