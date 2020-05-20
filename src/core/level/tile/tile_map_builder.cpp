#include "tile_map_builder.h"

#include <tiled_object.h>

#include "game_constants.h"
#include "spawnpoint.h"
#include "tile.h"
#include "tile_map_impl.h"
#include "tiled_map.h"

using namespace centurion;

namespace wanderer {

UniquePtr<ITileMap> TileMapBuilder::create(const SharedPtr<TileSet>& tileSet,
                                           const tiled::TiledMap& tiledMap)
{
  auto map = UniquePtr<TileMapImpl>(new TileMapImpl{tileSet});

  map->m_nRows = tiledMap.get_height();
  map->m_nCols = tiledMap.get_width();

  auto& objectGroup = tiledMap.get_tiled_object_groups().front();  // FIXME
  for (const auto& object : objectGroup->get_objects()) {
    const auto type_attr = object.attribute("type");
    if (type_attr && type_attr == "Spawnpoint") {
      const auto x_attr = object.attribute("x");
      const auto y_attr = object.attribute("y");
      const auto id_prop = object.property("entity_id");
      if (x_attr && y_attr && id_prop) {
        const auto x =
            tiledMap.convert_x(std::stof(*x_attr), GameConstants::tile_size);
        const auto y =
            tiledMap.convert_y(std::stof(*y_attr), GameConstants::tile_size);
        const auto id = std::stoi(*id_prop);

        Spawnpoint spawnpoint{static_cast<EntityID>(id), Vector2{x, y}};
        map->m_spawnpoints.push_back(spawnpoint);

        if (spawnpoint.get_entity_id() == EntityID::Player) {
          map->m_playerSpawnPos = spawnpoint.get_position();
        }

      } else {
        Log::warn("Failed to load spawnpoint!");
      }
    }
  }

  return map;
}

}  // namespace wanderer
