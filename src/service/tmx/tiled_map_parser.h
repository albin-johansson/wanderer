#pragma once
#include "pugixml.hpp"
#include "tile_map.h"
#include "tile_map_layer.h"
#include "tile_set.h"
#include "image_generator.h"
#include <string>
#include <memory>

namespace albinjohansson::wanderer {

class TiledMapParser {
 private:
  [[nodiscard]] pugi::xml_document LoadDocument(const std::string& path);

 public:
  TiledMapParser();

  ~TiledMapParser();

  std::unique_ptr<TileMap> LoadMap(ImageGenerator& imageGenerator, const std::string& file);
};

}
