#pragma once
#include "tile_map_layer.h"
#include "tile_id.h"
#include "vector_2.h"
#include "map_position.h"
#include <memory>
#include <vector>
#include <unordered_map>

namespace albinjohansson::wanderer {

class TileSet;
class TileObject;

/**
 * The TileMapLayerImpl class is an implementation of the ITileMapLayer interface.
 *
 * @since 0.1.0
 */
class TileMapLayerImpl final : public ITileMapLayer {
 private:
  const int nRows;
  const int nCols;
  std::shared_ptr<TileSet> tileSet = nullptr;
  std::vector<TileID> tiles;
  std::unordered_map<MapPosition, std::shared_ptr<TileObject>> tileObjects;
  bool isGroundLayer = false;

  /**
   * Initializes all of the tile objects of the layer.
   *
   * @since 0.1.0
   */
  void InitTileObjects();

  /**
   * Converts an index into a position.
   *
   * @param index the index that will be converted.
   * @return a position.
   * @since 0.1.0
   */
  [[nodiscard]] Vector2 CreatePosition(int index) const;

 public:
  /**
   * @param tileSet the associated tile set.
   * @param nRows the number of rows in the layer.
   * @param nCols the number of columns in the layer.
   * @param tiles all of the tiles of the layer.
   * @throws NullPointerException if the supplied tile set is null.
   * @since 0.1.0
   */
  TileMapLayerImpl(const std::shared_ptr<TileSet>& tileSet,
                   int nRows,
                   int nCols,
                   std::vector<TileID>&& tiles);

  ~TileMapLayerImpl() noexcept override;

  void Update(const TileMapBounds& bounds) override;

  void SetGroundLayer(bool isGroundLayer) noexcept override;

  void AddObjects(const TileMapBounds& bounds,
                  std::vector<IGameObject*>& objects) override;

  [[nodiscard]] TileID GetTileId(int row, int col) const override;

  [[nodiscard]] bool IsGroundLayer() const noexcept override;

  [[nodiscard]] int GetIndex(int row, int col) const noexcept override;

};

}
