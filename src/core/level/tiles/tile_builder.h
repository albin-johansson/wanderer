#pragma once
#include "tile.h"
#include "tiled_animation.h"

namespace albinjohansson::tiled {

class TiledTileSet;

}

namespace albinjohansson::wanderer {

class Image;

class TileBuilder {
 private:
  [[nodiscard]] static TileAnimation CreateAnimation(tiled::TiledAnimation animation);

 public:
  TileBuilder();

  ~TileBuilder();

  [[nodiscard]] Tile Create(const std::shared_ptr<Image>& image,
                            const tiled::TiledTileSet& tiledTileSet,
                            TileID id,
                            int index) const;

};

}
