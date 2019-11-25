#pragma once
#include "renderer.h"
#include "render_bounds.h"
#include <vector>

namespace albinjohansson::wanderer {

class TileMapLayer final {
 private:
  const int nRows;
  const int nCols;
  std::vector<int> tiles;

 public:
  TileMapLayer(int nRows, int nCols, std::vector<int>&& tiles);

  ~TileMapLayer();

  void Draw(Renderer& renderer, RenderBounds bounds) const;

  void SetTile(int row, int col, int id);

  [[nodiscard]] int GetTile(int row, int col) const;

  [[nodiscard]] int GetIndex(int row, int col) const noexcept {
    return row * nCols + col;
  }

};

}
