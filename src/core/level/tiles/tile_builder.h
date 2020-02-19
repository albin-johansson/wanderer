#pragma once
#include <texture.h>
#include <tiled_tile_set.h>

#include "tile.h"
#include "tiled_animation.h"

namespace albinjohansson::wanderer {

class TileBuilder {
 private:
  [[nodiscard]] static TileAnimation create_animation(
      tiled::TiledAnimation animation);

 public:
  TileBuilder() = delete;

  ~TileBuilder() = default;

  [[nodiscard]] static Tile create(
      const std::shared_ptr<centurion::video::Texture>& image,
      const tiled::TiledTileSet& tiledTileSet,
      TileID id,
      int index);
};

}  // namespace albinjohansson::wanderer
