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

  [[nodiscard]] TileSet_uptr LoadTileSet(const pugi::xml_node& mapRootNode);

  TileAnimation CreateAnimation(tiled::TiledAnimation animation);

  [[nodiscard]] std::vector<TileID> CreateTileVector(const std::vector<int>& tiles) const;

 public:

  TiledMapParser(ImageGenerator& imageGenerator, const std::string& file);

  ~TiledMapParser();

  [[nodiscard]] ITileMap_uptr GetMap() noexcept { return std::move(map); }
};

}
