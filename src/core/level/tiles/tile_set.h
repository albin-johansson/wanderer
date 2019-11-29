#pragma once
#include "tile.h"
#include <vector>
#include <unordered_map>
#include <memory>

namespace albinjohansson::wanderer {

class TileSet final {
 private:
  const int nTiles;
  std::unordered_map<int, Tile> tiles;

 public:
  explicit TileSet(int nTiles);

  ~TileSet();

  void Tick(int index, ILevel& level);

  void Insert(int index, const Tile& tile);

  [[nodiscard]] const Tile& GetTile(int index) { return tiles.at(index); }
};

using TileSet_uptr = std::unique_ptr<TileSet>;
using TileSet_sptr = std::shared_ptr<TileSet>;
using TileSet_wptr = std::weak_ptr<TileSet>;

}
