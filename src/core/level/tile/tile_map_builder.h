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

  [[nodiscard]] static std::unique_ptr<ITileMap> create(
      const std::shared_ptr<TileSet>& tileSet,
      const tiled::TiledMap& tiledMap);
};

}  // namespace wanderer
