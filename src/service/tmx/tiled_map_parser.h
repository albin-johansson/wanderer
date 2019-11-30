#pragma once
#include "pugixml.hpp"
#include "tile_map.h"
#include "tile_map_layer.h"
#include "tile_set.h"
#include "image_generator.h"
#include "image.h"
#include "animation.h"
#include "rectangle.h"
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <map>

namespace albinjohansson::wanderer {

struct TTS { // temp tile set
  Image_sptr img = nullptr;
  int tilecount;
  int size;
  TileID firstgid;
  TileID lastgid;
  std::map<TileID, Animation> animations;
  std::map<TileID, Rectangle> hitboxes;
};

class TiledMapParser {
 private:
  TileMap_uptr map = nullptr;
  const std::string& file;
  ImageGenerator& imageGenerator;

  void LoadMap();

  [[nodiscard]] pugi::xml_document LoadDocument(const std::string& path);

  [[nodiscard]] std::vector<TileMapLayer_uptr> LoadLayers(const pugi::xml_node& mapRootNode);

 public:

  TiledMapParser(ImageGenerator& imageGenerator, const std::string& file);

  ~TiledMapParser();

  [[nodiscard]] TileMap_uptr GetMap() noexcept { return std::move(map); }
};

}
