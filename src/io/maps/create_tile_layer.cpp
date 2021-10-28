#include "create_tile_layer.hpp"

#include <vector>  // vector

#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/tile_animation.hpp"
#include "components/tile_layer.hpp"
#include "components/tile_object.hpp"
#include "components/tileset.hpp"
#include "core/game_constants.hpp"
#include "core/utils/centurion_utils.hpp"
#include "hitboxes.hpp"
#include "systems/physics/hitbox_system.hpp"
#include "tactile_io_utils.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto MakeTileMatrix(const int32 nRows, const int32 nCols)
    -> std::vector<std::vector<TileID>>
{
  return {static_cast<usize>(nRows),
          std::vector<TileID>(static_cast<usize>(nCols), glob::empty_tile)};
}

void AddGroundLayer(const Tactile::IO::TileLayer& irTileLayer,
                    comp::Level& level,
                    const int32 layerIndex)
{
  const auto entity = level.registry.create();
  auto& layer = level.registry.emplace<comp::TileLayer>(entity);
  layer.z = layerIndex;

  const auto nRows = Tactile::IO::GetRowCount(irTileLayer);
  const auto nCols = Tactile::IO::GetColumnCount(irTileLayer);
  layer.matrix = MakeTileMatrix(nRows, nCols);

  for (int32 row = 0; row < nRows; ++row) {
    for (int32 col = 0; col < nCols; ++col) {
      layer.matrix[row][col] = TileID(Tactile::IO::GetTile(irTileLayer, row, col));
    }
  }

  level.registry.sort<comp::TileLayer>(
      [](const comp::TileLayer& lhs, const comp::TileLayer& rhs) noexcept {
        return lhs.z < rhs.z;
      });
}

void AddTileObject(comp::Level& level,
                   const TileID id,
                   const float x,
                   const float y,
                   const int32 layerIndex)
{
  auto& registry = level.registry;
  const auto& tileset = registry.get<comp::Tileset>(level.tileset);

  const auto tileEntity = tileset.tiles.at(id);
  const auto& tile = registry.get<comp::Tile>(tileEntity);

  const auto entity = registry.create();
  auto& tileObject = registry.emplace<comp::TileObject>(entity);
  tileObject.tile_entity = tileEntity;

  auto& drawable = registry.emplace<comp::Drawable>(entity);
  drawable.texture = tile.texture;
  drawable.src = tile.src;
  drawable.dst = cen::frect{{x, y}, glob::tile_size<cen::farea>};
  drawable.depth = tile.depth;
  drawable.layer = layerIndex;

  if (const auto* tileHitbox = registry.try_get<comp::Hitbox>(tileEntity)) {
    const auto& hitbox =
        registry.emplace<comp::Hitbox>(entity, sys::WithPosition(*tileHitbox, {x, y}));
    AddHitboxToTree(level.tree, entity, hitbox);
  }

  if (const auto* tileAnimation = registry.try_get<comp::TileAnimation>(tileEntity)) {
    registry.emplace<comp::TileAnimation>(entity, *tileAnimation);
  }
}

void AddTileObjects(const Tactile::IO::Map& irMap,
                    const Tactile::IO::TileLayer& irTileLayer,
                    comp::Level& level,
                    const int32 layerIndex)
{
  const auto fTileWidth = static_cast<float>(Tactile::IO::GetTileWidth(irMap));
  const auto fTileHeight = static_cast<float>(Tactile::IO::GetTileHeight(irMap));

  const auto xRatio = glob::tile_width<float> / fTileWidth;
  const auto yRatio = glob::tile_height<float> / fTileHeight;

  const auto tw = fTileWidth * xRatio;
  const auto th = fTileHeight * yRatio;

  const auto nRows = Tactile::IO::GetRowCount(irTileLayer);
  const auto nCols = Tactile::IO::GetColumnCount(irTileLayer);

  for (int32 row = 0; row < nRows; ++row) {
    for (int32 col = 0; col < nCols; ++col) {
      const auto id = TileID(Tactile::IO::GetTile(irTileLayer, row, col));
      if (!is_empty(id)) {
        const auto x = static_cast<float>(col) * tw;
        const auto y = static_cast<float>(row) * th;
        AddTileObject(level, id, x, y, layerIndex);
      }
    }
  }
}

}  // namespace

void CreateTileLayer(const Tactile::IO::Map& irMap,
                     const Tactile::IO::Layer& irLayer,
                     comp::Level& level,
                     int32 layerIndex)
{
  const auto& irTileLayer = Tactile::IO::GetTileLayer(irLayer);
  if (GetBool(irLayer, "ground")) {
    AddGroundLayer(irTileLayer, level, layerIndex);
  }
  else {
    AddTileObjects(irMap, irTileLayer, level, layerIndex);
  }
}

}  // namespace wanderer