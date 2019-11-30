#pragma once
#include "tile.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdint>

namespace albinjohansson::wanderer {

/**
 * The TileSet class represents a set of tiles that are unique.
 *
 * @since 0.1.0
 */
class TileSet final {
 private:
  const int nTiles;
  std::unordered_map<TileID, Tile> tiles;

 public:
  /**
   * @param nTiles the number of tiles in the set.
   * @since 0.1.0
   */
  explicit TileSet(int nTiles);

  ~TileSet();

  /**
   * Updates the state of the tile associated with the supplied ID.
   *
   * @param id the ID associated with the tile that will be updated.
   * @param level the level that the tile is located in.
   * @since 0.1.0
   */
  void Tick(TileID id, ILevel& level);

  /**
   * Associates the supplied ID with the supplied tile.
   *
   * @param id the ID that will be associated with the tile.
   * @param tile the tile to associated with the ID.
   * @since 0.1.0
   */
  void Insert(TileID id, const Tile& tile);

  [[nodiscard]] const Tile& GetTile(TileID id) const { return tiles.at(id); }
};

using TileSet_uptr = std::unique_ptr<TileSet>;
using TileSet_sptr = std::shared_ptr<TileSet>;
using TileSet_wptr = std::weak_ptr<TileSet>;

}
