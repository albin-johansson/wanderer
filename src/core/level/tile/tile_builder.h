#pragma once
#include <texture.h>
#include <tiled_tile_set.h>

#include "tile.h"
#include "tiled_animation.h"

namespace wanderer {

class TileBuilder {
 public:
  TileBuilder() = delete;

  ~TileBuilder() = default;

  [[nodiscard]] static Tile create(const std::shared_ptr<ctn::Texture>& image,
                                   const tiled::TiledTileSet& tiledTileSet,
                                   TileID id,
                                   int index);

 private:
  [[nodiscard]] static TileAnimation create_animation(
      tiled::TiledAnimation animation);
};

}  // namespace wanderer
