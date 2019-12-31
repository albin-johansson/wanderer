#pragma once
#include "tile_set.h"
#include "tiled_tile_set.h"
#include <pugixml.hpp>
#include <memory>

namespace albinjohansson::wanderer {

class ImageGenerator;

class TileSetBuilder final {
 private:
  [[nodiscard]]
  static tiled::TiledTileSet CreateTiledTileSet(const pugi::xml_node& tileSetNode, TileID firstId);

 public:
  TileSetBuilder() = delete;

  ~TileSetBuilder() = default;

  [[nodiscard]]
  static std::unique_ptr<TileSet> Create(const pugi::xml_node& mapRoot,
                                         ImageGenerator& imageGenerator);

};

}
