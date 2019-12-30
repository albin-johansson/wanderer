#include "tiled_map_parser.h"
#include "tile_map_impl.h"
#include "tile_map_layer_impl.h"
#include "tile_set.h"
#include "tile_map_builder.h"
#include "tile_map_layer_builder.h"
#include "tile_set_builder.h"
#include "image_generator.h"
#include "image.h"
#include "tiled_map.h"
#include "pugi_utils.h"

namespace albinjohansson::wanderer {

// TODO entity parsing, item parsing...

TiledMapParser::TiledMapParser() = default;

TiledMapParser::~TiledMapParser() = default;

std::unique_ptr<ITileMap> TiledMapParser::Load(ImageGenerator& imageGenerator,
                                               const std::string& file) const {
  const auto mapDocument = PugiUtils::LoadDocument(file);
  const auto mapNode = mapDocument.child("map");

  tiled::TiledMap tiledMap(mapNode);

  TileSetBuilder tileSetBuilder;
  std::shared_ptr<TileSet> tileSet = tileSetBuilder.Create(mapNode, imageGenerator);

  auto map = TileMapBuilder().Create(tileSet, tiledMap);

  TileMapLayerBuilder layerBuilder;
  for (const auto& tiledLayer : tiledMap.GetLayers()) {
    map->AddLayer(layerBuilder.Create(tileSet, *tiledLayer));
  }

  return map;
}

}