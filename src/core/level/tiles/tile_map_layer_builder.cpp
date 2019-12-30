#include "tile_map_layer_builder.h"
#include "tile_map_layer_impl.h"
#include "tile_set.h"
#include "tile_object.h"
#include "tiled_layer.h"

namespace albinjohansson::wanderer {

TileMapLayerBuilder::TileMapLayerBuilder() = default;

TileMapLayerBuilder::~TileMapLayerBuilder() = default;

void TileMapLayerBuilder::InitTileObjects(TileMapLayerImpl& layer) const {
  int index = 0;
  for (const auto id : layer.tiles) {
    if (id != Tile::EMPTY) {
      const auto& tile = layer.tileSet->GetTile(id);
      if (tile.IsObject()) {
        auto object = std::make_shared<TileObject>(id,
                                                   CreatePosition(index, layer.nCols),
                                                   layer.tileSet);
        object->SetDepth(tile.GetDepth());

        if (tile.IsBlocked()) {
          Hitbox hitbox = tile.GetHitbox();

          hitbox.SetX(object->GetX());
          hitbox.SetY(object->GetY());

          object->SetHitbox(hitbox);
        }

        const auto matrixPos = MathUtils::IndexToMatrixPos(index, layer.nCols);
        MapPosition mapPos = {matrixPos.first, matrixPos.second};

        layer.tileObjects.emplace(mapPos, object);
      }
    }
    ++index;
  }
}

Vector2 TileMapLayerBuilder::CreatePosition(int index, int nCols) const {
  const auto pos = MathUtils::IndexToMatrixPos(index, nCols);
  return Vector2(pos.second * Tile::SIZE, pos.first * Tile::SIZE);
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

  InitTileObjects(*layer);

  return layer;
}

}
