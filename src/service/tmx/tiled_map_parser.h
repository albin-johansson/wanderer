#pragma once
#include "pugixml.hpp"
#include "tile_map.h"
#include "tile_map_layer.h"
#include "tile_set.h"
#include "image_generator.h"
#include "image.h"
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace albinjohansson::wanderer {

struct TTS { // temp tile set
  Image_sptr img = nullptr;
  int tilecount;
  int size;
  TileID firstgid;
  TileID lastgid;
};

class TiledMapParser {
 private:
  int nTiles = 0;

  [[nodiscard]] pugi::xml_document LoadDocument(const std::string& path);

  [[nodiscard]] std::vector<TTS> CreateTileSetInfo(ImageGenerator& imageGenerator,
                                                   const pugi::xml_node& mapRootNode);

  [[nodiscard]] std::vector<TileMapLayer_uptr> CreateTileMapLayers(
      const pugi::xml_node& mapRootNode);

  void PrepareTileSets(const std::vector<TTS>& tempTileSets,
                       TileSet& tileSet,
                       TileImageSet& imageSet);

 public:
  TiledMapParser();

  ~TiledMapParser();

  std::unique_ptr<TileMap> LoadMap(ImageGenerator& imageGenerator, const std::string& file);
};

}
