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
 * The TileMapLayerImpl class is an implementation of the ITileMapLayer interface. In order to
 * create instances of this class, see TileMapLayerBuilder.
 *
 * @since 0.1.0
 * @see TileMapLayerBuilder
 */
class TileMapLayerImpl final : public ITileMapLayer {
 private:
  friend class TileMapLayerBuilder;

  int nRows = 0;
  int nCols = 0;
  std::shared_ptr<TileSet> tileSet = nullptr;
  std::vector<TileID> tiles;
  std::unordered_map<MapPosition, std::shared_ptr<TileObject>> tileObjects;
  bool isGroundLayer = false;

  explicit TileMapLayerImpl(const std::shared_ptr<TileSet>& tileSet);

 public:
  ~TileMapLayerImpl() noexcept override;

  void Update(const TileMapBounds& bounds) override;

  void AddObjects(const TileMapBounds& bounds,
                  std::vector<IGameObject*>& objects) override;

  [[nodiscard]] TileID GetTileId(int row, int col) const override;

  [[nodiscard]] bool IsGroundLayer() const noexcept override;

  [[nodiscard]] int GetIndex(int row, int col) const noexcept override;

  [[nodiscard]] int GetRows() const noexcept override;

  [[nodiscard]] int GetCols() const noexcept override;

};

}
