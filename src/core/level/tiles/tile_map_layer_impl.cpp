#include "tile_map_layer_impl.h"
#include "tile.h"
#include "objects.h"
#include "tile_render_group.h"
#include "drawable_tile.h"
#include <map>

namespace albinjohansson::wanderer {

TileMapLayerImpl::TileMapLayerImpl(TileSet_sptr tileSet,
                                   int nRows,
                                   int nCols,
                                   std::vector<TileID> tiles)
    : nRows(nRows), nCols(nCols), tiles(std::move(tiles)) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));
}

TileMapLayerImpl::~TileMapLayerImpl() = default;

void TileMapLayerImpl::Update(const TileMapBounds& bounds) {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      TileID id = GetTileId(row, col);
      if (id == 0) {
        continue;
      }
      tileSet->Tick(id);
    }
  }
}

void TileMapLayerImpl::Draw(Renderer& renderer,
                            const TileMapBounds& bounds,
                            const Viewport& viewport) const {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      // FIXME duplicated rendering code from DrawableTile

      TileID id = GetTileId(row, col);
      if (id == Tile::EMPTY) {
        continue;
      }

      const Vector2 pos = {col * Tile::SIZE, row * Tile::SIZE};
      const auto& tile = tileSet->GetTile(id);

      TileID frameId = tile.GetFrameId();

      tile.Draw(pos, renderer, viewport, tileSet->GetSource(frameId));
    }
  }
}

TileID TileMapLayerImpl::GetTileId(int row, int col) const {
  try {
    return tiles.at(GetIndex(row, col));
  } catch (std::exception& e) {
    SDL_Log("Failed to get tile ID of tile at (%i, %i)", row, col);
    throw;
  }
}

void TileMapLayerImpl::SetGroundLayer(bool isGroundLayer) noexcept {
  this->isGroundLayer = isGroundLayer;
}

//std::vector<ISortableDrawable_sptr> TileMapLayerImpl::CreateDrawables() const {
//  std::vector<ISortableDrawable_sptr> drawables;
//  std::map<int, std::vector<std::tuple<int, int, TileID>>> groups;
//
//  auto i = 0;
//  for (const auto& id : tiles) {
//    if (id == Tile::EMPTY) {
//      ++i;
//      continue;
//    }
//
//    const auto& tile = tileSet->GetTile(id);
//
//    if (tile.HasGroup()) {
//      const auto groupId = tile.GetGroup();
//      const auto renderGroup = tile.GetRenderGroup();
//
//      if (groups.count(groupId)) {
//        groups.at(groupId).emplace_back(i, renderGroup, id);
//      } else {
//        std::vector<std::tuple<int, int, TileID>> ids;
//        ids.emplace_back(i, renderGroup, id);
//        groups.emplace(groupId, ids);
//      }
//
//    } else {
//      const auto x = static_cast<float>(i % nCols) * Tile::SIZE;
//      const auto y = (static_cast<float>(i) / static_cast<float>(nCols)) * Tile::SIZE;
//      drawables.push_back(std::make_unique<DrawableTile>(x, y, id, tileSet));
//    }
//
//    ++i;
//  }
//
//  for (const auto& groupPair : groups) {
//    std::vector<std::pair<int, DrawableTile_sptr>> drawableTiles;
//
//    for (const auto& idTuple : groupPair.second) {
//      const auto index = std::get<0>(idTuple);
//      const auto renderGroup = std::get<1>(idTuple);
//      const auto id = std::get<2>(idTuple);
//
//      // FIXME this is wrong???
//      const auto x = static_cast<float>(index % nCols) * Tile::SIZE;
//      const auto y = (static_cast<float>(index) / static_cast<float>(nCols)) * Tile::SIZE;
//
//      drawableTiles.emplace_back(renderGroup, std::make_unique<DrawableTile>(x, y, id, tileSet));
//    }
//
//    std::map<int, std::vector<DrawableTile_sptr>> renderGroups;
//    for (const auto& drawableTilePair : drawableTiles) {
//      const auto rgroupId = drawableTilePair.first;
//
//      if (renderGroups.count(rgroupId)) {
//        renderGroups.at(rgroupId).push_back(drawableTilePair.second);
//      } else {
//        std::vector<DrawableTile_sptr> v;
//        v.push_back(drawableTilePair.second);
//        renderGroups.emplace(rgroupId, v);
//      }
//    }
//
//    for (const auto& group : renderGroups) {
//      const auto& dtiles = group.second;
//
//      const auto x = dtiles.back()->GetX(); // FIXME
//      const auto y = dtiles.back()->GetY();
//
//      drawables.push_back(std::make_shared<TileRenderGroup>(x, y, dtiles));
//    }
//  }
//
//  return drawables;
//}

const std::vector<TileID>& TileMapLayerImpl::GetTiles() const noexcept {
  return tiles;
}

int TileMapLayerImpl::GetIndex(int row, int col) const noexcept {
  return row * nCols + col;
}

bool TileMapLayerImpl::IsGroundLayer() const noexcept {
  return isGroundLayer;
}

}
