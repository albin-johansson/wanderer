#pragma once
#include "pugixml.hpp"
#include "tile_map.h"
#include "tile_map_layer.h"
#include "tile_set.h"
#include "image_generator.h"
#include "image.h"
#include "tiled_animation.h"
#include <string>
#include <vector>
#include <map>

namespace albinjohansson::wanderer {

class TiledMapParser final {
 private:
  ITileMap_uptr map = nullptr;
  const std::string& file;
  ImageGenerator& imageGenerator;

  void LoadMap();

  [[nodiscard]] pugi::xml_document LoadDocument(const std::string& path);

  [[nodiscard]] std::vector<ITileMapLayer_uptr> LoadLayers(const pugi::xml_node& mapRootNode);

  [[nodiscard]] TileSet_uptr LoadTileSet(const pugi::xml_node& mapRootNode);

  void LoadTileHitbox(const pugi::xml_node& objectNode,
                      TileProperties& properties,
                      int tileSize);

  TileAnimation CreateAnimation(tiled::TiledAnimation animation);

  Image_sptr LoadSheetImage(const pugi::xml_node& imageNode);

 public:

  TiledMapParser(ImageGenerator& imageGenerator, const std::string& file);

  ~TiledMapParser();

  [[nodiscard]] ITileMap_uptr GetMap() noexcept { return std::move(map); }
};

}
