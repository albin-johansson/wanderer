#include "tile_map_builder.h"
#include <tiled_object.h>
#include "tile_map_impl.h"
#include "tiled_map.h"
#include "tile.h"
#include "game_constants.h"
#include "spawnpoint.h"

namespace albinjohansson::wanderer {

std::unique_ptr<ITileMap> TileMapBuilder::create(const std::shared_ptr<TileSet>& tileSet,
                                                 const tiled::TiledMap& tiledMap) {
  auto map = std::unique_ptr<TileMapImpl>(new TileMapImpl{tileSet});

  map->nRows = tiledMap.get_height();
  map->nCols = tiledMap.get_width();

  auto& objectGroup = tiledMap.get_tiled_object_groups().front(); // FIXME
  for (const auto& object : objectGroup->get_objects()) {

    const auto type_attr = object.attribute("type");
    if (type_attr && type_attr == "Spawnpoint") {
      const auto x_attr = object.attribute("x");
      const auto y_attr = object.attribute("y");
      const auto id_prop = object.property("entity_id");
      if (x_attr && y_attr && id_prop) {
        const auto x = tiledMap.convert_x(std::stof(*x_attr), GameConstants::tile_size);
        const auto y = tiledMap.convert_y(std::stof(*y_attr), GameConstants::tile_size);
        const auto id = std::stoi(*id_prop);

        Spawnpoint spawnpoint{static_cast<EntityID>(id), Vector2{x, y}};
        map->spawnpoints.push_back(spawnpoint);

        if (spawnpoint.get_entity_id() == EntityID::Player) {
          map->playerSpawnPos = spawnpoint.get_position();
        }

      } else {
        SDL_Log("Failed to load spawnpoint!");
      }
    }
  }

  return map;
}

}
