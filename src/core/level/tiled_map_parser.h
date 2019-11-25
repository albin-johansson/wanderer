#pragma once
#include "pugixml.hpp"
#include "tile_map_layer.h"
#include "image_generator.h"
#include <string>

namespace albinjohansson::wanderer {

class TiledMapParser {
 private:
  [[nodiscard]] TileMapLayer CreateTileMapLayer(const pugi::xml_node& layerNode);

  [[nodiscard]] Image_uptr CreateTileSheet(const pugi::xml_node& sheetNode,
                                           ImageGenerator& imageGenerator,
                                           const std::string& parentPath);

 public:
  TiledMapParser(ImageGenerator& imageGenerator, const std::string& file);

  ~TiledMapParser();
};

}
