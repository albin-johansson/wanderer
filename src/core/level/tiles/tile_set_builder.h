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
  static tiled::TiledTileSet create_tiled_tile_set(const pugi::xml_node& tileSetNode, TileID firstId);

 public:
  TileSetBuilder() = delete;

  ~TileSetBuilder() = default;

  [[nodiscard]]
  static std::unique_ptr<TileSet> create(const pugi::xml_node& mapRoot,
                                         ImageGenerator& imageGenerator);

};

}
