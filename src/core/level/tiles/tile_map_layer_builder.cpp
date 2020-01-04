#include "tile_map_layer_builder.h"
#include "tile_map_layer_impl.h"
#include "tile_set.h"
#include "tile_object.h"
#include "tiled_layer.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

TileMapLayerBuilder::TileMapLayerBuilder() = default;

TileMapLayerBuilder::~TileMapLayerBuilder() = default;

void TileMapLayerBuilder::InitTileObjects(TileMapLayerImpl& layer) const {
  int index = 0;

  for (const auto id : layer.tiles) {
    if (id != Tile::EMPTY) {
      const auto& tile = layer.tileSet->GetTile(id);
      if (tile.IsObject()) {
        auto object = std::make_unique<TileObject>(id,
                                                   CreatePosition(index, layer.nCols),
                                                   layer.tileSet);
        object->SetDepth(tile.GetDepth());

        if (tile.IsBlocked()) {
          auto hitbox = tile.GetHitbox();

          hitbox.SetX(object->get_x());
          hitbox.SetY(object->get_y());

          object->SetHitbox(hitbox);
        }

        const auto[row, col] = MathUtils::IndexToMatrixPos(index, layer.nCols);
        const MapPosition mapPos{row, col};

        layer.tileObjects.emplace(mapPos, std::move(object));
      }
    }
    ++index;
  }
}

Vector2 TileMapLayerBuilder::CreatePosition(int index, int nCols) const {
  const auto[row, col] = MathUtils::IndexToMatrixPos(index, nCols);
  return Vector2(col * tileSize, row * tileSize);
}

std::vector<TileID> TileMapLayerBuilder::CreateTileVector(const std::vector<int>& tiles) {
  std::vector<TileID> result;
  result.reserve(tiles.size());
  for (int i : tiles) {
    result.push_back(static_cast<TileID>(i));
  }
  return result;
}

std::unique_ptr<ITileMapLayer> TileMapLayerBuilder::Create(const std::shared_ptr<TileSet>& tileSet,
                                                           const tiled::TiledLayer& tiledLayer) const {
  auto layer = std::unique_ptr<TileMapLayerImpl>(new TileMapLayerImpl(tileSet));

  layer->nRows = tiledLayer.GetRows();
  layer->nCols = tiledLayer.GetCols();
  layer->isGroundLayer = tiledLayer.GetBool("ground");
  layer->tiles = CreateTileVector(tiledLayer.GetTiles());

  layer->tileObjects.reserve(tiledLayer.GetNonEmptyTiles());

  InitTileObjects(*layer);

  return layer;
}

}
