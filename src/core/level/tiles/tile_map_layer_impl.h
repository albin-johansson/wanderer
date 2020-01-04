#pragma once
#include "tile_map_layer.h"
#include "tile_object.h"
#include "tile_id.h"
#include "vector_2.h"
#include "map_position.h"
#include <memory>
#include <vector>
#include <unordered_map>

namespace albinjohansson::wanderer {

class TileSet;

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

  std::shared_ptr<TileSet> tileSet = nullptr;
  std::unordered_map<MapPosition, std::unique_ptr<TileObject>> tileObjects;
  std::vector<TileID> tiles;
  int nRows = 0;
  int nCols = 0;
  bool isGroundLayer = false;

  explicit TileMapLayerImpl(const std::shared_ptr<TileSet>& tileSet);

 public:
  ~TileMapLayerImpl() noexcept override;

  void update(const TileMapBounds& bounds) override;

  void add_objects(const TileMapBounds& bounds, std::vector<IGameObject*>& objects) override;

  [[nodiscard]]
  TileID get_tile_id(int row, int col) const override;

  [[nodiscard]]
  bool is_ground_layer() const noexcept override;

  [[nodiscard]]
  int get_index(int row, int col) const noexcept override;

  [[nodiscard]]
  int get_rows() const noexcept override;

  [[nodiscard]]
  int get_cols() const noexcept override;
};

}
