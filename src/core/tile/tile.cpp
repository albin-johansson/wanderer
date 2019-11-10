#include "tile.h"

namespace wanderer::core {

Tile::Tile(int row, int col, int id) : row(row), col(col), id(id) {}

void Tile::Draw(visuals::Renderer& renderer) const noexcept {
  auto x = GetCol() * SIZE;
  auto y = GetRow() * SIZE;

  renderer.SetColor(0x72, 0x9E, 0x74);
  renderer.RenderFillRect(x, y, SIZE, SIZE);
}

}