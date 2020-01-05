#include "tile_map_builder.h"
#include "tile_map_impl.h"
#include "tiled_map.h"
#include "tiled_object.h"
#include "tile.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

std::unique_ptr<ITileMap> TileMapBuilder::create(const std::shared_ptr<TileSet>& tileSet,
                                                 const tiled::TiledMap& tiledMap) {
  auto map = std::unique_ptr<TileMapImpl>(new TileMapImpl{tileSet});

  map->nRows = tiledMap.get_height();
  map->nCols = tiledMap.get_width();

  auto& objectGroup = tiledMap.get_tiled_object_groups().front();
  for (const auto& object : objectGroup->get_objects()) {
    if (object.has_attribute("type") &&
        object.get_attribute("type") == "Spawnpoint" &&
        object.has_property("name") &&
        object.get_property("name").value == "player") {

      const auto x = tiledMap.convert_x(std::stof(object.get_attribute("x")), tileSize);
      const auto y = tiledMap.convert_y(std::stof(object.get_attribute("y")), tileSize);
      map->playerSpawnPos.set(x, y);
    }
  }

  // TODO spawn points for entities

  return map;
}

}
