#pragma once
#include <unordered_map>

#include "tile.h"
#include "tile_id.h"

namespace wanderer {

/**
 * The TileSet class represents a set of tiles that are unique.
 *
 * @since 0.1.0
 */
class TileSet final {
 private:
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
   * @since 0.1.0
   */
  void tick(TileID id);

  /**
   * Associates the supplied ID with the supplied tile.
   *
   * @param id the ID that will be associated with the tile.
   * @param tile the tile to associated with the ID.
   * @since 0.1.0
   */
  void insert(TileID id, const Tile& tile);

  /**
   * Returns the tile associated with the supplied tile ID. This method will
   * throw an exception if the ID isn't associated with a tile in this tile set.
   *
   * @param id the ID associated with the desired tile.
   * @return the tile associated with the supplied tile ID.
   * @since 0.1.0
   */
  [[nodiscard]] const Tile& get_tile(TileID id) const;
};

}  // namespace wanderer
