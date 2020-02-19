#pragma once
#include <tiled_layer.h>

#include <memory>

#include "tile_map_layer.h"
#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class TileSet;
class TileMapLayerImpl;

/**
 * The TileMapLayerBuilder class is responsible for creating instances of the
 * ITileMapLayer interface. This class is a friend of the TileMapLayerImpl
 * class.
 *
 * @since 0.1.0
 * @see ITileMapLayer
 * @see TileMapLayerImpl
 */
class TileMapLayerBuilder final {
 private:
  /**
   * Initializes all of the tile objects of the layer.
   *
   * @param layer the layer that holds the tile objects.
   * @since 0.1.0
   */
  void init_tile_objects(TileMapLayerImpl& layer) const;

  /**
   * Converts an index into a position.
   *
   * @param index the index that will be converted.
   * @param nCols the number of columns in the layer.
   * @return a position.
   * @since 0.1.0
   */
  [[nodiscard]] Vector2 create_position(int index, int nCols) const;

  [[nodiscard]] static std::vector<TileID> create_tile_vector(
      const std::vector<int>& tiles);

 public:
  TileMapLayerBuilder();

  ~TileMapLayerBuilder();

  /**
   * Creates and returns a tile map layer.
   *
   * @param tileSet the associated tile set.
   * @param tiledLayer the tiled layer that will serve as the base for the
   * created tile map layer.
   * @return a unique pointer to a tile map layer.
   * @since 0.1.0
   */
  [[nodiscard]] unique<ITileMapLayer> create(
      const shared<TileSet>& tileSet,
      const tiled::TiledLayer& tiledLayer) const;
};

}  // namespace albinjohansson::wanderer
