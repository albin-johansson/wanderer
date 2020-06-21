#pragma once

#include <named_type.hpp>
#include <vector>

#include "wanderer_stdinc.h"

namespace wanderer {

using TileLayerEntity = fluent::
    NamedType<entt::entity, struct TileLayerEntityTag, fluent::Comparable>;

struct TileLayer final {
  using TileMatrix = std::vector<std::vector<TileID>>;

  TileMatrix matrix;
  int nRows;
  int nCols;
};

}  // namespace wanderer
