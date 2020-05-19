#pragma once
#include <texture_loader.h>
#include <tiled_tile_set.h>

#include <memory>
#include <pugixml.hpp>

#include "tile_set.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class TileSetBuilder final {
 private:
  [[nodiscard]] static tiled::TiledTileSet create_tiled_tile_set(
      const pugi::xml_node& tileSetNode,
      TileID firstId);

 public:
  TileSetBuilder() = delete;

  ~TileSetBuilder() = default;

  [[nodiscard]] static UniquePtr<TileSet> create(
      const pugi::xml_node& mapRoot,
      ctn::TextureLoader& textureLoader);
};

}  // namespace wanderer
