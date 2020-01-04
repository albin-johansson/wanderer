#include "tile_map_builder.h"
#include "tile_map_impl.h"
#include "tiled_map.h"
#include "tiled_object.h"
#include "tile.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

std::unique_ptr<ITileMap> TileMapBuilder::create(const std::shared_ptr<TileSet>& tileSet,
                                                 const tiled::TiledMap& tiledMap) {
  auto map = std::unique_ptr<TileMapImpl>(new TileMapImpl(tileSet));

  map->nRows = tiledMap.GetHeight();
  map->nCols = tiledMap.GetWidth();

  auto& objectGroup = tiledMap.GetTiledObjectGroups().front();
  for (const auto& object : objectGroup->GetObjects()) {
    if (object.HasAttribute("type") &&
        object.GetAttribute("type") == "Spawnpoint" &&
        object.HasProperty("name") &&
        object.GetProperty("name").value == "player") {

      const auto x = tiledMap.ConvertX(std::stof(object.GetAttribute("x")), tileSize);
      const auto y = tiledMap.ConvertY(std::stof(object.GetAttribute("y")), tileSize);
      map->playerSpawnPos.set(x, y);
    }
  }

  // TODO spawn points for entities

  return map;
}

}
