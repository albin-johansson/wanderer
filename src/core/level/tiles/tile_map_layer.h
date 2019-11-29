#pragma once
#include "renderer.h"
#include "render_bounds.h"
#include "tile_image_set.h"
#include "viewport.h"
#include <vector>
#include <memory>

namespace albinjohansson::wanderer {

class TileMapLayer final {
 private:
  const int nRows;
  const int nCols;
  std::vector<int> tiles;

 public:
  TileMapLayer(int nRows, int nCols, std::vector<int> tiles);

  ~TileMapLayer();

  void Draw(Renderer& renderer,
            RenderBounds bounds,
            const Viewport& viewport,
            const TileImageSet& images) const;

  [[nodiscard]] int GetTileId(int row, int col) const;

  [[nodiscard]] int GetIndex(int row, int col) const noexcept {
    return row * nCols + col;
  }

};

using TileMapLayer_uptr = std::unique_ptr<TileMapLayer>;
using TileMapLayer_sptr = std::shared_ptr<TileMapLayer>;
using TileMapLayer_wptr = std::weak_ptr<TileMapLayer>;

}
