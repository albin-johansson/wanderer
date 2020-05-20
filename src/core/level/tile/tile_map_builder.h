#pragma once
#include <tiled_map.h>

#include <memory>

#include "tile_map.h"

namespace wanderer {

class TileSet;

class TileMapBuilder final {
 public:
  TileMapBuilder() = delete;

  ~TileMapBuilder() = default;

  [[nodiscard]] static UniquePtr<ITileMap> create(
      const SharedPtr<TileSet>& tileSet,
      const tiled::TiledMap& tiledMap);
};

}  // namespace wanderer
