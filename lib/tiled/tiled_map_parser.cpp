#include "tiled_map_parser.h"

#include <texture.h>

#include "pugi_utils.h"
#include "tile_map_builder.h"
#include "tile_map_impl.h"
#include "tile_map_layer_builder.h"
#include "tile_map_layer_impl.h"
#include "tile_set.h"
#include "tile_set_builder.h"
#include "tiled_map.h"

using namespace centurion;

namespace wanderer {

// TODO entity parsing, item parsing...

std::unique_ptr<ITileMap> TiledMapParser::load(TextureLoader& textureLoader,
                                               const std::string& file)
{
  const auto mapDocument = PugiUtils::load_document(file);
  const auto mapNode = mapDocument.child("map");

  tiled::TiledMap tiledMap(mapNode);

  std::shared_ptr<TileSet> tileSet =
      TileSetBuilder::create(mapNode, textureLoader);

  auto map = TileMapBuilder::create(tileSet, tiledMap);

  TileMapLayerBuilder layerBuilder;
  for (const auto& tiledLayer : tiledMap.get_layers()) {
    map->add_layer(layerBuilder.create(tileSet, *tiledLayer));
  }

  return map;
}

}  // namespace wanderer