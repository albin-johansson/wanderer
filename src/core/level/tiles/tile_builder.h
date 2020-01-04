#pragma once
#include "tile.h"
#include "tiled_animation.h"

namespace centurion {

class Image;

}

namespace albinjohansson::tiled {

class TiledTileSet;

}

namespace albinjohansson::wanderer {

class TileBuilder {
 private:
  [[nodiscard]]
  static TileAnimation CreateAnimation(tiled::TiledAnimation animation);

 public:
  TileBuilder() = delete;

  ~TileBuilder() = default;

  [[nodiscard]] static Tile Create(const std::shared_ptr<centurion::Image>& image,
                                   const tiled::TiledTileSet& tiledTileSet,
                                   TileID id,
                                   int index);

};

}
