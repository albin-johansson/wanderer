#include "tile_map_layer_builder.h"

#include "game_constants.h"
#include "tile_map_layer_impl.h"
#include "tile_object.h"
#include "tile_set.h"
#include "tiled_layer.h"

namespace albinjohansson::wanderer {

TileMapLayerBuilder::TileMapLayerBuilder() = default;

TileMapLayerBuilder::~TileMapLayerBuilder() = default;

void TileMapLayerBuilder::init_tile_objects(TileMapLayerImpl& layer) const
{
  int index = 0;

  for (const auto id : layer.tiles) {
    if (id != Tile::EMPTY) {
      const auto& tile = layer.tileSet->get_tile(id);
      if (tile.is_object()) {
        auto object = std::make_unique<TileObject>(
            id, create_position(index, layer.nCols), layer.tileSet);
        object->SetDepth(tile.get_depth());

        if (tile.is_blocked()) {
          auto hitbox = tile.get_hitbox();

          hitbox.set_x(object->get_x());
          hitbox.set_y(object->get_y());

          object->SetHitbox(hitbox);
        }

        const auto [row, col] = Math::index_to_matrix_pos(index, layer.nCols);
        const MapPosition mapPos{row, col};

        layer.tileObjects.emplace(mapPos, std::move(object));
      }
    }
    ++index;
  }
}

Vector2 TileMapLayerBuilder::create_position(int index, int nCols) const
{
  const auto [row, col] = Math::index_to_matrix_pos(index, nCols);
  return Vector2{static_cast<float>(col) * GameConstants::tile_size,
                 static_cast<float>(row) * GameConstants::tile_size};
}

std::vector<TileID> TileMapLayerBuilder::create_tile_vector(
    const std::vector<int>& tiles)
{
  std::vector<TileID> result;
  result.reserve(tiles.size());
  for (int i : tiles) {
    result.push_back(static_cast<TileID>(i));
  }
  return result;
}

UniquePtr<ITileMapLayer> TileMapLayerBuilder::create(
    const SharedPtr<TileSet>& tileSet,
    const tiled::TiledLayer& tiledLayer) const
{
  auto layer = UniquePtr<TileMapLayerImpl>(new TileMapLayerImpl(tileSet));

  layer->nRows = tiledLayer.get_rows();
  layer->nCols = tiledLayer.get_cols();
  layer->isGroundLayer = tiledLayer.get_bool("ground");
  layer->tiles = create_tile_vector(tiledLayer.get_tiles());
  layer->tileObjects.reserve(
      static_cast<unsigned>(tiledLayer.get_non_empty_tiles()));

  init_tile_objects(*layer);

  return layer;
}

}  // namespace albinjohansson::wanderer
