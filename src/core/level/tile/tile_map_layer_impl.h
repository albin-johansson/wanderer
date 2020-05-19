#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "map_position.h"
#include "tile_id.h"
#include "tile_map_layer.h"
#include "tile_object.h"
#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class TileSet;

/**
 * The TileMapLayerImpl class is an implementation of the ITileMapLayer
 * interface. In order to create instances of this class, see
 * TileMapLayerBuilder.
 *
 * @since 0.1.0
 * @see TileMapLayerBuilder
 */
class TileMapLayerImpl final : public ITileMapLayer {
 private:
  friend class TileMapLayerBuilder;

  SharedPtr<TileSet> tileSet = nullptr;
  std::unordered_map<MapPosition, UniquePtr<TileObject>> tileObjects;
  std::vector<TileID> tiles;
  int nRows = 0;
  int nCols = 0;
  bool isGroundLayer = false;

  explicit TileMapLayerImpl(const SharedPtr<TileSet>& tileSet);

 public:
  ~TileMapLayerImpl() noexcept override;

  void update(const TileMapBounds& bounds) override;

  void add_objects(const TileMapBounds& bounds,
                   std::vector<IGameObject*>& objects) override;

  [[nodiscard]] TileID get_tile_id(int row, int col) const override;

  [[nodiscard]] bool is_ground_layer() const noexcept override;

  [[nodiscard]] int get_index(int row, int col) const noexcept override;

  [[nodiscard]] int get_rows() const noexcept override;

  [[nodiscard]] int get_cols() const noexcept override;
};

}  // namespace albinjohansson::wanderer
