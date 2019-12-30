#pragma once
#include "tile_map.h"
#include <memory>

namespace albinjohansson::tiled {

class TiledMap;

}

namespace albinjohansson::wanderer {

class TileSet;

class TileMapBuilder final {
 public:
  TileMapBuilder();

  ~TileMapBuilder();

  [[nodiscard]] std::unique_ptr<ITileMap> Create(const std::shared_ptr<TileSet>& tileSet,
                                                 const tiled::TiledMap& tiledMap) const;
};

}
