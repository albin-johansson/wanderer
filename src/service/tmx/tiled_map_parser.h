#pragma once
#include "pugixml.hpp"
#include "tile_map.h"
#include "tile_map_layer.h"
#include "image_generator.h"
#include <string>
#include <memory>

namespace albinjohansson::wanderer {

class TiledMapParser {
 private:
  [[nodiscard]] std::unique_ptr<TileMapLayer> CreateTileMapLayer(const pugi::xml_node& layerNode);

  [[nodiscard]] Image_uptr CreateTileSheet(const pugi::xml_node& sheetNode,
                                           ImageGenerator& imageGenerator,
                                           const std::string& parentPath);

 public:
  TiledMapParser();

  ~TiledMapParser();

  std::unique_ptr<TileMap> LoadMap(ImageGenerator& imageGenerator, const std::string& file);
};

}
