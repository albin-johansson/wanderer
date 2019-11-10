#pragma once
#include "drawable.h"
#include <memory>

namespace wanderer::core {

// TODO see the solution Notch used for one of his ludum dare games, where only the ID is stored
//  and there are only one actual instance of the Tile class that describes the different types.

class Tile : public IDrawable {
 private:
  int row;
  int col;
  int id;

 public:
  static constexpr int SIZE = 200;

  Tile(int row, int col, int id);

  ~Tile() = default;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override;

  [[nodiscard]] inline int GetRow() const noexcept { return row; }

  [[nodiscard]] inline int GetCol() const noexcept { return col; }

  [[nodiscard]] inline int GetId() const noexcept { return id; }
};

using Tile_uptr = std::unique_ptr<Tile>;
using Tile_sptr = std::shared_ptr<Tile>;
using Tile_wptr = std::weak_ptr<Tile>;

}
