#pragma once
#include "tile.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdint>

namespace albinjohansson::wanderer {

using TileID = uint16_t; // in order to be able to switch easily

class TileSet final {
 private:
  const int nTiles;
  std::unordered_map<TileID, Tile> tiles;

 public:
  explicit TileSet(int nTiles);

  ~TileSet();

  void Tick(TileID index, ILevel& level);

  void Insert(TileID index, const Tile& tile);

  [[nodiscard]] const Tile& GetTile(TileID index) { return tiles.at(index); }
};

using TileSet_uptr = std::unique_ptr<TileSet>;
using TileSet_sptr = std::shared_ptr<TileSet>;
using TileSet_wptr = std::weak_ptr<TileSet>;

}
